#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "unity.h"
#include "list.h"

typedef struct {
    LIST_NODE
    const char *name;
    uint16_t age;
} People;

static People tom = {
    .name = "Tom",
    .age = 30,
};

static People sam = {
    .name = "Sam",
    .age = 33,
};

static People joe = {
    .name = "Joe",
    .age = 40,
};

void test_List_new_ShouldReturnNotNULL(void)
{
    List *list = List_new();
    
    TEST_ASSERT_NOT_NULL(list);
    
    List_delete(list);
}

void test_List_add_ShouldAddNodeToList(void)
{
    List *list = List_new();
    
    List_add(list, (ListNode *)&tom);
    List_add(list, (ListNode *)&sam);
    List_add(list, (ListNode *)&joe);
    
    bool has_tom = false;
    bool has_sam = false;
    bool has_joe = false;
    int people_count = 0;
    
    People *people = (People *)List_get_head(list);
    while (people) {
        if (strcmp(people->name, "Tom") == 0) {
            has_tom = true;
        } else if (strcmp(people->name, "Sam") == 0) {
            has_sam = true;
        } else if (strcmp(people->name, "Joe") == 0) {
            has_joe = true;
        }
        
        people_count++;
        people = (People *)List_get_next((ListNode *)people);
    }
    
    TEST_ASSERT_TRUE(has_tom && has_sam && has_joe);
    TEST_ASSERT_EQUAL(3, people_count);
    
    List_delete(list);
}

void test_List_remove_ShouldRemoveNodeFromList(void)
{
    List *list = List_new();
    
    List_add(list, (ListNode *)&tom);
    List_add(list, (ListNode *)&sam);
    List_add(list, (ListNode *)&joe);
    
    List_remove(list, (ListNode *)&sam);
    
    bool has_tom = false;
    bool has_sam = false;
    bool has_joe = false;
    int people_count = 0;
    
    People *people = (People *)List_get_head(list);
    while (people) {
        if (strcmp(people->name, "Tom") == 0) {
            has_tom = true;
        } else if (strcmp(people->name, "Sam") == 0) {
            has_sam = true;
        } else if (strcmp(people->name, "Joe") == 0) {
            has_joe = true;
        }
        
        people_count++;
        people = (People *)List_get_next((ListNode *)people);
    }
    
    TEST_ASSERT_TRUE(has_tom && !has_sam && has_joe);
    TEST_ASSERT_EQUAL(2, people_count);   
    
    List_delete(list);
}