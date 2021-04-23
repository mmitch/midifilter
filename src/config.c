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

static const bool channel_active[] = {
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


bool is_channel_active(midi_channel ch) {
	return channel_active[ch];
}
