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

Envelope::Envelope(string name, bool isDefd):
	name(name), isDefd(isDefd) {
	type=Env;
}

Envelope::~Envelope() {
	// TODO Auto-generated destructor stub
}
