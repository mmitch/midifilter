/*
 * filter.c - filter MIDI events
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

#include "filter.h"

#include "alsa.h"
#include "config.h"
#include "state.h"

// event types: https://www.alsa-project.org/alsa-doc/alsa-lib/group___seq_events.html#gaef39e1f267006faf7abc91c3cb32ea40
// structs: https://www.alsa-project.org/alsa-doc/alsa-lib/seq__event_8h_source.html
typedef enum {
	without_channel,
	note,
	ctrl,
} event_data_type;

static event_data_type get_event_data_type(snd_seq_event_t *midi_event) {
	switch (midi_event->type) {

	case SND_SEQ_EVENT_NOTE:
	case SND_SEQ_EVENT_NOTEON:
	case SND_SEQ_EVENT_NOTEOFF:
	case SND_SEQ_EVENT_KEYPRESS:
		return note;

	case SND_SEQ_EVENT_CONTROLLER:
	case SND_SEQ_EVENT_PGMCHANGE:
	case SND_SEQ_EVENT_CHANPRESS:
	case SND_SEQ_EVENT_PITCHBEND:
	case SND_SEQ_EVENT_CONTROL14:
	case SND_SEQ_EVENT_NONREGPARAM:
	case SND_SEQ_EVENT_REGPARAM:
	case SND_SEQ_EVENT_SONGPOS:
	case SND_SEQ_EVENT_SONGSEL:
	case SND_SEQ_EVENT_QFRAME:
	case SND_SEQ_EVENT_TIMESIGN:
	case SND_SEQ_EVENT_KEYSIGN:
		return ctrl;

	default:
		return without_channel;
	}
}

static midi_channel get_midi_channel(snd_seq_event_t *midi_event) {
	switch(get_event_data_type(midi_event)) {

	case note:
		return midi_event->data.note.channel;

	case ctrl:
		return midi_event->data.control.channel;

	default:
		return CHANNEL_MAX;
	}
}

static snd_seq_event_t* filter_midi_event(snd_seq_event_t *midi_event) {
	// filter by channel
	midi_channel channel = get_midi_channel(midi_event);
	if (is_channel_active(channel)) {
		return midi_event;
	} else {
		return NULL;
	}
}

void* run_midi_filter_loop(void* vargp) {
	UNUSED(vargp);

	int old;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old);

	while(continue_running()) {
		snd_seq_event_t *midi_event = alsa_read();
		if (midi_event == NULL) {
			continue;
		}
		midi_event = filter_midi_event(midi_event);
		if (midi_event == NULL) {
			continue;
		}
		alsa_write(midi_event);
	}

	pthread_exit(0);
}
