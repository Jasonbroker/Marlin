
#include "machinesettings.h"
#include "../../Marlin.h"
#include "../../module/temperature.h"

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
    settings[index]->feedmultiply = feedmultiply;
#if TEMP_SENSOR_BED != 0
    settings[index]->BedTemperature = thermalManager.temp_bed.target;
#endif // TEMP_SENSOR_BED
    settings[index]->fanSpeed = thermalManager.fan_speed;
    for (int i=0; i<EXTRUDERS; i++)
    {
        settings[index]->HotendTemperature[i] = thermalManager.temp_hotend[i].target;
        settings[index]->extrudemultiply[i] = extrudemultiply[i];
    }
    for (int i=0; i<NUM_AXIS; i++)
    {
        settings[index]->max_acceleration_units_per_sq_second[i] = max_acceleration_units_per_sq_second[i];
        settings[index]->max_feedrate[i] = max_feedrate[i];
    }
    settings[index]->acceleration = acceleration;
    settings[index]->minimumfeedrate = planner.settings.min_feedrate_mm_s;
    settings[index]->mintravelfeedrate = planner.settings.min_travel_feedrate_mm_s;
    settings[index]->minsegmenttime = planner.settings.min_segment_time_us;
    settings[index]->max_xy_jerk = max_xy_jerk;
    settings[index]->max_z_jerk = max_z_jerk;
    settings[index]->max_e_jerk = max_e_jerk;

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

    feedmultiply = settings[index]->feedmultiply;
#if TEMP_SENSOR_BED != 0
    thermalManager.temp_bed.target = settings[index]->BedTemperature;
#endif // TEMP_SENSOR_BED
    thermalManager.set_fan_speed(0, settings[index]->fanSpeed);
    for (int i=0; i<EXTRUDERS; i++)
    {
      thermalManager.temp_hotend[i].target = settings[index]->HotendTemperature[i];
      extrudemultiply[i] = settings[index]->extrudemultiply[i];
    }
    for (int i=0; i<NUM_AXIS; i++)
    {
      max_acceleration_units_per_sq_second[i] = settings[index]->max_acceleration_units_per_sq_second[i];
      max_feedrate[i] = settings[index]->max_feedrate[i];
    }
    acceleration = settings[index]->acceleration;
    planner.settings.min_feedrate_mm_s = settings[index]->minimumfeedrate;
    planner.settings.min_travel_feedrate_mm_s = settings[index]->mintravelfeedrate;
    planner.settings.min_segment_time_us = settings[index]->minsegmenttime;
    max_xy_jerk = settings[index]->max_xy_jerk;
    max_z_jerk = settings[index]->max_z_jerk;
    max_e_jerk = settings[index]->max_e_jerk;

    delete settings[index];
    settings[index] = 0;

    return true;
}
