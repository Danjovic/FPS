////////////////////////////////////////////////////////////////////////////////
//      __________  _____
//     / ____/ __ \/ ___/
//    / /_  / /_/ /\__ \ 
//   / __/ / ____/___/ /
//  /_/ (_)_/  (_)____(_)  Foot Presto Switch
//
// Pedal Switch for playing FPS games
//
// Author: Daniel Jose Viana, danjovic@hotmail.com
//
// Version 0.6 - March, 2016 - Basic Release



////////////////////////////////////////////////////////////////////////////////
//    ___       __ _      _ _   _
//   |   \ ___ / _(_)_ _ (_) |_(_)___ _ _  ___
//   | |) / -_)  _| | ' \| |  _| / _ \ ' \(_-<
//   |___/\___|_| |_|_||_|_|\__|_\___/_||_/__/
//
#define _Pin_Left_footswitch    5
#define _Pin_Middle_footswitch  2
#define _Pin_Right_footswitch   0

#define _Key_Left_footswitch KEY_C   // Crouch
#define _Key_Middle_footswitch KEY_R // Reload
#define _Key_Right_footswitch KEY_V  // Melee


////////////////////////////////////////////////////////////////////////////////
//    _    _ _                 _
//   | |  (_) |__ _ _ __ _ _ _(_)___ ___
//   | |__| | '_ \ '_/ _` | '_| / -_|_-<
//   |____|_|_.__/_| \__,_|_| |_\___/__/
//
#include "DigiKeyboard.h"


////////////////////////////////////////////////////////////////////////////////
//   __   __        _      _    _
//   \ \ / /_ _ _ _(_)__ _| |__| |___ ___
//    \ V / _` | '_| / _` | '_ \ / -_|_-<
//     \_/\__,_|_| |_\__,_|_.__/_\___/__/
//

uint8_t lastkeys = 0;
uint8_t footkeys;

////////////////////////////////////////////////////////////////////////////////
//    ___             _   _
//   | __|  _ _ _  __| |_(_)___ _ _  ___
//   | _| || | ' \/ _|  _| / _ \ ' \(_-<
//   |_| \_,_|_||_\__|\__|_\___/_||_/__/
//




////////////////////////////////////////////////////////////////////////////////
//    ___ ___ _____ _   _ ___
//   / __| __|_   _| | | | _ \
//   \__ \ _|  | | | |_| |  _/
//   |___/___| |_|  \___/|_|
//
void setup() {

  // Set pullups for pedal switches and define them as inputs
  digitalWrite(_Pin_Left_footswitch, HIGH);
  pinMode(_Pin_Left_footswitch, INPUT);

  digitalWrite(_Pin_Middle_footswitch, HIGH);
  pinMode(_Pin_Middle_footswitch, INPUT);

  digitalWrite(_Pin_Right_footswitch, HIGH);
  pinMode(_Pin_Right_footswitch, INPUT);

  // This is needed before start sending keys
  DigiKeyboard.sendKeyStroke(0);

}



////////////////////////////////////////////////////////////////////////////////
//    __  __      _        _
//   |  \/  |__ _(_)_ _   | |   ___  ___ _ __
//   | |\/| / _` | | ' \  | |__/ _ \/ _ \ '_ \
//   |_|  |_\__,_|_|_||_| |____\___/\___/ .__/
//                                      |_|
void loop() {

  uint8_t i; // index for keystrokes

  // Sample footkeys. We have 3 keys
  footkeys = 0;

  if ((digitalRead(_Pin_Left_footswitch) == 0))   footkeys |= (1 << _Pin_Left_footswitch);
  if ((digitalRead(_Pin_Middle_footswitch) == 0)) footkeys |= (1 << _Pin_Middle_footswitch);
  if ((digitalRead(_Pin_Right_footswitch) == 0))  footkeys |= (1 << _Pin_Right_footswitch);

  // if switches changed state send new report to host
  if (footkeys != lastkeys) {                // on change
    lastkeys = footkeys;                     // update key state

    // Sync with the next interrupt
    while (!usbInterruptIsReady()) {
      usbPoll();
      _delay_ms(5);
    }

    // clear buffer by default
    memset( DigiKeyboard.reportBuffer , 0, sizeof( DigiKeyboard.reportBuffer));

    // Now set active keys in report
    if (footkeys) {
      i = 1; // point to first key from report
      if (footkeys & (1 << _Pin_Left_footswitch))   DigiKeyboard.reportBuffer[i++] = _Key_Left_footswitch;
      if (footkeys & (1 << _Pin_Middle_footswitch))  DigiKeyboard.reportBuffer[i++] = _Key_Middle_footswitch;
      if ( footkeys & (1 << _Pin_Right_footswitch))  DigiKeyboard.reportBuffer[i++] = _Key_Right_footswitch;
    }

    // Now set to send the keystrokes in the next USB interrupt
    usbSetInterrupt( DigiKeyboard.reportBuffer, sizeof(DigiKeyboard.reportBuffer));
    while (!usbInterruptIsReady()) {
      usbPoll();
      _delay_ms(5);
    }
  }

  // cycle each 10ms
  DigiKeyboard.delay(10);
}

////////////////////////////////////////////////////////////////////////////////
// Ascii Titles by Patrick Gillespie http://patorjk.com/software/taag



