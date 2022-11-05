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

#include "Trackduino_bluetooth.h"
#pragma once

Bluetooth::Bluetooth() {
  BT_Serial.begin(115200); 
  enable = 1;
}

void Bluetooth::update() {
  if (serialEventRun && enable==1) Bluetooth::operating(); 
  //if (serialEventRun && enable==0) serialEventRun();
}

void Bluetooth::operating() {
  byte command[9] = {0};
  boolean f[6] = {0};
  int value[7] = {0};

  if (BT_Serial.available() >=commandSize) {
    
    for (int i = 0; i <= commandSize; i++) {
      command[i] = (byte)BT_Serial.read(); // Save command
    }
    while (BT_Serial.available()) BT_Serial.read(); // очиска мусора, чтобы не было задержек
      
    int fData = (int)command[7];
    // Найдем все включенные клавиши
    if (fData - 64 >= 0) { f[5] = true; fData -= 64; } // Зафиксируем, включен ли F6
    if (fData - 32 >= 0) { f[4] = true; fData -= 32; } // Зафиксируем, включен ли F5
    if (fData - 16 >= 0) { f[3] = true; fData -= 16; } // Зафиксируем, включен ли F4
    if (fData - 8 >= 0) { f[2] = true; fData -= 8; } // Зафиксируем, включен ли F3
    if (fData - 4 >= 0) { f[1] = true; fData -= 4; } // Зафиксируем, включен ли F2
    if (fData - 2 >= 0) { f[0] = true; fData -= 2; } // Зафиксируем, включен ли F1
    int buffer;
    for (int i=0;i<7;i++) {
      buffer = (int)command[i];
      if (buffer > 128) // Переведём знаковый байт в целое число с учетом знака
        buffer -= 256;
      value[i] = buffer;
    }

    x = value[0];
    y = value[1];
    z = value[2];
    w = value[3];
    ax = value[4];
    ay = value[5];
    az = value[6];
    
    f1 = f[0];
    f2 = f[1];
    f3 = f[2];
    f4 = f[3];
    f5 = f[4];
    f6 = f[5];

    // Согласно ТЗ расшифровка следующая:
    // 0 - x
    // 1 - y
    // 2 - z
    // 3 - w
    // 4 - ax
    // 5 - ay
    // 6 - az
    // 7 - f1..f6
    // 8 - голосовые команды. по умолчанию 0x00, 1-6 - номер команды
  }
}
