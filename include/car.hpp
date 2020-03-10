#ifndef _CAR_HPP_
#define _CAR_HPP_

//#include <wiringPi.h>
//#include <softPwm.h>
//#include <rotaryEncoder.hpp>
#include <lazysoft/motor.hpp>
#include <cstddef>
#include <iostream>
#include <chrono>

/*
        SENSOR
        M1 - M2
        M3 - M4

M1 - M3 -> left
M2 - M4 -> right

Green encoder  -> A
Yellow encoder -> B

*/

#define encoderM1A 23
#define encoderM1B 22

#define encoderM2A 27
#define encoderM2B 26

#define encoderM3A 25
#define encoderM3B 24

#define encoderM4A 29
#define encoderM4B 28

#define m1_cw 31
#define m1_ccw 14

#define m2_cw 12
#define m2_ccw 6

#define m3_cw 30
#define m3_ccw 21

#define m4_cw 10
#define m4_ccw 13

#define pwmM1 3
#define pwmM2 2
#define pwmM3 4
#define pwmM4 5

#define countPerCM 264
#define countPerDegrees 65
//#define countPerDegrees 76
// 1 rev = 5550 encoder counts
// 1 rev = 21 cm lineal

//#define leftPWM 4


//#define rightPWM 5

class Car{
	public:
		Car();
		Motor* m1 = NULL;
		Motor* m2 = NULL;
		Motor* m3 = NULL;
		Motor* m4 = NULL;
		int pwmValue;
		void position(int x = 0, int y = 0);
		void move(int cm = 0);
		void spin(int degrees = 0);
		void resetMotorsValue();
};
#endif
