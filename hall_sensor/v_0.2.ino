volatile int count = 0;
volatile int switcher = 0;
unsigned long time_old = 0;
unsigned long timer = 0;

void setup() {
  Serial.begin(250000);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), intsr, RISING);
}

void loop() {
  if (switcher == 1) {
    timer = millis() - time_old;
    Serial.print("RPM is ");
    Serial.println(60000/timer);
    Serial.print("Time is ");
    Serial.println(timer);
    switcher = 0;
    time_old = millis();
  }
}

void intsr() {
  count++;
  switcher = 1;
}
