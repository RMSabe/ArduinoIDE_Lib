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

/*This code is a basic driver for generic alphanumeric LCD displays.*/

#ifndef LCD_HPP
#define LCD_HPP

#include "globldef.h"

struct _lcd_info {
	uint8_t db4;
	uint8_t db5;
	uint8_t db6;
	uint8_t db7;
	uint8_t rs;
	uint8_t e;
	uint8_t n_chars;
	uint8_t n_lines;
};

class LCD {
	public:
		LCD(uint8_t db4, uint8_t db5, uint8_t db6, uint8_t db7, uint8_t rs, uint8_t e, uint8_t nCharsPerLine, uint8_t nLines) __PROGMEM_CODE__;
		~LCD(void) __PROGMEM_CODE__;

		/*
		 * begin()
		 *
		 * Initializes LCD object.
		 * returns true if successful, false otherwise.
		 */

		bool begin(void) __PROGMEM_CODE__;

		/*
		 * resetPinout()
		 *
		 * Redefine the GPIO pins connected to the display. (Requires object reinitialization "begin()")
		 */

		void resetPinout(uint8_t db4, uint8_t db5, uint8_t db6, uint8_t db7, uint8_t rs, uint8_t e) __PROGMEM_CODE__;

		/*
		 * resetDisplaySize()
		 *
		 * Redefine the display size (characters per line, number of lines). (Requires object reinitialization "begin()")
		 */

		void resetDisplaySize(uint8_t nCharsPerLine, uint8_t nLines) __PROGMEM_CODE__;

		/*
		 * getStatus()
		 *
		 * returns the current object status.
		 */

		intptr_t getStatus(void) __PROGMEM_CODE__;

		/*
		 * getNCharsPerLine() & getNLines()
		 *
		 * returns the number of characters per line and the number of lines, respectivelly, or -1 if error.
		 */

		int8_t getNCharsPerLine(void) __PROGMEM_CODE__;
		int8_t getNLines(void) __PROGMEM_CODE__;

		/*
		 * setDisplayMode()
		 *
		 * set the display power/cursor view mode.
		 * returns true if successful, false otherwise.
		 */

		bool setDisplayMode(intptr_t displayMode) __PROGMEM_CODE__;

		/*
		 * clear()
		 *
		 * clear the display screen.
		 * returns true if successful, false otherwise.
		 */

		bool clear(void) __PROGMEM_CODE__;

		/*
		 * home()
		 *
		 * set cursor position to (0 , 0)
		 * returns true if successful, false otherwise.
		 */

		bool home(void) __PROGMEM_CODE__;

		/*
		 * setCursorPosition()
		 *
		 * set the cursor position. "cx" horizontal coordinate (character position within a line), "cy" vertical coordinate (line).
		 * returns true if successful, false otherwise.
		 */

		bool setCursorPosition(uint8_t cx, uint8_t cy) __PROGMEM_CODE__;

		/*
		 * printChar()
		 *
		 * print a single character at the current cursor position.
		 * returns true if successful, false otherwise.
		 */

		bool printChar(char c) __PROGMEM_CODE__;

		/*
		 * printText()
		 *
		 * print a text at the current cursor position.
		 * returns true if successful, false otherwise.
		 */

		bool printText(const char *text) __PROGMEM_CODE__;
		bool printText(const char *text, uintptr_t length) __PROGMEM_CODE__;

		/*
		 * fillScreenChar()
		 *
		 * print a repeated character on the whole screen.
		 * returns true if successful, false otherwise.
		 */

		bool fillScreenChar(char c) __PROGMEM_CODE__;

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
		static constexpr uintptr_t _CMD_DELAY_US = 1024u;
		static constexpr uintptr_t _EN_DELAY_US = 1u;

		__attribute__((aligned(PTR_SIZE_BITS))) struct _lcd_info _info;

		__attribute__((aligned(PTR_SIZE_BITS))) intptr_t _status = this->STATUS_UNINITIALIZED;

		void _send_byte(bool reg, uint8_t byte) __PROGMEM_CODE__;
		void _write_nibble(uint8_t nibble) __PROGMEM_CODE__;

		void _send_init_nibble(void) __PROGMEM_CODE__;

		bool _validate_info(void) __PROGMEM_CODE__;

		bool _phys_text_cx_cy_to_virt_text_cx_cy(uint8_t *p_virtcx, uint8_t *p_virtcy, uint8_t physcx, uint8_t physcy) __PROGMEM_CODE__;
};

#endif /*LCD_HPP*/

