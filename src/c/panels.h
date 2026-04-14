#pragma once
#include <pebble.h>

typedef enum {
  PANEL_COMPANION_CUBE = 0,
  PANEL_CUBE_DROP,
  PANEL_ATLAS_PBODY,
  PANEL_BALLDROP,
  PANEL_BALLFACE,
  PANEL_BOUNCE,
  PANEL_CAKE,
  PANEL_CUBEFACE,
  PANEL_DODGE,
  PANEL_DROP,
  PANEL_DROWNING,
  PANEL_GLADOS,
  PANEL_JUMPPAD,
  PANEL_LASERCUBE,
  PANEL_PORTALBRIDGE,
  PANEL_PORTALFLY,
  PANEL_PORTALFLY2,
  PANEL_POTATO,
  PANEL_SLIDERUN,
  PANEL_TURRET,
  PANEL_WHEATLEY,
  PANEL_APERTURE,
  PANEL_COUNT
} Panel;

GBitmap *panels_load(Panel panel);
void     panels_unload(GBitmap *bitmap);
void     panels_draw_panel(GContext *ctx, GRect box, Panel panel, GPoint text_origin, const char *text);
