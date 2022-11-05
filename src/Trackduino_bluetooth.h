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

#ifndef BT_Serial
#define BT_Serial Serial
#endif

#include <Arduino.h>

#define commandSize 12

#define timeout_bluetooth_enable 250 // если больше этого времени не можем поймать блютуз - то он сейчас не работает
#define timeout_bluetooth_end_package_data 50 // если больше этого времени не было данных, начит был конец одного пакета

class Bluetooth {

  public:

    void setup();
    void update();

    int x,y,z,w,ax,ay,az;
    // нулевые элементы не используем для удобства пользователся
    bool f[7];
    int slider[4];

    bool enable;

  private:

    void clear_data();
};


void Bluetooth::setup() {
  Serial.begin(9600);
  BT_Serial.begin(9600); 
  enable = 1;
}

void Bluetooth::clear_data() {
  x = 0;
  y = 0;
  z = 0;
  w = 0;
  ax = 0;
  ay = 0;
  az = 0;
  for (int i = 0; i<7; i++) f[i] = 0;
  for (int i = 0; i<4; i++) slider[i] = 0;
}

void Bluetooth::update() {
  
  if (!enable) return;

  Bluetooth::clear_data();

  byte command[commandSize] = {0};

  // реализовано так, потому что спасибо авторам прекрасной андроид программы 
  // данные идут тупо потоком, без каких либо особых разделяющих символов,
  // есть только более крупная задержка между данными и все
  unsigned long int t;
  do {
    t = millis();
    while (!BT_Serial.available()) {
      if (millis()-t>timeout_bluetooth_enable) return;
    }
    command[0] = BT_Serial.read();
  } while (millis()-t<timeout_bluetooth_end_package_data);

  for (int i = 1; i < commandSize; i++) {
    t = millis();
    while (!BT_Serial.available()) {
      if (millis()-t>timeout_bluetooth_enable) return;
    }
    command[i] = BT_Serial.read();
  }
  
  while (BT_Serial.available()) BT_Serial.read(); // очиска мусора, чтобы не было задержек

  // тестим, выводим
  /*for (int i = 0; i < commandSize; i++) {
    Serial.print(command[i]);
    Serial.print(" ");
  }
  Serial.println();*/
  
  int fData = (int)command[7];
  // Найдем все включенные клавиши
  if (fData - 64 >= 0) { f[6] = true; fData -= 64; } // Зафиксируем, включен ли F6
  if (fData - 32 >= 0) { f[5] = true; fData -= 32; } // Зафиксируем, включен ли F5
  if (fData - 16 >= 0) { f[4] = true; fData -= 16; } // Зафиксируем, включен ли F4
  if (fData - 8  >= 0) { f[3] = true; fData -= 8;  } // Зафиксируем, включен ли F3
  if (fData - 4  >= 0) { f[2] = true; fData -= 4;  } // Зафиксируем, включен ли F2
  if (fData - 2  >= 0) { f[1] = true; fData -= 2;  } // Зафиксируем, включен ли F1
  
  int value[7] = {0};
  for (int i=0;i<7;i++) {
    value[i] = (int)command[i];
    if (value[i] > 128) // Переведём знаковый байт в целое число с учетом знака
      value[i] -= 256;
  }
  x = value[0];
  y = value[1];
  z = value[2];
  w = value[3];
  ax = value[4];
  ay = value[5];
  az = value[6];
  
  for (int i=1;i<4;i++)
    slider[i] = (int)command[i+8];
}
