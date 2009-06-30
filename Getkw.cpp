/** \file Getkw.cpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

using namespace std;
#include <iostream>
#include <fstream>

#include "Getkw.h"

#define TEST_ARRAY if (len > 1) cout << "Warning, invalid length of 1 for " << name << endl

Getkw::Getkw(string file) {

	if (file.empty() || file.compare("stdin") == 0 || file.compare("STDIN")) {
		toplevel = read_input(cin);
	} else {
		const char *fname = file.data();
		ifstream fis(fname);
		if (fis.bad()) {
			cout << "Open failed: " << file << endl;
			throw 256;
		}
		toplevel = read_input(fis);

		cur = toplevel;
	}
}

Getkw::~Getkw() {
	// TODO Auto-generated destructor stub
}

void Getkw::set_strict(bool flag) {
}

void Getkw::set_verbose(bool flag) {
}

Section *Getkw::read_input(istream &fis) {
	return NULL;
}

Section *Getkw::readSect(istream &fis) {
	string name;
	string tagname;
	string tag;
	string dummy;
	int nsect, nkeys, i;
	string set;

	fis >> dummy >> name >> nsect >> set;
	fis >> dummy >> tag >> nkeys;
	cout << name << tag[0] << nsect << nkeys << set[0];
	if (tag[0] == 'T') {
		fis >> tag;
		tagname=name + "<"+tag+">";
		cout << "TAG: "<< tag << " "<<  tagname;
		Section sect = Section(name, tag);
	} else {
		Section sect = Section(name);
	}

	sect.isDefined(convBool(set));

	for (i = 0; i < nkeys; i++) {
		sect.addKey(readKey(fis));
	}
	for (i = 0; i < nsect; i++) {
		sect.addSect(readSsect(fis));
	}

	return sect;
}

Keyword *Getkw::readKey(ifstream &fis) {
	string type, name, set;
	int len;

	cout << "@@@ In readKey()\n";
	fis >> type >> name >> len >> set;
	cout << type << ":" << name << ":" << len << ":" << set << endl;

	bool setf = convBool(set);
	int kind = convKind(type);
	Keyword *key;

	string ss;
	vector<int> iv;
	vector<double> dv;
	vector<bool> bv;
	vector<string> sv;

	switch (kind) {
	case Int:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		int is;
		fis >> is;
		key = new Keyval<int> (name, is, setf);
		break;
	case Dbl:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		double ds;
		fis >> ds;
		key = new Keyval<double> (name, ds, setf);
		break;
	case Bool:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		bool bs;
		fis >> bs;
		key = new Keyval<bool> (name, bs, setf);
		break;
	case Str:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		getline(fis, ss);
		key = new Keyval<string> (name, ss, setf);
		break;
	case IntArray:
		if (len == 0)
			return NULL;
		int ival;
		for (int i = 0; i < len; i++) {
			fis >> ival;
			iv.push_back(ival);
		}
		key = new Keyvec<int> (name, iv, setf);
		break;
	case DblArray:
		if (len == 0)
			return NULL;
		double dval;
		for (int i = 0; i < len; i++) {
			fis >> dval;
			dv.push_back(dval);
		}
		key = new Keyvec<double> (name, dv, setf);
		break;
	case BoolArray:
		if (len == 0)
			return NULL;
		bool bval;
		for (int i = 0; i < len; i++) {
			fis >> ss;
			bval = convBool(ss);
			bv.push_back(bval);
		}
		key = new Keyvec<bool> (name, bv, setf);
		break;
	case StrArray:
	case Data:
		if (len == 0)
			return NULL;
		for (int i = 0; i < len; i++) {
			fis >> ss;
			sv.push_back(ss);
		}
		key = new Keyvec<string> (name, sv, setf);
		break;
	default:
		cout << "Unknown keyword type: " << type << " (" << kind << ")\n";
		return NULL;
		break;
	}
	return key;

}

bool Getkw::convBool(const string val) {
	const string T = "True";

	if (val.compare(T) == 0)
		return true;
	return false;

}

int Getkw::convKind(const string typ) {
	static const string INT = "INT";
	static const string DBL = "DBL";
	static const string BOOL = "BOOL";
	static const string STRING = "STRING";
	static const string DATA = "DATA";
	static const string INT_ARRAY = "INT_ARRAY";
	static const string DBL_ARRAY = "DBL_ARRAY";
	static const string BOOL_ARRAY = "BOOL_ARRAY";
	static const string STRING_ARRAY = "STRING_ARRAY";
	if (typ.compare(INT) == 0)
		return Int;
	if (typ.compare(DBL) == 0)
		return Dbl;
	if (typ.compare(BOOL) == 0)
		return Bool;
	if (typ.compare(STRING) == 0)
		return Str;
	if (typ.compare(DATA) == 0)
		return Data;
	if (typ.compare(INT_ARRAY) == 0)
		return IntArray;
	if (typ.compare(DBL_ARRAY) == 0)
		return DblArray;
	if (typ.compare(BOOL_ARRAY) == 0)
		return BoolArray;
	if (typ.compare(STRING_ARRAY) == 0)
		return StrArray;
	return -1;
}

