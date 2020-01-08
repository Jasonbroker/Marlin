#ifndef TINKERGNOME_H
#define TINKERGNOME_H

#include "../../module/temperature.h"
#include "UltiLCD2_menu_utils.h"

// low pass filter constant, from 0.0 to 1.0 -- Higher numbers mean more smoothing, less responsiveness.
// 0.0 would be completely disabled, 1.0 would ignore any changes
#define LOW_PASS_SMOOTHING 0.90
#define DEFAULT_FILAMENT_AREA 6.3793966

extern float recover_height;
extern float recover_position[NUM_AXIS];
extern int recover_temperature[EXTRUDERS];

extern float e_smoothed_speed[EXTRUDERS];
extern float current_nominal_speed;

void tinkergnome_init();
void lcd_menu_maintenance_expert();
void lcd_menu_print_heatup_tg();
void lcd_menu_printing_tg();
void lcd_menu_move_axes();
void manage_led_timeout();
void manage_encoder_position(int8_t encoder_pos_interrupt);
void lcd_init_extrude();
void lcd_menu_expert_extrude();
void recover_start_print(const char *cmd);
void lcd_menu_recover_init();
void lcd_menu_expert_recover();
void reset_printing_state();
void endofprint_retract_store();

// for adaptive of marlin 2.0
extern uint8_t printing_state;
#define PRINT_STATE_NORMAL      0
#define PRINT_STATE_DWELL       1
#define PRINT_STATE_WAIT_USER   2
#define PRINT_STATE_HEATING     3
#define PRINT_STATE_HEATING_BED 4
#define PRINT_STATE_HOMING      5
#define PRINT_STATE_RECOVER     6
#define PRINT_STATE_START       7
#define PRINT_STATE_ABORT       255

FORCE_INLINE void lcd_print_tune_nozzle0() { lcd_tune_value(thermalManager.temp_hotend[0].target, 0, thermalManager.temp_range[0].maxtemp - 15); }
#if EXTRUDERS > 1
FORCE_INLINE void lcd_print_tune_nozzle1() { lcd_tune_value(thermalManager.temp_hotend[i].target, 0, thermalManager.temp_range[1].maxtemp - 15); }
#endif
#if TEMP_SENSOR_BED != 0
FORCE_INLINE void lcd_print_tune_bed() { lcd_tune_value(thermalManager.temp_bed.target, 0, BED_MAXTEMP - 15); }
#endif

#ifdef UM2PLUS
#define DEFAULT_AXIS_DIR 0xFD
#else
#define DEFAULT_AXIS_DIR 0x15
#endif

#define MAX_HEATING_TEMPERATURE_INCREASE 10
#define MAX_HEATING_CHECK_MILLIS (30 * 1000)

extern float volume_to_filament_length[EXTRUDERS];

#endif //TINKERGNOME_H
