#ifndef ULTI_LCD2_H
#define ULTI_LCD2_H
#include <Arduino.h>
#include "../../inc/MarlinConfigPre.h"

#ifdef ENABLE_ULTILCD2
#include "UltiLCD2_low_lib.h"
#include "../ultralcd.h"

void lcd_init();
void lcd_update();
// FORCE_INLINE void lcd_setstatus(const char* message) {}
void lcd_setstatus(const char* message);
const char * lcd_getstatus();
void lcd_clearstatus();
void lcd_buttons_update();
FORCE_INLINE void lcd_reset_alert_level() {}
FORCE_INLINE void lcd_buzz(long duration,uint16_t freq) {}

void doCooldown();

// #define LCD_MESSAGEPGM(x)
// #define LCD_ALERTMESSAGEPGM(x)

extern uint8_t led_brightness_level;
extern uint8_t led_mode;
extern float dsp_temperature[EXTRUDERS];
extern float dsp_temperature_bed;
#define LED_MODE_ALWAYS_ON      0
#define LED_MODE_ALWAYS_OFF     1
#define LED_MODE_WHILE_PRINTING 2
#define LED_MODE_BLINK_ON_DONE  3

#define SERIAL_CONTROL_TIMEOUT 2500

#endif

class MarlinUI {
    public:
    FORCE_INLINE static void init() {lcd_init();};
    void set_status(const char* message, const bool=false);
    static void set_status_P(PGM_P const message, const int8_t level=0);
    static void reset_status();
    static void refresh();
    void MarlinUI::update();
    void MarlinUI::update_buttons();

    static inline void set_alert_status_P(PGM_P const) {}

    static inline void reset_alert_level() {}  // 999


    // just for adaput for marlin2
    static constexpr bool wait_for_bl_move = false;
    static constexpr bool has_status() { return false; }
    void status_printf_P(const uint8_t, PGM_P message, ...);
}; 

extern MarlinUI ui;

#endif//ULTI_LCD2_H
