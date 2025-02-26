/*
 * display.h - display interface
 *
 * Copyright (C) 2021-2025  Christian Garbs <mitch@cgarbs.de>
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

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "command.h"

void clear_screen(void);
void print_command(const cmd* command);
void print_configuration(void);
void print_configuration_brief(void);
void print_error(const char* message, const char* reason);
void print_spacer(void);
void print_status(const char* status);

#endif
