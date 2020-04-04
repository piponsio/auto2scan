#include <scan.hpp>
Scan::Scan(const char* dev, speed_t baud, const char* outfile_name, bool xyz_file, bool info_file, int info){

	this->my_storm32 = Storm32_command(dev, baud);

	this->outfile_name = outfile_name;
	this->xyz_file = xyz_file;
	this->info_file = info_file;
	this->info = info;

	if(xyz_file == 1) this->updatePath(0);
	if(info_file == 1) this->updatePath(1);
}
void Scan::updatePath(int mode){

	if(mode==0){
		this->path_xyz = "data/";
		this->path_xyz += this->outfile_name;
		this->path_xyz += "-";
		if(this->count_file < 10) this->path_xyz += "00";
		else if(this->count_file < 100) this->path_xyz += "0";
 		this->path_xyz += std::to_string(this->count_file);
		this->path_xyz += ".xyz";
	}
	if(mode==1){
		this->path_info = "data/";
		this->path_info += this->outfile_name;
		this->path_info += "-";
		if(this->count_file < 10) this->path_info += "00";
		else if(this->count_file < 100) this->path_info += "0";
 		this->path_info += std::to_string(this->count_file);
		this->path_info += ".info";
	}

}
void Scan::simple(double x_displacement, double y_displacement, double z_displacement){

	if(this->xyz_file == 1) this->outfile_xyz.open(this->path_xyz);
	if(this->info_file == 1) this->outfile_info.open(this->path_info);

	__u16 distance;
	__u8  busyFlag;

	myLidarLite.i2c_init();
	myLidarLite.configure(0);

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

	this->my_storm32.setAngle(pitch, 0.0, yaw);

	while(angles[0] >= pitch_max + pitch_tolerance || pitch_max < pitch){

		this->my_storm32.getAngles();
		angles[0] = this->my_storm32.angles[0];
		angles[1] = this->my_storm32.angles[1];
		angles[2] = this->my_storm32.angles[2];

		if(this->info == 2){
			std::cout << std::dec << angles[0] << "\t";
			std::cout << std::dec << angles[1] << "\t";
			std::cout << std::dec << angles[2] << "\t";

			std::cout << std::dec << pitch_flag << "\t";
			std::cout << std::dec << yaw_flag << "\t";

			std::cout << std::dec << pitch << "\t";
			std::cout << std::dec << yaw << std::endl;

		}

		if(this->info_file == 1){
			this->outfile_info << std::dec << angles[0] << "\t";
			this->outfile_info << std::dec << angles[1] << "\t";
			this->outfile_info << std::dec << angles[2] << "\t";

			this->outfile_info << std::dec << pitch_flag << "\t";
			this->outfile_info << std::dec << yaw_flag << "\t";

			this->outfile_info << std::dec << pitch << "\t";
			this->outfile_info << std::dec << yaw << std::endl;
		}

		if( ( (yaw-yaw_tolerance) <= angles[2]) && (angles[2] <= (yaw+yaw_tolerance) ) ){
			if(yaw_flag == true && pitch_flag == 0){
				pitch -= 1;
				this->my_storm32.setAngle(pitch, 0.0, yaw);
				if(this->info == 1){
					std::cout << std::dec << angles[0] << "\t";
					std::cout << std::dec << angles[1] << "\t";
					std::cout << std::dec << angles[2] << std::endl;
				}
			}
			yaw_flag = false;

		}
		else yaw_flag = true;

		if( ( (pitch-pitch_tolerance) <= angles[0]) && (angles[0] <= (pitch+pitch_tolerance) )){
			if(pitch_flag == true && yaw_flag == 0){
				yaw = (yaw > 0)?(yaw_min):(yaw_max);
				this->my_storm32.setAngle(pitch, 0.0, yaw);
				if(this->info == 1){
					std::cout << std::dec << +angles[0] << "\t";
					std::cout << std::dec << +angles[1] << "\t";
					std::cout << std::dec << +angles[2] << std::endl;
				}
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

			if(this->xyz_file == 1){
				this->outfile_xyz << std::fixed << (x + x_displacement) << " ";
				this->outfile_xyz << std::fixed << (y + y_displacement) << " ";
				this->outfile_xyz << std::fixed << (z + z_displacement) << std::endl;
			}
		}
	}
	this->my_storm32.setAngle(0.0, 0.0, 0.0);
	this->count_file++;
	this->updatePath(0);
	this->updatePath(1);
	if(this->xyz_file == 1) this->outfile_xyz.close();
	if(this->info_file == 1) this->outfile_info.close();
}
