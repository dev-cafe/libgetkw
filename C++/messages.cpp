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

/*
 * \file messages.cpp
 *
 *  \date Jul 24, 2009
 *  \author Jonas Juselius <jonas.juselius@uit.no> \n
 *          CTCC, University of Tromsø
 *
 * \brief
 */

#include "messages.hpp"

int GetkwMessageStream::msg::DebugLevel = 0;
std::ostream * GetkwMessageStream::msg::out = &std::cout;
