#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD settings
#define LCD_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLUMNS, LCD_ROWS);

// Pin Definitions
#define BUTTON1_PIN 18
#define BUTTON2_PIN 19
#define BUTTON3_PIN 15
#define RELAY1_PIN 33
#define RELAY2_PIN 25
#define BUZZER_PIN 32

// State variables
bool relay1State = false; // Initially off
bool relay2State = false; // Initially off
bool buzzerState = false; // Initially off

void setup() {
  
  // Initial states
  digitalWrite(RELAY1_PIN, HIGH); // Inverted logic: relay off
  digitalWrite(RELAY2_PIN, HIGH); // Inverted logic: relay off
  digitalWrite(BUZZER_PIN, HIGH); // Inverted logic: buzzer off

  // Initialize I2C
  Wire.begin();

  // Initialize LCD display
  lcd.init();
  lcd.backlight();

  // Initialize pins
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  

  // Initial display
  lcd.setCursor(0, 0);
  lcd.print("R1:OFF R2:OFF");
  lcd.setCursor(0, 1);
  lcd.print("B:OFF         ");
}

void loop() {
  static bool button1Pressed = false;
  static bool button2Pressed = false;
  static bool button3Pressed = false;
  static unsigned long lastDebounceTime1 = 0;
  static unsigned long lastDebounceTime2 = 0;
  static unsigned long lastDebounceTime3 = 0;
  const unsigned long debounceDelay = 50;

  // Read the state of Button 1
  if (digitalRead(BUTTON1_PIN) == LOW) {
    if (!button1Pressed && millis() - lastDebounceTime1 > debounceDelay) {
      button1Pressed = true;
      lastDebounceTime1 = millis();

      // Toggle Relay 1 state
      relay1State = !relay1State;
      digitalWrite(RELAY1_PIN, relay1State ? LOW : HIGH); // Inverted logic

      // Update display
      lcd.setCursor(0, 0);
      lcd.print("R1:");
      lcd.print(relay1State ? "OFF " : "ON ");
    }
  } else {
    button1Pressed = false;
  }

  // Read the state of Button 2
  if (digitalRead(BUTTON2_PIN) == LOW) {
    if (!button2Pressed && millis() - lastDebounceTime2 > debounceDelay) {
      button2Pressed = true;
      lastDebounceTime2 = millis();

      // Toggle Relay 2 state
      relay2State = !relay2State;
      digitalWrite(RELAY2_PIN, relay2State ? LOW : HIGH); // Inverted logic

      // Update display
      lcd.setCursor(7, 0);
      lcd.print("R2:");
      lcd.print(relay2State ? "OFF " : "ON ");
    }
  } else {
    button2Pressed = false;
  }

  // Read the state of Button 3
  if (digitalRead(BUTTON3_PIN) == LOW) {
    if (!button3Pressed && millis() - lastDebounceTime3 > debounceDelay) {
      button3Pressed = true;
      lastDebounceTime3 = millis();

      // Toggle Buzzer state
      buzzerState = !buzzerState;
      digitalWrite(BUZZER_PIN, buzzerState ? LOW : HIGH); // Inverted logic

      // Update display
      lcd.setCursor(0, 1);
      lcd.print("B:");
      lcd.print(buzzerState ? "OFF " : "ON ");
      lcd.print("         "); // Clear leftover characters
    }
  } else {
    button3Pressed = false;
  }
}
