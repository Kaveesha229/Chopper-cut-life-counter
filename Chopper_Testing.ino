#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int relayPin = 7;
int stepPin = 2;
int dirPin = 3;
int switchpin = 4;
int sw;


bool blinkState = true;
unsigned long lastBlink = 0;
int blinkInterval = 1000;
int eyePos = 0;
unsigned long lastAnim = 0;
int animInterval = 300;

int pulseDelay = 500;

unsigned long previousMillis = 0;
unsigned long stepperRelayInterval = 2000;
bool relayState = false;
unsigned long onCount = 0;

int b = 1;

void oled();
void stp();
void hold();
void drawScreen();
void animateEyes();

void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, LOW);

  pinMode(switchpin, INPUT_PULLUP);

  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    for (;;)
      ;
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println("Starting..");
  display.display();
  delay(1000);
}

void loop() {
  sw = digitalRead(switchpin);
  if (sw == LOW) {
    if (b == 1) {
      unsigned long startMillis = millis();
      const unsigned long waitTime = 50;
      while (millis() - startMillis < waitTime) {
        stp();
      }
      b = 2;
    }

    if (b == 2) {
      hold();
      delay(500);
      b = 3;
    }

    if (b == 3) {
      digitalWrite(relayPin, HIGH);
      onCount++;
      oled();
      delay(1000);
      digitalWrite(relayPin, LOW);
      delay(300);
      b = 1;
    }
  } else {
    animateEyes();
  }
}

void oled() {
  Serial.print("Chopper Count: ");
  Serial.println(onCount);

  display.clearDisplay();
  display.setCursor(0, 10);
  display.print("Chopper :");
  display.setCursor(0, 35);
  display.setTextSize(3);
  display.print(onCount);
  display.setTextSize(2);
  display.display();
}

void stp() {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(pulseDelay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(pulseDelay);
}

void hold() {
  digitalWrite(stepPin, LOW);
  delayMicroseconds(pulseDelay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(pulseDelay);
  digitalWrite(relayPin, LOW);
}

void drawScreen() {
  display.clearDisplay();

  display.setCursor(0, 10);
  display.setTextSize(2.5);
  display.print("STOP");

  display.setCursor(0, 35);
  display.setTextSize(3);
  display.print(onCount);
  display.setTextSize(2);

  int y = 32;
  int eyeSizeX = 22;
  int eyeSizeY = 18;
  int baseX = 70;
  int spacing = 25;

  if (blinkState) {
    if (eyePos == 0) {
      display.fillRoundRect(baseX, y, eyeSizeX, eyeSizeY, 4, SSD1306_WHITE);
      display.fillRoundRect(baseX + spacing, y, eyeSizeX, eyeSizeY, 4, SSD1306_WHITE);
    } else {
      display.fillRoundRect(baseX + 5, y, eyeSizeX, eyeSizeY, 4, SSD1306_WHITE);
      display.fillRoundRect(baseX + spacing + 5, y, eyeSizeX, eyeSizeY, 4, SSD1306_WHITE);
    }
  } else {
    display.fillRect(baseX, y + eyeSizeY / 2, eyeSizeX, 2, SSD1306_WHITE);
    display.fillRect(baseX + spacing, y + eyeSizeY / 2, eyeSizeX, 2, SSD1306_WHITE);
  }

  display.display();
}

void animateEyes() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastAnim >= animInterval) {
    lastAnim = currentMillis;
    eyePos = !eyePos;
  }

  if (currentMillis - lastBlink >= blinkInterval) {
    lastBlink = currentMillis;
    blinkState = !blinkState;
  }

  drawScreen();
}