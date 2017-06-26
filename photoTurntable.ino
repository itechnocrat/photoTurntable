/* File photo_table_0.1.ino */

#include "define.h"
#include "function.h"
#include "function.c"
#include "QuadDisplay2.h"

QuadDisplay quadDisplay(9);

void setup() {
  pinMode(PIN_MOTOR_DO_STEP, OUTPUT);
  pinMode(PIN_MOTOR_DIRECTION_ROTATION, OUTPUT);
  pinMode(PIN_MOTOR_ON, OUTPUT);
  pinMode(DO_SHOT, OUTPUT);
  pinMode(PIN_POWER_MOTOR, OUTPUT);
  pinMode(PIN_START_APP, INPUT);
  // digitalWrite(PIN_START_APP, LOW);
  pinMode(LED_BUILTIN, OUTPUT); // это косметика, на алгоритм не влияет
  digitalWrite(LED_BUILTIN, LOW);
  // pinMode(pin_Potentiometer, INPUT);

  quadDisplay.begin();
  quadDisplay.displayClear();
  quadDisplay.displayDigits(QD_O, QD_n, QD_NONE, QD_NONE); // on

  // open the serial port at 9600 bps
  Serial.begin(9600);
}

void loop() {
  // Чтобы начать/возобновить работу нужно нажать кнопку START/RESET
  while (digitalRead(PIN_START_APP)) {
    ;
  }

  // Фотосет 1
  motor_up();

  // Для каждого из необходимого количества снимков ...
  for (int i = 0; i < SHOTS; ++i) {

    // Затвор
    do_shot();

    // Поворачиваем столик по часовой стрелке на необходимое количество шагов
    motor_do_step((STEPS_TO_SHOT), (CLOCKWISE_ROTATION));

    // Пауза чтобы столик остановился и фотоаппарат успел записать снимок на карту
    delay(500);
  }

  // крутим столик обратно в нуль-положение
  motor_do_step((STEPS_TO_SHOT * SHOTS), (COUNTER_CLOCKWISE_ROTATION));

  // Фотосет 2
  // Для каждого из необходимого количества снимков...
  for (int i = 0; i < SHOTS; ++i) {

    // Затвор
    do_shot();

    // Поворачиваем столик на необходимое количество шагов
    motor_do_step((STEPS_TO_SHOT), (COUNTER_CLOCKWISE_ROTATION));

    // Пауза чтобы столик остановился и фотоаппарат успел записать снимок на карту
    delay(500);
  }

  // крутим столик обратно в нуль-положение
  motor_do_step((STEPS_TO_SHOT * SHOTS), (CLOCKWISE_ROTATION));

  // После завершения съёмки выключаем и обесточиваем двигатель
  motor_down();
}
