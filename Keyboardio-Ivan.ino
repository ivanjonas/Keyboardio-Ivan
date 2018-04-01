// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
  * These #include directives pull in the Kaleidoscope firmware core,
  * as well as the Kaleidoscope plugins we use in the Model 01's firmware
  */
#include "Kaleidoscope.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "LED-Off.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-Stalker.h"
#include "Kaleidoscope-DualUse.h"
#include "src/LangPack-German/LangPack-German.h"


/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */
enum { MACRO_VERSION_INFO
//   , MACRO_NAME
     };


/** The Model 01's key layouts are defined as 'keymaps'. By default, there are two
  * keymaps: The standard COLEMAK keymap and the "Function layer" keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  *
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like COLEMAK, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  */
enum { COLEMAK, LAZYNUMBERS, PROGRAMMING, FUNCTION }; // layers

/** This comment temporarily turns off astyle's indent enforcement
  * so we can make the keymaps actually resemble the physical key layout better
  */
// *INDENT-OFF*

/** Convenience definitions.
 */
#define R(n) (Key){.raw = kaleidoscope::language::n}

#define ANGLE_L LSHIFT(Key_Comma)
#define ANGLE_R LSHIFT(Key_Period)
#define BRACKET_L Key_LeftBracket
#define BRACKET_R Key_RightBracket
#define PAREN_L Key_LeftParen
#define PAREN_R Key_RightParen
#define CURLY_L Key_LeftCurlyBracket
#define CURLY_R Key_RightCurlyBracket
#define PIPE LSHIFT(Key_Backslash)
#define UNDERSCORE LSHIFT(Key_Minus)

#define VOLUME_DOWN Consumer_VolumeDecrement
#define VOLUME_UP   Consumer_VolumeIncrement
#define TRACK_PREV  Consumer_ScanPreviousTrack
#define TRACK_NEXT  Consumer_ScanNextTrack
#define PLAY_PAUSE  Consumer_PlaySlashPause


const Key keymaps[][ROWS][COLS] PROGMEM = {

  [COLEMAK] = KEYMAP_STACKED
  (XXX,           Key_1, Key_2,  Key_3, Key_4, Key_5,   Key_LEDEffectNext,
   Key_Backtick,  Key_Q, Key_W,  Key_F, Key_P, Key_G,   Key_Tab,
   Key_PageUp,    Key_A, Key_R,  Key_S, Key_T, Key_D,
   Key_PageDown,  Key_Z, Key_X,  Key_C, Key_V, Key_B,   XXX,
   Key_Backspace, Key_LeftShift, Key_LeftAlt,  Key_LeftGui,
   Key_LeftControl,

   Key_PrintScreen,   Key_6, Key_7, Key_8,     Key_9,      Key_0,         Consumer_Mute,
   Key_Enter,         Key_J, Key_L, Key_U,     Key_Y,      Key_Semicolon, Key_Equals,
                      Key_H, Key_N, Key_E,     Key_I,      Key_O,         Key_Quote,
   Key_PcApplication, Key_K, Key_M, Key_Comma, Key_Period, Key_Slash,     XXX,
   MT(RightAlt, Escape), ShiftToLayer(LAZYNUMBERS), Key_Spacebar, ShiftToLayer(PROGRAMMING),
   ShiftToLayer(FUNCTION)),


  [LAZYNUMBERS] = KEYMAP_STACKED
  (XXX, XXX,           XXX,           XXX,           XXX,           XXX,             XXX,
   XXX, LSHIFT(Key_1), LSHIFT(Key_2), LSHIFT(Key_3), LSHIFT(Key_4), LSHIFT(Key_5),   ___,
   ___, Key_1,         Key_2,         Key_3,         Key_4,         Key_5,
   ___, XXX,           XXX,           XXX,           XXX,           XXX,             XXX,
   ___, ___, ___, ___,
   ___,

   XXX, XXX,           XXX,           XXX,           XXX,                XXX,        XXX,
   ___, LSHIFT(Key_6), LSHIFT(Key_7), LSHIFT(Key_8), LSHIFT(Key_Equals), Key_Equals, XXX,
        Key_6,         Key_7,         Key_8,         Key_9,              Key_0,      XXX,
   XXX, XXX,           XXX,           XXX,           XXX,                XXX,        XXX,
   ___, ___, ___, ___,
   ___),


  [PROGRAMMING] =  KEYMAP_STACKED
  (XXX, Key_F1,  Key_F2,    Key_F3,  Key_F4,  Key_F5,   XXX,
   XXX, XXX,     XXX,       XXX,     XXX,     XXX,      XXX,
   XXX, ANGLE_L, BRACKET_L, CURLY_L, PAREN_L, Key_Slash,
   XXX, XXX,     XXX,       XXX,     XXX,     XXX,      XXX,
   XXX, ___, ___, ___,
   ___,

   XXX,            Key_F6,        Key_F7,  Key_F8,     Key_F9,    Key_F10, Key_F11,
   Key_ScrollLock, XXX,           XXX,     UNDERSCORE, Key_Minus, PIPE,    ___,
                   Key_Backslash, PAREN_R, CURLY_R,    BRACKET_R, ANGLE_R, ___,
   Key_Pause,      XXX,           XXX,     XXX,        XXX,       XXX,     XXX,
   ___, ___, ___, ___,
   ___),


  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,      Key_F2,    Key_F3,      Key_F4,     Key_F5,       Key_Insert,
   Key_Tab,  VOLUME_DOWN, VOLUME_UP, TRACK_PREV,  TRACK_NEXT, PLAY_PAUSE,   ___,
   Key_Home, R(DEU_AU),   R(DEU_OU), R(DEU_SSCH), R(DEU_UU),  XXX,
   Key_End,  XXX,         XXX,       XXX,         XXX,        XXX,          XXX,
   Key_Delete, ___, ___, ___,
   ___,

   LALT(Key_PrintScreen), Key_F6,       Key_F7,        Key_F8,        Key_F9,         Key_F10, Key_F11,
   Key_ScrollLock,        Key_PageUp,   Key_Home,      Key_UpArrow,   Key_End,        XXX,     Key_F12,
                          Key_PageDown, Key_LeftArrow, Key_DownArrow, Key_RightArrow, XXX,     XXX,
   Key_Pause,             XXX,          XXX,           XXX,           XXX,            XXX,     Key_Mute,
   ___, ___, Key_Enter, ___,
   ___)
};

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*


/** versionInfoMacro handles the 'firmware version info' macro
  *  When a key bound to the macro is pressed, this macro
  *  prints out the firmware build information as virtual keystrokes
  */
static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}


/** macroAction dispatches keymap events that are tied to a macro
  * to that macro. It takes two uint8_t parameters.
  *
  * The first is the macro being called (the entry in the 'enum' earlier in this file).
  * The second is the state of the keyswitch. You can use the keyswitch state to figure out
  * if the key has just been toggled on, is currently pressed or if it's just been released.
  *
  * The 'switch' statement should have a 'case' for each entry of the macro enum.
  * Each 'case' statement should call out to a function to handle the macro in question.
  */
const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;
  }
  return MACRO_NONE;
}


/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(
    // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
    &BootGreetingEffect,

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // The stalker effect lights up the keys you've pressed recently
    &StalkerEffect,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    &LEDRainbowEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

    &DualUse,

    &German,

    // The macros plugin adds support for macros
    &Macros
  );

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}


/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */
void loop() {
  Kaleidoscope.loop();
}