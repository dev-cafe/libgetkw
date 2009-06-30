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
	//this->kind=convKind(kind);
}

Keyword::~Keyword() {
}

