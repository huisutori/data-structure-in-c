/*
 *  Author: Huisu Ju <kng0258@naver.com>
 *  License: MIT
 */
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "str.h"

typedef struct {
    size_t length;
    size_t capacity;
    char buffer[];
} __attribute__ ((packed)) StringPrototype;

String String_new(const char *content)
{
    size_t length = content ? strlen(content) : 0;
    size_t capacity = length * STRING_CAPACITY_FACTOR;
    if (capacity < STRING_CAPACITY_MIN) {
        capacity = STRING_CAPACITY_MIN;
    }
    
    StringPrototype *string = calloc(1, sizeof(StringPrototype) + capacity);
    *string = (StringPrototype) {
        .length = length,
        .capacity = capacity,
    };
    
    if (content) {
        memcpy(string->buffer, content, length);
    } 
    
    return (String)string->buffer;
}

void String_delete(String _string)
{
    StringPrototype *string = (StringPrototype *)(_string - sizeof(StringPrototype));
    
    free(string);
}

size_t String_length(const String _string)
{
    StringPrototype *string = (StringPrototype *)(_string - sizeof(StringPrototype));
    
    return string->length;
}