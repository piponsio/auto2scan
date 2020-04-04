#ifndef _SCAN_HPP_
#define _SCAN_HPP_

#include <linux/types.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include <lazysoft/storm32_command.hpp>
#include <garmin/lidarlite_v3.h>

LIDARLite_v3 myLidarLite;
#define PI 3.14159265

class Scan{
	private:
		int count_file = 0;
		Storm32_command my_storm32;
		bool info = false;
		bool xyz_file = true;
		bool info_file = false;
		const char* outfile_name;
		std::ofstream outfile_xyz;
		std::ofstream outfile_info;
		std::string path_xyz;
		std::string path_info;
		void updatePath(int mod = 0);

	public:
		Scan(const char* dev = "/dev/ttyACM0", speed_t baud = B9600, const char* outfile_name = "test01", bool xyz_file = 1, bool info_file = 0, int info = 0);
		void simple(double x_displacement = 0.0, double y_displacement = 0.0, double z_displacement = 0.0);
};
#endif
