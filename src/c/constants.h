#pragma once

// ---------------------------------------------------------------------------
// Layout - All
// ---------------------------------------------------------------------------
#define EDGE_LEFT               PBL_IF_ROUND_ELSE(44, 10)
#define EDGE_TOP                PBL_IF_ROUND_ELSE(10, 6)
#define EDGE_BOTTOM             PBL_IF_ROUND_ELSE(10, 2)
#define EDGE_RIGHT              2        
#define DIVIDER_HEIGHT          1
// ---------------------------------------------------------------------------
// Layout - From Top
// ---------------------------------------------------------------------------
// Layout - Time
#define HOURS_HEIGHT            70
#define HOURS_TOP               PBL_IF_ROUND_ELSE(10, 6)
#define MINUTES_OFFSET_X        48
#define MINUTES_OFFSET_Y        36
// Layout - Computed
#define FROM_TOP_HEIGHT         EDGE_TOP + DIVIDER_HEIGHT + HOURS_TOP + HOURS_HEIGHT
// ---------------------------------------------------------------------------
// Layout - From Bottom
// ---------------------------------------------------------------------------
// Layout - Panels
#define PANEL_WIDTH             42
#define PANEL_HEIGHT            42
#define PANEL_INTER_SPACING     2
// Layout - Battery
#define BATTERY_HEIGHT          12
#define BATTERY_SPACING         2
#define BATTERY_BOTTOM          2
#define BAR_LINE_W              1
#define BAR_LINE_GAP            2
// Layout - Divider
#define DIVIDER_BOTTOM          2 
// Layout - Date
#define DATE_FONT               fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD)
#define DATE_HEIGHT             18
#define DATE_BOTTOM             2
// Layout - Computed
#define ABOVE_PANELS_HEIGHT     DATE_HEIGHT + DATE_BOTTOM + DIVIDER_HEIGHT + DIVIDER_BOTTOM + BATTERY_HEIGHT + BATTERY_SPACING
#define PANEL_DUAL_ROW          h - (FROM_TOP_HEIGHT + ABOVE_PANELS_HEIGHT) > (PANEL_HEIGHT + PANEL_INTER_SPACING) * 2                  
#define PANEL_EXTRA_COLUMN      w - (EDGE_LEFT + EDGE_RIGHT) > (PANEL_WIDTH + PANEL_INTER_SPACING) * 3
// ---------------------------------------------------------------------------
