#include <stdbool.h>
#include "unity.h"
#include "priority_queue.h"

static bool less(const void *data1, const void *data2)
{
    return (*(int *)data1 < *(int *)data2);
}

void test_PQueue_new_ShouldReturnEmptyPriorityQueue(void)
{
    PQueue *pqueue = PQueue_new(10, less);
    
    TEST_ASSERT_NOT_NULL(pqueue);
    TEST_ASSERT_TRUE(PQueue_is_empty(pqueue));
    
    PQueue_delete(pqueue);
}

void test_PQueue_new_ShouldGuaranteeGivenSize(void)
{
    PQueue *pqueue = PQueue_new(3, less);
    
    int arr[] = { 1, 2, 3, 4 };
    
    int err;
    for (int i = 0; i < 3; i++) {
        err = PQueue_push(pqueue, &arr[i]);
        TEST_ASSERT_EQUAL(0, err);
    }
    TEST_ASSERT_TRUE(PQueue_is_full(pqueue));
    
    err = PQueue_push(pqueue, &arr[3]);
    TEST_ASSERT_NOT_EQUAL(0, err);
    
    PQueue_delete(pqueue);
}

void test_PQueue_peek_ShouldReturnHighestPriorityData(void)
{   
    PQueue *pqueue = PQueue_new(10, less);
    
    int arr[] = { 39, 22, -3, 20, 200, -39, 0 };
    
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        PQueue_push(pqueue, &arr[i]);
    }
    
    int *data = PQueue_peek(pqueue);
        
    TEST_ASSERT_EQUAL(-39, *data);
    
    PQueue_delete(pqueue);
}

void test_PQueue_pop_ShouldReturnAndRemoveHighestPriorityData(void)
{
    PQueue *pqueue = PQueue_new(10, less);
    
    int arr[] = { 39, 22, -3, 20, 200, -39, 0 };
    
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        PQueue_push(pqueue, &arr[i]);
    }
    
    int *data = PQueue_pop(pqueue);    
    TEST_ASSERT_EQUAL(-39, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_EQUAL(-3, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_EQUAL(0, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_EQUAL(20, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_EQUAL(22, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_EQUAL(39, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_EQUAL(200, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_NULL(data);
    
    PQueue_delete(pqueue);
}

void test_PQueue_erase_ShouldSilentlyEraseData(void)
{
    PQueue *pqueue = PQueue_new(10, less);
    
    int arr[] = { 39, 22, -3, 20, 200, -39, 0 };
    
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        PQueue_push(pqueue, &arr[i]);
    }
    PQueue_erase(pqueue, &arr[3]);  // erase 20
    PQueue_erase(pqueue, &arr[4]);  // erase 200
    
    int *data = PQueue_pop(pqueue);    
    TEST_ASSERT_EQUAL(-39, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_EQUAL(-3, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_EQUAL(0, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_EQUAL(22, *data);
    
    data = PQueue_pop(pqueue);
    TEST_ASSERT_EQUAL(39, *data);

    data = PQueue_pop(pqueue);
    TEST_ASSERT_NULL(data);
    
    PQueue_delete(pqueue);
}