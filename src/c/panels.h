#pragma once
#include <pebble.h>

typedef enum {
  PANEL_COMPANION_CUBE = 0,
  PANEL_CUBE_DROP,
  PANEL_COUNT
} Panel;

GBitmap *panels_load(Panel panel);
void     panels_unload(GBitmap *bitmap);
void     panels_draw_aperture(GContext *ctx, GRect box, int level);
