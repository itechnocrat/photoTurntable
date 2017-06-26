#include "Arduino.h"
// Двигатель:
// количество шагов на один оборот вала 200, т.е. 360 / 200 = 1,8 градуса/шаг, т.е.
// один шаг = 1,8 градусов
#define ONE_STEP 1,8

// Передаточный коэффициент шестерёнок = 2
#define GEAR_RATIO 2

// Величина шага с учетом коэффициента
#define ONE_STEP_REAL ONE_STEP * GEAR_RATIO

// Желаемый угол поворота стола
#define REQUIRED_TURN 45

// Количество шагов двигателя для желаемого поворота стола
#define NUMBER_OF_STEPS REQUIRED_TURN / ONE_STEP_REAL

// Желаемое количество кадров
#define SHOTS 10

// Количество шагов между кадрами
#define STEPS_TO_SHOT NUMBER_OF_STEPS / SHOTS

// Выдержка времени между шагами.
// Чем больше это число, тем медленнее вращается двигатель
#define TIME_BETWEEN_STEPS 10

// Направление вращения стола
// По часовой стрелке
#define CLOCKWISE_ROTATION HIGH

// Против часовой стрелки
#define COUNTER_CLOCKWISE_ROTATION LOW

// Пины:
// Troyka-Stepper:

#define PIN_MOTOR_ON                  11 // Включение двигателя GVE
#define PIN_MOTOR_DIRECTION_ROTATION  A3 // Направление вращения DVG
#define PIN_MOTOR_DO_STEP             A4 // Шаг двигателя SVG

// Управляющий затвором фотоаппарата пин
#define DO_SHOT 4

// Управляющий подачей напряжения питания на двигатель пин
#define PIN_POWER_MOTOR 5

// Что-то делающая кнопка S1
#define PIN_START_APP 12

// Время действия переднего фронта сигнала для шага двигателя
#define TIME_RISING_EDGE 

// #define pin_Potentiometer A0
// #define pin13 13 // On board Led
