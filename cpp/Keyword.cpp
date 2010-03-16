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

using namespace std;

Keyword::Keyword(const string name, bool isDefd) :
	name(name), isDefd(isDefd) {
	kind = Undefined;
}

Keyword::~Keyword() {
}

int Keyword::getInt() const {
	int i;
	get(i);
	return i;
}

double Keyword::getDbl() const {
	double d;
	get(d);
	return d;
}

bool Keyword::getBool() const {
	bool b;
	get(b);
	return b;
}

string Keyword::getStr() const {
	string str;
	get(str);
	return str;
}

vector<int> Keyword::getIntVec() const {
	vector<int> v;
	get(v);
	return v;
}

vector<double> Keyword::getDblVec() const {
	vector<double> v;
	get(v);
	return v;
}

vector<bool> Keyword::getBoolVec() const {
	vector<bool> v;
	get(v);
	return v;
}

vector<string> Keyword::getStrVec() const {
	vector<string> v;
	get(v);
	return v;
}

template <class T> void Keyword::throwErrorWrongKind(T &t) const {
	int rkind = isKind(t);
	if (rkind != kind) {
		string err = "Keyword type mismatch: requested '" + getNamedKind(rkind) +
				"', is '" + getNamedKind(kind) + "'";
		throw GetkwError(err);
	}
}

const string &Keyword::getNamedKind(int i) {
	static const string INT = "Int";
	static const string DBL = "Dbl";
	static const string BOOL = "Bool";
	static const string STR = "Str";
	static const string INT_ARRAY = "IntArray";
	static const string DBL_ARRAY = "DblArray";
	static const string BOOL_ARRAY = "BoolArray";
	static const string STR_ARRAY = "StrArray";
	static const string UNDEF = "Undefined";
	static const string UNKN = "Unknown";

	switch (i) {
	case (Int):
		return INT;
	case (Dbl):
		return DBL;
	case (Bool):
		return BOOL;
	case (Str):
		return STR;
	case (IntArray):
		return INT_ARRAY;
	case (DblArray):
		return DBL_ARRAY;
	case (BoolArray):
		return BOOL_ARRAY;
	case (StrArray):
		return STR_ARRAY;
	case (Undefined):
		return UNDEF;
	}
	return UNKN;
}

