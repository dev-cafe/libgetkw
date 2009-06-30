/** \file Keyword.cpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

#include "Keyword.h"
#include "Keyval.h"
#include "Keyvec.h"

#define TEST_ARRAY if (len > 1) cout << "Warning, invalid length of 1 for " << name << endl

Keyword::Keyword(const string name, bool isDefd) :
	name(name), isDefd(isDefd) {
	//this->kind=convKind(kind);
}

Keyword::~Keyword() {
}

Keyword *Keyword::readKey(ifstream &fis) {
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
		key = new Keyval<int> (name, setf, is);
		break;
	case Dbl:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		double ds;
		fis >> ds;
		key = new Keyval<double> (name, setf, ds);
		break;
	case Bool:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		bool bs;
		fis >> bs;
		key = new Keyval<bool> (name, setf, bs);
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

bool Keyword::convBool(const string val) {
	const string T = "True";

	if (val.compare(T) == 0)
		return true;
	return false;

}

int Keyword::convKind(const string typ) {
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
