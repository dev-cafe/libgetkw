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

Keyword::Keyword(const string name, bool isDefd) :
	name(name), isDefd(isDefd) {
	kind = Undefined;
}

Keyword::~Keyword() {
}

template <class T> void Keyword::throwErrorWrongKind(T &t) {
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

