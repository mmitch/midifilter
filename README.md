a software MIDI filter
======================

[![Linux Build status](https://github.com/mmitch/midifilter/workflows/Linux%20Build/badge.svg)](https://github.com/mmitch/midifilter/actions?query=workflow%3A%22Linux+Build%22)
[![CodeQL status](https://github.com/mmitch/midifilter/workflows/CodeQL/badge.svg)](https://github.com/mmitch/midifilter/actions?query=workflow%3ACodeQL)

This project provides an ALSA MIDI client that will resend all
received MIDI messages (basically MIDI thru in software), but
additionally allows to filter out MIDI channels and remap Controller
Changes.


project home: https://github.com/mmitch/midifilter


installation
------------

1. Have the ALSA development files installed (eg. `libasound2-dev`).
2. Run `make`.
3. The `midifilter` binary will be placed in the `bin/` directory.


usage
-----

1. Run the `midifilter` binary.
2. Use `aconnect` to connect MIDI input and output.
3. Enter `h` at the prompt to get a list of all available commands.

If you want to edit the default configuration of midifilter, edit
`config.h` and recompile.


copyright
---------

midifilter  -  a software MIDI filter  
Copyright (C) 2021-2025  Christian Garbs <mitch@cgarbs.de>  
Licensed under GNU GPL v3 (or later)  

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
