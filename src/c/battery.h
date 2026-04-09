#pragma once
#include <pebble.h>

Layer *battery_layer_create(GRect frame);
void   battery_layer_destroy(void);
void   battery_set_clay_mode(bool clay);
