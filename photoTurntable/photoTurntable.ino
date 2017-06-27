/* File photo_table_0.1.ino исправил всек */


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
      float grad=0;
      int REQUIRED_TURN = 60;
      int NUMBER_OF_STEPS = (REQUIRED_TURN/(ONE_STEP_REAL));
      int STEPS_TO_SHOT;
          STEPS_TO_SHOT=(NUMBER_OF_STEPS) / SHOTS;
      float  real_angle = (STEPS_TO_SHOT*(SHOTS)*0.9);
      int TIME_BETWEEN_STEPS = 12;
      
  // Чтобы начать/возобновить работу нужно нажать кнопку START/RESET
  while (digitalRead(PIN_START_APP)) {
    ;
  }

Serial.print("ONE_STEP: "); Serial.println(ONE_STEP);
Serial.print("GEAR_RATIO: "); Serial.println(GEAR_RATIO);
Serial.print("ONE_STEP_REAL: "); Serial.println(ONE_STEP_REAL);
Serial.print("REQUIRED_TURN: "); Serial.println(REQUIRED_TURN);
Serial.print("NUMBER_OF_STEPS: "); Serial.println(NUMBER_OF_STEPS);
Serial.print("SHOTS: "); Serial.println(SHOTS);
Serial.print("STEPS_TO_SHOT: "); Serial.println(STEPS_TO_SHOT);
Serial.print("TIME_BETWEEN_STEPS: "); Serial.println(TIME_BETWEEN_STEPS);
Serial.print("реальный угол отклонения от середины: "); Serial.println(real_angle);
  motor_up();
  delay(500);
  // крутим столик к первому кадру из нуль положения
  Serial.print("задержка между шагами: "); Serial.println(TIME_BETWEEN_STEPS);
  motor_do_step((STEPS_TO_SHOT * SHOTS), (COUNTER_CLOCKWISE_ROTATION), (TIME_BETWEEN_STEPS));
    
  // Фотосет 1

  // Для каждого из необходимого количества снимков ... Снимков будет сколько интервалов + 1. 
  for (int i = 1; i < (SHOTS*2+2); ++i) {
      /* считаем угол поворота*/
      grad = (STEPS_TO_SHOT*(i-1)*0.9)-real_angle;
      
      quadDisplay.displayInt(grad);
      delay(700);
      quadDisplay.displayInt(i);
    Serial.print("поворот стола: "); Serial.print(grad);Serial.print("градусов, ");Serial.print("i= :");Serial.println(i);
    // Затвор
    do_shot();
    // Пауза после фотки 
    delay(500);
    // Поворачиваем столик по часовой стрелке на необходимое количество шагов. последний шаг фоткаем но не поворачиваем стол, - незачем
    if (i != (SHOTS*2+1)) {
    motor_do_step((STEPS_TO_SHOT), (CLOCKWISE_ROTATION),  (TIME_BETWEEN_STEPS));
    }
    
    // Пауза перед фоткой
    
    //delay(700);
  }


delay(1000);

  // крутим столик обратно в нуль-положение
  TIME_BETWEEN_STEPS = 8;
  Serial.print("задержка между шагами: "); Serial.println(TIME_BETWEEN_STEPS);
  motor_do_step((STEPS_TO_SHOT * SHOTS), (COUNTER_CLOCKWISE_ROTATION), (TIME_BETWEEN_STEPS));

  // После завершения съёмки выключаем и обесточиваем двигатель
  motor_down();
  delay(700);
  quadDisplay.displayDigits(QD_A, QD_L, QD_L, QD_NONE); // on
  

}
