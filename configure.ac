#
# Copyright 2020 Rafael Lorandi <coolparadox@gmail.com>
#
# This file is part of galton-board, a naive game-like simulation of
# a Galton board.
# 
# galton-board is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# galton-board is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with galton-board.  If not, see <http://www.gnu.org/licenses/>
#

AC_PREREQ([2.69])
LT_PREREQ([2.4.2])
AC_INIT([galton-board],[0.0.0],[coolparadox@gmail.com])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_SUBST([PROJECT_BRIEF], ["game-like galton board simulator"])

AM_PROG_AR
AC_PROG_CXX
AC_LANG([C++])

PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0 >= 3.8.0])

AX_CXX_COMPILE_STDCXX_17
AS_VAR_IF([HAVE_CXX17], [1], [], [
    AC_MSG_ERROR([compiler with C++17 support not found])
])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
