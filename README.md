a software MIDI filter
======================

[![Linux Build status](https://github.com/mmitch/midifilter/workflows/Linux%20Build/badge.svg?branch=master)](https://github.com/mmitch/midifilter/actions?query=workflow%3A%22Linux+Build%22)
[![CodeQL status](https://github.com/mmitch/midifilter/workflows/CodeQL/badge.svg?branch=master)](https://github.com/mmitch/midifilter/actions?query=workflow%3ACodeQL)

This project provides an ALSA MIDI client that will resend all
received MIDI messages (basically MIDI thru in software), but
additionally allows to filter out MIDI channels and remap Controller
Changes.


project home: https://github.com/mmitch/midifilter


configuration
-------------

Until the interactive mode is finished, configuration is done at
compile time in `config.h`.


copyright
---------

midifilter  -  a software MIDI filter  
Copyright (C) 2021  Christian Garbs <mitch@cgarbs.de>  
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
