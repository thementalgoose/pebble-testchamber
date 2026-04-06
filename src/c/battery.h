#pragma once
#include <pebble.h>

Layer *battery_layer_create(GRect frame);
void   battery_layer_destroy(void);
