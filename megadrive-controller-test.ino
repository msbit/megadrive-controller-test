enum struct Pin: uint8_t {
  UP_Z = 5,       //  serial pin 1, Arduino pin 1 is used for serial TX
  DOWN_Y = 2,     //  serial pin 2
  LEFT_X = 3,     //  serial pin 3
  RIGHT_MODE = 4, //  serial pin 4
  A_B = 6,        //  serial pin 6
  SELECT = 7,     //  serial pin 7
  START_C = 9,    //  serial pin 9
};

enum struct Button: uint8_t {
  UP, DOWN, LEFT, RIGHT,
  START, A, B, C,
  MODE, X, Y, Z,
};

constexpr Button buttons[] = {
  Button::UP, Button::DOWN, Button::LEFT, Button::RIGHT,
  Button::START, Button::A, Button::B, Button::C,
  Button::MODE, Button::X, Button::Y, Button::Z,
};

struct ButtonMapping {
  const Button button;
  const Pin pin;
};

struct ButtonLabel {
  const Button button;
  const char label[2];
};

constexpr ButtonLabel labels[] = {
  {Button::UP, "U"},
  {Button::DOWN, "D"},
  {Button::LEFT, "L"},
  {Button::RIGHT, "R"},
  {Button::START, "S"},
  {Button::A, "A"},
  {Button::B, "B"},
  {Button::C, "C"},
  {Button::MODE, "M"},
  {Button::X, "X"},
  {Button::Y, "Y"},
  {Button::Z,  "Z"},
};

constexpr ButtonMapping low[] = {
  {Button::A, Pin::A_B},
  {Button::START, Pin::START_C},
};

constexpr ButtonMapping high3Button[] = {
  {Button::UP, Pin::UP_Z},
  {Button::DOWN, Pin::DOWN_Y},
  {Button::LEFT, Pin::LEFT_X},
  {Button::RIGHT, Pin::RIGHT_MODE},
  {Button::B, Pin::A_B},
  {Button::C, Pin::START_C},
};

constexpr ButtonMapping high6Button[] = {
  {Button::Z, Pin::UP_Z},
  {Button::Y, Pin::DOWN_Y},
  {Button::X, Pin::LEFT_X},
  {Button::MODE, Pin::RIGHT_MODE},
  {Button::B, Pin::A_B},
  {Button::C, Pin::START_C},
};

void printButtons(const bool[12]);
void blinkButtons(const bool[12]);

void _pinMode(Pin, uint8_t);
int _digitalRead(Pin);
void _digitalWrite(Pin, uint8_t);

constexpr auto period = 1000 / 60;
auto loopcount = 0;

void setup() {
  Serial.begin(9600);

  _pinMode(Pin::UP_Z, INPUT_PULLUP);
  _pinMode(Pin::DOWN_Y, INPUT_PULLUP);
  _pinMode(Pin::LEFT_X, INPUT_PULLUP);
  _pinMode(Pin::RIGHT_MODE, INPUT_PULLUP);
  _pinMode(Pin::A_B, INPUT_PULLUP);
  _pinMode(Pin::START_C, INPUT_PULLUP);

  _pinMode(Pin::SELECT, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  _digitalWrite(Pin::SELECT, HIGH);
}

void loop() {
  bool buttonStates[] = {
    HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,
    HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,
  };

  _digitalWrite(Pin::SELECT, LOW);

  // Phase 1, low
  for (const auto &mapping : low) {
    buttonStates[static_cast<uint8_t>(mapping.button)] = _digitalRead(mapping.pin);
  }

  _digitalWrite(Pin::SELECT, HIGH);

  // Phase 1, high
  for (const auto &mapping : high3Button) {
    buttonStates[static_cast<uint8_t>(mapping.button)] = _digitalRead(mapping.pin);
  }

  _digitalWrite(Pin::SELECT, LOW);

  // Phase 2, low
  for (const auto &mapping : low) {
    buttonStates[static_cast<uint8_t>(mapping.button)] = _digitalRead(mapping.pin);
  }

  _digitalWrite(Pin::SELECT, HIGH);

  // Phase 2, high
  for (const auto &mapping : high3Button) {
    buttonStates[static_cast<uint8_t>(mapping.button)] = _digitalRead(mapping.pin);
  }

  _digitalWrite(Pin::SELECT, LOW);

  if (_digitalRead(Pin::UP_Z) == LOW) {
    // Phase 3, low
    for (const auto &mapping : low) {
      buttonStates[static_cast<uint8_t>(mapping.button)] = _digitalRead(mapping.pin);
    }

    _digitalWrite(Pin::SELECT, HIGH);

    // Phase 3, high
    for (const auto &mapping : high6Button) {
      buttonStates[static_cast<uint8_t>(mapping.button)] = _digitalRead(mapping.pin);
    }

    _digitalWrite(Pin::SELECT, LOW);

    // Phase 4, low
    for (const auto &mapping : low) {
      buttonStates[static_cast<uint8_t>(mapping.button)] = _digitalRead(mapping.pin);
    }

    _digitalWrite(Pin::SELECT, HIGH);

    // Phase 3, high
    for (const auto &mapping : high3Button) {
      buttonStates[static_cast<uint8_t>(mapping.button)] = _digitalRead(mapping.pin);
    }
  } else {
    _digitalWrite(Pin::SELECT, HIGH);
  }

  if (loopcount == 10) {
    printButtons(buttonStates);
    loopcount = 0;
  }

  blinkButtons(buttonStates);

  ++loopcount;
  delay(period);
}

void printButtons(const bool buttonStates[12]) {
  for (const auto &label : labels) {
    Serial.print(buttonStates[static_cast<uint8_t>(label.button)] == LOW ? label.label : ".");
  }

  Serial.println("");
}

void blinkButtons(const bool buttonStates[12]) {
  for (const auto &button: buttons) {
    if (buttonStates[static_cast<uint8_t>(button)] == LOW) {
      return digitalWrite(LED_BUILTIN, HIGH);
    }
  }

  digitalWrite(LED_BUILTIN, LOW);
}

void _pinMode(Pin pin, uint8_t mode) {
  pinMode(static_cast<uint8_t>(pin), mode);
}

int _digitalRead(Pin pin) {
  return digitalRead(static_cast<uint8_t>(pin));
}

void _digitalWrite(Pin pin, uint8_t value) {
  digitalWrite(static_cast<uint8_t>(pin), value);
}
