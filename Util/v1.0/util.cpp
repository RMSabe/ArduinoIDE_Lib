/*
 * Basic Utilities Library for Arduino IDE.
 * Version 1.0
 *
 * Author: Rafael Sabe
 * Email: rafaelmsabe@gmail.com
 */

#include "util.h"
#include <string.h>

__attribute__((aligned(PTR_SIZE_BITS))) const uintptr_t PTR_MAX_VALUE = ~((uintptr_t) 0u);
__attribute__((aligned(PTR_SIZE_BITS))) const uintptr_t PTR_MSB_VALUE = (1u << (PTR_SIZE_BITS - 1u));
__attribute__((aligned(PTR_SIZE_BITS))) char textbuf[TEXTBUF_SIZE_CHARS] = {'\0'};

intptr_t cstr_getlength(const char *str)
{
	uintptr_t len;

	if(str == NULL) return -1;

	len = 0u;
	while(str[len] != '\0') len++;

	return (intptr_t) len;
}

intptr_t cstr_locatechar(const char *str, char c)
{
	uintptr_t len;
	uintptr_t n_char;

	if(str == NULL) return -1;

	len = (uintptr_t) cstr_getlength(str);

	n_char = 0u;
	while(n_char < len)
	{
		if(str[n_char] == c) return (intptr_t) n_char;
		n_char++;
	}

	return -1;
}

bool cstr_compare(const char *str1, const char *str2)
{
	uintptr_t num1;
	uintptr_t num2;

	if(str1 == NULL) return false;
	if(str2 == NULL) return false;

	num1 = (uintptr_t) cstr_getlength(str1);
	num2 = (uintptr_t) cstr_getlength(str2);

	if(num1 != num2) return false;

	num1 = 0u;
	while(num1 < num2)
	{
		if(str1[num1] != str2[num1]) return false;
		num1++;
	}

	return true;
}

bool cstr_compare_upto_len(const char *str1, const char *str2, uintptr_t stop_index)
{
	uintptr_t num1;
	uintptr_t num2;

	if(str1 == NULL) return false;
	if(str2 == NULL) return false;

	num1 = (uintptr_t) cstr_getlength(str1);
	num2 = (uintptr_t) cstr_getlength(str2);

	if((num1 < stop_index) && (num2 < stop_index)) return cstr_compare(str1, str2);
	if((num1 < stop_index) || (num2 < stop_index)) return false;

	num1 = 0u;
	while(num1 < stop_index)
	{
		if(str1[num1] != str2[num1]) return false;
		num1++;
	}

	return true;
}

bool cstr_compare_upto_char(const char *str1, const char *str2, char stop_char)
{
	intptr_t num1;
	intptr_t num2;

	if(str1 == NULL) return false;
	if(str2 == NULL) return false;

	num1 = cstr_locatechar(str1, stop_char);
	num2 = cstr_locatechar(str2, stop_char);

	if((num1 < 0) && (num2 < 0)) return cstr_compare(str1, str2);

	if(num1 < 0) goto _l_cstr_compare_upto_char_compareloop;

	if((num2 < 0) || (num1 < num2)) num2 = num1;

_l_cstr_compare_upto_char_compareloop:

	num1 = 0;
	while(num1 < num2)
	{
		if(str1[num1] != str2[num1]) return false;
		num1++;
	}

	return true;
}

bool cstr_copy(const char *input_str, char *output_str, uintptr_t bufferout_length)
{
	uintptr_t stop_index;

	if(input_str == NULL) return false;
	if(output_str == NULL) return false;
	if(!bufferout_length) return false;

	stop_index = (uintptr_t) cstr_getlength(input_str);

	if(stop_index > (bufferout_length - 1u)) stop_index = bufferout_length - 1u;

	memcpy(output_str, input_str, stop_index);

	output_str[stop_index] = '\0';

	return true;
}

bool cstr_copy_upto_len(const char *input_str, char *output_str, uintptr_t bufferout_length, uintptr_t stop_index, bool append_nullchar)
{
	uintptr_t input_len;

	if(input_str == NULL) return false;
	if(output_str == NULL) return false;
	if(!bufferout_length) return false;

	output_str[bufferout_length - 1u] = '\0'; /*Write null char terminator to the end of output buffer, for safety.*/

	input_len = (uintptr_t) cstr_getlength(input_str);
	if(input_len < stop_index) stop_index = input_len;

	if(stop_index > (bufferout_length - 1u)) stop_index = bufferout_length - 1u;

	memcpy(output_str, input_str, stop_index);

	if(append_nullchar) output_str[stop_index] = '\0';

	return true;
}

bool cstr_copy_upto_char(const char *input_str, char *output_str, uintptr_t bufferout_length, char stop_char, bool append_nullchar)
{
	intptr_t num1;

	if(input_str == NULL) return false;
	if(output_str == NULL) return false;
	if(!bufferout_length) return false;

	num1 = cstr_locatechar(input_str, stop_char);

	if(num1 < 0) num1 = cstr_getlength(input_str);

	return cstr_copy_upto_len(input_str, output_str, bufferout_length, (uintptr_t) num1, append_nullchar);
}

bool cstr_tolower(char *str, uintptr_t buffer_length)
{
	uintptr_t len;
	uintptr_t n_char;

	if(str == NULL) return false;
	if(!buffer_length) return false;

	str[buffer_length - 1u] = '\0';

	len = (uintptr_t) cstr_getlength(str);

	n_char = 0u;
	while(n_char < len)
	{
		if((str[n_char] >= 0x41) && (str[n_char] <= 0x5a)) str[n_char] |= 0x20;
		n_char++;
	}

	return true;
}

bool cstr_toupper(char *str, uintptr_t buffer_length)
{
	uintptr_t len;
	uintptr_t n_char;

	if(str == NULL) return false;
	if(!buffer_length) return false;

	str[buffer_length - 1u] = '\0';

	len = (uintptr_t) cstr_getlength(str);

	n_char = 0u;
	while(n_char < len)
	{
		if((str[n_char] >= 0x61) && (str[n_char] <= 0x7a)) str[n_char] &= 0xdf;
		n_char++;
	}

	return true;
}

bool _is_power2(uintptr_t value)
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

uintptr_t _get_closest_power2_floor(uintptr_t value)
{
	uintptr_t numptr;

	if(!value) return 0u;
	if(_is_power2(value)) return value;

	if(value > PTR_MSB_VALUE) return PTR_MSB_VALUE;

	numptr = _get_closest_power2_ceil(value);
	numptr = (numptr >> 1);

	return numptr;
}

uintptr_t _get_closest_power2_ceil(uintptr_t value)
{
	uintptr_t numptr;

	if(!value) return 0u;
	if(_is_power2(value)) return value;

	numptr = 1u;

	while(numptr)
	{
		if(!(value/numptr)) return numptr;
		numptr = (numptr << 1);
	}

	return numptr;
}

uintptr_t _get_closest_power2_round(uintptr_t value)
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

