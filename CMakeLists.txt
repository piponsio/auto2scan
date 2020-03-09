cmake_minimum_required(VERSION 3.0)
project(auto2scan VERSION 0.1.0)

#find_library(wiringPi_LIB wiringPi)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/LazysoftCppLibrary)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/LIDARLite_RaspberryPi_Library)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/LIDARLite_RaspberryPi_Library/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/LazysoftCppLibrary/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set(SCAN_HEADER
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scan.cpp
)
set(CAR_HEADER
        ${CMAKE_CURRENT_SOURCE_DIR}/src/car.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/src/rotaryEncoder.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/LazysoftCppLibrary/src/motor.cpp
)
#set(ROTARYENCODER_HEADER
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/rotaryEncoder.cpp
#)
#set(MOTOR_HEADER
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/motor.cpp
#)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/lib/shared)

add_library(scan SHARED ${SCAN_HEADER})
add_library(car SHARED ${CAR_HEADER})
#add_library(rotaryEncoder SHARED ${ROTARYENCODER_HEADER})
#add_library(motor SHARED ${MOTOR_HEADER})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(auto2scan ${CMAKE_CURRENT_SOURCE_DIR}/src/auto2scan.cpp)
target_link_libraries(auto2scan storm32_command lidarlite_v3 scan car ${wiringPi_LIB})

#add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp)
#target_link_libraries(test car ${wiringPi_LIB})

#add_executable(stop-car ${CMAKE_CURRENT_SOURCE_DIR}/src/stop-car.cpp)
#target_link_libraries(stop-car car ${wiringPi_LIB})

#target_link_libraries(stop-car )
