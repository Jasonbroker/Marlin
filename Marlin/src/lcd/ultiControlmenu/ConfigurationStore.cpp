#include "../../Marlin.h"
#include "../../module/planner.h"
#include "../../module/temperature.h"
#include "../ultralcd.h"
#include "UltiLCD2.h"
#include "ConfigurationStore.h"
#include "../../module/stepper.h"
#include "../../feature/fwretract.h"

void _EEPROM_writeData(int &pos, uint8_t* value, uint8_t size)
{
    do
    {
        eeprom_write_byte((unsigned char*)pos, *value);
        pos++;
        value++;
    }while(--size);
}
#define EEPROM_WRITE_VAR(pos, value) _EEPROM_writeData(pos, (uint8_t*)&value, sizeof(value))
void _EEPROM_readData(int &pos, uint8_t* value, uint8_t size)
{
    do
    {
        *value = eeprom_read_byte((unsigned char*)pos);
        pos++;
        value++;
    }while(--size);
}
#define EEPROM_READ_VAR(pos, value) _EEPROM_readData(pos, (uint8_t*)&value, sizeof(value))
//======================================================================================




#define EEPROM_OFFSET 100


// IMPORTANT:  Whenever there are changes made to the variables stored in EEPROM
// in the functions below, also increment the version number. This makes sure that
// the default values are used whenever there is a change to the data, to prevent
// wrong data being written to the variables.
// ALSO:  always make sure the variables in the Store and retrieve sections are in the same order.
#ifndef EEPROM_VERSION
  #ifdef UM2PLUS
    #define EEPROM_VERSION "V12"
  #else
    #define EEPROM_VERSION "V11"
  #endif
#endif

#ifdef EEPROM_SETTINGS
void Config_StoreSettings()
{
  char ver[4]= "000";
  int i=EEPROM_OFFSET;
  EEPROM_WRITE_VAR(i,ver); // invalidate data first
  EEPROM_WRITE_VAR(i,planner.settings.axis_steps_per_mm);
  EEPROM_WRITE_VAR(i,planner.settings.max_feedrate_mm_s);
  EEPROM_WRITE_VAR(i,planner.settings.max_acceleration_mm_per_s2);
  EEPROM_WRITE_VAR(i,planner.settings.acceleration);
  EEPROM_WRITE_VAR(i,planner.settings.retract_acceleration);
  EEPROM_WRITE_VAR(i,planner.settings.min_feedrate_mm_s);
  EEPROM_WRITE_VAR(i,planner.settings.min_travel_feedrate_mm_s);
  EEPROM_WRITE_VAR(i,planner.settings.min_segment_time_us);
  EEPROM_WRITE_VAR(i,planner.max_jerk.x);
  EEPROM_WRITE_VAR(i,planner.max_jerk.z);
  EEPROM_WRITE_VAR(i,planner.max_jerk.e);
  EEPROM_WRITE_VAR(i,add_homeing);

  #ifndef ULTIPANEL
  int plaPreheatHotendTemp = PREHEAT_1_TEMP_HOTEND, plaPreheatHPBTemp = PREHEAT_1_TEMP_BED, plaPreheatFanSpeed = PREHEAT_1_FAN_SPEED;
  int absPreheatHotendTemp = PREHEAT_2_TEMP_HOTEND, absPreheatHPBTemp = PREHEAT_2_TEMP_BED, absPreheatFanSpeed = PREHEAT_2_FAN_SPEED;
  #endif
  EEPROM_WRITE_VAR(i,plaPreheatHotendTemp);
  EEPROM_WRITE_VAR(i,plaPreheatHPBTemp);
  EEPROM_WRITE_VAR(i,plaPreheatFanSpeed);
  EEPROM_WRITE_VAR(i,absPreheatHotendTemp);
  EEPROM_WRITE_VAR(i,absPreheatHPBTemp);
  EEPROM_WRITE_VAR(i,absPreheatFanSpeed);
  #ifdef PIDTEMP
    EEPROM_WRITE_VAR(i,_PID_Kp(0));
    EEPROM_WRITE_VAR(i,_PID_Ki(0));
    EEPROM_WRITE_VAR(i,_PID_Kd(0));
  #else
	float dummy = 3000.0f;
    EEPROM_WRITE_VAR(i,dummy);
    dummy = 0.0f;
    EEPROM_WRITE_VAR(i,dummy);
    EEPROM_WRITE_VAR(i,dummy);
  #endif
  EEPROM_WRITE_VAR(i,stepper.motor_current_setting);
  #ifdef ENABLE_ULTILCD2
  EEPROM_WRITE_VAR(i,led_brightness_level);
  EEPROM_WRITE_VAR(i,led_mode);
  #else
  uint8_t dummyByte=0;
  EEPROM_WRITE_VAR(i,dummyByte);
  EEPROM_WRITE_VAR(i,dummyByte);
  #endif
  EEPROM_WRITE_VAR(i,fwretract.settings.retract_length);
  EEPROM_WRITE_VAR(i,fwretract.settings.retract_feedrate_mm_s);
  char ver2[4]=EEPROM_VERSION;
  i=EEPROM_OFFSET;
  EEPROM_WRITE_VAR(i,ver2); // validate data
  SERIAL_ECHO_START();
  SERIAL_ECHOLNPGM("Settings Stored");
}
#endif //EEPROM_SETTINGS


#ifdef EEPROM_CHITCHAT
void Config_PrintSettings()
{  // Always have this function, even with EEPROM_SETTINGS disabled, the current values will be shown
    SERIAL_ECHO_START();
    SERIAL_ECHOLNPGM("Steps per unit:");
    SERIAL_ECHO_START();
    SERIAL_ECHOPAIR("  M92 X",planner.settings.axis_steps_per_mm[X_AXIS]);
    SERIAL_ECHOPAIR(" Y",planner.settings.axis_steps_per_mm[Y_AXIS]);
    SERIAL_ECHOPAIR(" Z",planner.settings.axis_steps_per_mm[Z_AXIS]);
    SERIAL_ECHOPAIR(" E",planner.settings.axis_steps_per_mm[E_AXIS]);
    SERIAL_EOL;

    SERIAL_ECHO_START();
    SERIAL_ECHOLNPGM("Maximum feedrates (mm/s):");
    SERIAL_ECHO_START();
    SERIAL_ECHOPAIR("  M203 X",planner.settings.max_feedrate_mm_s[X_AXIS]);
    SERIAL_ECHOPAIR(" Y",planner.settings.max_feedrate_mm_s[Y_AXIS] );
    SERIAL_ECHOPAIR(" Z", planner.settings.max_feedrate_mm_s[Z_AXIS] );
    SERIAL_ECHOPAIR(" E", planner.settings.max_feedrate_mm_s[E_AXIS]);
    SERIAL_EOL;

    SERIAL_ECHO_START();
    SERIAL_ECHOLNPGM("Maximum Acceleration (mm/s2):");
    SERIAL_ECHO_START();
    SERIAL_ECHOPAIR("  M201 X" ,max_acceleration_units_per_sq_second[X_AXIS] );
    SERIAL_ECHOPAIR(" Y" , max_acceleration_units_per_sq_second[Y_AXIS] );
    SERIAL_ECHOPAIR(" Z" ,max_acceleration_units_per_sq_second[Z_AXIS] );
    SERIAL_ECHOPAIR(" E" ,max_acceleration_units_per_sq_second[E_AXIS]);
    SERIAL_EOL;
    SERIAL_ECHO_START();
    SERIAL_ECHOLNPGM("Acceleration: S=acceleration, T=retract acceleration");
    SERIAL_ECHO_START();
    SERIAL_ECHOPAIR("  M204 S",acceleration );
    SERIAL_ECHOPAIR(" T" ,retract_acceleration);
    SERIAL_EOL;

    SERIAL_ECHO_START();
    SERIAL_ECHOLNPGM("Advanced variables: S=Min feedrate (mm/s), T=Min travel feedrate (mm/s), B=minimum segment time (ms), X=maximum XY jerk (mm/s),  Z=maximum Z jerk (mm/s),  E=maximum E jerk (mm/s)");
    SERIAL_ECHO_START();
    SERIAL_ECHOPAIR("  M205 S",planner.settings.min_feedrate_mm_s );
    SERIAL_ECHOPAIR(" T" ,planner.settings.min_travel_feedrate_mm_s );
    SERIAL_ECHOPAIR(" B" ,planner.settings.min_segment_time_us );
    SERIAL_ECHOPAIR(" X" ,planner.max_jerk.x);
    SERIAL_ECHOPAIR(" Z" ,planner.max_jerk.z);
    SERIAL_ECHOPAIR(" E" ,planner.max_jerk.e);
    SERIAL_EOL;

    SERIAL_ECHO_START();
    SERIAL_ECHOLNPGM("Home offset (mm):");
    SERIAL_ECHO_START();
    SERIAL_ECHOPAIR("  M206 X",add_homeing[X_AXIS] );
    SERIAL_ECHOPAIR(" Y" ,add_homeing[Y_AXIS] );
    SERIAL_ECHOPAIR(" Z" ,add_homeing[Z_AXIS] );
    SERIAL_EOL;
#ifdef PIDTEMP
    SERIAL_ECHO_START();
    SERIAL_ECHOLNPGM("PID settings:");
    SERIAL_ECHO_START();
    SERIAL_ECHOPAIR("   M301 P",_PID_Kp(0));
    SERIAL_ECHOPAIR(" I" ,unscalePID_i(_PID_Ki(0)));
    SERIAL_ECHOPAIR(" D" ,unscalePID_d(_PID_Kd(0)));
    SERIAL_EOL;
#endif
}
#endif


#ifdef EEPROM_SETTINGS
void Config_RetrieveSettings()
{
    int i=EEPROM_OFFSET;
    char stored_ver[4];
    char ver[4]=EEPROM_VERSION;
    EEPROM_READ_VAR(i,stored_ver); //read stored version
    //  SERIAL_ECHOLN("Version: [" << ver << "] Stored version: [" << stored_ver << "]");
    if (strncmp(ver,stored_ver,3) == 0)
    {
        // version number match
        EEPROM_READ_VAR(i,planner.settings.axis_steps_per_mm);
        EEPROM_READ_VAR(i,planner.settings.max_feedrate_mm_s);
        EEPROM_READ_VAR(i,max_acceleration_units_per_sq_second);

        // steps per sq second need to be updated to agree with the units per sq second (as they are what is used in the planner)
		reset_acceleration_rates();

        EEPROM_READ_VAR(i,acceleration);
        EEPROM_READ_VAR(i,retract_acceleration);
        EEPROM_READ_VAR(i,planner.settings.min_feedrate_mm_s);
        EEPROM_READ_VAR(i,planner.settings.min_travel_feedrate_mm_s);
        EEPROM_READ_VAR(i,planner.settings.min_segment_time_us);
        EEPROM_READ_VAR(i,planner.max_jerk.x);
        EEPROM_READ_VAR(i,planner.max_jerk.z));
        EEPROM_READ_VAR(i,planner.max_jerk.e);
        EEPROM_READ_VAR(i,add_homeing);
        #ifndef ULTIPANEL
        int plaPreheatHotendTemp, plaPreheatHPBTemp, plaPreheatFanSpeed;
        int absPreheatHotendTemp, absPreheatHPBTemp, absPreheatFanSpeed;
        #endif
        EEPROM_READ_VAR(i,plaPreheatHotendTemp);
        EEPROM_READ_VAR(i,plaPreheatHPBTemp);
        EEPROM_READ_VAR(i,plaPreheatFanSpeed);
        EEPROM_READ_VAR(i,absPreheatHotendTemp);
        EEPROM_READ_VAR(i,absPreheatHPBTemp);
        EEPROM_READ_VAR(i,absPreheatFanSpeed);
        #ifndef PIDTEMP
        float Kp,Ki,Kd;
        #endif
        // do not need to scale PID values as the values in EEPROM are already scaled
        EEPROM_READ_VAR(i,_PID_Kp(0));
        EEPROM_READ_VAR(i,_PID_Ki(0));
        EEPROM_READ_VAR(i,_PID_Kd(0));
        EEPROM_READ_VAR(i,stepper.motor_current_setting);
        #ifdef ENABLE_ULTILCD2
        EEPROM_READ_VAR(i,led_brightness_level);
        EEPROM_READ_VAR(i,led_mode);
        #else
        uint8_t dummyByte;
        EEPROM_READ_VAR(i,dummyByte);
        EEPROM_READ_VAR(i,dummyByte);
        #endif
        EEPROM_READ_VAR(i,fwretract.settings.retract_length);
        EEPROM_READ_VAR(i,fwretract.settings.retract_feedrate_mm_s);

		// Call updatePID (similar to when we have processed M301)
		updatePID();
        SERIAL_ECHO_START();
        SERIAL_ECHOLNPGM("Stored settings retrieved");
    }
    else
    {
        Config_ResetDefault();
    }
    if (strncmp_P(ver, PSTR("V010"), 3) == 0)
    {
        i = EEPROM_OFFSET + 84;
        EEPROM_READ_VAR(i,add_homeing);
    }
    Config_PrintSettings();
}
#endif

void Config_ResetDefault()
{
    float tmp1[]=DEFAULT_AXIS_STEPS_PER_UNIT;
    float tmp2[]=DEFAULT_MAX_FEEDRATE;
    long tmp3[]=DEFAULT_MAX_ACCELERATION;
    for (short i=0;i<4;i++)
    {
        axis_steps_per_mm[i]=tmp1[i];
        max_feedrate[i]=tmp2[i];
        max_acceleration_units_per_sq_second[i]=tmp3[i];
    }

    // steps per sq second need to be updated to agree with the units per sq second
    reset_acceleration_rates();

    acceleration=DEFAULT_ACCELERATION;
    retract_acceleration=DEFAULT_RETRACT_ACCELERATION;
    planner.settings.min_feedrate_mm_s=DEFAULT_MINIMUMFEEDRATE;
    planner.settings.min_segment_time_us=DEFAULT_MINSEGMENTTIME;
    planner.settings.min_travel_feedrate_mm_s=DEFAULT_MINTRAVELFEEDRATE;
    max_xy_jerk=DEFAULT_XYJERK;
    max_z_jerk=DEFAULT_ZJERK;
    max_e_jerk=DEFAULT_EJERK;
    add_homeing[0] = add_homeing[1] = add_homeing[2] = 0;
#ifdef ULTIPANEL
    plaPreheatHotendTemp = PREHEAT_1_TEMP_HOTEND;
    plaPreheatHPBTemp = PREHEAT_1_TEMP_BED;
    plaPreheatFanSpeed = PREHEAT_1_FAN_SPEED;
    absPreheatHotendTemp = PREHEAT_2_TEMP_HOTEND;
    absPreheatHPBTemp = PREHEAT_2_TEMP_BED;
    absPreheatFanSpeed = PREHEAT_2_FAN_SPEED;
#endif
#ifdef PIDTEMP
    _PID_Kp(0) = DEFAULT_Kp;
    _PID_Ki(0) = scalePID_i(DEFAULT_Ki);
    _PID_Kd(0) = scalePID_d(DEFAULT_Kd);

    // call updatePID (similar to when we have processed M301)
    updatePID();

//#ifdef PID_ADD_EXTRUSION_RATE
//    Kc = DEFAULT_Kc;
//#endif//PID_ADD_EXTRUSION_RATE
#endif//PIDTEMP
    float tmp_motor_current_setting[]=DEFAULT_PWM_MOTOR_CURRENT;
    stepper.motor_current_setting[0] = tmp_motor_current_setting[0];
    stepper.motor_current_setting[1] = tmp_motor_current_setting[1];
    stepper.motor_current_setting[2] = tmp_motor_current_setting[2];

    #ifdef ENABLE_ULTILCD2
    led_brightness_level = 100;
    led_mode = LED_MODE_ALWAYS_ON;
    #endif
    fwretract.settings.retract_length = 4.5;
    fwretract.settings.retract_feedrate_mm_s = 25 * 60;

SERIAL_ECHO_START();
SERIAL_ECHOLNPGM("Hardcoded Default Settings Loaded");

}
