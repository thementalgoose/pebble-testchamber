#include "time.h"
#include "panels.h"
#include "constants.h"

static Layer     *s_time_layer;
static TextLayer *s_date_layer;

static int  s_hours_val   = 0;
static int  s_minutes_val = 0;
static bool s_is_pm       = false;

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

// ---------------------------------------------------------------------------
// Time layer — draws hours, minutes, and AM/PM sequentially
// ---------------------------------------------------------------------------

static void time_layer_update_proc(Layer *layer, GContext *ctx) {
  bool is_24h = clock_is_24h_style();
  GRect bounds = layer_get_bounds(layer);
  int16_t x = 0;

  // Hours (large digits) — suppress leading zero in 12h mode
  if (!is_24h && s_hours_val < 10) {
    GBitmap *bmp = s_num_large[s_hours_val];
    draw_digit(ctx, bmp, GPoint(x, 0));
    x += gbitmap_get_bounds(bmp).size.w + 2;
  } else {
    GBitmap *tens = s_num_large[s_hours_val / 10];
    GBitmap *ones = s_num_large[s_hours_val % 10];
    draw_digit(ctx, tens, GPoint(x, 0));
    x += gbitmap_get_bounds(tens).size.w + 2;
    draw_digit(ctx, ones, GPoint(x, 0));
    x += gbitmap_get_bounds(ones).size.w + 2;
  }

  // Minutes (small digits)
  GBitmap *min_tens = s_num_small[s_minutes_val / 10];
  GBitmap *min_ones = s_num_small[s_minutes_val % 10];
  draw_digit(ctx, min_tens, GPoint(x, HOURS_HEIGHT - 35));
  x += gbitmap_get_bounds(min_tens).size.w + 2;
  draw_digit(ctx, min_ones, GPoint(x, HOURS_HEIGHT - 35));
  x += gbitmap_get_bounds(min_ones).size.w + 2;

  // AM/PM indicator (12h mode only)
  if (!is_24h) {
    graphics_context_set_text_color(ctx, GColorBlack);
    graphics_draw_text(ctx, s_is_pm ? "PM" : "AM",
                       fonts_get_system_font(FONT_KEY_GOTHIC_14),
                       GRect(x, HOURS_HEIGHT - 14, bounds.size.w - x, 14),
                       GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  time_update();
}

void time_update(void) {
  time_t temp = time(NULL);
  struct tm *t = localtime(&temp);

  bool is_24h = clock_is_24h_style();
  s_hours_val   = is_24h ? t->tm_hour : (t->tm_hour % 12 ?: 12);
  s_minutes_val = t->tm_min;
  s_is_pm       = t->tm_hour >= 12;

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
