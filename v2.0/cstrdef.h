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

#ifndef CSTRDEF_H
#define CSTRDEF_H

#include "globldef.h"

/*
 * cstr_getlength()
 * returns the length of a null-terminated string, or -1 if error.
 */

extern intptr_t cstr_getlength(const char *str) __PROGMEM_CODE__;

/*
 * cstr_locatechar()
 * search for a specific char (c) on a null-terminated string.
 *
 * returns the index of the first matching character found, or returns -1 if character is not on string or error.
 */

extern intptr_t cstr_locatechar(const char *str, char c) __PROGMEM_CODE__;

/*
 * cstr_compare()
 * compares 2 null-terminated strings.
 *
 * returns true if they're equal, false if they're not equal or error.
 */

extern bool cstr_compare(const char *str1, const char *str2) __PROGMEM_CODE__;

/*
 * cstr_compare_upto_len()
 * compares 2 null-terminated strings up to a certain length (stop_index).
 *
 * fail_if_nolen sets the outcome of this function if both strings are shorter than stop_index
 * if both strings are shorter than given stop_index and fail_if_nolen is set to "true", then function will return "false", even if both strings are equal.
 * if both strings are shorter than given stop_index and fail_if_nolen is set to "false", then function will a do normal cstr_compare() process.
 *
 * returns true if both strings are equal up to the given stop_index, false if not equal or error.
 */

extern bool cstr_compare_upto_len(const char *str1, const char *str2, uintptr_t stop_index, bool fail_if_nolen) __PROGMEM_CODE__;

/*
 * cstr_compare_upto_char()
 * compares 2 null-terminated strings until it reaches a specific character (stop_char) on either string.
 *
 * fail_if_nochar sets the outcome of this function if neither strings have the stop_char.
 * If neither strings have the given stop_char and fail_if_nochar is set to "true", then function will return "false", even if both strings are equal.
 * If neither strings have the given stop_char and fail_if_nochar is set to "false", then function will do a normal cstr_compare() process.
 *
 * returns true if both strings are equal up to the given stop_char, false if not equal or error.
 */

extern bool cstr_compare_upto_char(const char *str1, const char *str2, char stop_char, bool fail_if_nochar) __PROGMEM_CODE__;

/*
 * cstr_copy()
 * copy the content of an input null-terminated string to an output string. Append null-terminator character to the output string.
 *
 * if output string buffer - 1 (null-terminator) is shorter than input string, all remaining input characters past buffer length - 1 will be truncated from output string.
 *
 * returns true if successful, false if error.
 */

extern bool cstr_copy(const char *input_str, char *output_str, uintptr_t bufferout_length) __PROGMEM_CODE__;

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

extern bool cstr_copy_upto_len(const char *input_str, char *output_str, uintptr_t bufferout_length, uintptr_t stop_index, bool append_nullchar) __PROGMEM_CODE__;

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

extern bool cstr_copy_upto_char(const char *input_str, char *output_str, uintptr_t bufferout_length, char stop_char, bool append_nullchar) __PROGMEM_CODE__;

/*
 * cstr_tolower() & cstr_toupper()
 *
 * converts all letters from a null-terminated string to lower-case or upper-case.
 *
 * returns true if successful, false otherwise.
 */

extern bool cstr_tolower(char *str, uintptr_t buffer_length) __PROGMEM_CODE__;
extern bool cstr_toupper(char *str, uintptr_t buffer_length) __PROGMEM_CODE__;

#endif /*CSTRDEF_H*/

