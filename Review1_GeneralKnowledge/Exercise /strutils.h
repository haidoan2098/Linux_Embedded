#ifndef __STRUTILS_H__
#define __STRUTILS_H__

#include <stdint.h>

// Reverses a string in-place.
void str_reverse(char *str);    

// Removes leading and trailing whitespace from a string.
void str_trim(char *str);

// Safely converts a string to an integer.
int str_to_int(const char *str, int *out_num);


#endif // __STRUTILS_H__
