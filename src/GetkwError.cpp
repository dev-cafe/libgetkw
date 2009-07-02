/*
 * \file GetkwError.cpp
 *
 *  \date Jul 2, 2009
 *  \author Jonas Juselius <jonas.juselius@uit.no> \n
 *          CTCC, University of Tromsø
 *
 * \breif
 */

#include "GetkwError.h"

GetkwError::GetkwError(const string &err, bool verbose): msg(err), verbose(verbose) {
	if (verbose) {
		cout << "Error! " << msg << endl;
	}
}

GetkwError::~GetkwError() throw() {
	// TODO Auto-generated destructor stub
}
