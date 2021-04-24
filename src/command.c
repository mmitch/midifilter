/*
 * command.c - commands executed by user input
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

#include "command.h"

#include <stddef.h>

#include "display.h"
#include "state.h"

#define CMD(K, C, A, D, FN) { .key = (K), .channel_argument = (C), .numeric_argument = (A), .handler = FN, .description = D }

static void quit(midi_channel ch, int arg) {
	UNUSED(ch);
	UNUSED(arg);

	stop_running();
}

static void show_configuration(midi_channel ch, int arg) {
	UNUSED(ch);
	UNUSED(arg);

	clear_screen();
	print_configuration();
}

static void show_help(midi_channel, int);

static const cmd commands[] = {
	CMD('h', false, false, "list available commands", show_help),
	CMD('l', false, false, "list current configuration", show_configuration),
	CMD('q', false, false, "quit midifilter", quit),
	CMD('?', false, false, "list available commands", show_help),
};

static void show_help(midi_channel ch, int arg) {
	UNUSED(ch);
	UNUSED(arg);

	clear_screen();
	for (long unsigned int i=0; i<ARRAY_LENGTH(commands); i++) {
		print_command(&commands[i]);
	}
	print_spacer();
}

const cmd* get_command(char key) {
	for (long unsigned int i=0; i<ARRAY_LENGTH(commands); i++) {
		if (commands[i].key == key) {
			return &commands[i];
		}
	}
	return NULL;
}
