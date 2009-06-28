/*
 * \file Envelope.cpp
 *
 *  \date Jun 26, 2009
 *  \author Jonas Juselius <jonas.juselius@uit.no> \n
 *          CTCC, University of Tromsø
 *
 * \breif
 */

#include "Envelope.h"

Envelope::Envelope(const string &name, bool isDefd): isDefd(isDefd) {
	type=Env;
	this->name=string(name);
}

Envelope::~Envelope() {
	// TODO Auto-generated destructor stub
}
