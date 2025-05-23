#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int trigPins[4] = {2, 4, 6, 8};
int echoPins[4] = {3, 5, 7, 9};
String slotNames[4] = {"Slot 1", "Slot 2", "Slot 3", "Slot 4"};

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();

  for (int i = 0; i < 4; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }

  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  delay(2000);
  lcd.clear();
}

void loop() {
  for (int i = 0; i < 4; i++) {
    long duration;
    int distance;

    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);

    duration = pulseIn(echoPins[i], HIGH);
    distance = duration * 0.034 / 2;

    lcd.setCursor(0, 0);
    lcd.print(slotNames[i] + ":");

    lcd.setCursor(0, 1);
    if (distance < 10) {
      lcd.print("Occupied      ");
    } else {
      lcd.print("Vacant        ");
    }

    delay(1500);
    lcd.clear();
  }
}