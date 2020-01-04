#!/usr/bin/env bash

# This script is to package the Marlin package for Arduino
# This script should run under Linux and Mac OS X, as well as Windows with Cygwin.

#############################
# CONFIGURATION
#############################

##Which version name are we appending to the final archive
export BUILD_NAME=18.08.1

#############################
# Actual build script
#############################

if [ -z `which make` ]; then
	MAKE=mingw32-make
else
	MAKE=make
fi


# Change working directory to the directory the script is in
# http://stackoverflow.com/a/246128
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

# #For building under MacOS we need gnutar instead of tar
# if [ -z `which gnutar` ]; then
# 	TAR=tar
# else
# 	TAR=gnutar
# fi

#############################
# Build the required firmwares
#############################

if [ -d "D:/arduino-1.8.1" ]; then
	ARDUINO_PATH=D:/arduino-1.8.1
	ARDUINO_VERSION=181
elif [ -d "/Applications/Arduino.app/Contents/Resources/Java" ]; then
	ARDUINO_PATH=/Applications/Arduino.app/Contents/Resources/Java
	ARDUINO_VERSION=105
elif [ -d "D:/Arduino" ]; then
	ARDUINO_PATH=D:/Arduino
	ARDUINO_VERSION=165
else
	ARDUINO_PATH=/usr/share/arduino
	ARDUINO_VERSION=105
fi


#Build the Ultimaker2 firmwares.
# gitClone https://github.com/TinkerGnome/Ultimaker2Marlin.git _Ultimaker2Marlin
# cd _Ultimaker2Marlin/Marlin

# USE_CHANGE_TEMPERATURE

$MAKE -j 3 HARDWARE_MOTHERBOARD=72 ARDUINO_INSTALL_DIR=${ARDUINO_PATH} ARDUINO_VERSION=${ARDUINO_VERSION} BUILD_DIR=_Ultimaker2extended clean
sleep 2
mkdir _Ultimaker2extended
$MAKE -j 3 HARDWARE_MOTHERBOARD=72 ARDUINO_INSTALL_DIR=${ARDUINO_PATH} ARDUINO_VERSION=${ARDUINO_VERSION} BUILD_DIR=_Ultimaker2extended DEFINES="'STRING_CONFIG_H_AUTHOR=\"Tinker_${BUILD_NAME}e\"' TEMP_SENSOR_1=0 EXTRUDERS=1 FILAMENT_SENSOR_PIN=30 BABYSTEPPING DEFAULT_POWER_BUDGET=175 HEATER_0_MAXTEMP=315 HEATER_1_MAXTEMP=315 HEATER_2_MAXTEMP=315"

cp _Ultimaker2extended/Marlin.hex resources/firmware/Tinker-MarlinUltimaker2extended-${BUILD_NAME}.hex

$MAKE -j 3 HARDWARE_MOTHERBOARD=72 ARDUINO_INSTALL_DIR=${ARDUINO_PATH} ARDUINO_VERSION=${ARDUINO_VERSION} BUILD_DIR=_Ultimaker2extendedDual clean
sleep 2
mkdir _Ultimaker2extendedDual
$MAKE -j 3 HARDWARE_MOTHERBOARD=72 ARDUINO_INSTALL_DIR=${ARDUINO_PATH} ARDUINO_VERSION=${ARDUINO_VERSION} BUILD_DIR=_Ultimaker2extendedDual DEFINES="'STRING_CONFIG_H_AUTHOR=\"Tinker_${BUILD_NAME}e\"' TEMP_SENSOR_1=20 EXTRUDERS=2 FILAMENT_SENSOR_PIN=30 BABYSTEPPING DEFAULT_POWER_BUDGET=160 HEATER_0_MAXTEMP=315 HEATER_1_MAXTEMP=315 HEATER_2_MAXTEMP=315"

cp _Ultimaker2extendedDual/Marlin.hex resources/firmware/Tinker-MarlinUltimaker2extended-dual-${BUILD_NAME}.hex


$MAKE -j 3 HARDWARE_MOTHERBOARD=72 ARDUINO_INSTALL_DIR=${ARDUINO_PATH} ARDUINO_VERSION=${ARDUINO_VERSION} BUILD_DIR=_Ultimaker2extendedPlus clean
sleep 2
mkdir _Ultimaker2extendedPlus
$MAKE -j 3 HARDWARE_MOTHERBOARD=72 ARDUINO_INSTALL_DIR=${ARDUINO_PATH} ARDUINO_VERSION=${ARDUINO_VERSION} BUILD_DIR=_Ultimaker2extendedPlus DEFINES="'STRING_CONFIG_H_AUTHOR=\"Tinker_${BUILD_NAME}e+\"' TEMP_SENSOR_1=0 EXTRUDERS=1 FILAMENT_SENSOR_PIN=30 BABYSTEPPING UM2PLUS DEFAULT_POWER_BUDGET=175 HEATER_0_MAXTEMP=315 HEATER_1_MAXTEMP=315 HEATER_2_MAXTEMP=315 'EEPROM_VERSION=\"V12\"'"

cp _Ultimaker2extendedPlus/Marlin.hex resources/firmware/Tinker-MarlinUltimaker2extendedPlus-${BUILD_NAME}.hex

$MAKE -j 3 HARDWARE_MOTHERBOARD=72 ARDUINO_INSTALL_DIR=${ARDUINO_PATH} ARDUINO_VERSION=${ARDUINO_VERSION} BUILD_DIR=_Ultimaker2extendedPlusDual clean
sleep 2
mkdir _Ultimaker2extendedPlusDual
$MAKE -j 3 HARDWARE_MOTHERBOARD=72 ARDUINO_INSTALL_DIR=${ARDUINO_PATH} ARDUINO_VERSION=${ARDUINO_VERSION} BUILD_DIR=_Ultimaker2extendedPlusDual DEFINES="'STRING_CONFIG_H_AUTHOR=\"Tinker_${BUILD_NAME}e+\"' TEMP_SENSOR_1=20 EXTRUDERS=2 FILAMENT_SENSOR_PIN=30 BABYSTEPPING UM2PLUS DEFAULT_POWER_BUDGET=160 HEATER_0_MAXTEMP=315 HEATER_1_MAXTEMP=315 HEATER_2_MAXTEMP=315 'EEPROM_VERSION=\"V12\"'"

cp _Ultimaker2extendedPlusDual/Marlin.hex resources/firmware/Tinker-MarlinUltimaker2extendedPlus-dual-${BUILD_NAME}.hex

