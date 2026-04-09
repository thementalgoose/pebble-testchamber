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
    size: 1,
  },
  {
    type: 'section',
    items: [
      {
        type: 'heading',
        defaultValue: 'Bottom Row',
      },
      {
        type: 'select',
        messageKey: 'PANEL_SLOT_1',
        label: 'Slot 1',
        defaultValue: 3,
        options: PANEL_OPTIONS,
      },
      {
        type: 'select',
        messageKey: 'PANEL_SLOT_2',
        label: 'Slot 2',
        defaultValue: 2,
        options: PANEL_OPTIONS,
      },
      {
        type: 'select',
        messageKey: 'PANEL_SLOT_3',
        label: 'Slot 3',
        defaultValue: 0,
        options: PANEL_OPTIONS,
      },
      {
        type: 'select',
        messageKey: 'PANEL_SLOT_4',
        label: 'Slot 4 (wide displays only)',
        defaultValue: 20,
        options: PANEL_OPTIONS,
      },
    ],
  },
  {
    type: 'section',
    items: [
      {
        type: 'heading',
        defaultValue: 'Top Row (tall displays only)',
      },
      {
        type: 'select',
        messageKey: 'PANEL_SLOT_5',
        label: 'Slot 5',
        defaultValue: 19,
        options: PANEL_OPTIONS,
      },
      {
        type: 'select',
        messageKey: 'PANEL_SLOT_6',
        label: 'Slot 6',
        defaultValue: 11,
        options: PANEL_OPTIONS,
      },
      {
        type: 'select',
        messageKey: 'PANEL_SLOT_7',
        label: 'Slot 7',
        defaultValue: 6,
        options: PANEL_OPTIONS,
      },
      {
        type: 'select',
        messageKey: 'PANEL_SLOT_8',
        label: 'Slot 8 (wide displays only)',
        defaultValue: 17,
        options: PANEL_OPTIONS,
      },
    ],
  },
  {
    type: 'submit',
    defaultValue: 'Save',
  },
];
