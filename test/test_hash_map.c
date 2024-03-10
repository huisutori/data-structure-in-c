#include <stdbool.h>
#include "unity.h"
#include "list.h"
#include "hash_map.h"

void test_HashMap_new_ShouldCreateHashMap_WhoseSizeIsPrimeNumber(void)
{
    HashMap *map = HashMap_new(8);
    
    TEST_ASSERT_NOT_NULL(map);
    TEST_ASSERT_EQUAL(11, HashMap_size(map));
    
    HashMap_delete(map);
}

void test_HashMap_new_ShouldCreateHashMap_WhoseSizeExceedDesignatedMinimum(void)
{
    HashMap *map = HashMap_new(1);
    
    TEST_ASSERT_NOT_NULL(map);
    TEST_ASSERT_EQUAL(5, HashMap_size(map));
    
    HashMap_delete(map);
}

void test_HashMap_put_ShouldInsertDataIntoMap(void)
{
    HashMap *map = HashMap_new(8);
    int a = 3, b = 5;
    
    int err = HashMap_put(map, "data A", &a);
    TEST_ASSERT_EQUAL(0, err);
    
    err = HashMap_put(map, "data B", &b);
    TEST_ASSERT_EQUAL(0, err);
    
    int *data = HashMap_get(map, "data A");
    TEST_ASSERT_EQUAL(3, *data);
    
    data = HashMap_get(map, "data B");
    TEST_ASSERT_EQUAL(5, *data);
    
    HashMap_delete(map);
}

void test_HashMap_remove_ShouldRemoveDataFromMap(void)
{
    HashMap *map = HashMap_new(8);
    int a = 3, b = 5, c =7;
    
    HashMap_put(map, "data A", &a);
    HashMap_put(map, "data B", &b);
    HashMap_put(map, "data C", &c);
    
    TEST_ASSERT_EQUAL(3, HashMap_count(map));
    
    HashMap_remove(map, "data B");
    
    TEST_ASSERT_EQUAL(2, HashMap_count(map));
    
    int *data = HashMap_get(map, "data B");
    TEST_ASSERT_NULL(data);
    
    HashMap_delete(map);
}

static struct Node {
    const char *key;
    int data;
    bool has_lookedup;
} node[] = {
    {
        .key = "node 1",
        .data = 1,
    },
    {
        .key = "node 2",
        .data = 2,
    },
    {
        .key = "node 3",
        .data = 3,
    },
    {
        .key = "node 4",
        .data = 4,
    },
};

static void lookup_hashmap(const char *key, void *data)
{
    struct Node *node = (struct Node *)data;
    node->has_lookedup = true;
    
    printf("%s %d\n", key, node->data);
}

void test_HashMap_iterate_ShouldTraverseAllData(void)
{
    HashMap *map = HashMap_new(8);

    
    for (int i = 0; i < 4; i++) {
        node[i].has_lookedup = false;
        HashMap_put(map, node[i].key, &node[i]);
    }
    
    HashMap_iterate(map, lookup_hashmap);
    
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_TRUE(node[i].has_lookedup);
    }
}