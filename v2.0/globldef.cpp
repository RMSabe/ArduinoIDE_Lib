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

#include "globldef.h"

__PROGMEM_DATA__ __attribute__((aligned(PTR_SIZE_BITS))) const uintptr_t PTR_MAX_VALUE = ~((uintptr_t) 0u);
__PROGMEM_DATA__ __attribute__((aligned(PTR_SIZE_BITS))) const uintptr_t PTR_MSB_VALUE = (((uintptr_t) 1u) << (PTR_SIZE_BITS - 1u));

__attribute__((aligned(PTR_SIZE_BITS))) char textbuf[TEXTBUF_SIZE_CHARS] = {'\0'};

__PROGMEM_CODE__ bool _is_power2(uintptr_t value)
{
	uintptr_t numptr;

	if(!value) return false;

	numptr = 1u;

	while(numptr)
	{
		if(numptr == value) return true;
		numptr = (numptr << 1);
	}

	return false;
}

__PROGMEM_CODE__ uintptr_t _get_closest_power2_floor(uintptr_t value)
{
	uintptr_t numptr;

	if(!value) return 0u;
	if(_is_power2(value)) return value;

	if(value > PTR_MSB_VALUE) return PTR_MSB_VALUE;

	numptr = _get_closest_power2_ceil(value);
	numptr = (numptr >> 1);

	return numptr;
}

__PROGMEM_CODE__ uintptr_t _get_closest_power2_ceil(uintptr_t value)
{
	uintptr_t numptr;

	if(!value) return 0u;
	if(_is_power2(value)) return value;

	numptr = 1u;

	while(numptr)
	{
		if(!(value/numptr)) break;
		numptr = (numptr << 1);
	}

	return numptr;
}

__PROGMEM_CODE__ uintptr_t _get_closest_power2_round(uintptr_t value)
{
	uintptr_t numptr1;
	uintptr_t numptr2;

	if(!value) return 0u;
	if(_is_power2(value)) return value;

	if(value > PTR_MSB_VALUE)
	{
		numptr1 = value - PTR_MSB_VALUE;
		numptr2 = PTR_MAX_VALUE - value;

		if(numptr1 < numptr2) return PTR_MSB_VALUE;
		return 0u;
	}

	numptr2 = _get_closest_power2_ceil(value);
	numptr1 = (numptr2 >> 1);

	if((value - numptr1) < (numptr2 - value)) return numptr1;

	return numptr2;
}

