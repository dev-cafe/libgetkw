/** \file Keyval.cpp
 *
 * \date Jun 4, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief Keyword with a value. Very useful.
 */

#include "Keyval.h"

template<class T>
Keyval<T>::~Keyval() {
	// TODO Auto-generated destructor stub
}

template <class T>
ostream& Keyval<T>::print(ostream& o) {
	return o << name << ": " << arg << " (" << isDefd << ")";
}

template class Keyval<int> ;
template class Keyval<double> ;
template class Keyval<bool> ;
template class Keyval<string> ;
//template class Keyval<vector<int> >;
//template class Keyval<vector<double> >;
//template class Keyval<vector<bool> >;
//template class Keyval<vector<string> >;
