#define IR 8
#define BUZZER A0
#define CATCH 12       // Relay1
#define LOCK 10        // Relay2
#define ACTUATOR 5     // Relay3
#define LOCK2 3         // Relay4
#define BUTTON_PIN 6   // Push button
#define MODE_LED A4    // Mode LED

int count = 0;
int lastState = LOW;
int bottleTarget = 4;  // Default

void setup() {
  pinMode(IR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(CATCH, OUTPUT);
  pinMode(LOCK, OUTPUT);
  pinMode(ACTUATOR, OUTPUT);
  pinMode(LOCK2, OUTPUT);
  pinMode(MODE_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initial states
  digitalWrite(BUZZER, LOW);
  digitalWrite(CATCH, LOW);
  digitalWrite(LOCK, HIGH);
  digitalWrite(ACTUATOR, LOW);
  digitalWrite(LOCK2, HIGH);

  // ---- Startup Mode Selection ----
  // Beep 2 times to indicate power ON
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    delay(200);
  }
}

  // bool buttonPressed = false;

  // // Wait 3s for button press
  // unsigned long startTime = millis();
  // while (millis() - startTime < 3000) {
  //   if (digitalRead(BUTTON_PIN) == LOW) {
  //     buttonPressed = true;
  //   }
  // }

  // Mode decision
//   if (buttonPressed) {
//     bottleTarget = 6;
//     digitalWrite(MODE_LED, LOW);   // LED OFF = 4 bottles

//     // Beep 4 times to indicate 4-bottle mode
//     for (int i = 0; i < 6; i++) {
//       digitalWrite(BUZZER, HIGH);
//       delay(200);
//       digitalWrite(BUZZER, LOW);
//       delay(200);
//     }
//   } else {
//     bottleTarget = 4;
//     digitalWrite(MODE_LED, HIGH);  // LED ON = 6 bottles

//     // Beep 6 times to indicate 6-bottle mode
//     for (int i = 0; i < 4; i++) {
//       digitalWrite(BUZZER, HIGH);
//       delay(200);
//       digitalWrite(BUZZER, LOW);
//       delay(200);
//     }
//   }
// }

void loop() 
{
  int currentState = digitalRead(IR);

  if (lastState == LOW && currentState == HIGH) {
    count++;
    delay(50); // debounce
  }
  lastState = currentState;

  if (count >= bottleTarget) {
    // Step 1: Buzzer for 500ms
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER, LOW);
    delay(100);
    // Step 2: Lock HIGH
    digitalWrite(LOCK, LOW);
    delay(2000);
    // Step 3: Catch HIGH
        digitalWrite(LOCK2, LOW);
        // delay(500);
    digitalWrite(CATCH, HIGH);
    // delay(1000);


    delay(1000);

    // Step 4: Actuator HIGH
    digitalWrite(ACTUATOR, HIGH);
    delay(3200);

    // Step 5: Pump ON
    // digitalWrite(PUMP, HIGH);
    delay(6000);
    // digitalWrite(PUMP, LOW);
    delay(1500);

    // Step 6: Actuator LOW
    digitalWrite(ACTUATOR, LOW);
    delay(2000);

    // Step 7: Catch LOW
    digitalWrite(CATCH, LOW);
    delay(4000);

    // Step 8: Lock LOW
    digitalWrite(LOCK, HIGH);
    digitalWrite(LOCK2, HIGH);

    // Reset count
    count = 0;
  }
}
