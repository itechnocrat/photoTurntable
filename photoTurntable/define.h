#include "Arduino.h"
// Двигатель:
// количество шагов на один оборот вала 200, т.е. 360 / 200 = 1,8 градуса/шаг, т.е.
// один шаг мотора = 1,8 градусов = 0,9 градуса повора выключателя
#define ONE_STEP 1.8

// Передаточный коэффициент шестерёнок = 0,5
#define GEAR_RATIO 0.5

// угол повороты выключателя на 1 шаг мотора = 0,9
#define ONE_STEP_REAL ONE_STEP * GEAR_RATIO

// Желаемый угол поворота стола - половина от всего диапазона, в каждую сторону от центра
//#define REQUIRED_TURN 60;

// Количество шагов двигателя для желаемого поворота стола в каждую сторону 
//#define NUMBER_OF_STEPS REQUIRED_TURN/(ONE_STEP_REAL)

// Желаемое количество интервалов на которое разбить желаемый угол повора в однусторону REQUIRED_TURN. кадров будет на 1 больше. как столбы и секции забора
#define SHOTS 6

// Количество шагов между кадрами
//#define STEPS_TO_SHOT NUMBER_OF_STEPS / SHOTS

// Выдержка времени между шагами.
// Чем больше это число, тем медленнее вращается двигатель
//#define TIME_BETWEEN_STEPS 12


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

//счетчик градусов 
//int gradusu;


// #define pin_Potentiometer A0
// #define pin13 13 // On board Led
