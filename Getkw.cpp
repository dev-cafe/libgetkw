/** \file Getkw.cpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

using namespace std;

#include "Getkw.h"

#define TEST_ARRAY if (len > 1) cout << "Warning, invalid length of 1 for " << name << endl

Getkw::Getkw(string file) {

	if (file.empty() || file.compare("stdin") == 0 || file.compare("STDIN")) {
		toplevel = readSect(cin);
	} else {
		const char *fname = file.data();
		ifstream fis(fname);
		if (fis.bad()) {
			cout << "Open failed: " << file << endl;
			throw 256;
		}
		toplevel = readSect(fis);

		cur = toplevel;
	}
}

Getkw::~Getkw() {
	delete toplevel;
}

void Getkw::set_strict(bool flag) {
}

void Getkw::set_verbose(bool flag) {
}

Section *Getkw::readSect(istream &fis) {
	string name;
	string tag;
	string dummy;
	string set;
	int nsect, nkeys, i;
	bool isSet, hasTag;

	fis >> dummy >> name >> nsect >> set;
	fis >> dummy >> tag >> nkeys;
	cout << name << tag << nsect << nkeys << set;
	isSet = convBool(set);
	hasTag = convBool(tag);

	Keyword *key;
	Section *sect;
	Section *thissect = new Section(name);
	sect->setDefined(isSet);
	if (hasTag) {
		fis >> tag;
		sect->setTag(tag);
	}

	for (i = 0; i < nkeys; i++) {
		// mem leak
		key = readKey(fis);
		thissect->addKey(key);
		//delete key;
	}
	for (i = 0; i < nsect; i++) {
		// mem leak
		sect = readSect(fis);
		thissect->addSect(*sect);
		delete sect;
	}

	return sect;
}

Keyword *Getkw::readKey(istream &fis) {
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
		string err = "Unknown keyword type: " + name + " <> " + type;
		throw err;
		break;
	}
	return key;

}

bool Getkw::convBool(const string val) {
	if (val[0] == 'T' or val[0] == 't')
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

