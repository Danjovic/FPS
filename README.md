# F.P.S. Foot Presto Switch

Pedal Switch for playing FPS games

This project provides an USB keyboard emulator to be activated by feet either individually or simultaneously.
It is based on a DigisPark board with updated DigiKeyboard.h library.

# Instructions

1.  Download the modified library "DigiKeyboard_6keys.h" and copy it to the following folder/directory:

  - Under Windows
  
    c:\Users\username\AppData\Roaming\Arduino15\packages\digistump\hardware\avr\1.6.5\libraries\DigisparkKeyboard\
  
  - Under Linux
  
  /home/username/.arduino15/packages/digistump/hardware/avr/1.6.7/libraries/DigisparkKeyboard/
3

2. Include the modified library in your project and whenever is necessary to send multiple keys use the modified library:
```c++
#include "DigiKeyboard_6keys.h" 
```
Then you can send simultaneous keys by adding keystrokes to output buffer
```c++
// clear buffer by default
memset( DigiKeyboard.reportBuffer , 0, sizeof( DigiKeyboard.reportBuffer));

// Now add up to 6 keys to report
DigiKeyboard.reportBuffer[i++] = _Key_A;
DigiKeyboard.reportBuffer[i++] = _Key_B;
DigiKeyboard.reportBuffer[i++] = _Key_C;
DigiKeyboard.reportBuffer[i++] = _Key_D;
DigiKeyboard.reportBuffer[i++] = _Key_E;
DigiKeyboard.reportBuffer[i++] = _Key_F;

// Now set to send the keystrokes in the next USB interrupt
usbSetInterrupt( DigiKeyboard.reportBuffer, sizeof(DigiKeyboard.reportBuffer));
  while (!usbInterruptIsReady()) {
    usbPoll();
    _delay_ms(5);
  }
```
To release all the keys, simply send a clear buffer
