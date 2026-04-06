#include <pebble.h>
#include "panels.h"
#include "battery.h"
#include "time.h"

// Layout constants (rectangular display: 144x168)
#define START_MARGIN      10
#define DIVIDER_TOP_Y     (PBL_IF_ROUND_ELSE(44, 2) + START_MARGIN)
#define HOURS_Y           (PBL_IF_ROUND_ELSE(50, 6) + START_MARGIN)
#define HOURS_H           70
#define DIVIDER_BOT_Y     (HOURS_Y + HOURS_H + 8)
#define DATE_Y            (DIVIDER_BOT_Y + 6)
#define CUBE_SZ           PBL_IF_ROUND_ELSE(40, 50)
#define BATTERY_Y         (DATE_Y + 28)
#define BATTERY_H         8

static Window     *s_window;
static Layer      *s_canvas_layer;
static BitmapLayer *s_cube_layer;
static GBitmap    *s_cube_bitmap;

static void canvas_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  int16_t w = bounds.size.w;
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, GPoint(START_MARGIN, DIVIDER_TOP_Y), GPoint(w - 1, DIVIDER_TOP_Y));
  graphics_draw_line(ctx, GPoint(START_MARGIN, DIVIDER_BOT_Y), GPoint(w - 1, DIVIDER_BOT_Y));
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  int16_t w = bounds.size.w;

  // Full-screen canvas layer for drawing dividers
  s_canvas_layer = layer_create(bounds);
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
  layer_add_child(window_layer, s_canvas_layer);

  // Time layer — hours + minutes digit images
  Layer *time_layer = time_layer_create(GRect(START_MARGIN, HOURS_Y, w - START_MARGIN * 2, HOURS_H));
  layer_add_child(window_layer, time_layer);

  // Date label
  TextLayer *date_layer = time_date_layer_create(GRect(START_MARGIN, DATE_Y, w - START_MARGIN * 2, 24));
  layer_add_child(window_layer, text_layer_get_layer(date_layer));

  // Battery progress bar
  Layer *battery_layer = battery_layer_create(GRect(START_MARGIN, BATTERY_Y, w - START_MARGIN * 2, BATTERY_H));
  layer_add_child(window_layer, battery_layer);

  // Companion Cube panel
  s_cube_bitmap = panels_load(PANEL_CUBE_DROP);
  s_cube_layer = bitmap_layer_create(GRect((w - CUBE_SZ) / 2, DATE_Y + 30, CUBE_SZ, CUBE_SZ));
  bitmap_layer_set_bitmap(s_cube_layer, s_cube_bitmap);
  bitmap_layer_set_compositing_mode(s_cube_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_cube_layer));
}

static void window_unload(Window *window) {
  layer_destroy(s_canvas_layer);
  time_destroy();
  battery_layer_destroy();
  bitmap_layer_destroy(s_cube_layer);
  panels_unload(s_cube_bitmap);
}

static void init(void) {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers){
    .load   = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);

  time_update();
}

static void deinit(void) {
  window_destroy(s_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
