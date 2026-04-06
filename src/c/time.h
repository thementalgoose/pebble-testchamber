#pragma once
#include <pebble.h>

Layer     *time_layer_create(GRect frame);
TextLayer *time_date_layer_create(GRect frame);
void       time_update(void);
void       time_destroy(void);
