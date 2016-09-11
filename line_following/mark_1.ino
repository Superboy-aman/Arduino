const int dirn_bit1 = 2;
const int dirn_bit2 = 4; 
const int intensity1 = 10; 
const int intensity2 = 11;
const int infred_pins[] = {13, 3, 5, 6, 7, 8, 9, 12};

int sensor_group[3];
int hash[][8] = {{0, 0, 0, 0, 0, 0, 0, 0},{0, 10, 20, 30, 40, 50, 60, 70}};

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 8; i++) {
        pinMode(infred_pins[i], INPUT);
    }
    pinMode(dirn_bit1, OUTPUT);
    pinMode(dirn_bit2, OUTPUT);
    pinMode(intensity1, OUTPUT);
    pinMode(intensity2, OUTPUT);
}

void printSensorArray() {
    int x = 0;
    for(int i = 0; i < 8; i++) {
        x = digitalRead(infred_pins[i]);
        Serial.print(x);
        hash[0][i] = x;
    }
    // Serial.print("    ");
    // Serial.print(getSensorState(0,2));
    // Serial.print("    ");
    // Serial.print(getSensorState(3,4));
    // Serial.print("    ");
    // Serial.print(getSensorState(5,7));
    // Serial.print("    ");
    Serial.print("\n");
}

int getSensorState(int first, int last) {
    int avg = 0, count = 0;
    for (int i = first; i <= last; i++) {
        avg += hash[0][i] * hash[1][i];
        count += hash[0][i];
    }
    avg /= count;
    return avg;  
}

void walkForward(int power1, int power2, int interval) {
    digitalWrite(dirn_bit1, HIGH);
    digitalWrite(dirn_bit2, HIGH);
    analogWrite(intensity1, power1);
    analogWrite(intensity2, power2);
    delay(interval);
}

void walkBackward(int power1, int power2, int interval) {
    digitalWrite(dirn_bit1, LOW);
    digitalWrite(dirn_bit2, LOW);
    analogWrite(intensity1, power1);
    analogWrite(intensity2, power2);
    delay(interval);
}

void leanLeft(int interval) {
    analogWrite(intensity2, 0);
}

void powerLeft(int power1, int power2, int interval) {
    digitalWrite(dirn_bit1, HIGH);
    digitalWrite(dirn_bit2, LOW);
    analogWrite(intensity1, power1);
    analogWrite(intensity2, power2);
    delay(interval);
}

void leanRight(int interval) {
    analogWrite(intensity1, 0);
}

void powerRight(int power1, int power2, int interval) {
    digitalWrite(dirn_bit1, LOW);
    digitalWrite(dirn_bit2, HIGH);
    analogWrite(intensity1, power1);
    analogWrite(intensity2, power2);
    delay(interval);
}

void stopBot() {
    analogWrite(intensity1, 0);
    analogWrite(intensity2, 0);
}

void loop() {
    printSensorArray();
    sensor_group[0] = getSensorState(0, 2);
    sensor_group[1] = getSensorState(3, 4);
    sensor_group[2] = getSensorState(5, 7);
    if ((getSensorState(0, 7) == -1))
        stopBot();
    else if ((sensor_group[0] == -1) && (sensor_group[1] != -1) && (sensor_group[2] == -1))
        walkForward(75, 75, 100);
    else if((sensor_group[0] != -1) && (sensor_group[2]) == -1)
        powerLeft(75, 75, 100);
    else if((sensor_group[0] == -1) && (sensor_group[2] != -1))
        powerRight(75, 75, 100);
    else;
}

// mark_2: something involving a bitwise XOR op.
// mark_3: use grounded average as a multiplier for intensity.
