enum struct Pin: uint8_t {
  UP = 5,        //  serial pin 1
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

const char buttonLabels[12][2] = {
  "-", "-", "-", "-", "A", "S", "U", "D", "L", "R", "B", "C"  
};

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
  
  buttons[static_cast<uint8_t>(Button::UP1)] = _digitalRead(Pin::UP);
  buttons[static_cast<uint8_t>(Button::DOWN1)] = _digitalRead(Pin::DOWN);
  buttons[static_cast<uint8_t>(Button::GND1)] = _digitalRead(Pin::GND_LEFT);
  buttons[static_cast<uint8_t>(Button::GND2)] = _digitalRead(Pin::GND_RIGHT);
  buttons[static_cast<uint8_t>(Button::A)] = _digitalRead(Pin::A_B);
  buttons[static_cast<uint8_t>(Button::START)] = _digitalRead(Pin::START_C);

  _digitalWrite(Pin::SELECT, HIGH);

  buttons[static_cast<uint8_t>(Button::UP2)] = _digitalRead(Pin::UP);
  buttons[static_cast<uint8_t>(Button::DOWN2)] = _digitalRead(Pin::DOWN);
  buttons[static_cast<uint8_t>(Button::LEFT)] = _digitalRead(Pin::GND_LEFT);
  buttons[static_cast<uint8_t>(Button::RIGHT)] = _digitalRead(Pin::GND_RIGHT);
  buttons[static_cast<uint8_t>(Button::B)] = _digitalRead(Pin::A_B);
  buttons[static_cast<uint8_t>(Button::C)] = _digitalRead(Pin::START_C);

  printButtons(buttons);
  
  delay(100);
}

void printButtons(const bool *buttons) {
  auto pressed = false;
  
  Serial.print("[");
  for (auto i = 0; i < 11; i++) {
    if (buttons[i] == LOW) {
      pressed = true;
      Serial.print(buttonLabels[i]);
    } else {
      Serial.print(" ");
    }
    Serial.print(" ");
  }
  if (buttons[11] == LOW) {
    pressed = true;
    Serial.print(buttonLabels[11]);
  } else {
    Serial.print(" ");
  }
  Serial.println("]");

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
