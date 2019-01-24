!
! getkw -- a simple input parser
! Copyright (C) 2019 Jonas Juselius and contributors.
!
! This file is part of getkw.
!
! This Source Code Form is subject to the terms of the Mozilla Public
! License, v. 2.0. If a copy of the MPL was not distributed with this
! file, You can obtain one at http://mozilla.org/MPL/2.0/.
!
! For information on the complete list of contributors to the
! getkw library, see: <http://getkw.readthedocs.io/>
!

module kinds_m
  implicit none
  integer, parameter :: MP = kind(0)
  integer, parameter :: SP = kind(0.0e0)
  integer, parameter :: DP = kind(0.0d0)

  integer, parameter :: I2 = 2
  integer, parameter :: I4 = 4
  integer, parameter :: I8 = 8
end module
