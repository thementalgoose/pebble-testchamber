#pragma once
#include <pebble.h>

Layer     *time_layer_create(GRect frame);
TextLayer *time_date_layer_create(GRect frame);
void       time_update(void);
void       time_destroy(void);
void       time_set_ampm(bool show);

void panels_load_digits(void);
void panels_unload_digits(void);