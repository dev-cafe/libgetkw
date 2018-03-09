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
 * \file GetkwError.hpp
 *
 *  \date Jul 2, 2009
 *  \author Jonas Juselius <jonas.juselius@uit.no> \n
 *          CTCC, University of Tromsø
 *
 * \breif
 */

#ifndef GETKWERROR_H_
#define GETKWERROR_H_

#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

// TODO: define ABORT_EXCEPTION and redefine THROW not to throw, but abort.

#define THROW_GETKW(X)                                                              \
  {                                                                                 \
    std::ostringstream _err;                                                        \
    _err << "Error: " << __func__ << ",  line " << __LINE__ << " in  " << __FILE__  \
         << ": " << X << endl;                                                      \
    throw GetkwError(_err);                                                         \
  }

using namespace std;

class GetkwError : public exception {
public:
  GetkwError();
  GetkwError(const string & err);
  GetkwError(ostringstream & err);
  virtual ~GetkwError() throw();
  void trigger(const string & msg);
  static void setVerbose(bool flag);
  static void setStrict(bool flag);
  friend ostream & operator<<(ostream & o, const GetkwError & e) {
    return o << e.msg;
  }
  //	virtual const char *what() {
  //		return err.c_str();
  //	}
private:
  string msg;
  static bool verbose;
  static bool strict;
};

#endif /* GETKWERROR_H_ */
