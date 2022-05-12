constexpr auto PIN_UP = 5;        //  serial pin 1
constexpr auto PIN_DOWN = 2;      //  serial pin 2
constexpr auto PIN_GND_LEFT = 3;  //  serial pin 3
constexpr auto PIN_GND_RIGHT = 4; //  serial pin 4
constexpr auto PIN_A_B = 6;       //  serial pin 6
constexpr auto PIN_SELECT = 7;    //  serial pin 7
constexpr auto PIN_START_C = 9;   //  serial pin 9

constexpr auto VALUE_UP1 = 0;
constexpr auto VALUE_DOWN1 = 1;
constexpr auto VALUE_GND1 = 2;
constexpr auto VALUE_GND2 = 3;
constexpr auto VALUE_A = 4;
constexpr auto VALUE_START = 5;
constexpr auto VALUE_UP2 = 6;
constexpr auto VALUE_DOWN2 = 7;
constexpr auto VALUE_LEFT = 8;
constexpr auto VALUE_RIGHT = 9;
constexpr auto VALUE_B = 10;
constexpr auto VALUE_C = 11;

const char valueLabels[12][2] = {
  "-", "-", "-", "-", "A", "S", "U", "D", "L", "R", "B", "C"  
};

void setup() {
  Serial.begin(9600);

  pinMode(PIN_UP, INPUT);
  pinMode(PIN_DOWN, INPUT);
  pinMode(PIN_GND_LEFT, INPUT);
  pinMode(PIN_GND_RIGHT, INPUT);
  pinMode(PIN_A_B, INPUT);
  pinMode(PIN_START_C, INPUT);
  
  pinMode(PIN_SELECT, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  bool values[12] = {
    LOW, LOW, LOW, LOW, LOW, LOW, 
    LOW, LOW, LOW, LOW, LOW, LOW,
  };
  
  digitalWrite(PIN_SELECT, LOW);
  
  values[0] = digitalRead(PIN_UP);
  values[1] = digitalRead(PIN_DOWN);
  values[2] = digitalRead(PIN_GND_LEFT);
  values[3] = digitalRead(PIN_GND_RIGHT);
  values[4] = digitalRead(PIN_A_B);
  values[5] = digitalRead(PIN_START_C);

  digitalWrite(PIN_SELECT, HIGH);

  values[6] = digitalRead(PIN_UP);
  values[7] = digitalRead(PIN_DOWN);
  values[8] = digitalRead(PIN_GND_LEFT);
  values[9] = digitalRead(PIN_GND_RIGHT);
  values[10] = digitalRead(PIN_A_B);
  values[11] = digitalRead(PIN_START_C);

  printValues(values);
  
  delay(100);
}

void printValues(const bool *values) {
  auto pressed = false;
  
  Serial.print("[");
  for (auto i = 0; i < 11; i++) {
    if (values[i] == LOW) {
      pressed = true;
      Serial.print(valueLabels[i]);
    } else {
      Serial.print(" ");
    }
    Serial.print(" ");
  }
  if (values[11] == LOW) {
    pressed = true;
    Serial.print(valueLabels[11]);
  } else {
    Serial.print(" ");
  }
  Serial.println("]");

  digitalWrite(LED_BUILTIN, pressed ? HIGH : LOW);
}
