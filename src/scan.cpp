#include <scan.hpp>
void Scan::simple(Storm32_command storm32, const char* outfile_name, double x_displacement = 0.0, double y_displacement = 0.0, double z_displacement = 0.0){

	std::string path_xyz = "data/";
	path_xyz += outfile_name;
	path_xyz += ".xyz";

	std::string path_info = "data/";
	path_info += outfile_name;
	path_info += ".info";
//	std::cout << path_xyz << std::endl;

	std::ofstream outfile_xyz;
	std::ofstream outfile_info;

	storm32.setDataLogger(&outfile_info);

	outfile_xyz.open(path_xyz);
	outfile_info.open(path_info);

	__u16 distance;
	__u8  busyFlag;

	myLidarLite.i2c_init();
	myLidarLite.configure(0);

	//Storm32_command storm32(dev, B9600);
//	std::cout << "INIT VAR" << std::endl;

	double pitch, yaw;
	double x,y,z;
	double angles[] = {0.0, 0.0, 0.0};

	double theta = 0.0;
	double fi = 0;
	double radio = 0;

	bool pitch_flag = true;
	bool yaw_flag = true;

	double yaw_tolerance = 0.5;
	double pitch_tolerance = 0.5;

	const double pitch_min = 31.0;
	const double pitch_max = -92.0;

	const double yaw_min = -180.0;
	const double yaw_max = 180.0;

	pitch = pitch_min;
	yaw = yaw_min;
//	std::cout << "INIT setAngle" << std::endl;

	storm32.setAngle(pitch, 0.0, yaw);

//	std::cout << "INIT loop" << std::endl;

	while(angles[0] >= pitch_max + pitch_tolerance || pitch_max < pitch){

		storm32.getAngles();
		angles[0] = storm32.angles[0];
		angles[1] = storm32.angles[1];
		angles[2] = storm32.angles[2];

		std::cout << std::dec << angles[0] << "\t";
		std::cout << std::dec << angles[1] << "\t";
		std::cout << std::dec << angles[2] << "\t";

		std::cout << std::dec << pitch_flag << "\t";
		std::cout << std::dec << yaw_flag << "\t";

		std::cout << std::dec << pitch << "\t";
		std::cout << std::dec << yaw << std::endl;

		outfile_info << std::dec << angles[0] << "\t";
		outfile_info << std::dec << angles[1] << "\t";
		outfile_info << std::dec << angles[2] << "\t";

		outfile_info << std::dec << pitch_flag << "\t";
		outfile_info << std::dec << yaw_flag << "\t";

		outfile_info << std::dec << pitch << "\t";
		outfile_info << std::dec << yaw << std::endl;

		if( ( (yaw-yaw_tolerance) <= angles[2]) && (angles[2] <= (yaw+yaw_tolerance) ) ){
			if(yaw_flag == true && pitch_flag == 0){
				pitch -= 1;
				storm32.setAngle(pitch, 0.0, yaw);

	//			std::cout << std::dec << angles[0] << "\t";
	//			std::cout << std::dec << angles[1] << "\t";
	//			std::cout << std::dec << angles[2] << std::endl;
			}
			yaw_flag = false;

		}
		else yaw_flag = true;

		if( ( (pitch-pitch_tolerance) <= angles[0]) && (angles[0] <= (pitch+pitch_tolerance) )){
			if(pitch_flag == true && yaw_flag == 0){
				yaw = (yaw > 0)?(yaw_min):(yaw_max);
				storm32.setAngle(pitch, 0.0, yaw);

	//			std::cout << std::dec << +angles[0] << "\t";
	//			std::cout << std::dec << +angles[1] << "\t";
	//			std::cout << std::dec << +angles[2] << std::endl;
			}
			pitch_flag = false;
		}
		else pitch_flag = true;

        	busyFlag = myLidarLite.getBusyFlag();
        	if (busyFlag == 0x00){
       	     		myLidarLite.takeRange();
            		distance = myLidarLite.readDistance();

			theta = angles[2]*PI/180.0;
			fi = (90+angles[0])*PI/180.0;
			radio = distance/100.0;

			x = radio*sin(fi)*cos(theta);
			y = radio*sin(fi)*sin(theta);
			z = radio*cos(fi);

			//x = (distance/100.0)*sin((90+angles[0])*PI/180.0)*cos(angles[2]*PI/180.0);
			//y = (distance/100.0)*sin((90+angles[0])*PI/180.0)*sin(angles[2]*PI/180.0);
			//z = (distance/100.0)*cos((90+angles[0])*PI/180.0);

			outfile_xyz << std::fixed << (x + x_displacement) << " ";
			outfile_xyz << std::fixed << (y + y_displacement) << " ";
			outfile_xyz << std::fixed << (z + z_displacement) << std::endl;
		}
	}
	storm32.setAngle(0.0, 0.0, 0.0);
	outfile_xyz.close();
}
