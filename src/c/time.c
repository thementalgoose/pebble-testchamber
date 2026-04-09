#include "time.h"
#include "panels.h"
#include "constants.h"

static Layer     *s_time_layer;
static TextLayer *s_date_layer;

static int s_hours_val   = 0;
static int s_minutes_val = 0;

static void time_layer_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  panels_draw_hours(ctx, GRect(0, 0, bounds.size.w, HOURS_HEIGHT), s_hours_val);
  panels_draw_minutes(ctx, GRect(MINUTES_OFFSET_X, MINUTES_OFFSET_Y,
                                 bounds.size.w - MINUTES_OFFSET_X,
                                 HOURS_HEIGHT - MINUTES_OFFSET_Y), s_minutes_val);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  time_update();
}

void time_update(void) {
  time_t temp = time(NULL);
  struct tm *t = localtime(&temp);

  s_hours_val   = clock_is_24h_style() ? t->tm_hour : (t->tm_hour % 12 ?: 12);
  s_minutes_val = t->tm_min;

  static char s_date[12];
  strftime(s_date, sizeof(s_date), "%d/%m", t);
  text_layer_set_text(s_date_layer, s_date);

  layer_mark_dirty(s_time_layer);
}

Layer *time_layer_create(GRect frame) {
  panels_load_digits();

  s_time_layer = layer_create(frame);
  layer_set_update_proc(s_time_layer, time_layer_update_proc);

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  return s_time_layer;
}

TextLayer *time_date_layer_create(GRect frame) {
  s_date_layer = text_layer_create(frame);
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorBlack);
  text_layer_set_font(s_date_layer, DATE_FONT);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentLeft);
  return s_date_layer;
}

void time_destroy(void) {
  tick_timer_service_unsubscribe();
  layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  panels_unload_digits();
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
