int redled = 11;
int greenled = 10;
int blueled = 9;
int pot1 = A1;
int cycleCount = 0;
int bPin = 2;
int currentBVal = 1;

void setup() {
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(bPin, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int bVal = getBVal(bPin, currentBVal, 4);
  switch (bVal) {
    case 1:
      runLEDs(255,104,1);
      break;
    case 2:
      potLEDControl(pot1);
      break;
    case 3:
      spectrumCycle();
      break;
    case 4:
      colors();
      break;
    default:
      runLEDs(0,0,0);
    break;
  }
  digitalWrite(13, LOW);
}

void runLEDs(int red, int green, int blue) {
  analogWrite(redled, red);
  analogWrite(greenled, green);
  analogWrite(blueled, blue);
}
int getPot(int potPin) {
  int potValue = analogRead(potPin);
  return potValue;
}
void colors()
{
  // Red
  runLEDs(255,0,0);
  // Green
  runLEDs(0,255,0);
  delay(1000);
  // Blue
  runLEDs(0,0,255);
  delay(1000);
  // Yellow
  runLEDs(255,255,0);
  delay(1000);
  // Cyan
  runLEDs(0,255,255);
  delay(1000);
  //Purple
  runLEDs(255,0,255);
  delay(1000);
  // White
  runLEDs(255,255,255);
  delay(1000);
}
void spectrumValueToLED(int value) {
  int red;
  int green;
  int blue;
  if (value <= 255) {
    red = 255 - value;
    green = value;
    blue = 0;
  } else if (value >= 256 && value <= 511) {
    red = 0;
    green = 255 - (value - 256);
    blue = value - 256;
  } else {
    red = value - 512;
    green = 0;
    blue = 255 - (value - 512);
  }
  runLEDs(red, green, blue);
}
void potLEDControl(int potPin) {
  int potValue = getPot(potPin);
  double numVal = potValue;
  double specValue = ((numVal / 1023) * 767);
  int spectrumValue = specValue;
  spectrumValueToLED(spectrumValue);
}
void spectrumCycle() {
  if (cycleCount < 768) {
    spectrumValueToLED(cycleCount);
    cycleCount++;
  } 
  if (cycleCount == 768) {
    cycleCount = 0;
  }
  delay(10);
}
int getBVal(int pin, int oldVal, int caseNumber) {
  Serial.println("HI");
  Serial.println(digitalRead(pin));
  if (digitalRead(pin) == 0) {
    
    int newVal = oldVal + 1;
    currentBVal = newVal;
    return newVal;
    digitalWrite(13, HIGH);
  } else {
    return currentBVal;
  }
  if (currentBVal == caseNumber) {
    currentBVal = 0;
  }
}

