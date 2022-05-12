enum struct Pin: uint8_t {
  UP = 5,        //  serial pin 1, Arduino pin 1 is used for serial TX
  DOWN = 2,      //  serial pin 2
  GND_LEFT = 3,  //  serial pin 3
  GND_RIGHT = 4, //  serial pin 4
  A_B = 6,       //  serial pin 6
  SELECT = 7,    //  serial pin 7
  START_C = 9,   //  serial pin 9
};

enum struct Button: uint8_t {
  UP1, DOWN1, GND1, GND2, A, START,
  UP2, DOWN2, LEFT, RIGHT, B, C,
};

struct ButtonMapping {
  const Button button;
  const Pin pin;
  const char label[2];
};

constexpr ButtonMapping low[2] = {
  {Button::A, Pin::A_B, "A"},
  {Button::START, Pin::START_C, "S"},
};

constexpr ButtonMapping high[6] = {
  {Button::UP2, Pin::UP, "U"},
  {Button::DOWN2, Pin::DOWN, "D"},
  {Button::LEFT, Pin::GND_LEFT, "L"},
  {Button::RIGHT, Pin::GND_RIGHT, "R"},
  {Button::B, Pin::A_B, "B"},
  {Button::C, Pin::START_C, "C"},
};

void printButtons(const bool *);

void _pinMode(Pin, uint8_t);
int _digitalRead(Pin);
void _digitalWrite(Pin, uint8_t);

void setup() {
  Serial.begin(9600);

  _pinMode(Pin::UP, INPUT);
  _pinMode(Pin::DOWN, INPUT);
  _pinMode(Pin::GND_LEFT, INPUT);
  _pinMode(Pin::GND_RIGHT, INPUT);
  _pinMode(Pin::A_B, INPUT);
  _pinMode(Pin::START_C, INPUT);

  _pinMode(Pin::SELECT, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  bool buttons[12] = {
    LOW, LOW, LOW, LOW, LOW, LOW,
    LOW, LOW, LOW, LOW, LOW, LOW,
  };

  _digitalWrite(Pin::SELECT, LOW);

  for (const auto &mapping : low) {
    buttons[static_cast<uint8_t>(mapping.button)] = _digitalRead(mapping.pin);
  }

  _digitalWrite(Pin::SELECT, HIGH);

  for (const auto &mapping : high) {
    buttons[static_cast<uint8_t>(mapping.button)] = _digitalRead(mapping.pin);
  }

  printButtons(buttons);

  delay(100);
}

void printButtons(const bool *buttons) {
  auto pressed = false;

  for (const auto &mapping : low) {
    if (buttons[static_cast<uint8_t>(mapping.button)] == LOW) {
      pressed = true;
      Serial.print(mapping.label);
    } else {
      Serial.print(".");
    }
  }

  for (const auto &mapping : high) {
    if (buttons[static_cast<uint8_t>(mapping.button)] == LOW) {
      pressed = true;
      Serial.print(mapping.label);
    } else {
      Serial.print(".");
    }
  }

  Serial.println("");

  digitalWrite(LED_BUILTIN, pressed ? HIGH : LOW);
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
