#
# Copyright 2018 Rafael Lorandi <coolparadox@gmail.com>
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

#SUBDIRS = src @UNIT_TEST_SUBDIR@ @INTEGRATION_TEST_SUBDIR@
#SUBDIRS = src
#dist_doc_DATA = README

ACLOCAL_AMFLAGS = -I m4

#test: check
#	if test -z "@INTEGRATION_TEST_SUBDIR@" ; then echo "error: integration tests are disabled." ; false ; fi
#	cd "@INTEGRATION_TEST_SUBDIR@" && $(MAKE) test
#.SILENT: test
#.PHONY: test

#clean-local:
#	rm -rf doc

totalclean: maintainer-clean
	-rm -f *.in~
	-rm -f aclocal.m4 ar-lib compile config.guess config.h.in config.sub configure depcomp install-sh ltmain.sh missing
	-rm -rf m4/ doc/
	-find . -type f -name Makefile.in -delete
	-find . -type f -name Makefile -delete
	-find . -depth -type d -name .deps -exec rm -rf '{}' ';'
	-find -name '*.gcno' -delete -o -name '*.gcda' -delete

#doc/html/index.html:
#	doxygen

#all-local: $(HTML_DOC)
#AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = galton_board
galton_board_SOURCES = \
	main.cpp
#galton_board_CPPFLAGS = -I@srcdir@/../../src
#galton_board_LDADD = @builddir@/../../src/.libs/libdn_clarith.la -lCppUTest -lCppUTestExt

