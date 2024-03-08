/*
 *  Author: Huisu Ju <kng0258@naver.com>
 *  License: MIT
 */
#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef const char * String;

String String_new(const char *content);
void String_delete(String string);

size_t String_length(String string);

#define STRING_CAPACITY_FACTOR  (1.5)
#define STRING_CAPACITY_MIN     (10)