#include <iostream>
#include <cstring>

#include <lazysoft/storm32_command.hpp>
#include <scan.hpp>
#include <car.hpp>

int main(int argc,char** argv){

	if(argc != 3) std::cout << "Ingrese direccion y nombre de archivo de datos\n\r";
	else{
		Scan my_scan(argv[1],B9600,argv[2],true,true,1);
		my_scan.simple();
//		Car wallF;
//genera segmentatio faul
/*		Serial com(argv[1], B9600);
		Storm32_command storm32(&com);

		char path01[30];
		strcpy(path01,argv[2]);
		strcat(path01,"-01");

		Scan::simple(storm32,path01,0.0,0.0,0.0);
*/
	}
	return 0;
}
