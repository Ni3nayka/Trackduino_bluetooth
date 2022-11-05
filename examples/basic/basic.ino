/*
   Integration the Trackduino to Arduino IDE:
   https://github.com/Ni3nayka/Trackduino_bluetooth

   author: Egor Bakay <egor_bakay@inbox.ru>
   write:  september 2022
   modify: november 2022
*/

// указываем к какому Serial подключен блютуз (если не написать, то будет использвоан Serial(0)) 
// если использовать данную опцию, обязательно писать до подключения библиотеки!
//#define BT_Serial Serial1       

// подключаем библиотеку
#include <Trackduino_bluetooth.h>

Bluetooth bluetooth;            // создадим объект для управления блютузом

// создаем объект для блютуза (через Trackduino (Robotrack) приложение для android смартфона)
// https://robotrack-rus.ru/wiki/doku.php/po/robotrek_pdu

void setup() {
  bluetooth.setup();            // инициализируем блютуз
  pinMode(13, OUTPUT);          // инициализируем пин встроенного светодиода
}

void loop () {

  // обновить блютуз
  bluetooth.update();

  int X = bluetooth.x;          // взять данные с джойстика, по оси X
  // bluetooth.x - взять данные с джойстика, по оси X [-100;100]
  // bluetooth.y - взять данные с джойстика, по оси Y [-100;100]
  // bluetooth.z - взять данные с джойстика, по оси Z [-100;100]
  // bluetooth.w - взять данные с джойстика, по оси W [-100;100]
  
  int aX = bluetooth.ax;        // взять угол наклона телефона по оси Х
  // bluetooth.ax - взять данные с акселерометра, по оси X [-100;100]
  // bluetooth.ay - взять данные с акселерометра, по оси Y [-100;100]
  // bluetooth.az - взять данные с акселерометра, по оси Z [-100;100]
     
  int S1 = bluetooth.slider[1]; // взять данные с первого слайдера
  // bluetooth.slider[1]; - взять данные с ползунка номер 1 [0;180]
  // bluetooth.slider[2]; - взять данные с ползунка номер 2 [0;180]
  // bluetooth.slider[3]; - взять данные с ползунка номер 3 [0;180]
  
  if (bluetooth.f[1]) {         // если кнопка f1 нажата
    digitalWrite(13, HIGH);     // включаем светодиод
  }
  else {                        // иначе
    digitalWrite(13, LOW);      // выключаем светодиод
  }
  // bluetooth.f[1] - состояние кнопки f1 [0;1]
  // bluetooth.f[2] - состояние кнопки f2 [0;1]
  // bluetooth.f[3] - состояние кнопки f3 [0;1]
  // bluetooth.f[4] - состояние кнопки f4 [0;1]
  // bluetooth.f[5] - состояние кнопки f5 [0;1]
  // bluetooth.f[6] - состояние кнопки f6 [0;1]
}
