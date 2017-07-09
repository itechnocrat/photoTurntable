#include <Arduino.h>
#include "pins.h"
#include "constants.h"

void do_shot() {
  digitalWrite(PIN_DO_SHOT, HIGH);
  delay(200);
  digitalWrite(PIN_DO_SHOT, LOW);
}

void direction_rotation_set(int direct) {
  digitalWrite(PIN_MOTOR_DIRECTION_ROTATION, direct);
}

void motor_do_step(int steps, int direct) {
  direction_rotation_set(direct);
  int i;
  for (i = 0; i < steps; ++i) {
    digitalWrite(PIN_MOTOR_DO_STEP, HIGH);
    delay(TIME_BETWEEN_STEPS);
    digitalWrite(PIN_MOTOR_DO_STEP, LOW);
  }
  ser_log("STEPS", i);
}

void motor_up() {
  // Подаем питание на двигатель
  digitalWrite(PIN_POWER_MOTOR, HIGH);

  // Включаем мотор
  digitalWrite(PIN_MOTOR_ON, HIGH);
}

void motor_down() {
  // Снимаем питание с двигателя
  digitalWrite(PIN_POWER_MOTOR, LOW);

  // Выключаем мотор
  digitalWrite(PIN_MOTOR_ON, LOW);
}

void ser_log(char string[], int value) {
  Serial.print(string);
  Serial.print(" = ");
  Serial.println(value);
}

void msg(char string[]) {
  Serial.print(string);
  Serial.println();
}