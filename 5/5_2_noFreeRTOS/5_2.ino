#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <math.h>

LiquidCrystal_I2C LCD(0x27,16,2);

unsigned short h = 12, m = 34, s = 56; //задать настоящее время

unsigned short acp2lux(unsigned short acp) {
  //МНК полином 4 степени с приведенной погрешностью 0.5% !
  unsigned short lux = 5.3088e+02 + 2.2937e+00 * acp - 6.2742e-03 * pow(acp, 2) + \
    7.5372e-06 * pow(acp, 3) - 3.1439e-09 * pow(acp, 4);
  return lux;
}

void setup() {
  LCD.init();
  LCD.backlight();
}

void loop() {
  unsigned short ACP = analogRead(A0);
  unsigned short LUX = acp2lux(ACP);

  LCD.setCursor(0, 1); LCD.print("LUX:");
  LCD.setCursor(5, 1); LCD.print(LUX);


  //RTC не подключился, пишем свой таймер :)
  s++;
  if (s > 59) {
    m++;
    s = 0;
  }
  if (m > 59) {
    h++;
    m = 0;
  }
  if (h > 23) {
    h = 0;
  }

  LCD.setCursor(0, 0); LCD.print("TIME:");
  LCD.setCursor(6, 0); LCD.print(h);
  LCD.setCursor(8, 0); LCD.print(":");
  LCD.setCursor(9, 0); LCD.print(m);
  LCD.setCursor(11, 0); LCD.print(":");
  LCD.setCursor(12, 0); LCD.print("%d ", s);


  delay(1000);
}
