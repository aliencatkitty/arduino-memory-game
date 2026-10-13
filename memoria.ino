const int leds[] = {2, 3, 4, 5};
// Order: red, green, blue, yellow

const int buttons[] = {11, 10, 9, 8};
// Order: red, green, blue, yellow

const int colorCount = 4;
const int maxSequenceLength = 100;

int sequence[maxSequenceLength];
int level = 0;

void setup() {
  for (int i = 0; i < colorCount; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
  }

  randomSeed(analogRead(A0));

  // Startup animation
  for (int i = 0; i < colorCount; i++) {
    digitalWrite(leds[i], HIGH);
    delay(150);
    digitalWrite(leds[i], LOW);
    delay(100);
  }

  delay(500);
}

void loop() {
  // Restart when the sequence reaches its maximum length
  if (level >= maxSequenceLength) {
    endGame();
    level = 0;
    delay(1000);
    return;
  }

  // Add a random color to the sequence
  sequence[level] = random(colorCount);
  level++;

  // Display the sequence
  showSequence();

  // Check the player's input
  if (playerGuessedCorrectly()) {
    delay(700);
  } else {
    endGame();
    level = 0;
    delay(1000);
  }
}

void showSequence() {
  delay(400);

  for (int i = 0; i < level; i++) {
    int color = sequence[i];

    digitalWrite(leds[color], HIGH);
    delay(500);
    digitalWrite(leds[color], LOW);
    delay(250);
  }
}

int waitForButton() {
  while (true) {
    for (int i = 0; i < colorCount; i++) {
      if (digitalRead(buttons[i]) == LOW) {
        delay(30);

        // Confirm the button press
        if (digitalRead(buttons[i]) == LOW) {
          digitalWrite(leds[i], HIGH);

          // Wait until the button is released
          while (digitalRead(buttons[i]) == LOW) {
            delay(10);
          }

          digitalWrite(leds[i], LOW);
          delay(30);

          return i;
        }
      }
    }
  }
}

bool playerGuessedCorrectly() {
  for (int i = 0; i < level; i++) {
    int button = waitForButton();

    // Check whether the pressed button matches the sequence
    if (button != sequence[i]) {
      return false;
    }
  }

  return true;
}

void endGame() {
  // Blink all LEDs three times
  for (int repetition = 0; repetition < 3; repetition++) {
    for (int i = 0; i < colorCount; i++) {
      digitalWrite(leds[i], HIGH);
    }

    delay(300);

    for (int i = 0; i < colorCount; i++) {
      digitalWrite(leds[i], LOW);
    }

    delay(300);
  }
}
