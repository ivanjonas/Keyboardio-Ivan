/* -*- mode: c++ -*-
 * Kaleidoscope-LangPack-German -- German language support
 * Based on Kaleidoscope-LangPack-Hungarian. All modifications are
 * trivial, therefore all copyright remains with the original author:
 * Copyright (C) 2016, 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#pragma once

#include <Kaleidoscope.h>
#include <Kaleidoscope-Ranges.h>

namespace kaleidoscope {
namespace language {

enum {
  GERMAN_FIRST = ranges::KALEIDOSCOPE_SAFE_START,
  DEU_AU = GERMAN_FIRST,
  DEU_OU,
  DEU_UU,
  DEU_SSCH,
  GERMAN_LAST = DEU_SSCH,
};

class German : public KaleidoscopePlugin {
 public:
  German(void);

  void begin(void) final;

 private:
  static Key eventHandlerHook(Key mapped_key, byte row, byte col, uint8_t key_state);
};

}
}

extern kaleidoscope::language::German German;
