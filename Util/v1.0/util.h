/*
 * Basic Utilities Library for Arduino IDE.
 * Version 1.0
 *
 * Author: Rafael Sabe
 * Email: rafaelmsabe@gmail.com
 */

#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define PTR_SIZE_BYTES (sizeof(void*))
#define PTR_SIZE_BITS (PTR_SIZE_BYTES*8U)

#define TEXTBUF_SIZE_CHARS 256U
#define TEXTBUF_SIZE_BYTES TEXTBUF_SIZE_CHARS

extern const uintptr_t PTR_MAX_VALUE;
extern const uintptr_t PTR_MSB_VALUE;
extern char textbuf[];

/*
 * cstr_getlength()
 * returns the length of a null-terminated string, or -1 if error.
 */

extern intptr_t cstr_getlength(const char *str);

/*
 * cstr_locatechar()
 * search for a specific char (c) on a null-terminated string.
 *
 * returns the index of the first matching character found, or returns -1 if character is not on string or error.
 */

extern intptr_t cstr_locatechar(const char *str, char c);

/*
 * cstr_compare()
 * compares 2 null-terminated strings.
 *
 * returns true if they're equal, false if they're not equal or error.
 */

extern bool cstr_compare(const char *str1, const char *str2);

/*
 * cstr_compare_upto_len()
 * compares 2 null-terminated strings up to a certain length (stop_index).
 *
 * if both strings are shorter than given stop_index, this function returns cstr_compare()
 *
 * returns true if both strings are equal up to the given stop_index, false if not equal or error.
 */

extern bool cstr_compare_upto_len(const char *str1, const char *str2, uintptr_t stop_index);

/*
 * cstr_compare_upto_char()
 * compares 2 null-terminated strings until it reaches a specific character (stop_char) on either string.
 *
 * If neither strings have the stop_char, function will perform a regular cstr_compare().
 *
 * returns true if both strings are equal up to the given stop_char, false if not equal or error.
 */

extern bool cstr_compare_upto_char(const char *str1, const char *str2, char stop_char);

/*
 * cstr_copy()
 * copy the content of an input null-terminated string to an output string. Append null-terminator character to the output string.
 *
 * if output string buffer - 1 (null-terminator) is shorter than input string, all remaining input characters past buffer length - 1 will be truncated from output string.
 *
 * returns true if successful, false if error.
 */

extern bool cstr_copy(const char *input_str, char *output_str, uintptr_t bufferout_length);

/*
 * cstr_copy_upto_len()
 * copy the content of an input null-terminated string to an output string up to a given stop_index.
 * 
 * if input string is shorter than given stop_index, this function will behave as cstr_copy()
 * if output string buffer - 1 (null-terminator) is shorter than stop_index, all remaining input characters past buffer length - 1 will be truncated from output string.
 *
 * if append_nullchar is true, function will append a null-terminator to the copied content on output buffer.
 * function will always write a null-terminator character at the end of output buffer, even if append_nullchar is false, for safety.
 *
 * returns true if successful, false otherwise.
 */

extern bool cstr_copy_upto_len(const char *input_str, char *output_str, uintptr_t bufferout_length, uintptr_t stop_index, bool append_nullchar);

/*
 * cstr_copy_upto_char()
 * copy the content of an input null-terminated string to an output string until it reaches a specific character (stop_char) on the input string.
 *
 * if input string does not have the stop_char, function will behave as cstr_copy()
 *
 * if append_nullchar is true, function will append a null-terminator to the copied content on output buffer.
 * function will always write a null-terminator character at the end of output buffer, even if append_nullchar is false, for safety.
 *
 * returns true if successful, false otherwise.
 */

extern bool cstr_copy_upto_char(const char *input_str, char *output_str, uintptr_t bufferout_length, char stop_char, bool append_nullchar);

/*
 * cstr_tolower() & cstr_toupper()
 *
 * converts all letters from a null-terminated string to lower-case or upper-case.
 *
 * returns true if successful, false otherwise.
 */

extern bool cstr_tolower(char *str, uintptr_t buffer_length);
extern bool cstr_toupper(char *str, uintptr_t buffer_length);

/*
 * _is_power2()
 *
 * check if a given value is a power of 2.
 *
 * returns true if so, false otherwise.
 */

extern bool _is_power2(uintptr_t value);

/*
 * _get_closest_power2_floor() & _get_closest_power2_ceil() & _get_closest_power2_round()
 *
 * function will floor/ceil/round a given value to the closest power of 2.
 *
 * returns the result power of 2 value, or 0 if not possible to retrieve closest power of 2 (given value is either 0 or too big).
 */

extern uintptr_t _get_closest_power2_floor(uintptr_t value);
extern uintptr_t _get_closest_power2_ceil(uintptr_t value);
extern uintptr_t _get_closest_power2_round(uintptr_t value);

#endif /*UTIL_H*/

