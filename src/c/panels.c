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

// ---------------------------------------------------------------------------
// Digit bitmaps
// ---------------------------------------------------------------------------

static const uint32_t s_num_large_ids[10] = {
  RESOURCE_ID_IMAGE_NUM_LARGE_0, RESOURCE_ID_IMAGE_NUM_LARGE_1,
  RESOURCE_ID_IMAGE_NUM_LARGE_2, RESOURCE_ID_IMAGE_NUM_LARGE_3,
  RESOURCE_ID_IMAGE_NUM_LARGE_4, RESOURCE_ID_IMAGE_NUM_LARGE_5,
  RESOURCE_ID_IMAGE_NUM_LARGE_6, RESOURCE_ID_IMAGE_NUM_LARGE_7,
  RESOURCE_ID_IMAGE_NUM_LARGE_8, RESOURCE_ID_IMAGE_NUM_LARGE_9,
};

static const uint32_t s_num_small_ids[10] = {
  RESOURCE_ID_IMAGE_NUM_SMALL_0, RESOURCE_ID_IMAGE_NUM_SMALL_1,
  RESOURCE_ID_IMAGE_NUM_SMALL_2, RESOURCE_ID_IMAGE_NUM_SMALL_3,
  RESOURCE_ID_IMAGE_NUM_SMALL_4, RESOURCE_ID_IMAGE_NUM_SMALL_5,
  RESOURCE_ID_IMAGE_NUM_SMALL_6, RESOURCE_ID_IMAGE_NUM_SMALL_7,
  RESOURCE_ID_IMAGE_NUM_SMALL_8, RESOURCE_ID_IMAGE_NUM_SMALL_9,
};

static GBitmap *s_num_large[10];
static GBitmap *s_num_small[10];

void panels_load_digits(void) {
  for (int i = 0; i < 10; i++) {
    s_num_large[i] = gbitmap_create_with_resource(s_num_large_ids[i]);
    s_num_small[i] = gbitmap_create_with_resource(s_num_small_ids[i]);
  }
}

void panels_unload_digits(void) {
  for (int i = 0; i < 10; i++) {
    gbitmap_destroy(s_num_large[i]);
    gbitmap_destroy(s_num_small[i]);
  }
}

static void draw_digit(GContext *ctx, GBitmap *bmp, GPoint origin) {
  GRect b = gbitmap_get_bounds(bmp);
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  graphics_draw_bitmap_in_rect(ctx, bmp, GRect(origin.x, origin.y, b.size.w, b.size.h));
}

void panels_draw_hours(GContext *ctx, GRect bounds, int hours) {
  GBitmap *tens_bmp = s_num_large[hours / 10];
  GBitmap *ones_bmp = s_num_large[hours % 10];
  int16_t tens_w = gbitmap_get_bounds(tens_bmp).size.w;
  draw_digit(ctx, tens_bmp, bounds.origin);
  draw_digit(ctx, ones_bmp, GPoint(bounds.origin.x + tens_w + 2, bounds.origin.y));
}

void panels_draw_minutes(GContext *ctx, GRect bounds, int minutes) {
  GBitmap *tens_bmp = s_num_small[minutes / 10];
  GBitmap *ones_bmp = s_num_small[minutes % 10];
  int16_t tens_w = gbitmap_get_bounds(tens_bmp).size.w;
  draw_digit(ctx, tens_bmp, bounds.origin);
  draw_digit(ctx, ones_bmp, GPoint(bounds.origin.x + tens_w + 2, bounds.origin.y));
}
