#include "battery.h"
#include "constants.h"

static Layer *s_battery_layer;
static int    s_charge_percent = 100;

static void battery_callback(BatteryChargeState state) {
  s_charge_percent = state.charge_percent;
  layer_mark_dirty(s_battery_layer);
}

static void battery_layer_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);

  int line_step   = BAR_LINE_W + BAR_LINE_GAP;
  int total_lines = bounds.size.w / line_step;
  int filled      = (total_lines * s_charge_percent) / 100;

  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_line(ctx, GPoint(0, 0), GPoint(bounds.size.w, 0));
  for (int i = 0; i < filled; i++) {
    int16_t x = i * line_step;
    for (int16_t dx = 0; dx < BAR_LINE_W; dx++) {
      graphics_draw_line(ctx,
        GPoint(x + dx, 4),
        GPoint(x + dx, bounds.size.h - 1));
    }
  }
}

Layer *battery_layer_create(GRect frame) {

  s_battery_layer = layer_create(frame);
  layer_set_update_proc(s_battery_layer, battery_layer_update_proc);

  s_charge_percent = battery_state_service_peek().charge_percent;
  battery_state_service_subscribe(battery_callback);

  return s_battery_layer;
}

void battery_layer_destroy(void) {
  battery_state_service_unsubscribe();
  layer_destroy(s_battery_layer);
  s_battery_layer = NULL;
}
