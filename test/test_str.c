#include <stddef.h>
#include <string.h>
#include "unity.h"
#include "str.h"

void test_String_new_ShouldReturnCharacterArray_WhenGivenValidContent(void)
{
    String string = String_new("Hello World!");
    
    TEST_ASSERT_NOT_NULL(string);
    TEST_ASSERT_EQUAL_STRING("Hello World!", string);
    
    String_delete(string);
}

void test_String_new_ShouldReturnEmptyCharacterArray_WhenGivenNULL(void)
{
    String string = String_new(NULL);
    
    TEST_ASSERT_NOT_NULL(string);
    TEST_ASSERT_EQUAL_STRING("", string);
    
    String_delete(string);
}

void test_String_length_ShouldReturnLengthOfString(void)
{
    String string = String_new("Life is difficult...");
    
    size_t string_length = String_length(string);
    
    TEST_ASSERT_EQUAL(strlen("Life is difficult..."), string_length);
    
    String_delete(string);
}