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

static char* filter_status(midi_channel ch) {
	return is_channel_active(ch) ? "ACTIVE" : "filtered";
}

void print_configuration() {
	for (midi_channel ch = 0; ch < CHANNEL_MAX; ch++) {
		printf("MIDI channel %2d is %s\n", ch+1, filter_status(ch));
	}
	printf("Events without channel are %s\n", filter_status(CHANNEL_MAX));
}
