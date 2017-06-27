#include "Arduino.h"
#include "define.h"


void do_shot() {
  digitalWrite(DO_SHOT, HIGH);
  delay(200);
  digitalWrite(DO_SHOT, LOW);
}

void set_direction_rotation(int direct) {
  digitalWrite(PIN_MOTOR_DIRECTION_ROTATION, direct);
}



void motor_do_step(int steps, int direct, int delay_step) {
  set_direction_rotation(direct);
  for (int i = 0; i < steps; ++i) {
    
    digitalWrite(PIN_MOTOR_DO_STEP, HIGH);
    delay(delay_step);
    digitalWrite(PIN_MOTOR_DO_STEP, LOW);
    delay(delay_step);
  }
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
