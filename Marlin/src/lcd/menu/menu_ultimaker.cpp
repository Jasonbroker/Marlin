#include "../../inc/MarlinConfigPre.h"

#if HAS_LCD_MENU && MOTHERBOARD == BOARD_ULTIMAIN_2

#include "menu.h"
#include "../../gcode/queue.h"

#ifdef USER_SCRIPT_DONE
  #define _DONE_SCRIPT "\n" USER_SCRIPT_DONE
#else
  #define _DONE_SCRIPT ""
#endif

void _lcd_user_gcode(PGM_P const cmd) {
  queue.inject_P(cmd);
  #if ENABLED(USER_SCRIPT_AUDIBLE_FEEDBACK) && HAS_BUZZER
    ui.completion_feedback();
  #endif
  #if ENABLED(USER_SCRIPT_RETURN)
    ui.return_to_status();
  #endif
}

void menu_user() {
  START_MENU();
  BACK_ITEM(MSG_MAIN);
  #if defined(USER_DESC_1) && defined(USER_GCODE_1)
    ACTION_ITEM_P(PSTR(USER_DESC_1), []{ _lcd_user_gcode(PSTR(USER_GCODE_1 _DONE_SCRIPT)); });
  #endif
  #if defined(USER_DESC_2) && defined(USER_GCODE_2)
    ACTION_ITEM_P(PSTR(USER_DESC_2), []{ _lcd_user_gcode(PSTR(USER_GCODE_2 _DONE_SCRIPT)); });
  #endif
  #if defined(USER_DESC_3) && defined(USER_GCODE_3)
    ACTION_ITEM_P(PSTR(USER_DESC_3), []{ _lcd_user_gcode(PSTR(USER_GCODE_3 _DONE_SCRIPT)); });
  #endif
  #if defined(USER_DESC_4) && defined(USER_GCODE_4)
    ACTION_ITEM_P(PSTR(USER_DESC_4), []{ _lcd_user_gcode(PSTR(USER_GCODE_4 _DONE_SCRIPT)); });
  #endif
  #if defined(USER_DESC_5) && defined(USER_GCODE_5)
    ACTION_ITEM_P(PSTR(USER_DESC_5), []{ _lcd_user_gcode(PSTR(USER_GCODE_5 _DONE_SCRIPT)); });
  #endif
  END_MENU();
}

#endif

