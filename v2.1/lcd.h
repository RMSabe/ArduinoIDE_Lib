/*
 * Basic Resources to ease development on Arduino IDE.
 * Version 2.1
 *
 * "config.h" is the macro configuration file. Developers may change some macro definitions. "config.h" is included in "globldef.h" file.
 * "globldef.h" is the global definitions file. It should be the first file included in every subsequent file.
 *
 * GitHub Repository: https://github.com/RMSabe/ArduinoIDE_Lib
 *
 * Author: Rafael Sabe
 * Email: rafaelmsabe@gmail.com
 */

#ifndef LCD_H
#define LCD_H 1

#include "globldef.h"

#define LCD_DISPLAYMODE_DISPLAY_OFF 0
#define LCD_DISPLAYMODE_DISPLAY_ON_CURSOR_OFF 1
#define LCD_DISPLAYMODE_DISPLAY_ON_CURSOR_ON 2
#define LCD_DISPLAYMODE_DISPLAY_ON_CURSOR_BLINK 3

/*
 * lcd_t : LCD object
 * Each LCD object contains the enable GPIO pin for that LCD, along with the number of characters per line and number of lines.
 *
 * LCD data GPIO pins, and RS GPIO pin are set by calling lcd_drv_init().
 * These pins are the same for all LCDs.
 */

struct _lcd {
	uint8_t gpio_e;		/*LCD Enable GPIO Pin*/
	uint8_t n_chars;	/*LCD Number of characters per line*/
	uint8_t n_lines;	/*LCD Number of lines*/
};

typedef struct _lcd lcd_t;

/*
 * lcd_drv_init()
 * Initializes the LCD driver GPIO pins.
 * Set the data and RS GPIO pins.
 * Must be called before calling any other functions in this driver.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_drv_init(uint8_t gpio_db4, uint8_t gpio_db5, uint8_t gpio_db6, uint8_t gpio_db7, uint8_t gpio_rs) __PROGMEM_CODE__;

/*
 * lcd_drv_deinit()
 * Deinitializes the LCD driver GPIO pins.
 * Requires reinitialization (lcd_drv_init()) for afterwards usage of driver.
 */

__EXTERNC__ void lcd_drv_deinit(void) __PROGMEM_CODE__;

/*
 * lcd_init()
 * Initializes the LCD object.
 * Must be called before using an LCD.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_init(lcd_t *p_lcd) __PROGMEM_CODE__;

/*
 * lcd_deinit()
 * Deinitializes the LCD enable GPIO pin.
 * Requires reinitialization (lcd_init()) if LCD is to be used again.
 */

__EXTERNC__ void lcd_deinit(lcd_t *p_lcd) __PROGMEM_CODE__;

/*
 * lcd_set_display_mode()
 * Set the LCD display on/off and cursor mode.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_set_display_mode(lcd_t *p_lcd, int8_t display_mode) __PROGMEM_CODE__;

/*
 * lcd_clear()
 * Clear the LCD screen.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_clear(lcd_t *p_lcd) __PROGMEM_CODE__;

/*
 * lcd_home()
 * Reset the LCD cursor position to (0, 0).
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_home(lcd_t *p_lcd) __PROGMEM_CODE__;

/*
 * lcd_move_cursor_left() & lcd_move_cursor_right()
 * Moves the LCD cursor a specific number of characters to the left or to the right.
 * "move_count": number of characters to move the cursor.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_move_cursor_left(lcd_t *p_lcd, uint8_t move_count) __PROGMEM_CODE__;
__EXTERNC__ bool lcd_move_cursor_right(lcd_t *p_lcd, uint8_t move_count) __PROGMEM_CODE__;

/*
 * lcd_set_cursor_position()
 * Sets the LCD cursor position.
 * cx: horizontal offset (character position within a line)
 * cy: vertical offset (line position)
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_set_cursor_position(lcd_t *p_lcd, uint8_t cx, uint8_t cy) __PROGMEM_CODE__;

/*
 * lcd_scroll_left() & lcd_scroll_right()
 * Scroll the LCD text a specific number of characters to the left or to the right.
 * "scroll_count": number of characters to scroll the text.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_scroll_left(lcd_t *p_lcd, uint8_t scroll_count) __PROGMEM_CODE__;
__EXTERNC__ bool lcd_scroll_right(lcd_t *p_lcd, uint8_t scroll_count) __PROGMEM_CODE__;

/*
 * lcd_print_char()
 * Prints a single character at the LCD current cursor position.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_print_char(lcd_t *p_lcd, char c) __PROGMEM_CODE__;

/*
 * lcd_print_text()
 * Prints a C-style null-terminated string at the LCD current cursor position.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_print_text(lcd_t *p_lcd, const char *text) __PROGMEM_CODE__;

/*
 * lcd_print_text_len()
 * Prints a C-style string of specified length at the LCD current cursor position.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_print_text_len(lcd_t *p_lcd, const char *text, uintptr_t length) __PROGMEM_CODE__;

/*
 * lcd_fill_screen_char()
 * Fills the LCD screen with a single given character.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool lcd_fill_screen_char(lcd_t *p_lcd, char c) __PROGMEM_CODE__;

#endif /*LCD_H*/

