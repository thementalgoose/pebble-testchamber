#pragma once
#include <pebble.h>

typedef enum {
  PANEL_COMPANION_CUBE = 0,
  PANEL_CUBE_DROP,
  PANEL_COUNT
} Panel;

GBitmap *panels_load(Panel panel);
void     panels_unload(GBitmap *bitmap);

void panels_load_digits(void);
void panels_unload_digits(void);
void panels_draw_hours(GContext *ctx, GRect bounds, int hours);
void panels_draw_minutes(GContext *ctx, GRect bounds, int minutes);
