#include "panels.h"
#include "constants.h"

// ---------------------------------------------------------------------------
// Panel bitmaps
// ---------------------------------------------------------------------------

static const uint32_t s_panel_resource_ids[PANEL_COUNT] = {
  [PANEL_COMPANION_CUBE] = RESOURCE_ID_IMAGE_PANEL_COMPANIONCUBE,
  [PANEL_CUBE_DROP]      = RESOURCE_ID_IMAGE_PANEL_CUBEDROP,
  [PANEL_ATLAS_PBODY]    = RESOURCE_ID_IMAGE_PANEL_ATLAS_PBODY,
  [PANEL_BALLDROP]       = RESOURCE_ID_IMAGE_PANEL_BALLDROP,
  [PANEL_BALLFACE]       = RESOURCE_ID_IMAGE_PANEL_BALLFACE,
  [PANEL_BOUNCE]         = RESOURCE_ID_IMAGE_PANEL_BOUNCE,
  [PANEL_CAKE]           = RESOURCE_ID_IMAGE_PANEL_CAKE,
  [PANEL_CUBEFACE]       = RESOURCE_ID_IMAGE_PANEL_CUBEFACE,
  [PANEL_DODGE]          = RESOURCE_ID_IMAGE_PANEL_DODGE,
  [PANEL_DROP]           = RESOURCE_ID_IMAGE_PANEL_DROP,
  [PANEL_DROWNING]       = RESOURCE_ID_IMAGE_PANEL_DROWNING,
  [PANEL_GLADOS]         = RESOURCE_ID_IMAGE_PANEL_GLADOS,
  [PANEL_JUMPPAD]        = RESOURCE_ID_IMAGE_PANEL_JUMPPAD,
  [PANEL_LASERCUBE]      = RESOURCE_ID_IMAGE_PANEL_LASERCUBE,
  [PANEL_PORTALBRIDGE]   = RESOURCE_ID_IMAGE_PANEL_PORTALBRIDGE,
  [PANEL_PORTALFLY]      = RESOURCE_ID_IMAGE_PANEL_PORTALFLY,
  [PANEL_PORTALFLY2]     = RESOURCE_ID_IMAGE_PANEL_PORTALFLY2,
  [PANEL_POTATO]         = RESOURCE_ID_IMAGE_PANEL_POTATO,
  [PANEL_SLIDERUN]       = RESOURCE_ID_IMAGE_PANEL_SLIDERUN,
  [PANEL_TURRET]         = RESOURCE_ID_IMAGE_PANEL_TURRET,
  [PANEL_WHEATLEY]       = RESOURCE_ID_IMAGE_PANEL_WHEATLEY,
};

static const uint32_t s_aperture_resource_ids[8] = {
  RESOURCE_ID_IMAGE_PANEL_APERATURE_0,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_1,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_2,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_3,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_4,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_5,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_6,
  RESOURCE_ID_IMAGE_PANEL_APERATURE_7,
};

GBitmap *panels_load(Panel panel) {
  return gbitmap_create_with_resource(s_panel_resource_ids[panel]);
}

void panels_unload(GBitmap *bitmap) {
  gbitmap_destroy(bitmap);
}

void panels_draw_panel(GContext *ctx, GRect box, Panel panel, GPoint text_origin, const char *text) {
  if (panel == PANEL_APERTURE) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int level = (t->tm_wday == 0) ? 7 : t->tm_wday;
    GBitmap *bmp = gbitmap_create_with_resource(s_aperture_resource_ids[level]);
    graphics_draw_bitmap_in_rect(ctx, bmp, box);
    gbitmap_destroy(bmp);
    return;
  }
  GBitmap *bmp = gbitmap_create_with_resource(s_panel_resource_ids[panel]);
  graphics_draw_bitmap_in_rect(ctx, bmp, box);
  gbitmap_destroy(bmp);
  if (text) {
    graphics_draw_text(ctx, text, PANEL_TEXT, GRect(text_origin.x, text_origin.y, box.size.w, box.size.h), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  }
  if (panel == PANEL_SLIDERUN) {
    HealthMetric metric = HealthMetricStepCount;
    HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, time_start_of_today(), time(NULL));
    if (mask & HealthServiceAccessibilityMaskAvailable) {
      HealthValue steps = health_service_sum(metric, time_start_of_today(), time(NULL));
      static char s_steps_buf[8];
      snprintf(s_steps_buf, sizeof(s_steps_buf), "%d", (int)steps);
      graphics_context_set_text_color(ctx, GColorBlack);
      graphics_draw_text(ctx, s_steps_buf, PANEL_TEXT, GRect(box.origin.x, box.origin.y, box.size.w, box.size.h), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);
    }
  }
}