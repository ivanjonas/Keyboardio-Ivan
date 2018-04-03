/* -*- mode: c++ -*-
 * Kaleidoscope-LangPack-German -- German language support
 * Based on Kaleidoscope-LangPack-German. All modifications are
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

#include "BetterShift.h"

typedef enum {
  AU,
  OU,
  UU,
  SSCH,
} GermanSymbol;

namespace kaleidoscope {
namespace language {

static void tap_key(uint8_t key_code) {
  Keyboard.press(key_code);
  Keyboard.sendReport();
  Keyboard.release(key_code);
  Keyboard.sendReport();
}

Key
German::eventHandlerHook(Key mapped_key, byte row, byte col, uint8_t key_state) {
  if (mapped_key.raw < GERMAN_FIRST || mapped_key.raw > GERMAN_LAST)
    return mapped_key;

  if (!keyToggledOn(key_state))
    return Key_NoKey;

  bool need_shift =  Keyboard.isModifierActive(Key_LeftShift.keyCode) ||
                    ::OneShot.isModifierActive(Key_LeftShift);
  bool is_alt_held = Keyboard.isModifierActive(Key_RightAlt.keyCode) ||
                    ::OneShot.isModifierActive(Key_RightAlt);

  GermanSymbol symbol = (GermanSymbol)(mapped_key.raw - GERMAN_FIRST);
  Key accent;
  uint8_t kc = 0;

  accent.flags = KEY_FLAGS;
  accent.keyCode = Key_Quote.raw;

  switch (symbol) {
  case AU:
    kc = Key_A.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case OU:
    kc = Key_O.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case UU:
    kc = Key_U.keyCode;
    accent.flags |= SHIFT_HELD;
    break;
  case SSCH:
    kc = Key_S.keyCode;
    accent.keyCode = 0;
    break;
  }

  // 1 - Hold AltGr.
  Keyboard.press(Key_RightAlt.keyCode);

  // 2 - Tap the accent key (with Shift as needed).
  // 2.1 - If there is no accent key, skip this step.
  if (accent.keyCode != 0) {
    if (accent.flags & SHIFT_HELD)
      Keyboard.press(Key_LeftShift.keyCode);
    else
      Keyboard.release(Key_LeftShift.keyCode);
    Keyboard.sendReport();

    tap_key(accent.keyCode);
  }

  // 3 - Tap the base key (with Shift as needed).
  if (need_shift)
    Keyboard.press(Key_LeftShift.keyCode);
  else
    Keyboard.release(Key_LeftShift.keyCode);

  tap_key(kc);

  // 4 - Cleanup. Release AltGr (unless it was being held at the beginning)
  if (!is_alt_held) {
    Keyboard.release(Key_RightAlt.keyCode);
  }

  return Key_NoKey;
}

German::German(void) {
}

void
German::begin(void) {
  Kaleidoscope.useEventHandlerHook(eventHandlerHook);
}

}
}

kaleidoscope::language::German German;
