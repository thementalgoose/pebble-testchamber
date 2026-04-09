#include "disconnection.h"

static Layer *s_disconnection_layer;

static void disconnection_draw(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

static void bluetooth_callback(bool connected) {
  layer_set_hidden(s_disconnection_layer, connected);
}

Layer *disconnection_layer_create(GRect frame) {
  s_disconnection_layer = layer_create(frame);
  layer_set_update_proc(s_disconnection_layer, disconnection_draw);

  connection_service_subscribe((ConnectionHandlers){
    .pebble_app_connection_handler = bluetooth_callback,
  });
  layer_set_hidden(s_disconnection_layer, connection_service_peek_pebble_app_connection());

  return s_disconnection_layer;
}

void disconnection_layer_destroy(void) {
  connection_service_unsubscribe();
  layer_destroy(s_disconnection_layer);
  s_disconnection_layer = NULL;
}
