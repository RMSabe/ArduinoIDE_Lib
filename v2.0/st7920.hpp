/*
 * Basic Resources to ease development on Arduino IDE.
 * Version 2.0
 *
 * "config.h" is the macro configuration file. Developers may change some macro definitions. "config.h" is included in "globldef.h" file.
 * "globldef.h" is the global definitions file. It should be the first file included in every subsequent file.
 *
 * GitHub Repository: https://github.com/RMSabe/ArduinoIDE_Lib
 *
 * Author: Rafael Sabe
 * Email: rafaelmsabe@gmail.com
 */

/*This code is a basic driver for the ST7920 monochromatic graphic LCD controller. (Standard 128x64 displays only!)*/

#ifndef ST7920_HPP
#define ST7920_HPP

#include "globldef.h"

struct _st7920_pinout {
	uint8_t db0;
	uint8_t db1;
	uint8_t db2;
	uint8_t db3;
	uint8_t db4;
	uint8_t db5;
	uint8_t db6;
	uint8_t db7;
	uint8_t rs;
	uint8_t rw; /*UNUSED*/
	uint8_t e;
	uint8_t reserved[5];
};

class ST7920 {
	public:
		ST7920(uint8_t db0, uint8_t db1, uint8_t db2, uint8_t db3, uint8_t db4, uint8_t db5, uint8_t db6, uint8_t db7, uint8_t rs, uint8_t e) __PROGMEM_CODE__;
		~ST7920(void) __PROGMEM_CODE__;

		/* begin()
		 * Initializes the st7920 object. Must be called before calling any other methods.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool begin(void) __PROGMEM_CODE__;

		/*
		 * resetPinout()
		 * Sets the new pin layout for the display. Requires reinitialization ("begin()").
		 */

		void resetPinout(uint8_t db0, uint8_t db1, uint8_t db2, uint8_t db3, uint8_t db4, uint8_t db5, uint8_t db6, uint8_t db7, uint8_t rs, uint8_t e) __PROGMEM_CODE__;

		/*
		 * getStatus()
		 * Returns the current object status value.
		 */

		intptr_t getStatus(void) __PROGMEM_CODE__;

		/*
		 * enableGraphicDisplay()
		 * Set graphic display to be on/off.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool enableGraphicDisplay(bool enable) __PROGMEM_CODE__;

		/*
		 * graphicDisplayIsEnabled()
		 *
		 * returns 1 if graphic display is on, 0 if graphic display is off, -1 if error.
		 */

		intptr_t graphicDisplayIsEnabled(void) __PROGMEM_CODE__;

		/*
		 * bufferSetPixel()
		 *
		 * Sets the value (on/off) of a single pixel in the buffer (coordinates cx , cy).
		 *
		 * returns true if successful, false otherwise.
		 */

		bool bufferSetPixel(uintptr_t cx, uintptr_t cy, bool lit) __PROGMEM_CODE__;

		/*
		 * bufferGetPixel()
		 *
		 * Gets the current value (on/off) of a single pixel in the buffer (coordinates cx , cy).
		 *
		 * returns 1 if pixel is on, 0 if pixel is off, -1 if error.
		 */

		intptr_t bufferGetPixel(uintptr_t cx, uintptr_t cy) __PROGMEM_CODE__;

		/*
		 * bufferTogglePixel()
		 *
		 * Toggles the current value (on/off) of a single pixel in the buffer (coordinates cx , cy).
		 *
		 * returns true if successful, false otherwise.
		 */

		bool bufferTogglePixel(uintptr_t cx, uintptr_t cy) __PROGMEM_CODE__;

		/*
		 * bufferSetPage()
		 *
		 * Sets the value of a page of pixels in the buffer (coordinates page_index , cy)
		 *
		 * returns true if successful, false otherwise.
		 */

		bool bufferSetPage(uintptr_t page_index, uintptr_t cy, uint16_t page_value) __PROGMEM_CODE__;

		/*
		 * bufferGetPage()
		 *
		 * Gets the current value of a page of pixels in the buffer (coordinates page_index , cy)
		 *
		 * returns uint16_t page value if successful, -1 otherwise.
		 */

		int32_t bufferGetPage(uintptr_t page_index, uintptr_t cy) __PROGMEM_CODE__;

		/*
		 * bufferTogglePage()
		 *
		 * Toggles the current value of a page of pixels in the buffer using the specified value (new value = old value ^ toggle value). (coordinates page_index , cy)
		 *
		 * returns true if successful, false otherwise
		 */

		bool bufferTogglePage(uintptr_t page_index, uintptr_t cy, uint16_t toggle_value) __PROGMEM_CODE__;

		/*
		 * bufferSetAll()
		 *
		 * Sets the value (on/off) for all pixels in the buffer.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool bufferSetAll(bool lit) __PROGMEM_CODE__;

		/*
		 * bufferToggleAll()
		 *
		 * Toggles the current pixel value (on/off) of every pixel in the buffer.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool bufferToggleAll(void) __PROGMEM_CODE__;

		/*
		 * bufferPaintPixel() & bufferPaintPage()
		 *
		 * Paints to the display the page value currently in the buffer. bufferPaintPage() takes the coordinates of the page (page_index , cy), whereas
		 * bufferPaintPixel() takes the coordinates (cx , cy) of a pixel within that page.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool bufferPaintPixel(uintptr_t cx, uintptr_t cy) __PROGMEM_CODE__;
		bool bufferPaintPage(uintptr_t page_index, uintptr_t cy) __PROGMEM_CODE__;

		/*
		 * bufferPaintAll()
		 *
		 * Paints the whole buffer to the display.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool bufferPaintAll(void) __PROGMEM_CODE__;

		/*
		 * clearGraphics()
		 *
		 * Clears all the pixels on both buffer and display. (Does not affect text).
		 *
		 * returns true if successful, false otherwise.
		 */

		bool clearGraphics(void) __PROGMEM_CODE__;

		/*
		 * setDisplayMode()
		 *
		 * Sets the display current state.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool setDisplayMode(intptr_t display_mode) __PROGMEM_CODE__;

		/*
		 * clearText()
		 *
		 * Clear any text on the display. (Does not affect graphics).
		 *
		 * returns true if successful, false otherwise.
		 */

		bool clearText(void) __PROGMEM_CODE__;

		/*
		 * cursorHome()
		 *
		 * Sets the text cursor position to 0 , 0 (first character, first line)
		 *
		 * returns true if successful, false otherwise.
		 */

		bool cursorHome(void) __PROGMEM_CODE__;

		/*
		 * setTextCursorPosition() & setWTextCursorPosition()
		 *
		 * Sets the text cursor position on display
		 *
		 * returns true if successful, false otherwise.
		 */

		bool setTextCursorPosition(uintptr_t cx, uintptr_t cy) __PROGMEM_CODE__;
		bool setWTextCursorPosition(uintptr_t cx, uintptr_t cy) __PROGMEM_CODE__;

		/*
		 * printChar()
		 *
		 * Prints a single character on display at the current cursor position.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool printChar(char c) __PROGMEM_CODE__;

		/*
		 * printText()
		 *
		 * Prints a text on display at the current cursor position.
		 * printText(const char *text) requires a null terminator character '\0' at the end.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool printText(const char *text) __PROGMEM_CODE__;
		bool printText(const char *text, uintptr_t length) __PROGMEM_CODE__;

		/*
		 * printWChar()
		 *
		 * Prints a single 16bit character (GB Character Code) at the current cursor position (Must be a valid wide char cursor position!).
		 *
		 * returns true if successful, false otherwise.
		 */

		bool printWChar(uint16_t wc) __PROGMEM_CODE__;

		/*
		 * printWText()
		 *
		 * Prints a 16bit character (GB Character Code) text at the current cursor position (Must be a valid wide char cursor position!).
		 * printWText(const uint16_t *wtext) requires a 16bit null terminator value '\0' at the end.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool printWText(const uint16_t *wtext) __PROGMEM_CODE__;
		bool printWText(const uint16_t *wtext, uintptr_t length) __PROGMEM_CODE__;

		/*
		 * fillScreenChar() & fillScreenWChar()
		 *
		 * Fills the display screen with a given 8bit ascii character or a 16bit GB character.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool fillScreenChar(char c) __PROGMEM_CODE__;
		bool fillScreenWChar(uint16_t wc) __PROGMEM_CODE__;

		/*
		 * clearDisplay()
		 *
		 * Clears both text and graphics.
		 *
		 * returns true if successful, false otherwise.
		 */

		bool clearDisplay(void) __PROGMEM_CODE__;

		enum Status {
			STATUS_ERROR = -1,
			STATUS_UNINITIALIZED = 0,
			STATUS_INITIALIZED = 1
		};

		enum DisplayMode {
			DISPLAYMODE_DISPLAY_OFF = 0,
			DISPLAYMODE_DISPLAY_ON_CURSOR_OFF = 1,
			DISPLAYMODE_DISPLAY_ON_CURSOR_ON = 2,
			DISPLAYMODE_DISPLAY_ON_CURSOR_BLINK = 3
		};

	private:
		static constexpr uintptr_t _PAGE_SIZE_PIXELS = 16u;
		static constexpr uintptr_t _PAGE_SIZE_BYTES = 2u;
		static constexpr uintptr_t _HEIGHT_PIXELS = 32u;
		static constexpr uintptr_t _WIDTH_PIXELS = 256u;
		static constexpr uintptr_t _WIDTH_PAGES = _WIDTH_PIXELS/_PAGE_SIZE_PIXELS;
		static constexpr uintptr_t _BUFFER_SIZE_PAGES = _WIDTH_PAGES*_HEIGHT_PIXELS;
		static constexpr uintptr_t _BUFFER_SIZE_BYTES = _BUFFER_SIZE_PAGES*_PAGE_SIZE_BYTES;

		static constexpr uintptr_t _N_WCHARS = 16u;
		static constexpr uintptr_t _N_LINES = 2u;
		static constexpr uintptr_t _N_CHARS = 2u*_N_WCHARS;

		static constexpr uintptr_t _CMD_LONG_DELAY_US = 1024u;
		static constexpr uintptr_t _CMD_SHORT_DELAY_US = 128u;
		static constexpr uintptr_t _EN_DELAY_US = 1u;

		static constexpr uint8_t _BASIC_INSTRUCTION_BYTE = 0x30;
		static constexpr uint8_t _EXT_INSTRUCTION_BYTE = 0x34;
		static constexpr uint8_t _GRAPHIC_DISPLAY_ENABLE_BIT = 0x02;

		__attribute__((aligned(PTR_SIZE_BITS))) struct _st7920_pinout _pins;
		__attribute__((aligned(PTR_SIZE_BITS))) uint16_t _page_buffer[_BUFFER_SIZE_PAGES];

		__attribute__((aligned(PTR_SIZE_BITS))) intptr_t _status = this->STATUS_UNINITIALIZED;

		bool _graphic_display_enabled = false;

		void _set_instruction_mode(bool ext) __PROGMEM_CODE__;

		void _send_byte(bool reg, uint8_t byte, uintptr_t cmddelay_us) __PROGMEM_CODE__;
		void _write_byte(uint8_t byte) __PROGMEM_CODE__;

		void _set_dataline_mode(bool output) __PROGMEM_CODE__;

		bool _validate_pins(void) __PROGMEM_CODE__;

		bool _phys_cx_cy_to_virt_bufindex_pageindex_cy_offset(uintptr_t cx, uintptr_t cy, uintptr_t *p_bufferindex, uintptr_t *p_pageindex, uintptr_t *p_cy, uintptr_t *p_offset) __PROGMEM_CODE__;
		bool _phys_pageindex_cy_to_virt_bufindex_pageindex_cy(uintptr_t page_index, uintptr_t cy, uintptr_t *p_bufferindex, uintptr_t *p_pageindex, uintptr_t *p_cy) __PROGMEM_CODE__;

		bool _phys_text_cx_cy_to_virt_wtext_cx_cy_addspace(uintptr_t cx, uintptr_t cy, uintptr_t *p_cx, uintptr_t *p_cy, bool *p_addspace) __PROGMEM_CODE__;
		bool _phys_wtext_cx_cy_to_virt_wtext_cx_cy(uintptr_t cx, uintptr_t cy, uintptr_t *p_cx, uintptr_t *p_cy) __PROGMEM_CODE__;

	public:
		/*
		 * Display Size Constants:
		 * Display is 128x64 pixels.
		 * Pixels are organized in pages.
		 * A Page is 16 horizontal adjancent pixels.
		 *
		 * WIDTH = 128 (pixels wide)
		 * HEIGHT = 64 (pixels tall)
		 * WIDTH_PAGES = 8 (16 pixel pages wide)
		 *
		 * N_CHARS = 16 (8bit ASCII characters per line)
		 * N_LINES = 4 (number of text lines on display)
		 * N_WCHARS = 8 (16bit GB wide characters per line)
		 */

		static constexpr uintptr_t WIDTH = _WIDTH_PIXELS/2u;
		static constexpr uintptr_t HEIGHT = _HEIGHT_PIXELS*2u;
		static constexpr uintptr_t WIDTH_PAGES = _WIDTH_PAGES/2u;

		static constexpr uintptr_t N_CHARS = _N_CHARS/2u;
		static constexpr uintptr_t N_LINES = _N_LINES*2u;
		static constexpr uintptr_t N_WCHARS = _N_WCHARS/2u;
};

#endif /*ST7920_HPP*/

