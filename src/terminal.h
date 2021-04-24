/*
 * terminal.h - terminal control characters
 *
 * Copyright (C) 2021  Christian Garbs <mitch@cgarbs.de>
 * Licensed under GNU GPL v3 (or later)
 *
 * This file is part of midifilter, a software MIDI filter.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

// for now, this is hardcoded to a standard ANSI/VT100 terminel

#define TERM_RESET "\033[0m"
#define TERM_BOLD "\033[1m"
#define TERM_DIM "\033[2m"
#define TERM_UNDERLINE "\033[4m"
#define TERM_INVERT "\033[7m"

#define TERM_CLEAR_SCREEN "\033[2J"

#endif
