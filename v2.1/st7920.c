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

#include "st7920.h"
#include <string.h>

#define __ST7920_CMD_LONG_DELAY_US 1024U
#define __ST7920_CMD_SHORT_DELAY_US 128U
#define __ST7920_EN_DELAY_US 1U

#define __ST7920_BASIC_INSTRUCTION_BYTE 0x30
#define __ST7920_EXT_INSTRUCTION_BYTE 0x34
#define __ST7920_GRAPHIC_DISPLAY_ENABLE_BIT 0x02

#define __ST7920_GPIO_INVALID ((uint8_t) -1)

struct __st7920_drv_info {
	uint8_t gpio_db0;
	uint8_t gpio_db1;
	uint8_t gpio_db2;
	uint8_t gpio_db3;
	uint8_t gpio_db4;
	uint8_t gpio_db5;
	uint8_t gpio_db6;
	uint8_t gpio_db7;
	uint8_t gpio_rs;
	uint8_t gpio_rw; /*Reserved for future use*/
};

typedef struct __st7920_drv_info _st7920_drv_info_t;

static _st7920_drv_info_t _st7920_drv_info = {
	.gpio_db0 = __ST7920_GPIO_INVALID,
	.gpio_db1 = __ST7920_GPIO_INVALID,
	.gpio_db2 = __ST7920_GPIO_INVALID,
	.gpio_db3 = __ST7920_GPIO_INVALID,
	.gpio_db4 = __ST7920_GPIO_INVALID,
	.gpio_db5 = __ST7920_GPIO_INVALID,
	.gpio_db6 = __ST7920_GPIO_INVALID,
	.gpio_db7 = __ST7920_GPIO_INVALID,
	.gpio_rs = __ST7920_GPIO_INVALID,
	.gpio_rw = __ST7920_GPIO_INVALID
};

static bool _st7920_drv_initialized = false;

static void _st7920_send_byte(st7920_t *p_st7920, uintptr_t cmddelay_us, uint8_t reg, uint8_t byte) __PROGMEM_CODE__;
static void _st7920_write_byte(uint8_t byte) __PROGMEM_CODE__;
static void _st7920_set_dataline_mode(bool output) __PROGMEM_CODE__;
static void _st7920_set_instruction_mode(st7920_t *p_st7920, bool ext_inst) __PROGMEM_CODE__;
static void _st7920_movetext_cursordisplay_leftright(st7920_t *p_st7920, uint8_t move_display, uint8_t move_right, uint8_t move_count) __PROGMEM_CODE__;

static bool _st7920_drv_validate_info(void) __PROGMEM_CODE__;
static bool _st7920_validate_ctx(st7920_t *p_st7920) __PROGMEM_CODE__;

static bool _st7920_phys_cxcy_to_virt_bufindex_pageindex_cy_offset(uintptr_t *p_bufindex, uint16_t *p_virtpageindex, uint16_t *p_virtcy, uint16_t *p_virtoffset, uint16_t phys_cx, uint16_t phys_cy) __PROGMEM_CODE__;
static bool _st7920_phys_pageindex_cy_to_virt_bufindex_pageindex_cy(uintptr_t *p_bufindex, uint16_t *p_virtpageindex, uint16_t *p_virtcy, uint16_t phys_pageindex, uint16_t phys_cy) __PROGMEM_CODE__;

static bool _st7920_phys_text_cxcy_to_virt_wtext_cxcy_addspace(uint8_t *p_virtcx, uint8_t *p_virtcy, uint8_t *p_addspace, uint8_t phys_cx, uint8_t phys_cy) __PROGMEM_CODE__;
static bool _st7920_phys_wtext_cxcy_to_virt_wtext_cxcy(uint8_t *p_virtcx, uint8_t *p_virtcy, uint8_t phys_cx, uint8_t phys_cy) __PROGMEM_CODE__;

__PROGMEM_CODE__ bool st7920_drv_init(uint8_t gpio_db0, uint8_t gpio_db1, uint8_t gpio_db2, uint8_t gpio_db3, uint8_t gpio_db4, uint8_t gpio_db5, uint8_t gpio_db6, uint8_t gpio_db7, uint8_t gpio_rs)
{
	_st7920_drv_initialized = false;

	_st7920_drv_info.gpio_db0 = gpio_db0;
	_st7920_drv_info.gpio_db1 = gpio_db1;
	_st7920_drv_info.gpio_db2 = gpio_db2;
	_st7920_drv_info.gpio_db3 = gpio_db3;
	_st7920_drv_info.gpio_db4 = gpio_db4;
	_st7920_drv_info.gpio_db5 = gpio_db5;
	_st7920_drv_info.gpio_db6 = gpio_db6;
	_st7920_drv_info.gpio_db7 = gpio_db7;
	_st7920_drv_info.gpio_rs = gpio_rs;

	if(!_st7920_drv_validate_info()) return false;

	pinMode(_st7920_drv_info.gpio_rs, OUTPUT);
	_st7920_set_dataline_mode(true);

	_st7920_drv_initialized = true;
	return true;
}

__PROGMEM_CODE__ void st7920_drv_deinit(void)
{
	_st7920_drv_initialized = false;

	if(_st7920_drv_info.gpio_db0 != __ST7920_GPIO_INVALID) pinMode(_st7920_drv_info.gpio_db0, INPUT);
	if(_st7920_drv_info.gpio_db1 != __ST7920_GPIO_INVALID) pinMode(_st7920_drv_info.gpio_db1, INPUT);
	if(_st7920_drv_info.gpio_db2 != __ST7920_GPIO_INVALID) pinMode(_st7920_drv_info.gpio_db2, INPUT);
	if(_st7920_drv_info.gpio_db3 != __ST7920_GPIO_INVALID) pinMode(_st7920_drv_info.gpio_db3, INPUT);
	if(_st7920_drv_info.gpio_db4 != __ST7920_GPIO_INVALID) pinMode(_st7920_drv_info.gpio_db4, INPUT);
	if(_st7920_drv_info.gpio_db5 != __ST7920_GPIO_INVALID) pinMode(_st7920_drv_info.gpio_db5, INPUT);
	if(_st7920_drv_info.gpio_db6 != __ST7920_GPIO_INVALID) pinMode(_st7920_drv_info.gpio_db6, INPUT);
	if(_st7920_drv_info.gpio_db7 != __ST7920_GPIO_INVALID) pinMode(_st7920_drv_info.gpio_db7, INPUT);
	if(_st7920_drv_info.gpio_rs != __ST7920_GPIO_INVALID) pinMode(_st7920_drv_info.gpio_rs, INPUT);

	return;
}

__PROGMEM_CODE__ bool st7920_init(st7920_t *p_st7920)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	pinMode(p_st7920->gpio_e, OUTPUT);
	digitalWrite(p_st7920->gpio_e, 0);

	_st7920_set_instruction_mode(p_st7920, false);
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x01);
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x80);
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x0c);

	p_st7920->_graphic_display_enabled = false;

	st7920_enable_graphic_display(p_st7920, true);
	st7920_clear_display(p_st7920);

	return true;
}

__PROGMEM_CODE__ void st7920_deinit(st7920_t *p_st7920)
{
	if(p_st7920 == NULL) return;
	if(p_st7920->gpio_e != __ST7920_GPIO_INVALID) pinMode(p_st7920->gpio_e, INPUT);

	return;
}

__PROGMEM_CODE__ bool st7920_enable_graphic_display(st7920_t *p_st7920, bool enable)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_set_instruction_mode(p_st7920, true);
	p_st7920->_graphic_display_enabled = enable;
	_st7920_set_instruction_mode(p_st7920, true);

	return true;
}

__PROGMEM_CODE__ int8_t st7920_graphic_display_is_enabled(st7920_t *p_st7920)
{
	if(!_st7920_validate_ctx(p_st7920)) return -1;

	if(p_st7920->_graphic_display_enabled) return 1;

	return 0;
}

__PROGMEM_CODE__ bool st7920_buffer_set_pixel(st7920_t *p_st7920, uint16_t cx, uint16_t cy, bool lit)
{
	uintptr_t _buffer_index;
	uint16_t _pixel_offset;

	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(!_st7920_phys_cxcy_to_virt_bufindex_pageindex_cy_offset(&_buffer_index, NULL, NULL, &_pixel_offset, cx, cy)) return false;

	if(lit) p_st7920->_vram_buffer[_buffer_index] |= (1 << _pixel_offset);
	else p_st7920->_vram_buffer[_buffer_index] &= ~(1 << _pixel_offset);

	return true;
}

__PROGMEM_CODE__ int8_t st7920_buffer_get_pixel(st7920_t *p_st7920, uint16_t cx, uint16_t cy)
{
	uintptr_t _buffer_index;
	uint16_t _pixel_offset;

	if(!_st7920_validate_ctx(p_st7920)) return -1;
	if(!_st7920_phys_cxcy_to_virt_bufindex_pageindex_cy_offset(&_buffer_index, NULL, NULL, &_pixel_offset, cx, cy)) return -1;

	if(p_st7920->_vram_buffer[_buffer_index] & (1 << _pixel_offset)) return 1;

	return 0;
}

__PROGMEM_CODE__ bool st7920_buffer_toggle_pixel(st7920_t *p_st7920, uint16_t cx, uint16_t cy)
{
	uintptr_t _buffer_index;
	uint16_t _pixel_offset;

	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(!_st7920_phys_cxcy_to_virt_bufindex_pageindex_cy_offset(&_buffer_index, NULL, NULL, &_pixel_offset, cx, cy)) return false;

	p_st7920->_vram_buffer[_buffer_index] ^= (1 << _pixel_offset);

	return true;
}

__PROGMEM_CODE__ bool st7920_buffer_set_page(st7920_t *p_st7920, uint16_t page_index, uint16_t cy, uint16_t page_value)
{
	uintptr_t _buffer_index;

	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(!_st7920_phys_pageindex_cy_to_virt_bufindex_pageindex_cy(&_buffer_index, NULL, NULL, page_index, cy)) return false;

	p_st7920->_vram_buffer[_buffer_index] = page_value;
	return true;
}

__PROGMEM_CODE__ int32_t st7920_buffer_get_page(st7920_t *p_st7920, uint16_t page_index, uint16_t cy)
{
	uintptr_t _buffer_index;

	if(!_st7920_validate_ctx(p_st7920)) return -1;
	if(!_st7920_phys_pageindex_cy_to_virt_bufindex_pageindex_cy(&_buffer_index, NULL, NULL, page_index, cy)) return -1;

	return (int32_t) p_st7920->_vram_buffer[_buffer_index];
}

__PROGMEM_CODE__ bool st7920_buffer_toggle_page(st7920_t *p_st7920, uint16_t page_index, uint16_t cy, uint16_t toggle_mask)
{
	uintptr_t _buffer_index;

	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(!_st7920_phys_pageindex_cy_to_virt_bufindex_pageindex_cy(&_buffer_index, NULL, NULL, page_index, cy)) return false;

	p_st7920->_vram_buffer[_buffer_index] ^= toggle_mask;
	return true;
}

__PROGMEM_CODE__ bool st7920_buffer_set_all(st7920_t *p_st7920, bool lit)
{
	uint8_t _byte;

	if(!_st7920_validate_ctx(p_st7920)) return false;

	if(lit) _byte = 0xff;
	else _byte = 0x0;

	memset(p_st7920->_vram_buffer, _byte, __ST7920_VRAM_SIZE_BYTES);
	return true;
}

__PROGMEM_CODE__ bool st7920_buffer_toggle_all(st7920_t *p_st7920)
{
	uintptr_t _buffer_index;

	if(!_st7920_validate_ctx(p_st7920)) return false;

	for(_buffer_index = 0u; _buffer_index < __ST7920_VRAM_SIZE_PAGES; _buffer_index++)
		p_st7920->_vram_buffer[_buffer_index] = ~(p_st7920->_vram_buffer[_buffer_index]);

	return true;
}

__PROGMEM_CODE__ bool st7920_buffer_paint_pixel(st7920_t *p_st7920, uint16_t cx, uint16_t cy)
{
	uint16_t _page_index;

	_page_index = cx/__ST7920_PAGE_WIDTH_PIXELS;

	return st7920_buffer_paint_page(p_st7920, _page_index, cy);
}

__PROGMEM_CODE__ bool st7920_buffer_paint_page(st7920_t *p_st7920, uint16_t page_index, uint16_t cy)
{
	uintptr_t _buffer_index;
	uint16_t _virtpageindex;
	uint16_t _virtcy;
	uint16_t _page_value;

	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(!_st7920_phys_pageindex_cy_to_virt_bufindex_pageindex_cy(&_buffer_index, &_virtpageindex, &_virtcy, page_index, cy)) return false;

	_page_value = p_st7920->_vram_buffer[_buffer_index];

	_st7920_set_instruction_mode(p_st7920, true);

	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, (uint8_t) (0x80 | _virtcy));
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, (uint8_t) (0x80 | _virtpageindex));

	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) (_page_value >> 8));
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) _page_value);

	return true;
}

__PROGMEM_CODE__ bool st7920_buffer_paint_all(st7920_t *p_st7920)
{
	uintptr_t _buffer_index;
	uint16_t _page_value;
	uint8_t _virtpageindex;
	uint8_t _virtcy;

	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_set_instruction_mode(p_st7920, true);

	_buffer_index = 0u;
	for(_virtcy = 0u; _virtcy < __ST7920_VIRT_HEIGHT_PIXELS; _virtcy++)
	{
		_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, (0x80 | _virtcy));
		_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x80);

		for(_virtpageindex = 0u; _virtpageindex < __ST7920_VIRT_WIDTH_PAGES; _virtpageindex++)
		{
			if(_buffer_index >= __ST7920_VRAM_SIZE_PAGES) return false;

			_page_value = p_st7920->_vram_buffer[_buffer_index];

			_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) (_page_value >> 8));
			_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) _page_value);

			_buffer_index++;
		}
	}

	return true;
}

__PROGMEM_CODE__ bool st7920_clear_graphics(st7920_t *p_st7920)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	st7920_buffer_set_all(p_st7920, false);
	st7920_buffer_paint_all(p_st7920);
	return true;
}

__PROGMEM_CODE__ bool st7920_set_display_mode(st7920_t *p_st7920, int8_t display_mode)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_set_instruction_mode(p_st7920, false);

	switch(display_mode)
	{
		case ST7920_DISPLAYMODE_DISPLAY_OFF:
			_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x08);
			return true;

		case ST7920_DISPLAYMODE_DISPLAY_ON_CURSOR_OFF:
			_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x0c);
			return true;

		case ST7920_DISPLAYMODE_DISPLAY_ON_CURSOR_ON:
			_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x0e);
			return true;

		case ST7920_DISPLAYMODE_DISPLAY_ON_CURSOR_BLINK:
			_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x0f);
			return true;
	}

	return false;
}

__PROGMEM_CODE__ bool st7920_clear_text(st7920_t *p_st7920)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	st7920_fill_screen_char(p_st7920, ' ');

	_st7920_set_instruction_mode(p_st7920, false);
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x80);
	return true;
}

__PROGMEM_CODE__ bool st7920_cursor_home(st7920_t *p_st7920)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_set_instruction_mode(p_st7920, false);
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x02);

	return true;
}

__PROGMEM_CODE__ bool st7920_move_text_cursor_left(st7920_t *p_st7920, uint8_t move_count)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_movetext_cursordisplay_leftright(p_st7920, 0, 0, move_count);
	return true;
}

__PROGMEM_CODE__ bool st7920_move_text_cursor_right(st7920_t *p_st7920, uint8_t move_count)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_movetext_cursordisplay_leftright(p_st7920, 0, 1, move_count);
	return true;
}

__PROGMEM_CODE__ bool st7920_set_text_cursor_position(st7920_t *p_st7920, uint8_t cx, uint8_t cy)
{
	uint8_t _addspace;

	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(!_st7920_phys_text_cxcy_to_virt_wtext_cxcy_addspace(&cx, &cy, &_addspace, cx, cy)) return false;

	_st7920_set_instruction_mode(p_st7920, false);

	if(cy) _st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x90);
	else _st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x80);

	st7920_move_text_cursor_right(p_st7920, cx);

	if(_addspace) _st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) ' ');

	return true;
}

__PROGMEM_CODE__ bool st7920_set_wtext_cursor_position(st7920_t *p_st7920, uint8_t cx, uint8_t cy)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(!_st7920_phys_wtext_cxcy_to_virt_wtext_cxcy(&cx, &cy, cx, cy)) return false;

	_st7920_set_instruction_mode(p_st7920, false);

	if(cy) _st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x90);
	else _st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x80);

	st7920_move_text_cursor_right(p_st7920, cx);

	return true;
}

__PROGMEM_CODE__ bool st7920_scroll_text_left(st7920_t *p_st7920, uint8_t scroll_count)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_movetext_cursordisplay_leftright(p_st7920, 1, 0, scroll_count);
	return true;
}

__PROGMEM_CODE__ bool st7920_scroll_text_right(st7920_t *p_st7920, uint8_t scroll_count)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_movetext_cursordisplay_leftright(p_st7920, 1, 1, scroll_count);
	return true;
}

__PROGMEM_CODE__ bool st7920_print_char(st7920_t *p_st7920, char c)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_set_instruction_mode(p_st7920, false);
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) c);

	return true;
}

__PROGMEM_CODE__ bool st7920_print_wchar(st7920_t *p_st7920, uint16_t wc)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_set_instruction_mode(p_st7920, false);
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) (wc >> 8));
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) wc);

	return true;
}

__PROGMEM_CODE__ bool st7920_print_text(st7920_t *p_st7920, const char *text)
{
	uintptr_t _len;

	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(text == NULL) return false;

	_len = 0u;
	while(text[_len] != '\0') _len++;

	return st7920_print_text_len(p_st7920, text, _len);
}

__PROGMEM_CODE__ bool st7920_print_wtext(st7920_t *p_st7920, const uint16_t *wtext)
{
	uintptr_t _len;

	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(wtext == NULL) return false;

	_len = 0u;
	while(wtext[_len] != '\0') _len++;

	return st7920_print_wtext_len(p_st7920, wtext, _len);
}

__PROGMEM_CODE__ bool st7920_print_text_len(st7920_t *p_st7920, const char *text, uintptr_t length)
{
	uintptr_t _nchar;

	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(text == NULL) return false;

	_st7920_set_instruction_mode(p_st7920, false);

	_nchar = 0u;
	while(_nchar < length)
	{
		_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) text[_nchar]);
		_nchar++;
	}

	return true;
}

__PROGMEM_CODE__ bool st7920_print_wtext_len(st7920_t *p_st7920, const uint16_t *wtext, uintptr_t length)
{
	uintptr_t _nwchar;
	uint16_t _wchar;

	if(!_st7920_validate_ctx(p_st7920)) return false;
	if(wtext == NULL) return false;

	_st7920_set_instruction_mode(p_st7920, false);

	_nwchar = 0u;
	while(_nwchar < length)
	{
		_wchar = wtext[_nwchar];

		_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) (_wchar >> 8));
		_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) _wchar);
		_nwchar++;
	}

	return true;
}

__PROGMEM_CODE__ bool st7920_fill_screen_char(st7920_t *p_st7920, char c)
{
	uint8_t _nchar;
	uint8_t _nline;

	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_set_instruction_mode(p_st7920, false);

	for(_nline = 0u; _nline < __ST7920_VIRT_N_LINES; _nline++)
	{
		_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, (0x80 | (_nline << 4)));

		for(_nchar = 0u; _nchar < __ST7920_VIRT_N_CHARS; _nchar++)
			_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) c);
	}

	return true;
}

__PROGMEM_CODE__ bool st7920_fill_screen_wchar(st7920_t *p_st7920, uint16_t wc)
{
	uint8_t _nwchar;
	uint8_t _nline;

	if(!_st7920_validate_ctx(p_st7920)) return false;

	_st7920_set_instruction_mode(p_st7920, false);

	for(_nline = 0u; _nline < __ST7920_VIRT_N_LINES; _nline++)
	{
		_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, (0x80 | (_nline << 4)));

		for(_nwchar = 0u; _nwchar < __ST7920_VIRT_N_WCHARS; _nwchar++)
		{
			_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) (wc >> 8));
			_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 1, (uint8_t) wc);
		}
	}

	return true;
}

__PROGMEM_CODE__ bool st7920_clear_display(st7920_t *p_st7920)
{
	if(!_st7920_validate_ctx(p_st7920)) return false;

	st7920_clear_graphics(p_st7920);

	_st7920_set_instruction_mode(p_st7920, false);
	_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, 0x01);

	return true;
}

static __PROGMEM_CODE__ void _st7920_send_byte(st7920_t *p_st7920, uintptr_t cmddelay_us, uint8_t reg, uint8_t byte)
{
	if(p_st7920 == NULL) return;

	digitalWrite(p_st7920->gpio_e, 0);
	digitalWrite(_st7920_drv_info.gpio_rs, reg);
	delayMicroseconds(__ST7920_EN_DELAY_US);

	_st7920_write_byte(byte);
	digitalWrite(p_st7920->gpio_e, 1);
	delayMicroseconds(__ST7920_EN_DELAY_US);

	digitalWrite(p_st7920->gpio_e, 0);
	delayMicroseconds(cmddelay_us);

	return;
}

static __PROGMEM_CODE__ void _st7920_write_byte(uint8_t byte)
{
	digitalWrite(_st7920_drv_info.gpio_db7, (byte & 0x80));
	digitalWrite(_st7920_drv_info.gpio_db6, (byte & 0x40));
	digitalWrite(_st7920_drv_info.gpio_db5, (byte & 0x20));
	digitalWrite(_st7920_drv_info.gpio_db4, (byte & 0x10));
	digitalWrite(_st7920_drv_info.gpio_db3, (byte & 0x08));
	digitalWrite(_st7920_drv_info.gpio_db2, (byte & 0x04));
	digitalWrite(_st7920_drv_info.gpio_db1, (byte & 0x02));
	digitalWrite(_st7920_drv_info.gpio_db0, (byte & 0x01));

	return;
}

static __PROGMEM_CODE__ void _st7920_set_dataline_mode(bool output)
{
	uint8_t _mode;

	if(output) _mode = OUTPUT;
	else _mode = INPUT;

	pinMode(_st7920_drv_info.gpio_db0, _mode);
	pinMode(_st7920_drv_info.gpio_db1, _mode);
	pinMode(_st7920_drv_info.gpio_db2, _mode);
	pinMode(_st7920_drv_info.gpio_db3, _mode);
	pinMode(_st7920_drv_info.gpio_db4, _mode);
	pinMode(_st7920_drv_info.gpio_db5, _mode);
	pinMode(_st7920_drv_info.gpio_db6, _mode);
	pinMode(_st7920_drv_info.gpio_db7, _mode);

	return;
}

static __PROGMEM_CODE__ void _st7920_set_instruction_mode(st7920_t *p_st7920, bool ext_inst)
{
	uint8_t _mode;

	if(p_st7920 == NULL) return;

	if(ext_inst)
	{
		_mode = __ST7920_EXT_INSTRUCTION_BYTE;
		if(p_st7920->_graphic_display_enabled) _mode |= __ST7920_GRAPHIC_DISPLAY_ENABLE_BIT;
	}
	else _mode = __ST7920_BASIC_INSTRUCTION_BYTE;

	_st7920_send_byte(p_st7920, __ST7920_CMD_LONG_DELAY_US, 0, _mode);
	return;
}

static __PROGMEM_CODE__ void _st7920_movetext_cursordisplay_leftright(st7920_t *p_st7920, uint8_t move_display, uint8_t move_right, uint8_t move_count)
{
	uint8_t _ncount;
	uint8_t _byte;

	if(p_st7920 == NULL) return;

	_st7920_set_instruction_mode(p_st7920, false);

	_byte = 0x10;
	if(move_right) _byte |= 0x4;
	if(move_display) _byte |= 0x8;

	_ncount = 0u;
	while(_ncount < move_count)
	{
		_st7920_send_byte(p_st7920, __ST7920_CMD_SHORT_DELAY_US, 0, _byte);
		_ncount++;
	}

	return;
}

static __PROGMEM_CODE__ bool _st7920_drv_validate_info(void)
{
	if(_st7920_drv_info.gpio_db0 == __ST7920_GPIO_INVALID) return false;
	if(_st7920_drv_info.gpio_db1 == __ST7920_GPIO_INVALID) return false;
	if(_st7920_drv_info.gpio_db2 == __ST7920_GPIO_INVALID) return false;
	if(_st7920_drv_info.gpio_db3 == __ST7920_GPIO_INVALID) return false;
	if(_st7920_drv_info.gpio_db4 == __ST7920_GPIO_INVALID) return false;
	if(_st7920_drv_info.gpio_db5 == __ST7920_GPIO_INVALID) return false;
	if(_st7920_drv_info.gpio_db6 == __ST7920_GPIO_INVALID) return false;
	if(_st7920_drv_info.gpio_db7 == __ST7920_GPIO_INVALID) return false;
	if(_st7920_drv_info.gpio_rs == __ST7920_GPIO_INVALID) return false;

	/*if(_st7920_drv_info.gpio_rw == __ST7920_GPIO_INVALID) return false;*/ /*Reserved for future use*/

	return true;
}

static __PROGMEM_CODE__ bool _st7920_validate_ctx(st7920_t *p_st7920)
{
	if(!_st7920_drv_initialized) return false;
	if(p_st7920 == NULL) return false;
	if(p_st7920->gpio_e == __ST7920_GPIO_INVALID) return false;

	return true;
}

static __PROGMEM_CODE__ bool _st7920_phys_cxcy_to_virt_bufindex_pageindex_cy_offset(uintptr_t *p_bufindex, uint16_t *p_virtpageindex, uint16_t *p_virtcy, uint16_t *p_virtoffset, uint16_t phys_cx, uint16_t phys_cy)
{
	uintptr_t _bufindex;
	uint16_t _virtpageindex;
	uint16_t _virtcy;
	uint16_t _virtoffset;

	if((phys_cx >= __ST7920_PHYS_WIDTH_PIXELS) || (phys_cy >= __ST7920_PHYS_HEIGHT_PIXELS)) return false;

	_virtpageindex = phys_cx/__ST7920_PAGE_WIDTH_PIXELS;
	_virtoffset = __ST7920_PAGE_WIDTH_PIXELS - (phys_cx%__ST7920_PAGE_WIDTH_PIXELS) - 1u;
	_virtcy = phys_cy%__ST7920_VIRT_HEIGHT_PIXELS;

	if(phys_cy >= __ST7920_VIRT_HEIGHT_PIXELS) _virtpageindex += __ST7920_PHYS_WIDTH_PAGES;

	_bufindex = __ST7920_VIRT_WIDTH_PAGES*((uintptr_t) _virtcy) + ((uintptr_t) _virtpageindex);

	if(p_bufindex != NULL) *p_bufindex = _bufindex;
	if(p_virtpageindex != NULL) *p_virtpageindex = _virtpageindex;
	if(p_virtcy != NULL) *p_virtcy = _virtcy;
	if(p_virtoffset != NULL) *p_virtoffset = _virtoffset;

	return true;
}

static __PROGMEM_CODE__ bool _st7920_phys_pageindex_cy_to_virt_bufindex_pageindex_cy(uintptr_t *p_bufindex, uint16_t *p_virtpageindex, uint16_t *p_virtcy, uint16_t phys_pageindex, uint16_t phys_cy)
{
	uintptr_t _bufindex;
	uint16_t _virtpageindex;
	uint16_t _virtcy;

	if((phys_pageindex >= __ST7920_PHYS_WIDTH_PAGES) || (phys_cy >= __ST7920_PHYS_HEIGHT_PIXELS)) return false;

	_virtcy = phys_cy%__ST7920_VIRT_HEIGHT_PIXELS;
	_virtpageindex = phys_pageindex;

	if(phys_cy >= __ST7920_VIRT_HEIGHT_PIXELS) _virtpageindex += __ST7920_PHYS_WIDTH_PAGES;

	_bufindex = __ST7920_VIRT_WIDTH_PAGES*((uintptr_t) _virtcy) + ((uintptr_t) _virtpageindex);

	if(p_bufindex != NULL) *p_bufindex = _bufindex;
	if(p_virtpageindex != NULL) *p_virtpageindex = _virtpageindex;
	if(p_virtcy != NULL) *p_virtcy = _virtcy;

	return true;
}

static __PROGMEM_CODE__ bool _st7920_phys_text_cxcy_to_virt_wtext_cxcy_addspace(uint8_t *p_virtcx, uint8_t *p_virtcy, uint8_t *p_addspace, uint8_t phys_cx, uint8_t phys_cy)
{
	uint8_t _virtcx;
	uint8_t _virtcy;
	uint8_t _addspace;

	if((phys_cx >= __ST7920_PHYS_N_CHARS) || (phys_cy >= __ST7920_PHYS_N_LINES)) return false;

	_addspace = (phys_cx & 0x1);
	_virtcx = (phys_cx >> 1);
	_virtcy = phys_cy%__ST7920_VIRT_N_LINES;

	if(phys_cy >= __ST7920_VIRT_N_LINES) _virtcx += __ST7920_PHYS_N_WCHARS;

	if(p_virtcx != NULL) *p_virtcx = _virtcx;
	if(p_virtcy != NULL) *p_virtcy = _virtcy;
	if(p_addspace != NULL) *p_addspace = _addspace;

	return true;
}

static __PROGMEM_CODE__ bool _st7920_phys_wtext_cxcy_to_virt_wtext_cxcy(uint8_t *p_virtcx, uint8_t *p_virtcy, uint8_t phys_cx, uint8_t phys_cy)
{
	uint8_t _virtcx;
	uint8_t _virtcy;

	if((phys_cx >= __ST7920_PHYS_N_WCHARS) || (phys_cy >= __ST7920_PHYS_N_LINES)) return false;

	_virtcy = phys_cy%__ST7920_VIRT_N_LINES;
	_virtcx = phys_cx;

	if(phys_cy >= __ST7920_VIRT_N_LINES) _virtcx += __ST7920_PHYS_N_WCHARS;

	if(p_virtcx != NULL) *p_virtcx = _virtcx;
	if(p_virtcy != NULL) *p_virtcy = _virtcy;

	return true;
}

