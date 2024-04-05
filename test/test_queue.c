#include <stdio.h>
#include <stdbool.h>
#include "unity.h"
#include "queue.h"

typedef struct {
    QUEUE_NODE
    int age;
    char *name;
    bool is_checked;
} Human;

static Human james = {
    .age = 100,
    .name = "James",
};

static Human chalie = {
    .age = 99,
    .name = "Chalie",
};

static Human tomas = {
    .age = 103,
    .name = "Tomas",
};

static void iterator(QueueNode *node)
{
    Human *human = (Human *)node;
    
    human->is_checked = true;
    printf("%s: %s\n", __func__, human->name);
}

void test_Queue_new_ShouldNotReturnNULL(void)
{
    Queue *queue = Queue_new();
    
    TEST_ASSERT_NOT_NULL(queue);
    TEST_ASSERT_NULL(Queue_peek(queue));
    
    Queue_delete(queue);
}

void test_Queue_pop_ShouldReturnPushedData(void)
{
    Queue *queue = Queue_new();
    
    Queue_push(queue, (QueueNode *)&james);
    Queue_push(queue, (QueueNode *)&chalie);
    Queue_push(queue, (QueueNode *)&tomas);
    
    Human *human = (Human *)Queue_pop(queue);
    TEST_ASSERT_EQUAL_STRING("James", human->name);
   
    human = (Human *)Queue_pop(queue);
    TEST_ASSERT_EQUAL_STRING("Chalie", human->name);
    
    human = (Human *)Queue_pop(queue);
    TEST_ASSERT_EQUAL_STRING("Tomas", human->name);
    
    human = (Human *)Queue_pop(queue);
    TEST_ASSERT_NULL(human);
    
    Queue_delete(queue);
}

void test_Queue_peek_ShouldReturnFirstlyPushedData(void)
{
    Queue *queue = Queue_new();
    
    Queue_push(queue, (QueueNode *)&james);
    Queue_push(queue, (QueueNode *)&chalie);
    Queue_push(queue, (QueueNode *)&tomas);
    
    Human *human = (Human *)Queue_peek(queue);
    TEST_ASSERT_EQUAL_STRING("James", human->name);
    
    Queue_delete(queue);
}

void test_Queue_iterate_ShouldIterateAllNode(void)
{
    Queue *queue = Queue_new();
    
    james.is_checked = chalie.is_checked = tomas.is_checked = false;

    Queue_push(queue, (QueueNode *)&james);
    Queue_push(queue, (QueueNode *)&chalie);
    Queue_push(queue, (QueueNode *)&tomas);
    
    Queue_iterate(queue, iterator);
    
    TEST_ASSERT_TRUE(james.is_checked);
    TEST_ASSERT_TRUE(chalie.is_checked);
    TEST_ASSERT_TRUE(tomas.is_checked);
    
    Queue_delete(queue);
}