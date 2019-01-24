/*
 * getkw -- a simple input parser
 * Copyright (C) 2019 Jonas Juselius and contributors.
 *
 * This file is part of getkw.

 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on the complete list of contributors to the
 * getkw library, see: <http://getkw.readthedocs.io/>
 */

/*!
 * \file GetkwError.hpp
 * \date 2009, 2018
 * \author Jonas Juselius, Roberto Di Remigio
 * \brief Provide macros for error handling
 *
 *  Exceptions:
 *
 *  \verbatim
 *  GETKW_ERROR(<Error Message>)
 *  \endverbatim
 *
 *  Use this to catch errors that might occur because of faulty
 *  data, i.e. other people's errors. Mainly in the API to the
 *  external world.
 *
 *  Assertions:
 *
 *  \verbatim
 *  GETKW_ASSERT(<Condition>)
 *  \endverbatim
 *
 *  This is just a wrapper around the standard assert macro.
 *  Use this to catch your own errors, i.e. broken preconditions
 *  to the internal functions/classes. In release mode assertions
 *  are not checked!
 *
 *  Static assertions:
 *
 *  \verbatim
 *  GETKW_STATIC_ASSERT(<Condition>, <Error Message>)
 *  \endverbatim
 *
 *  Uses static_assert. Same usage pattern as for normal assertions. Static
 * assertions are checked at compile-time.
 */

#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

/// Macro to be used to signal error conditions
#define GETKW_ERROR(message)                                                        \
  {                                                                                 \
    std::ostringstream _err;                                                        \
    _err << "Getkw fatal error.\n"                                                  \
         << " In function " << __func__ << " at line " << __LINE__ << " of file "   \
         << __FILE__ << "\n"                                                        \
         << message << std::endl;                                                   \
    std::fprintf(stderr, "%s\n", _err.str().c_str());                               \
    std::exit(EXIT_FAILURE);                                                        \
  }

/// Macro to be used for assertions
#define GETKW_ASSERT(arg) assert(arg)

/// Macro to be used for static assertions
#define GETKW_STATIC_ASSERT(arg, msg) static_assert(arg, msg)
