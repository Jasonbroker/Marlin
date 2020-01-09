
#include "machinesettings.h"
#include "../../Marlin.h"
#include "../../module/temperature.h"
#include "../../module/motion.h"
#include "../../module/planner.h"

MachineSettings::MachineSettings()
{
    for (uint8_t i = 0; i<MAX_MACHINE_SETTINGS; ++i)
    {
        settings[i] = 0;
    }
}

MachineSettings::~MachineSettings()
{
    for (uint8_t i = 0; i<MAX_MACHINE_SETTINGS; ++i)
    {
        delete settings[i];
        settings[i] = 0;
    }
}

// store settings
bool MachineSettings::store(uint8_t index)
{
    if (index >= MAX_MACHINE_SETTINGS)
    {
        return false;
    }
    if (!settings[index])
    {
        if (freeMemory() > 200)
        {
            settings[index] = new t_machinesettings;
        }
        else
        {
            return false;
        }
    }
    settings[index]->feedmultiply = feedrate_percentage;
#if TEMP_SENSOR_BED != 0
    settings[index]->BedTemperature = thermalManager.temp_bed.target;
#endif // TEMP_SENSOR_BED
    settings[index]->fanSpeed = thermalManager.fan_speed;
    for (int i=0; i<EXTRUDERS; i++)
    {
        settings[index]->HotendTemperature[i] = thermalManager.temp_hotend[i].target;
        settings[index]->extrudemultiply[i] = planner.flow_percentage[i];
    }
    for (int i=0; i<NUM_AXIS; i++)
    {
        settings[index]->max_acceleration_units_per_sq_second[i] = planner.settings.max_acceleration_mm_per_s2[i];
        settings[index]->max_feedrate[i] = planner.settings.max_feedrate_mm_s[i];
    }
    settings[index]->acceleration = planner.settings.acceleration;
    settings[index]->minimumfeedrate = planner.settings.min_feedrate_mm_s;
    settings[index]->mintravelfeedrate = planner.settings.min_travel_feedrate_mm_s;
    settings[index]->minsegmenttime = planner.settings.min_segment_time_us;
    settings[index]->max_xy_jerk = planner.max_jerk[X_AXIS];
    settings[index]->max_z_jerk = planner.max_jerk[Z_AXIS];
    settings[index]->max_e_jerk = planner.max_jerk[E_AXIS];

    return true;
}

// recall settings
bool MachineSettings::recall(uint8_t index)
{
    if (index >= MAX_MACHINE_SETTINGS)
    {
        return false;
    }
    if (!settings[index])
    {
        return false;
    }

    feedrate_percentage = settings[index]->feedmultiply;
#if TEMP_SENSOR_BED != 0
    thermalManager.temp_bed.target = settings[index]->BedTemperature;
#endif // TEMP_SENSOR_BED
    thermalManager.set_fan_speed(0, settings[index]->fanSpeed);
    for (int i=0; i<EXTRUDERS; i++)
    {
      thermalManager.temp_hotend[i].target = settings[index]->HotendTemperature[i];
      planner.flow_percentage[i] = settings[index]->extrudemultiply[i];
    }
    for (int i=0; i<NUM_AXIS; i++)
    {
      planner.settings.max_acceleration_mm_per_s2[i] = settings[index]->max_acceleration_units_per_sq_second[i];
      planner.settings.max_feedrate[i] = settings[index]->max_feedrate[i];
    }
    planner.settings.acceleration = settings[index]->acceleration;
    planner.settings.min_feedrate_mm_s = settings[index]->minimumfeedrate;
    planner.settings.min_travel_feedrate_mm_s = settings[index]->mintravelfeedrate;
    planner.settings.min_segment_time_us = settings[index]->minsegmenttime;
    planner.max_jerk[X_AXIS] = settings[index]->max_xy_jerk;
    planner.max_jerk[Z_AXIS] = settings[index]->max_z_jerk;
    planner.max_jerk[E_AXIS] = settings[index]->max_e_jerk;

    delete settings[index];
    settings[index] = 0;

    return true;
}
