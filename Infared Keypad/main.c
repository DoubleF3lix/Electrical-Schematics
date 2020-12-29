// EDIT THIS TO CHANGE THE PASSCODE
char passcode[] = "7181";

#include <IRremote.h>
#define RECEIVER_PIN 2
IRrecv receiver(RECEIVER_PIN);

#include <LiquidCrystal_I2C.h>
decode_results results;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int LCDCharCount = 0;
char LCDText[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void(* resetFunc) (void) = 0;

void checkPasscode() {
  int arraysAreEqual = strcmp(LCDText, passcode);
  if (arraysAreEqual == 0) {
    lcd.clear();
    lcd.print("Correct!");
    delay(250);
    lcd.clear();
    delay(250);
    lcd.print("Correct!");
    delay(3000);
    lcd.clear();
    lcd.print("Resetting...");
    delay(2000);
    resetFunc();
  } else {
    lcd.clear();
    lcd.print("Incorrect!");
    delay(250);
    lcd.clear();
    delay(250);
    lcd.print("Incorrect!");
    delay(3000);
    clearLCD();
  }
}

void handleIRInput(char value) {
  lcd.print(value);
  LCDText[LCDCharCount] = value;
  Serial.println(LCDText);
  LCDCharCount++;
}

void clearLCD() {
  LCDText[0] = 0;
  LCDText[1] = 0;
  LCDText[2] = 0;
  LCDText[3] = 0;
  LCDText[4] = 0;
  LCDText[5] = 0;
  LCDText[6] = 0;
  LCDText[7] = 0;
  LCDText[8] = 0;
  LCDText[9] = 0;
  LCDText[10] = 0;
  LCDText[11] = 0;
  LCDText[12] = 0;
  LCDText[13] = 0;
  LCDText[14] = 0;
  LCDText[15] = 0;
  LCDText[16] = 0;
  lcd.clear();
  lcd.print("Enter passcode:");
  lcd.setCursor(0, 1);
  LCDCharCount = 0;
}

void backspace() {
  if (LCDCharCount > 0) {
    LCDText[--LCDCharCount] = 0;
    lcd.clear();
    lcd.print("Enter passcode:");
    lcd.setCursor(0, 1);
    lcd.print(LCDText);
    Serial.println(LCDText);
  }
}

void setup() {
  Serial.begin(9600);
  receiver.enableIRIn();
  receiver.blink13(true);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter passcode:");
  lcd.setCursor(0, 1);
  Serial.println("Startup done!");
}

void loop() {
  if (receiver.decode(&results)) {
    if (LCDCharCount <= 15) {
      //Serial.println(results.value, HEX);
      switch (results.value) {
        case 0xFF02FD:
          checkPasscode();
          break;
        case 0xFF4AB5:
          handleIRInput('0');
          break;
        case 0xFF6897:
          handleIRInput('1');
          break;
        case 0xFF9867:
          handleIRInput('2');
          break;
        case 0xFFB04F:
          handleIRInput('3');
          break;
        case 0xFF30CF:
          handleIRInput('4');
          break;
        case 0xFF18E7:
          handleIRInput('5');
          break;
        case 0xFF7A85:
          handleIRInput('6');
          break;
        case 0xFF10EF:
          handleIRInput('7');
          break;
        case 0xFF38C7:
          handleIRInput('8');
          break;
        case 0xFF5AA5:
          handleIRInput('9');
          break;
        case 0xFF42BD:
          backspace();
          break;
        case 0xFF52AD:
          clearLCD();
          break;
      }
    } else {
      switch (results.value) {
        case 0xFF02FD:
          checkPasscode();
          break;
        case 0xFF42BD:
          backspace();
          break;
        case 0xFF52AD:
          clearLCD();
          break;
      }
    }
    receiver.resume();
  }
}
