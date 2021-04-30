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

#include <stdlib.h>

#include <readline/history.h>
#include <readline/readline.h>

#include "command.h"
#include "display.h"
#include "state.h"

#define BUFLEN 32
static char buffer[BUFLEN];

static char* format_char_to_buffer(const char c) {
	if (snprintf(buffer, BUFLEN, "%c", c) >= BUFLEN) {
		buffer[BUFLEN-1] = '\0';
	}
	return buffer;
}

static char* format_int_to_buffer(const int i) {
	if (snprintf(buffer, BUFLEN, "%d", i) >= BUFLEN) {
		buffer[BUFLEN-1] = '\0';
	}
	return buffer;
}

static char* format_string_to_buffer(const char *s) {
	if (snprintf(buffer, BUFLEN, "%s? ", s) >= BUFLEN) {
		buffer[BUFLEN-3] = '?';
		buffer[BUFLEN-2] = ' ';
		buffer[BUFLEN-1] = '\0';
	}
	return buffer;
}

static void process_command(const cmd* command, const char* input) {
	midi_channel channel;
	int arg;

	int items_read = sscanf(input, "%d%d", &channel, &arg);

	if (command->channel_argument && items_read < 1) {
		char *input_channel = readline(format_string_to_buffer("MIDI channel"));
		if (input_channel == NULL) {
			print_error("input could not be parsed", "MIDI channel");
			return;
		}
		items_read = sscanf(input_channel, "%d%d", &channel, &arg);
		free(input_channel);
		if (items_read < 1) {
			print_error("input could not be parsed", "MIDI channel");
			return;
		}
		if (channel < 1 || channel > CHANNEL_MAX) {
			print_error("MIDI channel out of range", format_int_to_buffer(channel));
			return;
		}
		channel--;
	}
	
	if (command->argument_name != NULL && items_read < 2) {
		char *input_argument = readline(format_string_to_buffer(command->argument_name));
		if (input_argument == NULL) {
			print_error("input could not be parsed", command->argument_name);
			return;
		}
		items_read = sscanf(input_argument, "%d", &arg);
		free(input_argument);
		if (items_read < 1) {
			print_error("input could not be parsed", command->argument_name);
			return;
		}
		if (arg < 0 || arg > 127) {
			print_error("argument out of range", format_int_to_buffer(arg));
			return;
		}
	}
	
	command->handler(channel, arg);
}

void run_user_input_loop() {
	const cmd* command;

	do {
		char* input = readline("command? ");
		if (input == NULL) {
			continue;
		}

		if (strlen(input) > 0) {
			add_history(input);
			command = get_command(input[0]);
			if (command != NULL) {
				process_command(command, input+1);
			}
			else {
				print_error("unknown command", format_char_to_buffer(input[0]));
			}
		}

		free(input);
		print_spacer();
	} while (continue_running());
}
