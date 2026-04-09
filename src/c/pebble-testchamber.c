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

  GRect box_1 = GRect(EDGE_LEFT + ((PANEL_WIDTH + PANEL_INTER_SPACING) * 0), h - (EDGE_BOTTOM + PANEL_HEIGHT), PANEL_WIDTH, PANEL_HEIGHT);
  GRect box_2 = GRect(EDGE_LEFT + ((PANEL_WIDTH + PANEL_INTER_SPACING) * 1), h - (EDGE_BOTTOM + PANEL_HEIGHT), PANEL_WIDTH, PANEL_HEIGHT);
  GRect box_3 = GRect(EDGE_LEFT + ((PANEL_WIDTH + PANEL_INTER_SPACING) * 2), h - (EDGE_BOTTOM + PANEL_HEIGHT), PANEL_WIDTH, PANEL_HEIGHT);

  graphics_draw_rect(ctx, box_1);
  graphics_draw_rect(ctx, box_2);
  graphics_draw_rect(ctx, box_3);

  if (PANEL_EXTRA_COLUMN) { 
    GRect box_4 = GRect(EDGE_LEFT + ((PANEL_WIDTH + PANEL_INTER_SPACING) * 3), h - (EDGE_BOTTOM + PANEL_HEIGHT), PANEL_WIDTH, PANEL_HEIGHT);
    graphics_draw_rect(ctx, box_4);
  }

  if (PANEL_DUAL_ROW) { 
    GRect box_5 = GRect(EDGE_LEFT + ((PANEL_WIDTH + PANEL_INTER_SPACING) * 0), h - ((PANEL_HEIGHT * 2) + EDGE_BOTTOM + PANEL_INTER_SPACING), PANEL_WIDTH, PANEL_HEIGHT);
    GRect box_6 = GRect(EDGE_LEFT + ((PANEL_WIDTH + PANEL_INTER_SPACING) * 1), h - ((PANEL_HEIGHT * 2) + EDGE_BOTTOM + PANEL_INTER_SPACING), PANEL_WIDTH, PANEL_HEIGHT);
    GRect box_7 = GRect(EDGE_LEFT + ((PANEL_WIDTH + PANEL_INTER_SPACING) * 2), h - ((PANEL_HEIGHT * 2) + EDGE_BOTTOM + PANEL_INTER_SPACING), PANEL_WIDTH, PANEL_HEIGHT);

    graphics_draw_rect(ctx, box_5);
    graphics_draw_rect(ctx, box_6);
    graphics_draw_rect(ctx, box_7);

    if (PANEL_EXTRA_COLUMN) { 
      GRect box_8 = GRect(EDGE_LEFT + ((PANEL_WIDTH + PANEL_INTER_SPACING) * 3), h - ((PANEL_HEIGHT * 2) + EDGE_BOTTOM + PANEL_INTER_SPACING), PANEL_WIDTH, PANEL_HEIGHT);

      graphics_draw_rect(ctx, box_8);
    }
  }

}

static void canvas_draw_panel_content(Layer *layer, GContext *ctx) { 
  // GRect bounds = layer_get_bounds(layer);
  // int16_t w = bounds.size.w;
  // int16_t h = bounds.size.h;

  // GRect bound_1 = GRect(START_MARGIN, h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM), PANEL_BOX_SZ, PANEL_BOX_SZ);
  // GRect bound_2 = GRect(START_MARGIN + (1 * (PANEL_BOX_SZ + PANEL_BOX_SPACING)), h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM) + 1, PANEL_BOX_SZ, PANEL_BOX_SZ);
  // GRect bound_3 = GRect(START_MARGIN + (2 * (PANEL_BOX_SZ + PANEL_BOX_SPACING)), h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM) + 1, PANEL_BOX_SZ, PANEL_BOX_SZ);
  // GRect bound_4 = GRect(START_MARGIN + (3 * (PANEL_BOX_SZ + PANEL_BOX_SPACING)), h - (PANEL_BOX_SZ + PANEL_BOX_BOTTOM) + 1, PANEL_BOX_SZ, PANEL_BOX_SZ);

  // time_t now = time(NULL);
  // struct tm *t = localtime(&now);
  // int weekday = (t->tm_wday == 0) ? 7 : t->tm_wday;

  // // Bottom panel row: 3 equal boxes
  // panels_draw_aperture(ctx, bound_1, weekday);

  // panels_draw_panel(ctx, bound_2, PANEL_BALLDROP);
  // panels_draw_panel(ctx, bound_3, PANEL_ATLAS_PBODY);
}

static void canvas_top_divider(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  int16_t w = bounds.size.w;
  int16_t h = bounds.size.h;
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, GPoint(EDGE_LEFT, EDGE_TOP), GPoint(w - EDGE_RIGHT, EDGE_TOP));
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  int16_t w = bounds.size.w;
  int16_t h = bounds.size.h;

  // -----------------------------------------------------------------
  // From Top 
  // -----------------------------------------------------------------
  // Draw the top line
  s_canvas_layer = layer_create(bounds);
  layer_set_update_proc(s_canvas_layer, canvas_top_divider);
  layer_add_child(window_layer, s_canvas_layer);

  // Time layer — hours + minutes digit images
  Layer *time_layer = time_layer_create(GRect(EDGE_LEFT, EDGE_TOP + HOURS_TOP, w - (EDGE_LEFT + EDGE_RIGHT), HOURS_HEIGHT));
  layer_add_child(window_layer, time_layer);

  // -----------------------------------------------------------------
  // From Bottom 
  // -----------------------------------------------------------------

  // if (PANEL_EXTRA_COLUMN)
  // 3x1
  // 4x2
  


  // Panels
  s_canvas_panels = layer_create(bounds);
  layer_set_update_proc(s_canvas_panels, canvas_draw_panels);
  layer_add_child(window_layer, s_canvas_panels);

  int16_t panel_height = PANEL_DUAL_ROW ? ((PANEL_HEIGHT * 2) + PANEL_INTER_SPACING + EDGE_BOTTOM) : (EDGE_BOTTOM + PANEL_HEIGHT);
  int16_t battery_y = h - (panel_height + BATTERY_SPACING + BATTERY_HEIGHT);

  // Battery progress bar
  Layer *battery_layer = battery_layer_create(GRect(EDGE_LEFT, battery_y, w - EDGE_RIGHT, BATTERY_HEIGHT));
  layer_add_child(window_layer, battery_layer);
  
  // Date label
  TextLayer *date_layer = time_date_layer_create(GRect(EDGE_LEFT, battery_y - (DATE_BOTTOM + DATE_HEIGHT), w - (EDGE_LEFT + EDGE_RIGHT), DATE_HEIGHT));
  layer_add_child(window_layer, text_layer_get_layer(date_layer));
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
