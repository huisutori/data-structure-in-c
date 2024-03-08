/*
 *  Author: Huisu Ju <kng0258@naver.com>
 *  License: MIT
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

#define HASH_MAP_MIN_BUCKETS 5

typedef struct HashMap {
    size_t count;
    size_t size;
    List **buckets;
    size_t (*hash_func)(const char *);
} HashMap;

typedef struct {
    LIST_NODE
    const char *key;
    void *data;
} HashMapNode;

static size_t hash_func(const char *key)
{
    size_t key_len = strlen(key);
    size_t hash = key_len;
    
    for (int i = key_len - 1; i >= 0; i--) {
        hash <<= 4;
        hash += key[i];
    }
    
    return hash;
}

static bool is_prime_number(size_t number)
{
    if (number == 2) {
        return true;
    }
    if (number % 2 == 0) {
        return false;
    }

    for (size_t div = 3; div <= number / div; div += 2) {
        if (number % div == 0) {
            return false;
        }
    }
    return true;
}

static size_t get_larger_prime_number(size_t number)
{
    size_t n = number | 1;
    while (!is_prime_number(n)) {
        n += 2;
    }
    
    return n;
}

static size_t get_index_from_hash_val(HashMap *map, size_t hash_val)
{
    return hash_val % map->size;
}

static HashMapNode *create_node(const char *key, void *data)
{
    HashMapNode *node = malloc(sizeof(HashMapNode));
    if (!node) {
        return NULL;
    }
    node->key = key;
    node->data = data;
    
    return node;
}

static void delete_node(HashMapNode *node)
{
    free(node);
}

HashMap *HashMap_new(size_t capacity)
{
    HashMap *map = malloc(sizeof(HashMap));
    if (!map) {
        return NULL;
    }
    
    size_t size = capacity > HASH_MAP_MIN_BUCKETS ?
                  capacity : HASH_MAP_MIN_BUCKETS;
    
    if (!is_prime_number(size)) {
        size = get_larger_prime_number(size);
    }
    
    *map = (HashMap) {
        .count = 0,
        .size = size,
        .hash_func = hash_func,
    };
    
    map->buckets = malloc(sizeof(List *) * size);
    if (!map->buckets) {
        goto delete_map;
    }
    
    for (int i = 0; i < size; i++) {
        map->buckets[i] = List_new();
        if (!map->buckets[i]) {
            goto delete_buckets;
        }
    }
    
    return map;

delete_buckets:
    for (int i = 0; i < size; i++) {
        if (map->buckets[i]) {
            List_delete(map->buckets[i]);
        } else {
            break;
        }
    }
    free(map->buckets);
    
delete_map:
    free(map);
    
    return NULL;
}

void HashMap_delete(HashMap *map)
{
    for (int i = 0; i < map->size; i++) {
        HashMapNode *node = (HashMapNode *)List_get_head(map->buckets[i]);
        while (node) {
            HashMapNode *del_node = node;
            node = (HashMapNode *)List_get_next((ListNode *)node);
            
            delete_node(del_node);
        }
        List_delete(map->buckets[i]);
    }
    
    free(map->buckets);
    free(map);
}

int HashMap_put(HashMap *map, const char *key, void *data)
{
    size_t hash = map->hash_func(key);
    size_t index = get_index_from_hash_val(map, hash);

    HashMapNode *node = (HashMapNode *)List_get_head(map->buckets[index]);
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return -1;
        }
        node = (HashMapNode *)List_get_next((ListNode *)node);
    }
    
    HashMapNode *new_node = create_node(key, data);
    if (!new_node) {
        return -1;
    }
    
    List_add(map->buckets[index], (ListNode *)new_node);
    map->count++;
    
    return 0;
}

void *HashMap_get(HashMap *map, const char *key)
{
    size_t hash = map->hash_func(key);
    size_t index = get_index_from_hash_val(map, hash);
    
    HashMapNode *node = (HashMapNode *)List_get_head(map->buckets[index]);
    while (node) {
        if (strcmp(key, node->key) == 0) {
            return node->data;
        }
        node = (HashMapNode *)List_get_next((ListNode *)node);
    }
    
    return NULL;
}

void HashMap_remove(HashMap *map, const char *key)
{
    size_t hash = map->hash_func(key);
    size_t index = get_index_from_hash_val(map, hash);
    
    HashMapNode *node = (HashMapNode *)List_get_head(map->buckets[index]);
    while (node) {
        if (strcmp(key, node->key) == 0) {
            List_remove(map->buckets[index], (ListNode *)node);
            delete_node(node);
            map->count--;
            break;
        }
        node = (HashMapNode *)List_get_next((ListNode *)node);
    }
}

void HashMap_iterate(HashMap *map, void (*iter)(const char *key, void *data))
{
    for (int i = 0; i < map->size; i++) {
        HashMapNode *node = (HashMapNode *)List_get_head(map->buckets[i]);
        while (node) {
            iter(node->key, node->data);
            node = (HashMapNode *)List_get_next((ListNode *)node);
        }
    }
}

size_t HashMap_count(HashMap *map)
{
    return map->count;
}

size_t HashMap_size(HashMap *map)
{
    return map->size;
}

float HashMap_load_factor(HashMap *map)
{
    return map->count / (float)map->size;
}

void HashMap_set_custom_hash(HashMap *map, size_t (*hash)(const char *key))
{
    if (hash) {
        map->hash_func = hash;
    }
}