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

#include "lcd.h"
#include "cstrdef.h"

#define __LCD_CMD_DELAY_US 2048U
#define __LCD_EN_DELAY_US 1U

#define __LCD_GPIO_INVALID ((uint8_t) -1)

struct __lcd_drv_info {
	uint8_t gpio_db4;
	uint8_t gpio_db5;
	uint8_t gpio_db6;
	uint8_t gpio_db7;
	uint8_t gpio_rs;
};

typedef struct __lcd_drv_info _lcd_drv_info_t;

static _lcd_drv_info_t _lcd_drv_info = {
	.gpio_db4 = __LCD_GPIO_INVALID,
	.gpio_db5 = __LCD_GPIO_INVALID,
	.gpio_db6 = __LCD_GPIO_INVALID,
	.gpio_db7 = __LCD_GPIO_INVALID,
	.gpio_rs = __LCD_GPIO_INVALID
};

static bool _lcd_drv_initialized = false;

static void _lcd_send_byte(lcd_t *p_lcd, uint8_t reg, uint8_t byte) __PROGMEM_CODE__;
static void _lcd_write_nibble(uint8_t nibble) __PROGMEM_CODE__;
static void _lcd_send_init_nibble(lcd_t *p_lcd) __PROGMEM_CODE__;
static void _lcd_move_cursordisplay_leftright(lcd_t *p_lcd, uint8_t move_display, uint8_t move_right, uint8_t move_count) __PROGMEM_CODE__;

static bool _lcd_drv_validate_info(void) __PROGMEM_CODE__;
static bool _lcd_validate_ctx(lcd_t *p_lcd) __PROGMEM_CODE__;
static bool _lcd_phys_text_cxcy_to_virt_text_cxcy(lcd_t *p_lcd, uint8_t *p_virtcx, uint8_t *p_virtcy, uint8_t phys_cx, uint8_t phys_cy) __PROGMEM_CODE__;

__PROGMEM_CODE__ bool lcd_drv_init(uint8_t gpio_db4, uint8_t gpio_db5, uint8_t gpio_db6, uint8_t gpio_db7, uint8_t gpio_rs)
{
	_lcd_drv_initialized = false;

	_lcd_drv_info.gpio_db4 = gpio_db4;
	_lcd_drv_info.gpio_db5 = gpio_db5;
	_lcd_drv_info.gpio_db6 = gpio_db6;
	_lcd_drv_info.gpio_db7 = gpio_db7;
	_lcd_drv_info.gpio_rs = gpio_rs;

	if(!_lcd_drv_validate_info()) return false;

	pinMode(gpio_db4, OUTPUT);
	pinMode(gpio_db5, OUTPUT);
	pinMode(gpio_db6, OUTPUT);
	pinMode(gpio_db7, OUTPUT);
	pinMode(gpio_rs, OUTPUT);

	_lcd_drv_initialized = true;
	return true;
}

__PROGMEM_CODE__ void lcd_drv_deinit(void)
{
	_lcd_drv_initialized = false;

	if(_lcd_drv_info.gpio_db4 != __LCD_GPIO_INVALID) pinMode(_lcd_drv_info.gpio_db4, INPUT);
	if(_lcd_drv_info.gpio_db5 != __LCD_GPIO_INVALID) pinMode(_lcd_drv_info.gpio_db5, INPUT);
	if(_lcd_drv_info.gpio_db6 != __LCD_GPIO_INVALID) pinMode(_lcd_drv_info.gpio_db6, INPUT);
	if(_lcd_drv_info.gpio_db7 != __LCD_GPIO_INVALID) pinMode(_lcd_drv_info.gpio_db7, INPUT);
	if(_lcd_drv_info.gpio_rs != __LCD_GPIO_INVALID) pinMode(_lcd_drv_info.gpio_rs, INPUT);

	return;
}

__PROGMEM_CODE__ bool lcd_init(lcd_t *p_lcd)
{
	if(!_lcd_validate_ctx(p_lcd)) return false;

	pinMode(p_lcd->gpio_e, OUTPUT);
	digitalWrite(p_lcd->gpio_e, 0);

	_lcd_send_init_nibble(p_lcd);
	_lcd_send_byte(p_lcd, 0, 0x28);
	_lcd_send_byte(p_lcd, 0, 0x01);
	_lcd_send_byte(p_lcd, 0, 0x80);
	_lcd_send_byte(p_lcd, 0, 0x0c);

	return true;
}

__PROGMEM_CODE__ void lcd_deinit(lcd_t *p_lcd)
{
	if(p_lcd == NULL) return;
	if(p_lcd->gpio_e != __LCD_GPIO_INVALID) pinMode(p_lcd->gpio_e, INPUT);

	return;
}

__PROGMEM_CODE__ bool lcd_set_display_mode(lcd_t *p_lcd, int8_t display_mode)
{
	if(!_lcd_validate_ctx(p_lcd)) return false;

	switch(display_mode)
	{
		case LCD_DISPLAYMODE_DISPLAY_OFF:
			_lcd_send_byte(p_lcd, 0, 0x08);
			return true;

		case LCD_DISPLAYMODE_DISPLAY_ON_CURSOR_OFF:
			_lcd_send_byte(p_lcd, 0, 0x0c);
			return true;

		case LCD_DISPLAYMODE_DISPLAY_ON_CURSOR_ON:
			_lcd_send_byte(p_lcd, 0, 0x0e);
			return true;

		case LCD_DISPLAYMODE_DISPLAY_ON_CURSOR_BLINK:
			_lcd_send_byte(p_lcd, 0, 0x0f);
			return true;
	}

	return false;
}

__PROGMEM_CODE__ bool lcd_clear(lcd_t *p_lcd)
{
	if(!_lcd_validate_ctx(p_lcd)) return false;

	_lcd_send_byte(p_lcd, 0, 0x01);
	return true;
}

__PROGMEM_CODE__ bool lcd_home(lcd_t *p_lcd)
{
	if(!_lcd_validate_ctx(p_lcd)) return false;

	_lcd_send_byte(p_lcd, 0, 0x02);
	return true;
}

__PROGMEM_CODE__ bool lcd_move_cursor_left(lcd_t *p_lcd, uint8_t move_count)
{
	if(!_lcd_validate_ctx(p_lcd)) return false;

	_lcd_move_cursordisplay_leftright(p_lcd, 0, 0, move_count);
	return true;
}

__PROGMEM_CODE__ bool lcd_move_cursor_right(lcd_t *p_lcd, uint8_t move_count)
{
	if(!_lcd_validate_ctx(p_lcd)) return false;

	_lcd_move_cursordisplay_leftright(p_lcd, 0, 1, move_count);
	return true;
}

__PROGMEM_CODE__ bool lcd_set_cursor_position(lcd_t *p_lcd, uint8_t cx, uint8_t cy)
{
	if(!_lcd_validate_ctx(p_lcd)) return false;
	if(!_lcd_phys_text_cxcy_to_virt_text_cxcy(p_lcd, &cx, &cy, cx, cy)) return false;

	if(cy) _lcd_send_byte(p_lcd, 0, 0xc0);
	else _lcd_send_byte(p_lcd, 0, 0x80);

	lcd_move_cursor_right(p_lcd, cx);
	return true;
}

__PROGMEM_CODE__ bool lcd_scroll_left(lcd_t *p_lcd, uint8_t scroll_count)
{
	if(!_lcd_validate_ctx(p_lcd)) return false;

	_lcd_move_cursordisplay_leftright(p_lcd, 1, 0, scroll_count);
	return true;
}

__PROGMEM_CODE__ bool lcd_scroll_right(lcd_t *p_lcd, uint8_t scroll_count)
{
	if(!_lcd_validate_ctx(p_lcd)) return false;

	_lcd_move_cursordisplay_leftright(p_lcd, 1, 1, scroll_count);
	return true;
}

__PROGMEM_CODE__ bool lcd_print_char(lcd_t *p_lcd, char c)
{
	if(!_lcd_validate_ctx(p_lcd)) return false;

	_lcd_send_byte(p_lcd, 1, (uint8_t) c);
	return true;
}

__PROGMEM_CODE__ bool lcd_print_text(lcd_t *p_lcd, const char *text)
{
	uintptr_t _len;

	if(!_lcd_validate_ctx(p_lcd)) return false;
	if(text == NULL) return false;

	_len = (uintptr_t) cstr_getlength(text);

	return lcd_print_text_len(p_lcd, text, _len);
}

__PROGMEM_CODE__ bool lcd_print_text_len(lcd_t *p_lcd, const char *text, uintptr_t length)
{
	uintptr_t _nchar;

	if(!_lcd_validate_ctx(p_lcd)) return false;
	if(text == NULL) return false;

	_nchar = 0u;
	while(_nchar < length)
	{
		_lcd_send_byte(p_lcd, 1, (uint8_t) text[_nchar]);
		_nchar++;
	}

	return true;
}

__PROGMEM_CODE__ bool lcd_fill_screen_char(lcd_t *p_lcd, char c)
{
	uint8_t _nchar;

	if(!_lcd_validate_ctx(p_lcd)) return false;

	_lcd_send_byte(p_lcd, 0, 0x80);
	for(_nchar = 0u; _nchar < 40u; _nchar++) _lcd_send_byte(p_lcd, 1, (uint8_t) c);

	_lcd_send_byte(p_lcd, 0, 0xc0);
	for(_nchar = 0u; _nchar < 40u; _nchar++) _lcd_send_byte(p_lcd, 1, (uint8_t) c);

	return true;
}

static __PROGMEM_CODE__ void _lcd_send_byte(lcd_t *p_lcd, uint8_t reg, uint8_t byte)
{
	if(p_lcd == NULL) return;

	digitalWrite(p_lcd->gpio_e, 0);
	digitalWrite(_lcd_drv_info.gpio_rs, reg);

	delayMicroseconds(__LCD_EN_DELAY_US);

	_lcd_write_nibble((byte >> 4));
	digitalWrite(p_lcd->gpio_e, 1);
	delayMicroseconds(__LCD_EN_DELAY_US);

	digitalWrite(p_lcd->gpio_e, 0);
	delayMicroseconds(__LCD_EN_DELAY_US);

	_lcd_write_nibble(byte);
	digitalWrite(p_lcd->gpio_e, 1);
	delayMicroseconds(__LCD_EN_DELAY_US);

	digitalWrite(p_lcd->gpio_e, 0);
	delayMicroseconds(__LCD_CMD_DELAY_US);

	return;
}

static __PROGMEM_CODE__ void _lcd_write_nibble(uint8_t nibble)
{
	digitalWrite(_lcd_drv_info.gpio_db7, (nibble & 0x8));
	digitalWrite(_lcd_drv_info.gpio_db6, (nibble & 0x4));
	digitalWrite(_lcd_drv_info.gpio_db5, (nibble & 0x2));
	digitalWrite(_lcd_drv_info.gpio_db4, (nibble & 0x1));

	return;
}

static __PROGMEM_CODE__ void _lcd_send_init_nibble(lcd_t *p_lcd)
{
	if(p_lcd == NULL) return;

	digitalWrite(p_lcd->gpio_e, 0);
	digitalWrite(_lcd_drv_info.gpio_rs, 0);

	delayMicroseconds(__LCD_EN_DELAY_US);

	_lcd_write_nibble(0x2);
	digitalWrite(p_lcd->gpio_e, 1);
	delayMicroseconds(__LCD_EN_DELAY_US);

	digitalWrite(p_lcd->gpio_e, 0);
	delayMicroseconds((__LCD_CMD_DELAY_US << 1));

	return;
}

static __PROGMEM_CODE__ void _lcd_move_cursordisplay_leftright(lcd_t *p_lcd, uint8_t move_display, uint8_t move_right, uint8_t move_count)
{
	uint8_t _ncount;
	uint8_t _byte;

	if(p_lcd == NULL) return;

	_byte = 0x10;
	if(move_right) _byte |= 0x4;
	if(move_display) _byte |= 0x8;

	_ncount = 0u;
	while(_ncount < move_count)
	{
		_lcd_send_byte(p_lcd, 0, _byte);
		_ncount++;
	}

	return;
}

static __PROGMEM_CODE__ bool _lcd_drv_validate_info(void)
{
	if(_lcd_drv_info.gpio_db4 == __LCD_GPIO_INVALID) return false;
	if(_lcd_drv_info.gpio_db5 == __LCD_GPIO_INVALID) return false;
	if(_lcd_drv_info.gpio_db6 == __LCD_GPIO_INVALID) return false;
	if(_lcd_drv_info.gpio_db7 == __LCD_GPIO_INVALID) return false;
	if(_lcd_drv_info.gpio_rs == __LCD_GPIO_INVALID) return false;

	return true;
}

static __PROGMEM_CODE__ bool _lcd_validate_ctx(lcd_t *p_lcd)
{
	if(!_lcd_drv_initialized) return false;
	if(p_lcd == NULL) return false;
	if(p_lcd->gpio_e == __LCD_GPIO_INVALID) return false;

	return true;
}

static __PROGMEM_CODE__ bool _lcd_phys_text_cxcy_to_virt_text_cxcy(lcd_t *p_lcd, uint8_t *p_virtcx, uint8_t *p_virtcy, uint8_t phys_cx, uint8_t phys_cy)
{
	uint8_t _virtcx;
	uint8_t _virtcy;

	if(p_lcd == NULL) return false;
	if(phys_cx >= p_lcd->n_chars) return false;
	if(phys_cy >= p_lcd->n_lines) return false;

	_virtcy = (phys_cy & 0x1);
	_virtcx = phys_cx;

	phys_cy = (phys_cy >> 1);
	_virtcx += phys_cy*(p_lcd->n_chars);

	if(p_virtcx != NULL) *p_virtcx = _virtcx;
	if(p_virtcy != NULL) *p_virtcy = _virtcy;

	return true;
}

