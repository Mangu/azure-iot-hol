// Philly Code Camp IoT Workshop
// Test button wiring

// Define pins for the buttons
#define BUTTON_A_PIN 3
#define BUTTON_B_PIN 4
#define BUTTON_C_PIN 5

void setup() {
  Serial.begin(9600);

  // Uncomment next line to wait for a serial connection
  // while (!Serial) { }
 
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize button pins as input.
  pinMode(BUTTON_A_PIN, INPUT);
  pinMode(BUTTON_B_PIN, INPUT);
  pinMode(BUTTON_C_PIN, INPUT);

}

void loop() {
  
  bool buttonA = digitalRead(BUTTON_A_PIN);
  bool buttonB = digitalRead(BUTTON_B_PIN);
  bool buttonC = digitalRead(BUTTON_C_PIN);

  if (buttonA) {
    Serial.println("Button A");
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (buttonB) {
    Serial.println("Button B");
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (buttonC) {
    Serial.println("Button C");
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(100);
  
}

void blinkLED() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
   digitalWrite(LED_BUILTIN, LOW);
}
