#
# getkw -- a simple input parser
# Copyright (C) 2019 Jonas Juselius and contributors.
#
# This file is part of getkw.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# For information on the complete list of contributors to the
# getkw library, see: <http://getkw.readthedocs.io/>
#

# -*- coding: utf-8 -*-
"""Top-level package for getkw."""

__author__ = "Jonas Juselius, Roberto Di Remigio, Radovan Bast, Luca Frediani, Stig Rune Jensen, Ville Weijo"
__copyright__ = "Copyright 2018, dev-cafe"
__credits__ = [
    "Jonas Juselius", "Roberto Di Remigio", "Radovan Bast", "Luca Frediani",
    "Stig Rune Jensen", "Ville Weijo"
]
__license__ = "MPLv2"
__version__ = "1.5.0"
__maintainer__ = "Roberto Di Remigio, Radovan Bast, Stig Rune Jensen"
__status__ = "Production"

from .getkw import (Getkw, GetkwParser, Keyword, Section, check_ignored,
                    check_opt, check_required, parse_error)

__all__ = [
    'Section', 'Keyword', 'Getkw', 'GetkwParser', 'parse_error', 'check_opt',
    'check_required', 'check_ignored'
]
