/*
 * config.c - current configuration
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

#include "config.h"

static bool channel_active[] = {
	true,   // channel 1
	false,
	true,
	true,
	true,   // channel 5
	true,
	true,
	true,
	true,
	true,   // channel 10
	true,
	true,
	true,
	true,
	true,   // channel 15
	true,
	true,   // MIDI events without a channel
};

static midi_channel channel_target[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

bool is_channel_active(midi_channel ch) {
	return channel_active[ch];
}

midi_channel get_channel_target(midi_channel ch) {
	return channel_target[ch];
}

void set_channel_target(midi_channel ch, midi_channel target) {
	channel_target[ch] = target;
}

void toggle_channel(midi_channel ch) {
	channel_active[ch] = !channel_active[ch];
}
