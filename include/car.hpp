#ifndef _CAR_HPP_
#define _CAR_HPP_

#include <cstddef>
#include <iostream>
#include <chrono>

#include <lazysoft/motor.hpp>

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

class Car{
	private:
		int pwmValue;

		Motor* m1 = NULL;
		Motor* m2 = NULL;
		Motor* m3 = NULL;
		Motor* m4 = NULL;

		void spin(int degrees = 0, int info = 0);
		void move(int cm = 0, int info = 0);
		void resetMotorsValue();
		void printMotorInfo();


	public:
		Car();
		void position(int x = 0, int y = 0);
};
#endif
