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
Keyvec<T>::~Keyvec() {
}

template <class T>
ostream& Keyvec<T>::print(ostream& o) {
	o << this->name << ":" << endl;
	for (unsigned int i = 0; i < arg.size(); i++) {
		o << "  " << arg[i] <<endl;
	}
	return o << " (" << this->isset << ")";
}

template class Keyvec<int> ;
template class Keyvec<double> ;
template class Keyvec<bool> ;
template class Keyvec<string> ;
