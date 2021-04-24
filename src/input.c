/*
 * input.c - interactive control thread
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

#include "input.h"

#include <stdio.h>

#include "common.h"
#include "command.h"
#include "display.h"
#include "state.h"

#define BUFLEN 16
static char buffer[BUFLEN];

char* format_in_buffer(char c) {
	if (snprintf(buffer, BUFLEN, "%c", c) >= BUFLEN) {
		buffer[BUFLEN-1] = '\0';
	}
	return buffer;
}

void* handle_user_input(void* vargp) {
	UNUSED(vargp);

	char input;
	const cmd* command;
	do {
		print_prompt("command");
		do {
			scanf("%c", &input);
		} while (input == '\n');

		command = get_command(input);
		if (command != NULL) {
			command->handler(-1, -1);
		}
		else {
			print_error("unknown command", format_in_buffer(input));
		}

		print_spacer();
	} while (continue_running());

	return NULL;
}
