### Megadrive Controller Test

An Arduino sketch to allow testing the function of a Sega Megadrive 3 button controller. This will poll all the inputs at approximately 60Hz, blink the in-built LED if an input is detected, and output the status of each on the USB serial line every tenth sample, with the following order:

```
UDLRSABCMXYZ
```

where each position denotes the following buttons:

* `U`   up button
* `D`   down button
* `L`   left button
* `R`   right button
* `S`   start button
* `A`   A button
* `B`   B button
* `C`   C button
* `M`   mode button
* `X`   X button
* `Y`   Y button
* `Z`   Z button

The value at each position can either be the short label above, or `.` to indicate that the button isn't being pressed.

### Hardware

This has been developed and tested solely on an Arduino Uno.

The expected pin mapping is:

```
Arduino   Serial Port
    5           1
    2           2
    3           3
    4           4
    6           6
    7           7
    9           9
```

Deviation from the straight mapping is due to pin 1 on the Arduino Uno also being used as TX for the serial port.
