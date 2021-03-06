/*
 * command.h - command interface
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

#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "common.h"

#include <stdbool.h>

typedef void (*handle_cmd_fn)(midi_channel, int);

typedef struct {
	char key;
	bool channel_argument;
	const char *argument_name;
	handle_cmd_fn handler;
	const char* description;
} cmd;

const cmd* get_command(char key);

#endif
