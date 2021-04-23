/*
 * main.c - main program that orchestrates all other parts
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

#include <stdio.h>

#include "alsa.h"
#include "common.h"

int main() {
	printf("%s is starting\n", PROGRAM_NAME);

	bool alsa_init = alsa_open();
	if (!alsa_init) {
		goto SHUTDOWN;
	}
	puts("MIDI connections established");

	while(1) {
		snd_seq_event_t *midi_event = alsa_read();
		if (midi_event != NULL) {
			alsa_write(midi_event);
		}
	}

SHUTDOWN:
	if (alsa_init && alsa_close()) {
		puts("MIDI connections closed");
	}

	return 0;
}
