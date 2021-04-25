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

#include "config.h"
#include "display.h"
#include "alsa.h"
#include "state.h"

#define CMD(K, C, A, D, FN) { .key = (K), .channel_argument = (C), .argument_name = (A), .handler = FN, .description = D }

static void bank_select(midi_channel ch, int arg) {
	snd_seq_event_t bank_select;

	snd_seq_ev_clear(&bank_select);
	bank_select.type = SND_SEQ_EVENT_CONTROLLER;
	bank_select.data.control.channel = ch;
	bank_select.data.control.param = 0;
	bank_select.data.control.value = arg;

	alsa_write(&bank_select);
}

static void program_change(midi_channel ch, int arg) {
	snd_seq_event_t program_change;

	snd_seq_ev_clear(&program_change);
	program_change.type = SND_SEQ_EVENT_PGMCHANGE;
	program_change.data.control.channel = ch;
	program_change.data.control.value = arg;

	alsa_write(&program_change);
}

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

static void toggle_midi_channel(midi_channel ch, int arg) {
	UNUSED(arg);

	toggle_channel(ch);
}

static void toggle_midi_no_channel(midi_channel ch, int arg) {
	UNUSED(ch);
	UNUSED(arg);

	toggle_channel(CHANNEL_MAX);
}

static void show_help(midi_channel, int);

static const cmd commands[] = {
	CMD('b', true, "bank",     "bank select: send a coarse Bank Select control event (CC#0)", bank_select),
	CMD('h', false, NULL,      "help: list available commands", show_help),
	CMD('l', false, NULL,      "list current configuration", show_configuration),
	CMD('o', true,  NULL,      "on/off: toggle midi channel", toggle_midi_channel),
	CMD('O', false, NULL,      "on/off: toggle midi events w/o channel", toggle_midi_no_channel),
	CMD('p', true,  "program", "program change: send a Program Change control event", program_change),
	CMD('q', false, NULL,      "quit midifilter", quit),
	CMD('?', false, NULL,      "help: list available commands", show_help),
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
