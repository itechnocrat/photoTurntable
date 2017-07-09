/* File photoTurntable.ino */

#include <QuadDisplay2.h>
#include "pins.h"
#include "constants.h"

QuadDisplay quadDisplay(9);

// Количество шагов в желаемом угле поворота стола в одну сторону
int steps_in_turn;

// Количесто шагов между кадрами
int steps_between_shot;

void setup() {
  pinMode(PIN_MOTOR_DO_STEP, OUTPUT);
  pinMode(PIN_MOTOR_DIRECTION_ROTATION, OUTPUT);
  pinMode(PIN_MOTOR_ON, OUTPUT);
  pinMode(PIN_DO_SHOT, OUTPUT);
  pinMode(PIN_POWER_MOTOR, OUTPUT);
  pinMode(PIN_START_APP, INPUT);
  // digitalWrite(PIN_START_APP, LOW);
  // pinMode(pin_Potentiometer, INPUT);
  pinMode(LED_BUILTIN, OUTPUT); // это косметика, на алгоритм не влияет
  digitalWrite(LED_BUILTIN, LOW);

  quadDisplay.begin();
  quadDisplay.displayClear();
  quadDisplay.displayDigits(QD_O, QD_n, QD_NONE, QD_NONE); // on

  // open the serial port at 9600 bps
  Serial.begin(9600);

  // Количество шагов в желаемом угле поворота стола в одну сторону
  steps_in_turn = STEPS_ONE_TURNOVER * REQUIRED_TURN / 360;
  if (GEAR_RATIO < 0) steps_in_turn = steps_in_turn * GEAR_RATIO * -1;
    else steps_in_turn = steps_in_turn / GEAR_RATIO * -1;

  // Количесто шагов между кадрами
  steps_between_shot = steps_in_turn / REQUIRED_SHOTS;
  ser_log("steps_in_turn", steps_in_turn);
  ser_log("steps_between_shot", steps_between_shot);
  ser_log("REQUIRED_SHOTS", REQUIRED_SHOTS);
}

void loop() {
  // Фотосет 1
  msg("SET1");
  msg("CLOCKWISE_ROTATION");
  motor_up();

  // Для каждого из необходимого количества снимков ...
  for (int i = 0; i < REQUIRED_SHOTS; i++) {

    // Затвор
    do_shot();
    ser_log("SHOT", i+1);

    // Поворачиваем столик по часовой стрелке на необходимое количество шагов
    motor_do_step(steps_between_shot, CLOCKWISE_ROTATION);

    // Пауза чтобы столик остановился и фотоаппарат успел записать снимок на карту
    delay(500);
  }


  // крутим столик обратно в нуль-положение
  msg("COUNTER_CLOCKWISE_ROTATION");
  motor_do_step(steps_between_shot * REQUIRED_SHOTS, COUNTER_CLOCKWISE_ROTATION);

  // Фотосет 2
  msg("SET2");
  // Для каждого из необходимого количества снимков...
  for (int i = 0; i < REQUIRED_SHOTS; i++) {

    // Затвор
    do_shot();
    ser_log("SHOT", i+1);

    // Поворачиваем столик на необходимое количество шагов
    motor_do_step(steps_between_shot, COUNTER_CLOCKWISE_ROTATION);

    // Пауза чтобы столик остановился и фотоаппарат успел записать снимок на карту
    delay(500);
  }

  // крутим столик снова в нолик
  msg("CLOCKWISE_ROTATION");
  motor_do_step(steps_between_shot * REQUIRED_SHOTS, CLOCKWISE_ROTATION);

  // После завершения съёмки выключаем и обесточиваем двигатель
  motor_down();

  // Чтобы начать/возобновить работу нужно нажать кнопку START/RESET
  // while (digitalRead(PIN_START_APP)) {
  //   ;
  // }
  msg("END");
  while (1) {
    ;
  }

}
