var PANEL_OPTIONS = [
  { label: 'Companion Cube',  value: 0  },
  { label: 'Cube Drop',       value: 1  },
  { label: 'Atlas & P-Body',  value: 2  },
  { label: 'Ball Drop',       value: 3  },
  { label: 'Ball Face',       value: 4  },
  { label: 'Bounce',          value: 5  },
  { label: 'Cake',            value: 6  },
  { label: 'Cube Face',       value: 7  },
  { label: 'Dodge',           value: 8  },
  { label: 'Drop',            value: 9  },
  { label: 'Drowning',        value: 10 },
  { label: 'GLaDOS',          value: 11 },
  { label: 'Jump Pad',        value: 12 },
  { label: 'Laser Cube',      value: 13 },
  { label: 'Portal Bridge',   value: 14 },
  { label: 'Portal Fly',      value: 15 },
  { label: 'Portal Fly 2',    value: 16 },
  { label: 'Potato',          value: 17 },
  { label: 'Slide Run',       value: 18 },
  { label: 'Turret',          value: 19 },
  { label: 'Wheatley',        value: 20 },
];

function buildTable(columns, rows, isHideFinal) { 
  var result = "<p>Layout of the panels on the watch</p><br/>";
  result += `<table style="border: 1px solid black; width: 100%; table-layout: fixed;">`;
  for (let r = 0; r < rows; r++) { 
    result += `<tr style="border: 1px solid black;">`;
    for (let c = 1; c <= columns; c++) { 
      if (r == rows - 1 && c == columns && isHideFinal) { 
        result += `<th style="border: 1px solid black;"></th>`;
      } else { 
        result += `<th style="border: 1px solid black;">Panel ${(r * columns) + c}</th>`;
      }
    }
    result += `</tr>`;
  }
  result += `</table>`;
  return result;
}

let header = {
  type: 'heading',
  defaultValue: 'Panels',
}

function configurationSquareSmall() { 
  return { 
    type: 'section',
    capabilities: ["DISPLAY_144x168"],
    items: [
      header,
      {
        type: "text",
        defaultValue: buildTable(3, 1, false)
      },
      {
        type: "select",
        messageKey: "PANEL_1",
        defaultValue: 0,
        label: "Panel 1",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_2",
        defaultValue: 1,
        label: "Panel 2",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_3",
        defaultValue: 2,
        label: "Panel 3",
        options: PANEL_OPTIONS
      }
    ]
  }
}

function configurationSquareLarge() { 
  return { 
    type: 'section',
    capabilities: ["DISPLAY_200x228"],
    items: [
      header,
      {
        type: "text",
        defaultValue: buildTable(4, 2, false)
      },
      {
        type: "select",
        messageKey: "PANEL_5",
        defaultValue: 0,
        label: "Panel 1",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_6",
        defaultValue: 1,
        label: "Panel 2",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_7",
        defaultValue: 2,
        label: "Panel 3",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_8",
        defaultValue: 2,
        label: "Panel 4",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_1",
        defaultValue: 2,
        label: "Panel 5",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_2",
        defaultValue: 2,
        label: "Panel 6",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_3",
        defaultValue: 2,
        label: "Panel 7",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_4",
        defaultValue: 2,
        label: "Panel 8",
        options: PANEL_OPTIONS
      }
    ]
  }
}

function configurationRoundSmall() { 
  return { 
    type: 'section',
    capabilities: ["DISPLAY_180x180_ROUND"],
    items: [
      header,
      {
        type: "text",
        defaultValue: buildTable(3, 1, true)
      },
      {
        type: "select",
        messageKey: "PANEL_1",
        defaultValue: 0,
        label: "Panel 1",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_2",
        defaultValue: 1,
        label: "Panel 2",
        options: PANEL_OPTIONS
      }
    ]
  }
}

function configurationRoundLarge() { 
  return { 
    type: 'section',
    capabilities: ["DISPLAY_260x260_ROUND"],
    items: [
      header,
      {
        type: "text",
        defaultValue: buildTable(4, 2, true)
      },
      {
        type: "select",
        messageKey: "PANEL_5",
        defaultValue: 0,
        label: "Panel 1",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_6",
        defaultValue: 1,
        label: "Panel 2",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_7",
        defaultValue: 2,
        label: "Panel 3",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_8",
        defaultValue: 2,
        label: "Panel 4",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_1",
        defaultValue: 2,
        label: "Panel 5",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_2",
        defaultValue: 2,
        label: "Panel 6",
        options: PANEL_OPTIONS
      },
      {
        type: "select",
        messageKey: "PANEL_3",
        defaultValue: 2,
        label: "Panel 7",
        options: PANEL_OPTIONS
      }
    ]
  }
}

module.exports = [
  {
    type: 'heading',
    defaultValue: 'Test Chamber',
    size: 2,
  },
  {
    type: 'text',
    defaultValue: 'Configure below',
    size: 5,
  },
  {
    type: 'section',
    items: [
      {
        type: 'heading',
        defaultValue: 'Battery Indicator',
      },
      {
        type: 'toggle',
        messageKey: 'BATTERY_INDICATOR',
        label: 'Show battery percentage',
        defaultValue: true,
      }
    ]
  },
  configurationSquareSmall(),
  configurationSquareLarge(),
  configurationRoundSmall(),
  configurationRoundLarge(),
  {
    type: 'submit',
    defaultValue: 'Save',
  },
];
