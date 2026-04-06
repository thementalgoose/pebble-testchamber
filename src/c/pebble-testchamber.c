#include <pebble.h>
#include "constants.h"
#include "panels.h"
#include "battery.h"
#include "time.h"

static Window     *s_window;
static Layer      *s_canvas_layer;
static Layer      *s_canvas_panels;
static Layer      *s_canvas_panel_content;
static BitmapLayer *s_cube_layer;
static GBitmap    *s_cube_bitmap;

static void canvas_draw_panels(Layer *layer, GContext *ctx) { 
  GRect bounds = layer_get_bounds(layer);
  int16_t w = bounds.size.w;
  int16_t h = bounds.size.h;

  graphics_context_set_stroke_color(ctx, GColorBlack);
  int16_t width_of_3 = (PANEL_BOX_SZ + PANEL_BOX_SPACING) * 3;

  graphics_draw_rect(ctx, GRect(START_MARGIN + (0 * (PANEL_BOX_SZ + PANEL_BOX_SPACING)), h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM), PANEL_BOX_SZ, PANEL_BOX_SZ));
  graphics_draw_rect(ctx, GRect(START_MARGIN + (1 * (PANEL_BOX_SZ + PANEL_BOX_SPACING)), h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM), PANEL_BOX_SZ, PANEL_BOX_SZ));
  graphics_draw_rect(ctx, GRect(START_MARGIN + (2 * (PANEL_BOX_SZ + PANEL_BOX_SPACING)), h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM), PANEL_BOX_SZ, PANEL_BOX_SZ));
  if (width_of_3 + (PANEL_BOX_SZ + PANEL_BOX_SPACING + START_MARGIN) < w) { 
    graphics_draw_rect(ctx, GRect(START_MARGIN + (3 * (PANEL_BOX_SZ + PANEL_BOX_SPACING)), h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM), PANEL_BOX_SZ, PANEL_BOX_SZ));
  }
}

static void canvas_draw_panel_content(Layer *layer, GContext *ctx) { 
  GRect bounds = layer_get_bounds(layer);
  int16_t w = bounds.size.w;
  int16_t h = bounds.size.h;

  GRect bound_1 = GRect(START_MARGIN, h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM), PANEL_BOX_SZ, PANEL_BOX_SZ);
  GRect bound_2 = GRect(START_MARGIN + (1 * (PANEL_BOX_SZ + PANEL_BOX_SPACING)), h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM) + 1, PANEL_BOX_SZ, PANEL_BOX_SZ);
  GRect bound_3 = GRect(START_MARGIN + (2 * (PANEL_BOX_SZ + PANEL_BOX_SPACING)), h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM) + 1, PANEL_BOX_SZ, PANEL_BOX_SZ);
  GRect bound_4 = GRect(START_MARGIN + (3 * (PANEL_BOX_SZ + PANEL_BOX_SPACING)), h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM) + 1, PANEL_BOX_SZ, PANEL_BOX_SZ);

  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  int weekday = (t->tm_wday == 0) ? 7 : t->tm_wday;

  // Bottom panel row: 3 equal boxes
  graphics_draw_rect(ctx, bound_1);
  panels_draw_aperture(ctx, bound_1, weekday);
}

static void canvas_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  int16_t w = bounds.size.w;
  int16_t h = bounds.size.h;
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, GPoint(START_MARGIN, DIVIDER_TOP_Y), GPoint(w - 1, DIVIDER_TOP_Y));

  graphics_draw_line(ctx,
    GPoint(START_MARGIN, h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM + BATTERY_H + (BATTERY_SPACING + 4))), 
    GPoint(w - 1, h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM + BATTERY_H + (BATTERY_SPACING + 4)))
  );
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  int16_t w = bounds.size.w;
  int16_t h = bounds.size.h;

  // Full-screen canvas layer for drawing dividers
  s_canvas_layer = layer_create(bounds);
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
  layer_add_child(window_layer, s_canvas_layer);

  // Panels content
  s_canvas_panel_content = layer_create(bounds);
  layer_set_update_proc(s_canvas_panel_content, canvas_draw_panel_content);
  layer_add_child(window_layer, s_canvas_panel_content);
  
  // Panels
  s_canvas_panels = layer_create(bounds);
  layer_set_update_proc(s_canvas_panels, canvas_draw_panels);
  layer_add_child(window_layer, s_canvas_panels);

  // Battery progress bar
  Layer *battery_layer = battery_layer_create(GRect(START_MARGIN, h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM + BATTERY_SPACING + BATTERY_H), w - START_MARGIN * 2, BATTERY_H));
  layer_add_child(window_layer, battery_layer);

  int16_t h_of_top_of_battery = h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM + (BATTERY_SPACING * 2) + BATTERY_H);
  
  // Date label
  TextLayer *date_layer = time_date_layer_create(GRect(START_MARGIN, h_of_top_of_battery - 24, w - START_MARGIN * 2, 24));
  layer_add_child(window_layer, text_layer_get_layer(date_layer));

  // Time layer — hours + minutes digit images
  Layer *time_layer = time_layer_create(GRect(START_MARGIN, HOURS_Y, w - START_MARGIN * 2, HOURS_H));
  layer_add_child(window_layer, time_layer);
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
