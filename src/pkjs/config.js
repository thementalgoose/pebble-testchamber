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
  {
    type: 'submit',
    defaultValue: 'Save',
  },
];
