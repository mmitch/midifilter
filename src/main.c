/*
 * main.c - main program that orchestrates all other parts
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

#include <pthread.h>

#include "alsa.h"
#include "display.h"
#include "filter.h"
#include "input.h"
#include "state.h"

int main(void) {
	print_status(PROGRAM_NAME " is starting");

	bool alsa_init = alsa_open();
	if (!alsa_init) {
		goto SHUTDOWN;
	}
	print_status("MIDI connections established");

	print_spacer();
	print_configuration();
	print_spacer();

	pthread_t filter_thread;
	pthread_create(&filter_thread, NULL, run_midi_filter_loop, NULL);

	run_user_input_loop();
	print_status("Input loop stopped");

	pthread_cancel(filter_thread);
	pthread_join(filter_thread, NULL);
	print_status("MIDI filter stopped");

SHUTDOWN:
	if (alsa_init && alsa_close()) {
		print_status("MIDI connections closed");
	}

	print_status(PROGRAM_NAME " exited");
	return 0;
}
