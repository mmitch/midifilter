# Makefile - build script for midifilter
#
# Copyright (C) 2021  Christian Garbs <mitch@cgarbs.de>
# Licensed under GNU GPL v3 (or later)
#
# This file is part of midifilter, a software MIDI filter.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# bash is only needed for autobuild target (read needs -t)
SHELL := bash

pkgconfigs := alsa
warnings   := -Wall -Wextra -Wpedantic -Werror
libs       := -lpthread -lreadline

ifeq ($(shell command -v pkg-config),)
  $(error pkg-config not found)
endif

ifneq ($(shell pkg-config --print-errors --short-errors --exists $(pkgconfigs) || echo failed),)
  $(error missing packages, check installation prerequisites)
endif

CFLAGS  += $(shell pkg-config --cflags $(pkgconfigs)) $(warnings)
LDFLAGS += $(shell pkg-config --libs $(pkgconfigs)) $(libs)

# auto-optimize only when no other optimization level is given
# this enables -O0 to be set for coverage builds
ifeq (,$(findstring -O,$(CFLAGS)))
  CFLAGS  += -O3 -fPIC
  LDFLAGS += -fPIC
endif

srcdir   := ./src
builddir := ./build
bindir   := ./bin

sources  := $(wildcard $(srcdir)/*.c)
objects  := $(addprefix $(builddir)/,$(notdir $(sources:.c=.o)))
depends  := $(objects:.o=.d)
binary   := $(bindir)/midifilter

define gendep =
@echo dep $@
@set -e; rm -f $@; \
$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
sed -e 's,\($*\)\.o[ :]*,\1.o $@ : ,g' -e ':loop;s,/[^/]\+/\.\./,/,g;t loop' < $@.$$$$ > $@; \
rm -f $@.$$$$
endef

define compile =
$(CC) $(CFLAGS) -c -o $@ $<
endef

define link =
$(CC) -o $@ $^ $(LDFLAGS)
endef

all:	$(binary)

autobuild:
	-$(MAKE) all
	inotifywait -m -e modify -e create -e delete -e close_write -e move -r . \
	| grep --line-buffered -E '(Makefile|\.[cdho])$$' \
	| while read -r EVENT; do \
		while read -r -t 0.1 EVENT; do :; done; \
		$(MAKE) all; \
	done

include $(depends)

.PHONY: all clean autobuild

$(binary): $(objects) | $(bindir)
	$(link)

$(bindir) $(builddir):
	mkdir -p $@

$(objects) $(depends): | $(builddir)

clean:
	rm -f  *~
	rm -f  $(srcdir)/*~
	rm -rf $(bindir)
	rm -rf $(builddir)

$(builddir)/%.o: $(srcdir)/%.c $(builddir)/%.d
	$(compile)

$(builddir)/%.d: $(srcdir)/%.c
	$(gendep)

$(objects) $(depends): Makefile
