/*
 * getkw -- a simple input parser
 * Copyright (C) 2018 Jonas Juselius and contributors.
 *
 * This file is part of getkw.

 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on the complete list of contributors to the
 * getkw library, see: <http://getkw.readthedocs.io/>
 */

/*
 * \file GetkwError.cpp
 *
 *  \date Jul 2, 2009
 *  \author Jonas Juselius <jonas.juselius@uit.no> \n
 *          CTCC, University of Tromsø
 *
 * \breif
 */

#include "GetkwError.hpp"

bool GetkwError::strict = false;
bool GetkwError::verbose = true;

GetkwError::GetkwError() {}

GetkwError::GetkwError(const string & err) : msg(err) {
  if (verbose or strict) {
    cout << "Error: " << msg << endl;
  }
  if (strict) {
    cout << "Exiting..." << endl;
    exit(1);
  }
}

GetkwError::GetkwError(ostringstream & err) {
  this->msg = err.str();
  if (verbose or strict) {
    cout << "Error: " << msg << endl;
  }
  if (strict) {
    cout << "Exiting..." << endl;
    exit(1);
  }
}
GetkwError::~GetkwError() throw() {
  // TODO Auto-generated destructor stub
}

void GetkwError::trigger(const string & err) {
  msg = err;
  if (verbose or strict) {
    cout << "Error: " << msg << endl;
  }
  if (strict) {
    cout << "Exiting..." << endl;
    exit(1);
  }
  throw *this;
}

void GetkwError::setVerbose(bool flag) { verbose = flag; }

void GetkwError::setStrict(bool flag) { strict = flag; }
