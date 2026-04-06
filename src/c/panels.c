#include "panels.h"

// ---------------------------------------------------------------------------
// Panel bitmaps
// ---------------------------------------------------------------------------

static const uint32_t s_panel_resource_ids[PANEL_COUNT] = {
  [PANEL_COMPANION_CUBE] = RESOURCE_ID_IMAGE_PANEL_COMPANIONCUBE,
  [PANEL_CUBE_DROP]      = RESOURCE_ID_IMAGE_PANEL_CUBEDROP,
};

GBitmap *panels_load(Panel panel) {
  return gbitmap_create_with_resource(s_panel_resource_ids[panel]);
}

void panels_unload(GBitmap *bitmap) {
  gbitmap_destroy(bitmap);
}
