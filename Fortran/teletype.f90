!
! getkw -- a simple input parser
! Copyright (C) 2018 Jonas Juselius and contributors.
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

module teletype_m
  use kinds_m
  implicit none

  integer(I4), parameter :: STDOUT = 6
  integer(I4), parameter :: STDERR = 0
  integer(I4), parameter :: DEVNULL = -1

  character(160) :: str_g
  private ttunit, level, TTBUFSZ
  character(len=3), parameter :: fmt_a = '(a)'
  character(len=5), parameter :: fmt_aa = '(a,a)'
  character(len=7), parameter :: fmt_aaa = '(a,a,a)'
  character(len=6), parameter :: fmt_1xa = '(1x,a)'

  integer(SP), parameter :: TTBUFSZ = 8096
  integer(I4), parameter :: NONSTDOUT = 7
  integer(I4) :: ttunit = 6
  integer(I4) :: level = 0

  public xstr
  interface xstr
    module procedure xstr_isp
    module procedure xstr_rdp
    module procedure xstr_isp_vec
    module procedure xstr_rdp_vec
    module procedure xstr_frm_isp
    module procedure xstr_frm_rdp
  end interface
contains
  subroutine msg_out(str)
    character(*), intent(in) :: str

    if (ttunit == DEVNULL) return

    write (ttunit, fmt_1xa) trim(str)
  end subroutine

  subroutine msg_note(str)
    character(*), intent(in) :: str

    if (ttunit == DEVNULL) return

    write (ttunit, fmt_aa) ' *** ', trim(str)
  end subroutine

  subroutine msg_info(str)
    character(*), intent(in) :: str

    if (ttunit == DEVNULL) return

    write (ttunit, fmt_aa) ' INFO: ', trim(str)
  end subroutine

  subroutine msg_warn(str)
    character(*), intent(in) :: str

    if (ttunit == DEVNULL) return

    write (ttunit, fmt_aa) ' WARNING: ', trim(str)
  end subroutine

  subroutine msg_debug(str, l)
    character(*), intent(in) :: str
    integer(I4) :: l

    if (level == 0) return
    if (l > level) return

    write (STDOUT, fmt_aa) ' DEBUG: ', trim(str)
  end subroutine

  subroutine msg_error(str)
    character(*), intent(in) :: str

    write (STDERR, fmt_aaa) '<<< ERROR: ', trim(str), ' >>>'
  end subroutine

  subroutine msg_critical(str)
    character(*), intent(in) :: str

    write (STDERR, fmt_1xa) repeat('>', 70)
    write (STDERR, fmt_a) ' <'
    write (STDERR, fmt_aa) ' < ', trim(str)
    write (STDERR, fmt_a) ' <'
    write (STDERR, fmt_1xa) repeat('>', 70)
  end subroutine

  subroutine nl
    if (ttunit == DEVNULL) return

    write (ttunit, *)
  end subroutine

  subroutine set_teletype_unit(u)
    integer(I4), intent(in) :: u
    ttunit = u
  end subroutine

  subroutine get_teletype_unit(u)
    integer(I4), intent(out) :: u
    u = ttunit
  end subroutine

  subroutine set_debug_level(l)
    integer(I4), intent(in) :: l
    level = l
  end subroutine

  subroutine get_debug_level(l)
    integer(I4), intent(out) :: l
    l = level
  end subroutine

  subroutine disable_stdout()
    logical :: o_p

    inquire (STDOUT, opened=o_p)
    if (o_p) then
      close (STDOUT)
    end if
    open (STDOUT, file='/dev/null')

    inquire (NONSTDOUT, opened=o_p)
    if (.not. o_p) then
      open (NONSTDOUT, file='/dev/stdout')
    end if

    if (ttunit == STDOUT) then
      ttunit = NONSTDOUT
    end if
  end subroutine

  subroutine enable_stdout()
    logical :: o_p

    inquire (NONSTDOUT, opened=o_p)
    if (o_p) then
      close (NONSTDOUT)
    end if

    inquire (STDOUT, opened=o_p)
    if (.not. o_p) then
      open (STDOUT, file='/dev/stdout')
    end if

    if (ttunit == NONSTDOUT) then
      ttunit = STDOUT
    end if
  end subroutine

  function xstr_isp(arg) result(s)
    integer(SP), intent(in) :: arg
    character(TTBUFSZ) :: s

    write (s, *) arg
  end function

  function xstr_rdp(arg) result(s)
    real(DP), intent(in) :: arg
    character(TTBUFSZ) :: s

    write (s, *) arg
  end function

  function xstr_isp_vec(arg) result(s)
    integer(SP), dimension(:), intent(in) :: arg
    character(TTBUFSZ) :: s

    write (s, *) arg
  end function

  function xstr_rdp_vec(arg) result(s)
    real(DP), dimension(:), intent(in) :: arg
    character(TTBUFSZ) :: s

    write (s, *) arg
  end function

  function xstr_frm_isp(frm, arg) result(s)
    character(*) :: frm
    integer(SP), intent(in) :: arg
    character(TTBUFSZ) :: s

    write (s, frm) arg
  end function

  function xstr_frm_rdp(frm, arg) result(s)
    character(*) :: frm
    real(DP), intent(in) :: arg
    character(TTBUFSZ) ::  s

    write (s, frm) arg
  end function
end module
