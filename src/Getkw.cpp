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

Getkw::Getkw(const string file) {

	if (file.empty() != 0 || file.compare("stdin") == 0 || file.compare("STDIN") == 0) {
		cout << "Reading from stdin " << endl;
		toplevel = readSect(cin);
	} else {
		const char *fname = file.data();
		cout << "Opening file, " << file << endl;
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
	istringstream isi;
	string name;
	string tag;
	string dum1, dum2;
	string set;
	int nsect, nkeys, i;
	bool isSet, hasTag;

	cout << "@ In readSect" << endl;
	readline(fis, isi);
//	cout << "$$" << buf << endl;
	isi >> dum1 >> name >> nsect >> set;
	readline(fis, isi);
//	cout << "$$" << buf << e4ndl;
	isi >> dum1 >> tag >>  dum2 >> nkeys;
	cout <<"!"<< dum1 << tag << dum2 << nkeys <<endl;

	cout << "SECT=" << name << " TAG=" << tag << " NSECT=" << nsect <<
	" NKEYS=" << nkeys << " SET="<< set << endl;
	isSet = convBool(set);
	hasTag = convBool(tag);
	cout << isSet << hasTag << endl;

	Keyword *key;
	Section *sect;
	Section *thissect = new Section(name);
	thissect->setDefined(isSet);
	if (hasTag) {
		readline(fis,isi);
		isi >> tag;
		cout << "tag=" << tag;
		thissect->setTag(tag);
	}

	for (i = 0; i < nkeys; i++) {
		// mem leak
		key = readKey(fis);
		thissect->addKey(key);
		//delete key;
	}
	for (i = 0; i < nsect; i++) {
		// mem leak
		cout << "sectno " << i << endl;
		sect = readSect(fis);
		thissect->addSect(sect);
		//delete sect;
	}

	return thissect;
}

Keyword *Getkw::readKey(istream &fis) {
	istringstream isi;
	string type, name, set;
	int len;

	cout << "@@@ In readKey()\n";
	readline(fis, isi);
	isi >> type >> name >> len >> set;
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
		readline(fis, isi);
		isi >> is;
		key = new Keyval<int> (name, is, setf);
		break;
	case Dbl:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		double ds;
		readline(fis, isi);
		isi >> ds;
		cout << ds << endl;
		key = new Keyval<double> (name, ds, setf);
		break;
	case Bool:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		bool bs;
		readline(fis, isi);
		isi >> ss;
		bs=convBool(ss);
		key = new Keyval<bool> (name, bs, setf);
		cout << *key << endl;
		break;
	case Str:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		getline(fis, ss);
		cout << ss << endl;
		key = new Keyval<string> (name, ss, setf);
		break;
	case IntArray:
		if (len == 0)
			return NULL;
		int ival;
		for (int i = 0; i < len; i++) {
			readline(fis, isi);
			isi >> ival;
			iv.push_back(ival);
		}
		key = new Keyvec<int> (name, iv, setf);
		break;
	case DblArray:
		if (len == 0)
			return NULL;
		double dval;
		for (int i = 0; i < len; i++) {
			readline(fis, isi);
			isi >> dval;
			dv.push_back(dval);
		}
		key = new Keyvec<double> (name, dv, setf);
		break;
	case BoolArray:
		if (len == 0)
			return NULL;
		bool bval;
		for (int i = 0; i < len; i++) {
			readline(fis, isi);
			isi >> ss;
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
			getline(fis, ss);
			sv.push_back(ss);
		}
		key = new Keyvec<string> (name, sv, setf);
		break;
	default:
		cout << "WTF!" <<endl;
		string err = "Unknown keyword type: " + name + " <> " + type;
		throw err;
		break;
	}
	return key;

}

void Getkw::readline(istream &fis, istringstream &isi)
{
	static string buf;
	getline(fis, buf);
	isi.clear();
	isi.str(buf);
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
	static const string STR = "STR";
	static const string DATA = "DATA";
	static const string INT_ARRAY = "INT_ARRAY";
	static const string DBL_ARRAY = "DBL_ARRAY";
	static const string BOOL_ARRAY = "BOOL_ARRAY";
	static const string STR_ARRAY = "STR_ARRAY";
	if (typ.compare(INT) == 0)
		return Int;
	if (typ.compare(DBL) == 0)
		return Dbl;
	if (typ.compare(BOOL) == 0)
		return Bool;
	if (typ.compare(STR) == 0)
		return Str;
	if (typ.compare(DATA) == 0)
		return Data;
	if (typ.compare(INT_ARRAY) == 0)
		return IntArray;
	if (typ.compare(DBL_ARRAY) == 0)
		return DblArray;
	if (typ.compare(BOOL_ARRAY) == 0)
		return BoolArray;
	if (typ.compare(STR_ARRAY) == 0)
		return StrArray;
	return -1;
}

