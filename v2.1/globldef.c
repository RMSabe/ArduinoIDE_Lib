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

#include "globldef.h"

__attribute__((__aligned__(PTR_SIZE_BITS))) char textbuf[TEXTBUF_SIZE_CHARS] = {'\0'};

__PROGMEM_CODE__ bool _is_power2(uintptr_t value)
{
	uintptr_t _numptr;

	if(!value) return false;

	_numptr = 1u;

	while(_numptr)
	{
		if(_numptr == value) return true;
		_numptr = (_numptr << 1);
	}

	return false;
}

__PROGMEM_CODE__ uintptr_t _get_closest_power2_floor(uintptr_t value)
{
	uintptr_t _numptr;

	if(!value) return 0u;
	if(_is_power2(value)) return value;

	if(value > PTR_MSB_VALUE) return PTR_MSB_VALUE;

	_numptr = _get_closest_power2_ceil(value);
	_numptr = (_numptr >> 1);

	return _numptr;
}

__PROGMEM_CODE__ uintptr_t _get_closest_power2_ceil(uintptr_t value)
{
	uintptr_t _numptr;

	if(!value) return 0u;
	if(_is_power2(value)) return value;

	_numptr = 1u;

	while(_numptr)
	{
		if(_numptr > value) break;
		_numptr = (_numptr << 1);
	}

	return _numptr;
}

__PROGMEM_CODE__ uintptr_t _get_closest_power2_round(uintptr_t value)
{
	uintptr_t _numptr1;
	uintptr_t _numptr2;

	if(!value) return 0u;
	if(_is_power2(value)) return value;

	if(value > PTR_MSB_VALUE)
	{
		_numptr1 = value - PTR_MSB_VALUE;
		_numptr2 = PTR_MAX_VALUE - value;

		if(_numptr1 < _numptr2) return PTR_MSB_VALUE;
		return 0u;
	}

	_numptr2 = _get_closest_power2_ceil(value);
	_numptr1 = (_numptr2 >> 1);

	if((value - _numptr1) < (_numptr2 - value)) return _numptr1;

	return _numptr2;
}

