#pragma once
#include <pebble.h>

Layer     *time_layer_create(GRect frame);
TextLayer *time_date_layer_create(GRect frame);
void       time_update(void);
void       time_destroy(void);

void panels_load_digits(void);
void panels_unload_digits(void);
void panels_draw_hours(GContext *ctx, GRect bounds, int hours);
void panels_draw_minutes(GContext *ctx, GRect bounds, int minutes);