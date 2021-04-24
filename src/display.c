/*
 * display.c - show configuration
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

#include "display.h"

#include <stdio.h>

#include "common.h"
#include "config.h"
#include "terminal.h"

static char* filter_status(midi_channel ch) {
	return is_channel_active(ch) ? TERM_INVERT TERM_BOLD "ACTIVE" TERM_RESET : TERM_DIM "filtered" TERM_RESET;
}

static char* filter_status_brief(midi_channel ch) {
	return is_channel_active(ch) ? TERM_INVERT TERM_BOLD : TERM_DIM;
}

void print_command(const cmd* command) {
	printf( TERM_INVERT TERM_BOLD " %c " TERM_RESET " - %s\n", command->key, command->description);
}

void print_configuration() {
	for (midi_channel ch = 0; ch < CHANNEL_MAX; ch++) {
		printf("MIDI channel  " TERM_BOLD "%2d" TERM_RESET " is %s\n", ch+1, filter_status(ch));
	}
	printf("MIDI w/o channel is %s\n", filter_status(CHANNEL_MAX));
}

void print_configuration_brief() {
	printf("MIDI channels: ");
	for (midi_channel ch = 0; ch < CHANNEL_MAX; ch++) {
		printf("%s%2d%s  ", filter_status_brief(ch), ch+1, TERM_RESET);
	}
	printf("%sother%s\n", filter_status_brief(CHANNEL_MAX), TERM_RESET);
}

void print_error(const char* message, const char* reason) {
	fprintf(stderr, "%s: %s\n", message, reason);
}

void print_spacer() {
	puts("");
}

void print_status(const char* status) {
	puts(status);
}
