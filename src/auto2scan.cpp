//#include <bitset>



//#include <linux/types.h>
//#include <cmath>
//#include <fstream>
#include <iostream>
#include <cstring>
//#include <unistd.h>

#include <lazysoft/storm32_command.hpp>
#include <scan.hpp>
#include <car.hpp>

int main(int argc,char** argv){

	if(argc != 3) std::cout << "y la dirección del serial ? SALAME!\n\r";
	else{
		Serial com(argv[1], B9600);
		Storm32_command storm32(&com);
		Car wallF;

		char path01[30];
		strcpy(path01,argv[2]);
		strcat(path01,"-01");

		char path02[30];
		strcpy(path02,argv[2]);
		strcat(path02,"-02");

		wallF.position(40,20);

		Scan::simple(storm32,path01,0.0,0.0,0.0);


//		Scan::simple(storm32,path02,-5.0,-5.0,+5.0);

	}
	return 0;
}
