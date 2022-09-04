/*
 * Integration the Trackduino to Arduino IDE:
 * https://github.com/Ni3nayka/Trackduino
 * and integration Trackduino bluetooth app to arduino bluetooth:
 * https://github.com/Ni3nayka/Trackduino_bluetooth
 * 
 * Bluetooth::operating and Bluetooth::update - 
 * The code for this function is taken from the original IDE and is given a normal look
 * 
 * author: Egor Bakay <egor_bakay@inbox.ru>
 * write:  august 2022
 * modify: september 2022
 */

#include "bluetooth.h"

#ifndef Trackduino_bluetooth_Serial
#define Trackduino_bluetooth_Serial Serial
#endif

Bluetooth bluetooth;
