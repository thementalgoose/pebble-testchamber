#include "time.h"
#include "panels.h"

#define HOURS_H          70
#define MINUTES_OFFSET_X (38 + 10 + 10)  // matches START_MARGIN offset
#define MINUTES_OFFSET_Y 36

static Layer     *s_time_layer;
static TextLayer *s_date_layer;

static int s_hours_val   = 0;
static int s_minutes_val = 0;

static void time_layer_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  panels_draw_hours(ctx, GRect(0, 0, bounds.size.w, HOURS_H), s_hours_val);
  panels_draw_minutes(ctx, GRect(MINUTES_OFFSET_X, MINUTES_OFFSET_Y,
                                 bounds.size.w - MINUTES_OFFSET_X,
                                 HOURS_H - MINUTES_OFFSET_Y), s_minutes_val);
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
  strftime(s_date, sizeof(s_date), "%d %b", t);
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
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentLeft);
  return s_date_layer;
}

void time_destroy(void) {
  tick_timer_service_unsubscribe();
  layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  panels_unload_digits();
}
