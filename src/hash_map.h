/*
 *  Author: Huisu Ju <kng0258@naver.com>
 *  License: MIT
 */
#pragma once

#include <stddef.h>

typedef struct HashMap HashMap;

HashMap *HashMap_new(size_t capacity);
void HashMap_delete(HashMap *map);

int HashMap_put(HashMap *map, const char *key, void *data);
void *HashMap_get(HashMap *map, const char *key);
void HashMap_remove(HashMap *map, const char *key);

void HashMap_iterate(HashMap *map, void (*iter)(const char *key, void *data));

size_t HashMap_count(HashMap *map);
size_t HashMap_size(HashMap *map);
float HashMap_load_factor(HashMap *map);

void HashMap_set_custom_hash(HashMap *map, size_t (*hash)(const char *key));