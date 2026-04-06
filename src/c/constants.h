#pragma once

// ---------------------------------------------------------------------------
// Layout — margins & dividers
// ---------------------------------------------------------------------------
#define START_MARGIN      10
#define DIVIDER_TOP_Y     PBL_IF_ROUND_ELSE(44, 2)
#define DIVIDER_BOT_Y     (DATE_Y + 18)

// ---------------------------------------------------------------------------
// Layout — time / hours block
// ---------------------------------------------------------------------------
#define HOURS_Y           PBL_IF_ROUND_ELSE(50, 6)
#define HOURS_H           70
#define MINUTES_OFFSET_X  48
#define MINUTES_OFFSET_Y  36

// ---------------------------------------------------------------------------
// Layout — date row
// ---------------------------------------------------------------------------
#define DATE_Y            (HOURS_Y + HOURS_H + 4)



// ---------------------------------------------------------------------------
// Layout — battery bar
// ---------------------------------------------------------------------------
#define BATTERY_H         8
#define BATTERY_SPACING   2

#define BAR_LINE_W        1
#define BAR_LINE_GAP      2

// ---------------------------------------------------------------------------
// Layout — bottom panel row
// ---------------------------------------------------------------------------
#define PANEL_BOX_SZ      42
#define PANEL_BOX_SPACING 2 
#define PANEL_BOX_BOTTOM  4 
