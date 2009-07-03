/** \file Keyvec.cpp
 *
 * \date Jun 4, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

#include "Keyvec.h"

template<class T>
Keyvec<T>::Keyvec(const string &name, vector<T> &xarg, bool isDefd) :
	Keyword(name, isDefd), arg(xarg) {
	kind = isKind(arg);
}

template<class T>
Keyvec<T>::~Keyvec() {
}

template<class T>
ostream& Keyvec<T>::repr(ostream& o) {
	o << "  " << name << " = [ ";
	if (kind == StrArray) {
		o << endl;
		o << "\"" << arg[0] << "\"";
	} else {
		o << arg[0];
	}

	for (unsigned int i = 1; i < arg.size(); i++) {
		if (kind == StrArray) {
			o << ", " << endl << "\"" << arg[0] << "\"";
		} else {
			o << ", " << arg[0];
		}
	}
	return o << " ]";
}

template<class T>
Keyvec<T> *Keyvec<T>::clone() {
	return new Keyvec<T> (*this);
}

template<class T>
bool Keyvec<T>::get(vector<T> &t) {
	t = arg;
	if (isKind(t) != kind) {
		string err = "Keyword kind mismatch: " + getNamedKind(kind);
		throw GetkwError(err);
	}
	return isDefd;
}

template<class T>
void Keyvec<T>::set(vector<T> &t) {
	arg = t;
	isDefd = true;
	kind = isKind(t);
}

template class Keyvec<int> ;
template class Keyvec<double> ;
template class Keyvec<bool> ;
template class Keyvec<string> ;
