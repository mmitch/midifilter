/*
 * alsa.c - ALSA MIDI connection
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

#include "alsa.h"

#include "common.h"
#include "display.h"

static snd_seq_t *sequencer;
static int port_in;
static int port_out;

bool alsa_open(void)
{
	int err;
	
	if ((err = snd_seq_open(&sequencer, "default", SND_SEQ_OPEN_DUPLEX, 0)) != 0) {
		print_error("alsa: could not open sequencer", snd_strerror(err));
		return false;
	}

	snd_seq_set_client_name(sequencer, PROGRAM_NAME);

	port_in = snd_seq_create_simple_port(sequencer, "Input",
					  SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
					  SND_SEQ_PORT_TYPE_MIDI_GENERIC);
	if (port_in < 0) {
		print_error("alsa: could not open input sequencer port", snd_strerror(port_in));
		return false;
	}

	port_out = snd_seq_create_simple_port(sequencer, "Output",
					  SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ,
					  SND_SEQ_PORT_TYPE_MIDI_GENERIC);
	if (port_out < 0) {
		print_error("alsa: could not open output sequencer port", snd_strerror(port_out));
		return false;
	}

	snd_seq_addr_t destination;
	destination.client = snd_seq_client_id(sequencer);
	destination.port = port_in;

	snd_seq_port_subscribe_t *subscriptions;
	snd_seq_port_subscribe_alloca(&subscriptions);
	snd_seq_port_subscribe_set_dest(subscriptions, &destination);
	snd_seq_subscribe_port(sequencer, subscriptions);

	return true;
}

snd_seq_event_t* alsa_read(void)
{
	int bytes_left;
	snd_seq_event_t *alsa_event;

	bytes_left = snd_seq_event_input(sequencer, &alsa_event);

	if (bytes_left == -EAGAIN) {
		return NULL;
	}

	if (bytes_left == -ENOSPC) {
		print_error("alsa: dropped some MIDI input events", "queue overflow");
		return NULL;
	}

	return alsa_event;
}

void alsa_write (snd_seq_event_t *midi_event) {
	snd_seq_ev_set_source(midi_event, port_out);
	snd_seq_ev_set_subs(midi_event);
	snd_seq_ev_set_direct(midi_event);
	snd_seq_event_output(sequencer, midi_event);
	snd_seq_drain_output(sequencer);
}

bool alsa_close(void)
{
	int err;

	if ((err = snd_seq_delete_simple_port(sequencer, port_in)) != 0) {
		print_error("alsa: could not close input sequencer port", snd_strerror(err));
		return false;
	}

	if ((err = snd_seq_delete_simple_port(sequencer, port_out)) != 0) {
		print_error("alsa: could not close output sequencer port", snd_strerror(err));
		return false;
	}

	if ((err = snd_seq_close(sequencer)) != 0) {
		print_error("alsa: could not close sequencer", snd_strerror(err));
		return false;
	}

	return true;
}
