
//Pins
int N2O_PIN = 13;
int FUEL_PIN = 9;
int TRIGGER_PIN = 10;
int WOT_PIN = 1;
int CLUTCH_PIN = 2;
int RPM_PIN = 3;
int ARM_PIN = 4;

//Settings
int FUEL_TRIM = 255;
int N2O_TRIM = 255;
int MINIMUM_RPM = 3200;
int MAXIMUM_RPM = 6500;
bool CHECK_ARM = false;
bool CHECK_WOT = true;
bool CHECK_RPM = true;
bool CHECK_CLUTCH = true;

//Variables
volatile int RPM = 0;

void setup() {
  //Outputs
  pinMode(N2O_PIN, OUTPUT);
  pinMode(FUEL_PIN, OUTPUT);
  
  //Inputs
  pinMode(TRIGGER_PIN, INPUT);
  pinMode(WOT_PIN, INPUT_PULLUP);
  pinMode(CLUTCH_PIN, INPUT_PULLUP);
  pinMode(RPM_PIN, INPUT);
  pinMode(ARM_PIN, INPUT);
  
  analogWrite(N2O_PIN, 0);
  analogWrite(FUEL_PIN, 0);
}

void loop() {
  if (triggered() && passConditions()) {
    analogWrite(N2O_PIN, N2O_TRIM);
    analogWrite(FUEL_PIN, FUEL_TRIM);
  }
  else {
    analogWrite(N2O_PIN, 0);
    analogWrite(FUEL_PIN, 0);
  }
}

bool triggered() {
  return digitalRead(TRIGGER_PIN) == HIGH;
}

bool armed() {
  return digitalRead(ARM_PIN) == HIGH;
}

bool passRPM() {
  RPM = getRPM();
  if (RPM < MINIMUM_RPM) return false;
  if (RPM > MAXIMUM_RPM) return false;
  return true;
}

bool passConditions() {
  if (CHECK_ARM && !armed()) return false;
  if (CHECK_WOT && digitalRead(WOT_PIN) == LOW) return false;
  if (CHECK_CLUTCH && digitalRead(CLUTCH_PIN) == LOW) return false;
  if (CHECK_RPM && !passRPM()) return false;
  return true;
}

int getRPM() {
  return 0;
}

