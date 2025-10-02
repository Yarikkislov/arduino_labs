//выбор способов реализации решений для 2.4 и 2.5
#define _2_4_METHOD 0 //0 для маски или 1 для bitSet
#define _2_5_METHOD 0 //0 для цикла или 1 для __builtin_ctz

#define BUTTON_BYTE 0b00111000
//определение функции для 2.5 (два способа)
uint8_t get_ctz(int byte) {
  uint8_t ctz;
  if (byte == 0) ctz = 255;
  else {
    if (_2_5_METHOD == 0) {
      for (uint8_t n = 0; n < 8; ++n) {
        if (byte & (1 << n)) {
          ctz = n;
          break;
        }
      }
    }
    else ctz = (uint8_t)__builtin_ctz((unsigned int)byte);
  }
  return ctz;
}
//таймер дебаунса для 2.6
unsigned long times = micros();

void setup() {
  Serial.begin(9600);
  //2.1 настройка битов
  DDRD = 0b00000000;
  PORTD = BUTTON_BYTE;
  DDRB = BUTTON_BYTE;
  PORTB = 0b00000000;
}

void loop() {
  //2.6 все в цикле дебаунса 5 раз в секунду
  if (millis() - times > 200) {
    times = millis();
    uint8_t output_byte = 0b00000000;
    //2.2 вывод байта входа
    Serial.println(PIND, BIN);
    //2.3 позиции кнопок
    uint8_t input_byte = PIND ^ BUTTON_BYTE;
    for (uint8_t n = 0; n < 8; ++n) {
      if (input_byte & (1 << n)) {
        Serial.println(n);
        //2.4 формирование байта выхода (два способа)
        if (_2_4_METHOD == 0) {
          uint8_t mask = (1 << n);
          output_byte = (output_byte & ~mask) | (1 << n);
        }
        else {
          bitSet(output_byte, n);
        }
      }
    }
    Serial.println(output_byte, BIN);
    PORTB = output_byte;
    //2.5 возврат индекса младшего установленного бита
    uint8_t ctz = get_ctz((int)output_byte);
    Serial.println(ctz);
    //настройка вывода
    Serial.print("\n");
  }
}
