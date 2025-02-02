/*
 * alsa.h - ALSA interface
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

#ifndef _ALSA_H_
#define _ALSA_H_

#include <stdbool.h>

#include <alsa/asoundlib.h>

bool alsa_open(void);
snd_seq_event_t* alsa_read(void);
void alsa_write (snd_seq_event_t *midi_event);
bool alsa_close(void);

#endif
