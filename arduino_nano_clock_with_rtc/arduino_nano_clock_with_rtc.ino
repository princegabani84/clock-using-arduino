#include <Wire.h>
#include <RTClib.h>
#include <TM1637TinyDisplay.h>

#define CLK 3
#define DIO 2

#define BTN_SET 4
#define BTN_HH 5
#define BTN_MM 6

RTC_DS1307 rtc;
TM1637TinyDisplay display(CLK, DIO);

int mode = 0; // 0 = normal, 1 = set hour, 2 = set minute
unsigned long lastButtonTime = 0;

void setup() {
  pinMode(BTN_SET, INPUT_PULLUP);
  pinMode(BTN_HH, INPUT_PULLUP);
  pinMode(BTN_MM, INPUT_PULLUP);

  Wire.begin();
  rtc.begin();

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  display.setBrightness(7);
}

void loop() {
  DateTime now = rtc.now();

  // --- Mode Change ---
  if (digitalRead(BTN_SET) == LOW && millis() - lastButtonTime > 300) {
    mode = (mode + 1) % 3;
    lastButtonTime = millis();
  }

  // --- Time Setting ---
  if (mode == 1 && digitalRead(BTN_HH) == LOW && millis() - lastButtonTime > 300) {
    int newHour = (now.hour() + 1) % 24;
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), newHour, now.minute(), 0));
    lastButtonTime = millis();
  }

  if (mode == 2 && digitalRead(BTN_MM) == LOW && millis() - lastButtonTime > 300) {
    int newMinute = (now.minute() + 1) % 60;
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), newMinute, 0));
    lastButtonTime = millis();
  }

  now = rtc.now(); // Refresh after setting
  int hour = now.hour();
  int minute = now.minute();

  // Convert to 12-hour format
  if (hour == 0) hour = 12;
  else if (hour > 12) hour -= 12;

  uint8_t digits[4];

  bool blink = (millis() / 500) % 2 == 0;

  // --- Display digits ---
  digits[0] = display.encodeDigit(hour / 10);
  digits[1] = display.encodeDigit(hour % 10);
  digits[2] = display.encodeDigit(minute / 10);
  digits[3] = display.encodeDigit(minute % 10);

  // Add blinking logic
  if (mode == 1 && blink) { // blink HH
    digits[0] = digits[1] = 0;
  } else if (mode == 2 && blink) { // blink MM
    digits[2] = digits[3] = 0;
  }

  // Add blinking colon
  if ((millis() / 500) % 2 == 0) {
    digits[1] |= 0b10000000;
  }

  display.setSegments(digits);
  delay(100);
}
