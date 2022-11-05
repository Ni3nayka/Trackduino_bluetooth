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
 * modify: november 2022
 */

#pragma once

#ifndef Trackduino_bluetooth_Serial
#define BT_Serial Serial
#else
#define BT_Serial Trackduino_bluetooth_Serial
#endif

#include <Arduino.h>

#define commandSize 9

class Bluetooth {

  public:

    Bluetooth();
    //setup();
    void update();

    int x,y,z,w,ax,ay,az;
    bool f1,f2,f3,f4,f5,f6;

    bool enable;

  private:
    void operating();
};
