volatile int count = 0;

void setup() {
  Serial.begin(250000);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), intsr, RISING);
}

void loop() {
  Serial.println(count);
}

void intsr() {
  count++;
}
