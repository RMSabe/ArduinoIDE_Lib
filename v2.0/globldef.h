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

#ifndef GLOBLDEF_H
#define GLOBLDEF_H

#include "config.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <Arduino.h>

#ifdef FLASHMEM
#define __PROGMEM_CODE__ FLASHMEM
#else
#define __PROGMEM_CODE__ PROGMEM
#endif

#define __PROGMEM_DATA__ PROGMEM

#define PTR_SIZE_BYTES (sizeof(void*))
#define PTR_SIZE_BITS (PTR_SIZE_BYTES*8U)

#define TEXTBUF_SIZE_BYTES TEXTBUF_SIZE_CHARS

extern const uintptr_t PTR_MAX_VALUE __PROGMEM_DATA__;
extern const uintptr_t PTR_MSB_VALUE __PROGMEM_DATA__;
extern char textbuf[];

/*
 * _is_power2()
 *
 * check if a given value is a power of 2.
 *
 * returns true if so, false otherwise.
 */

extern bool _is_power2(uintptr_t value) __PROGMEM_CODE__;

/*
 * _get_closest_power2_floor() & _get_closest_power2_ceil() & _get_closest_power2_round()
 *
 * function will floor/ceil/round a given value to the closest power of 2.
 *
 * returns the result power of 2 value, or 0 if not possible to retrieve closest power of 2 (given value is either 0 or too big).
 */

extern uintptr_t _get_closest_power2_floor(uintptr_t value) __PROGMEM_CODE__;
extern uintptr_t _get_closest_power2_ceil(uintptr_t value) __PROGMEM_CODE__;
extern uintptr_t _get_closest_power2_round(uintptr_t value) __PROGMEM_CODE__;

#endif /*GLOBLDEF_H*/

