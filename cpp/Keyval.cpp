/** \file Keyval.cpp
 *
 * \date Jun 4, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief Keyword with a value. Very useful.
 */

#include "Keyval.h"

using namespace std;

template<class T>
Keyval<T>::Keyval(const string &name, T &xarg, bool isDefd) :
	Keyword(name, isDefd), arg(xarg) {
	kind = isKind(arg);
}

template<class T>
Keyval<T>::~Keyval() {
}

template<class T>
Keyval<T> *Keyval<T>::clone() {
	return new Keyval<T> (*this);
}

template<class T>
ostream& Keyval<T>::repr(ostream& o) const {
	if (kind == Str) {
		o << "  " + name << " = " << "\"" << arg << "\"";
	} else {
		o << "  " + name << " = " << arg;
	}
	return o;
}

template<class T>
bool Keyval<T>::get(T &t) const {
	t = arg;
	if (isKind(t) != kind) {
		string err = "Keyword kind mismatch: " + getNamedKind(kind);
		throw GetkwError(err);
	}
	return isDefd;
}

template<class T>
void Keyval<T>::set(T &t) {
	arg = t;
	isDefd = true;
	kind = isKind(t);
}

template class Keyval<int> ;
template class Keyval<double> ;
template class Keyval<bool> ;
template class Keyval<string> ;

