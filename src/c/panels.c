#include "panels.h"

// ---------------------------------------------------------------------------
// Panel bitmaps
// ---------------------------------------------------------------------------

static const uint32_t s_panel_resource_ids[PANEL_COUNT] = {
  [PANEL_COMPANION_CUBE] = RESOURCE_ID_IMAGE_PANEL_COMPANIONCUBE,
  [PANEL_CUBE_DROP]      = RESOURCE_ID_IMAGE_PANEL_CUBEDROP,
};

static const uint32_t s_aperture_resource_ids[8] = {
  RESOURCE_ID_IMAGE_PANEL_APERATURE_0,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_1,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_2,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_3,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_4,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_5,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_6,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_7,
};

GBitmap *panels_load(Panel panel) {
  return gbitmap_create_with_resource(s_panel_resource_ids[panel]);
}

void panels_unload(GBitmap *bitmap) {
  gbitmap_destroy(bitmap);
}

void panels_draw_aperture(GContext *ctx, GRect box, int level) {
  if (level < 1 || level > 7) return;
  GBitmap *bmp = gbitmap_create_with_resource(s_aperture_resource_ids[level]);
  graphics_draw_bitmap_in_rect(ctx, bmp, box);
  gbitmap_destroy(bmp);
}
