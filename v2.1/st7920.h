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

/*This code is a basic driver for the ST7920 monochromatic graphic LCD controller. (Standard 128x64 displays only!).*/

#ifndef ST7920_H
#define ST7920_H 1

#include "globldef.h"

/*INTERNAL USAGE MACROS*/

#define __ST7920_PAGE_SIZE_BYTES 2U
#define __ST7920_PAGE_WIDTH_PIXELS (__ST7920_PAGE_SIZE_BYTES*8U)

#define __ST7920_VIRT_WIDTH_PAGES 16U
#define __ST7920_VIRT_WIDTH_PIXELS (__ST7920_VIRT_WIDTH_PAGES*__ST7920_PAGE_WIDTH_PIXELS)
#define __ST7920_VIRT_HEIGHT_PIXELS 32U

#define __ST7920_VRAM_SIZE_PAGES (__ST7920_VIRT_WIDTH_PAGES*__ST7920_VIRT_HEIGHT_PIXELS)
#define __ST7920_VRAM_SIZE_BYTES (__ST7920_VRAM_SIZE_PAGES*__ST7920_PAGE_SIZE_BYTES)

#define __ST7920_VIRT_N_WCHARS 16U
#define __ST7920_VIRT_N_CHARS (__ST7920_VIRT_N_WCHARS*2U)
#define __ST7920_VIRT_N_LINES 2U

#define __ST7920_PHYS_WIDTH_PAGES (__ST7920_VIRT_WIDTH_PAGES/2U)
#define __ST7920_PHYS_WIDTH_PIXELS (__ST7920_VIRT_WIDTH_PIXELS/2U)
#define __ST7920_PHYS_HEIGHT_PIXELS (__ST7920_VIRT_HEIGHT_PIXELS*2U)

#define __ST7920_PHYS_N_WCHARS (__ST7920_VIRT_N_WCHARS/2U)
#define __ST7920_PHYS_N_CHARS (__ST7920_VIRT_N_CHARS/2U)
#define __ST7920_PHYS_N_LINES (__ST7920_VIRT_N_LINES*2U)

/*USER MACROS*/

#define ST7920_WIDTH __ST7920_PHYS_WIDTH_PIXELS
#define ST7920_HEIGHT __ST7920_PHYS_HEIGHT_PIXELS

#define ST7920_WIDTH_PAGES __ST7920_PHYS_WIDTH_PAGES

#define ST7920_N_WCHARS __ST7920_PHYS_N_WCHARS
#define ST7920_N_CHARS __ST7920_PHYS_N_CHARS
#define ST7920_N_LINES __ST7920_PHYS_N_LINES

#define ST7920_DISPLAYMODE_DISPLAY_OFF 0
#define ST7920_DISPLAYMODE_DISPLAY_ON_CURSOR_OFF 1
#define ST7920_DISPLAYMODE_DISPLAY_ON_CURSOR_ON 2
#define ST7920_DISPLAYMODE_DISPLAY_ON_CURSOR_BLINK 3

/*
 * st7920_t : ST7920 object
 * Each ST7920 LCD object contains the enable GPIO pin for that ST7920 controller.
 *
 * ST7920 data GPIO pins, and RS GPIO pin are set by calling st7920_drv_init().
 * These pins are the same for all LCD/ST7920 Controllers.
 *
 * This driver version does not use ST7920 RW pin. Connect it to 0V.
 */

struct _st7920 {
	__attribute__((__aligned__(16))) uint16_t _vram_buffer[__ST7920_VRAM_SIZE_PAGES]; /*Reserved for internal usage*/
	uint8_t _graphic_display_enabled; /*Reserved for internal usage*/
	uint8_t gpio_e; /*ST7920 Enable GPIO pin*/
};

typedef struct _st7920 st7920_t;

/*
 * st7920_drv_init()
 * Initializes the ST7920 data and RS GPIO pins.
 * Must be called before calling any other functions in this driver.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_drv_init(uint8_t gpio_db0, uint8_t gpio_db1, uint8_t gpio_db2, uint8_t gpio_db3, uint8_t gpio_db4, uint8_t gpio_db5, uint8_t gpio_db6, uint8_t gpio_db7, uint8_t gpio_rs) __PROGMEM_CODE__;

/*
 * st7920_drv_deinit()
 * Deinitializes the ST7920 data and RS GPIO pins.
 * Requires reinitialization (st7920_drv_init()) for afterwards usage of driver.
 */

__EXTERNC__ void st7920_drv_deinit(void) __PROGMEM_CODE__;

/*
 * st7920_init()
 * Initializes the ST7920 LCD object.
 * Must be called before using an ST7920.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_init(st7920_t *p_st7920) __PROGMEM_CODE__;

/*
 * st7920_deinit()
 * Deinitializes the ST7920 enable GPIO pin.
 * Requires object reinitialization (st7920_init()) if ST7920 is to be used again.
 */

__EXTERNC__ void st7920_deinit(st7920_t *p_st7920) __PROGMEM_CODE__;

/*
 * st7920_enable_graphic_display()
 * Enables/Disables ST7920 graphic resources.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_enable_graphic_display(st7920_t *p_st7920, bool enable) __PROGMEM_CODE__;

/*
 * st7920_graphic_display_is_enabled()
 * Check if ST7920 graphic resources are currently enabled.
 *
 * returns 1 if enabled, 0 if disabled, -1 if error.
 */

__EXTERNC__ int8_t st7920_graphic_display_is_enabled(st7920_t *p_st7920) __PROGMEM_CODE__;

/*
 * st7920_buffer_set_pixel()
 * set the value (on/off) of a single pixel in the buffer at coordinates (cx, cy).
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_buffer_set_pixel(st7920_t *p_st7920, uint16_t cx, uint16_t cy, bool lit) __PROGMEM_CODE__;

/*
 * st7920_buffer_get_pixel()
 * check the value (on/off) of a single pixel in the buffer at coordinates (cx, cy).
 *
 * returns 1 if on, 0 if off, -1 if error.
 */

__EXTERNC__ int8_t st7920_buffer_get_pixel(st7920_t *p_st7920, uint16_t cx, uint16_t cy) __PROGMEM_CODE__;

/*
 * st7920_buffer_toggle_pixel()
 * toggle the value (on/off) of a single pixel in the buffer at coordinates (cx, cy).
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_buffer_toggle_pixel(st7920_t *p_st7920, uint16_t cx, uint16_t cy) __PROGMEM_CODE__;

/*
 * st7920_buffer_set_page()
 * set the value of a page of pixels in the buffer at coordinates (page_index, cy).
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_buffer_set_page(st7920_t *p_st7920, uint16_t page_index, uint16_t cy, uint16_t page_value) __PROGMEM_CODE__;

/*
 * st7920_buffer_get_page()
 * get the value of a page of pixels in the buffer at coordinates (page_index, cy).
 *
 * returns page value if successful, or -1 if error.
 */

__EXTERNC__ int32_t st7920_buffer_get_page(st7920_t *p_st7920, uint16_t page_index, uint16_t cy) __PROGMEM_CODE__;

/*
 * st7920_buffer_toggle_page()
 * toggles the bits specified by "toggle_mask" of a pixel page value in the buffer at coordinates (page_index, cy).
 *
 * (page new value) = (page current value) XOR (toggle_mask)
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_buffer_toggle_page(st7920_t *p_st7920, uint16_t page_index, uint16_t cy, uint16_t toggle_mask) __PROGMEM_CODE__;

/*
 * st7920_buffer_set_all()
 * set the value (on/off) for all the pixels in the buffer.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_buffer_set_all(st7920_t *p_st7920, bool lit) __PROGMEM_CODE__;

/*
 * st7920_buffer_toggle_all()
 * toggle the value (on/off) for all the pixels in the buffer.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_buffer_toggle_all(st7920_t *p_st7920) __PROGMEM_CODE__;

/*
 * st7920_buffer_paint_pixel() & st7920_buffer_paint_page()
 * paint a specific page of pixels in the buffer to the ST7920 display. (pixel coordinates (cx, cy) / page coordinates(page_index, cy)).
 *
 * st7920_buffer_paint_pixel(): Although the function takes a single pixel coordinate, the entire page in the buffer will be painted, not just the single pixel.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_buffer_paint_pixel(st7920_t *p_st7920, uint16_t cx, uint16_t cy) __PROGMEM_CODE__;
__EXTERNC__ bool st7920_buffer_paint_page(st7920_t *p_st7920, uint16_t page_index, uint16_t cy) __PROGMEM_CODE__;

/*
 * st7920_buffer_paint_all()
 * paint the whole pixel page buffer to the ST7920 display.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_buffer_paint_all(st7920_t *p_st7920) __PROGMEM_CODE__;

/*
 * st7920_clear_graphics()
 * clear the pixel page buffer and the ST7920 display graphic content.
 * basically calls st7920_buffer_set_all(), then st7920_buffer_paint_all().
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_clear_graphics(st7920_t *p_st7920) __PROGMEM_CODE__;

/*
 * st7920_set_display_mode()
 * set the ST7920 display on/off and cursor view modes.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_set_display_mode(st7920_t *p_st7920, int8_t display_mode) __PROGMEM_CODE__;

/*
 * st7920_clear_text()
 * clear the ST7920 display text content.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_clear_text(st7920_t *p_st7920) __PROGMEM_CODE__;

/*
 * st7920_cursor_home()
 * set the ST7920 display text cursor position to (0, 0).
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_cursor_home(st7920_t *p_st7920) __PROGMEM_CODE__;

/*
 * st7920_move_text_cursor_left() & st7920_move_text_cursor_right()
 * move the ST7920 display text cursor to the left or to the right.
 * cursor moves by a specific number of wide-character units (move_count).
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_move_text_cursor_left(st7920_t *p_st7920, uint8_t move_count) __PROGMEM_CODE__;
__EXTERNC__ bool st7920_move_text_cursor_right(st7920_t *p_st7920, uint8_t move_count) __PROGMEM_CODE__;

/*
 * st7920_set_text_cursor_position() & st7920_set_wtext_cursor_position()
 * set the ST7920 display text cursor position.
 *
 * st7920_set_text_cursor_position: (cx = character position within a line / cy = line position).
 * st7920_set_wtext_cursor_position: (cx = wide-character position within a line / cy = line position).
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_set_text_cursor_position(st7920_t *p_st7920, uint8_t cx, uint8_t cy) __PROGMEM_CODE__;
__EXTERNC__ bool st7920_set_wtext_cursor_position(st7920_t *p_st7920, uint8_t cx, uint8_t cy) __PROGMEM_CODE__;

/*
 * st7920_scroll_text_left() & st7920_scroll_text_right()
 * scroll the ST7920 display text content to the left or to the right.
 * content moves by a specific number of wide-character units (scroll_count).
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_scroll_text_left(st7920_t *p_st7920, uint8_t scroll_count) __PROGMEM_CODE__;
__EXTERNC__ bool st7920_scroll_text_right(st7920_t *p_st7920, uint8_t scroll_count) __PROGMEM_CODE__;

/*
 * st7920_print_char() & st7920_print_wchar()
 * print a single character or GB2312 wide-character at the ST7920 display current text cursor position.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_print_char(st7920_t *p_st7920, char c) __PROGMEM_CODE__;
__EXTERNC__ bool st7920_print_wchar(st7920_t *p_st7920, uint16_t wc) __PROGMEM_CODE__;

/*
 * st7920_print_text() & st7920_print_wtext()
 * print a C-style null-terminated string of characters or GB2312 wide-characters at the ST7920 display current text cursor position.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_print_text(st7920_t *p_st7920, const char *text) __PROGMEM_CODE__;
__EXTERNC__ bool st7920_print_wtext(st7920_t *p_st7920, const uint16_t *wtext) __PROGMEM_CODE__;

/*
 * st7920_print_text_len() & st7920_print_wtext_len()
 * print a C-style string of characters or GB2312 wide-characters, with specified length, at the ST7920 display current text cursor position.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_print_text_len(st7920_t *p_st7920, const char *text, uintptr_t length) __PROGMEM_CODE__;
__EXTERNC__ bool st7920_print_wtext_len(st7920_t *p_st7920, const uint16_t *wtext, uintptr_t length) __PROGMEM_CODE__;

/*
 * st7920_fill_screen_char() & st7920_fill_screen_wchar()
 * fills the whole ST7920 display text content with a repeated character or GB2312 wide-character.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_fill_screen_char(st7920_t *p_st7920, char c) __PROGMEM_CODE__;
__EXTERNC__ bool st7920_fill_screen_wchar(st7920_t *p_st7920, uint16_t wc) __PROGMEM_CODE__;

/*
 * st7920_clear_display()
 * clear the ST7920 display text and graphic content.
 *
 * returns true if successful, false if error.
 */

__EXTERNC__ bool st7920_clear_display(st7920_t *p_st7920) __PROGMEM_CODE__;

#endif /*ST7920_H*/

