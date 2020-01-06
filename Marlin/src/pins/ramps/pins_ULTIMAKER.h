/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Ultimaker pin assignments
 */

/**
 * Rev B   2 JAN 2017
 *
 *  Added pin definitions for:
 *    M3, M4 & M5 spindle control commands
 *    case light
 */

#if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
  #error "Oops! Select 'Arduino/Genuino Mega or Mega 2560' in 'Tools > Board.'"
#endif

#define BOARD_INFO_NAME         "Ultimaker"
#define DEFAULT_MACHINE_NAME    BOARD_INFO_NAME
#define DEFAULT_SOURCE_CODE_URL "https://github.com/Ultimaker/Marlin"

//
// Servos
//
#define SERVO0_PIN         11

//
// Limit Switches
//
#define X_MIN_PIN          22
#define X_MAX_PIN          24
#define Y_MIN_PIN          26
#define Y_MAX_PIN          28
#define Z_MIN_PIN          30
#define Z_MAX_PIN          32

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN  32
#endif

//
// Steppers
//
#define X_STEP_PIN         25
#define X_DIR_PIN          23
#define X_ENABLE_PIN       27

#define Y_STEP_PIN         31
#define Y_DIR_PIN          33
#define Y_ENABLE_PIN       29

#define Z_STEP_PIN         37
#define Z_DIR_PIN          39
#define Z_ENABLE_PIN       35

#define E0_STEP_PIN        43
#define E0_DIR_PIN         45
#define E0_ENABLE_PIN      41

#define E1_STEP_PIN        49
#define E1_DIR_PIN         47
#define E1_ENABLE_PIN      48

//
// Temperature Sensors
//
#define TEMP_0_PIN          8
#define TEMP_1_PIN          9
#define TEMP_BED_PIN       10

//
// Heaters / Fans
//
#define HEATER_0_PIN        2
#define HEATER_1_PIN        3
#define HEATER_BED_PIN      4

#ifndef FAN_PIN
  #define FAN_PIN           7
#endif

//
// Misc. Functions
//
#ifdef ENABLE_ULTILCD2

#define SDPOWER_PIN                     -1
#define SDSS               53
#define MAX6675_SS_PIN                  13  // A13 or D13 (?) => PK5 or PB7
#define LED_PIN            13
#define PS_ON_PIN                   24  // PA2 (?)
#define KILL_PIN                    -1
#define SUICIDE_PIN        54
#define CASE_LIGHT_PIN      8
#define SAFETY_TRIGGERED_PIN        28  // PA6, PIN to detect the safety circuit has triggered
#define MAIN_VOLTAGE_MEASURE_PIN    14  // PK6, Analogue PIN to measure the main voltage, with a 100k - 4k7 resistor divider.

#undef MOTOR_CURRENT_PWM_XY_PIN
#undef MOTOR_CURRENT_PWM_Z_PIN
#undef MOTOR_CURRENT_PWM_E_PIN
#define MOTOR_CURRENT_PWM_XY_PIN    44  // PL5
#define MOTOR_CURRENT_PWM_Z_PIN     45  // PL4
#define MOTOR_CURRENT_PWM_E_PIN     46  // PL3

#define MOTOR_CURRENT_PWM_RANGE 2000

//arduino pin which triggers an piezzo beeper
#define BEEPER_PIN                      18  // PD3 / TXD1

#define LCD_PINS_RS                 20  // PD1 / SDA
#define LCD_PINS_ENABLE             15  // PJ0 / RXD3
#define LCD_PINS_D4                 14  // PJ1 / TXD3
#define LCD_PINS_D5                 21  // PD0 / SCL
#define LCD_PINS_D6                 5   // PE3
#define LCD_PINS_D7                 6   // PH3

//buttons are directly attached
#define BTN_EN1                     40  // PG1
#define BTN_EN2                     41  // PG0
#define BTN_ENC                     19  // PD2 / RXD1, the click

#define BLEN_C                      2
#define BLEN_B                      1
#define BLEN_A                      0

#define SD_DETECT_PIN                39  // PG2

//encoder rotation values
#define encrot0                     0
#define encrot1                     1
#define encrot2                     3
#define encrot3                     2

#ifndef FILAMENT_SENSOR_PIN
  #define FILAMENT_SENSOR_PIN         -1  // PC7 = D30; PD7 = D38
#endif

#endif
//
// LCD / Controller
//
#if HAS_SPI_LCD

  #define BEEPER_PIN 18

  #if ENABLED(NEWPANEL)

    #define LCD_PINS_RS    20
    #define LCD_PINS_ENABLE 17
    #define LCD_PINS_D4    16
    #define LCD_PINS_D5    21
    #define LCD_PINS_D6     5
    #define LCD_PINS_D7     6

    // Buttons directly attached
    #define BTN_EN1 40
    #define BTN_EN2 42
    #define BTN_ENC 19

    #define SD_DETECT_PIN 38

  #else // !NEWPANEL - Old style panel with shift register

    // Buttons attached to a shift register
    #define SHIFT_CLK 38
    #define SHIFT_LD 42
    #define SHIFT_OUT 40
    #define SHIFT_EN 17

    #define LCD_PINS_RS 16
    #define LCD_PINS_ENABLE 5
    #define LCD_PINS_D4 6
    #define LCD_PINS_D5 21
    #define LCD_PINS_D6 20
    #define LCD_PINS_D7 19

    #define SD_DETECT_PIN -1

  #endif // !NEWPANEL

#endif // HAS_SPI_LCD

//
// M3/M4/M5 - Spindle/Laser Control
//
#define SPINDLE_LASER_PWM_PIN     9   // Hardware PWM
#define SPINDLE_LASER_ENA_PIN    10   // Pullup!
#define SPINDLE_DIR_PIN          11   // use the EXP3 PWM header
