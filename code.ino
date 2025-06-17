#include <LiquidCrystal.h>

const int rs = 11, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
const int btnPoint = 8;
const int btnTrait = 9;
const int btnValid = 10;

const long antiRebond = 50;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int morse[37] = {
    12000, 21110, 21210, 21100, 10000, 11210, 22100, 11110, 11000, 12220, 21200, 12110, 22000, 21000, 22200, 12210, 22120, 12100, 11100, 20000, 11200, 11120, 12200, 21120, 21220, 22110,
    12222, 11222, 11122, 11112, 11111, 21111, 22111, 22211, 22221, 22222,
    00000 
};

const char lettres[37] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '?'
};
const int idxErr = 36;

long inCode = 0;
long curseur = 10000;
String phrase = "";
long lastPt = 0;
long lastTr = 0;
long lastVd = 0;

void setup() {
  Serial.begin(9600);
  pinMode(btnPoint, INPUT_PULLUP);
  pinMode(btnTrait, INPUT_PULLUP);
  pinMode(btnValid, INPUT_PULLUP);
  lcd.begin(16, 2);
  updateLcd();
}

int findIdx(long code) {
  for (int i = 0; i < 37; i++) {
    if (code == morse[i]) {
      return i;
    }
  }
  return idxErr;
}
void addSig(int sig) {
  if (curseur < 1) return; 
  inCode += curseur * sig;
  curseur /= 10;
  updateLcd();
}

void validLetter() {
  int idx = findIdx(inCode);
  phrase += lettres[idx];
  if (phrase.length() >= 16) {
    phrase = "";
  }
  inCode = 0;
  curseur = 10000;
  updateLcd();
}

void updateLcd() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  if (inCode == 0) {
    lcd.print("_");
  } else {
    lcd.print(inCode);
  }
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print(phrase);
}

void loop() {
  unsigned long now = millis();
  if (digitalRead(btnPoint) == LOW) {
    if (now - lastPt > antiRebond) {
      lastPt = now;
      addSig(1);
    }
  }
  if (digitalRead(btnTrait) == LOW) {
    if (now - lastTr > antiRebond) {
      lastTr = now;
      addSig(2);
    }
  }
  if (digitalRead(btnValid) == LOW) {
    if (now - lastVd > antiRebond) {
      lastVd = now;
      validLetter();
    }
  }
}
