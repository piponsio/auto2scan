#include <car.hpp>

Car::Car(){
	this->m1 = new Motor(pwmM1, 25, m1_cw, m1_ccw, encoderM1A, encoderM1B, true);
	this->m2 = new Motor(pwmM2, 28, m2_cw, m2_ccw, encoderM2B, encoderM2A, false);
	this->m3 = new Motor(pwmM3, 25, m3_cw, m3_ccw, encoderM3A, encoderM3B, true);
	this->m4 = new Motor(pwmM4, 28, m4_cw, m4_ccw, 0, encoderM4A, false);
	//Encoder del motor 4 dañado
}

void Car::position(int x, int y){
	std::chrono::microseconds timer;
        std::chrono::microseconds now;

	this->move(x);

	timer = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
        now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
	while( (now - timer) < std::chrono::microseconds(2000000)){ now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()); }

	if(y > 0) this->spin(90);
	if(y < 0) this->spin(-90);

	timer = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
        now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
	while( (now - timer) < std::chrono::microseconds(2000000)){ now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()); }

	this->move( (y > 0) ? y : y*-1);

	this->resetMotorsValue();
}
void Car::spin(int degrees, int info){

	int totalCount = countPerDegrees * degrees;

	while(
		(degrees > 0 &&
			(  (*this->m1).value > totalCount*-1
			|| (*this->m2).value < totalCount
			|| (*this->m3).value > totalCount*-1
			|| (*this->m4).value < totalCount)
		)
		|| (degrees < 0 &&
			(  (*this->m1).value < totalCount*-1
			|| (*this->m2).value > totalCount
			|| (*this->m3).value < totalCount*-1
			|| (*this->m4).value > totalCount)
		)
	){
		if(degrees > 0){
			(*this->m1).ccw(totalCount*-1,7,true);
			(*this->m2).ccw(totalCount,7,true);
			(*this->m3).ccw(totalCount*-1,5,true);
			(*this->m4).ccw(totalCount,5,true);
		}
		else{

			(*this->m1).cw(totalCount*-1,10,true);
			(*this->m2).cw(totalCount,17,true);
			(*this->m3).cw(totalCount*-1,10,true);
			(*this->m4).cw(totalCount,6,true);
		}
		if(info == 2) this->printMotorInfo();
	}

	this->resetMotorsValue();
	if(info == 1) this->printMotorInfo();
}

void Car::move(int cm, int info){
	int totalCount = countPerCM * cm;
	while(
		(cm > 0 &&
			(  (*this->m1).value < totalCount
			|| (*this->m2).value < totalCount
			|| (*this->m3).value < totalCount
			|| (*this->m4).value < totalCount)
		)
		|| (cm < 0 &&
			(  (*this->m1).value > totalCount
			|| (*this->m2).value > totalCount
			|| (*this->m3).value > totalCount
			|| (*this->m4).value > totalCount)
		)
	){
		if(cm > 0){
			(*this->m1).cw(totalCount);
			(*this->m2).ccw(totalCount);
		 	(*this->m3).cw(totalCount);
			(*this->m4).ccw(totalCount);
		}
		else{
			(*this->m1).ccw(totalCount);
			(*this->m2).cw(totalCount,5,true);
			(*this->m3).ccw(totalCount);
			(*this->m4).cw(totalCount);
		}
		if(info == 2) this->printMotorInfo();
	}
	this->resetMotorsValue();

	if(info == 1) this->printMotorInfo();

}

void Car::resetMotorsValue(){
	(*this->m1).stop();
	(*this->m2).stop();
	(*this->m3).stop();
	(*this->m4).stop();

	(*this->m1).value = 0;
	(*this->m2).value = 0;
	(*this->m3).value = 0;
	(*this->m4).value = 0;
}

void Car::printMotorInfo(){
	std::cout << "M1: " << (*this->m1).value << "(" << (*this->m1).pwm << ", " << digitalRead((*this->m1).pin_cw) << ", " << digitalRead((*this->m1).pin_ccw)  << ")" << " - ";
	std::cout << "M2: " << (*this->m2).value << "(" << (*this->m2).pwm << ", " << digitalRead((*this->m2).pin_cw) << ", " << digitalRead((*this->m2).pin_ccw)  << ")" << " - ";
	std::cout << "M3: " << (*this->m3).value << "(" << (*this->m3).pwm << ", " << digitalRead((*this->m3).pin_cw) << ", " << digitalRead((*this->m3).pin_ccw)  << ")" << " - ";
	std::cout << "M4: " << (*this->m4).value << "(" << (*this->m4).pwm << ", " << digitalRead((*this->m4).pin_cw) << ", " << digitalRead((*this->m4).pin_ccw)  << ")" << std::endl;
}
