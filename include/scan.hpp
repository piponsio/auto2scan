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
	public:
		static void simple(Storm32_command storm32, const char* outfile_name, double x_displacement, double y_displacement, double z_displacement);
};
#endif
