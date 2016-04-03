int input = 12;

void setup() {
  pinMode(input, INPUT);
  Serial.begin(9600);
  analogWrite(3, 255);
}
void loop() {
  Serial.print(rpm(input));
  Serial.println(" rpm");
}

int rpm(int pin) {
  long high_time = pulseIn(input, HIGH, 300000);
  if (high_time > 0) {
    long low_time = pulseIn(input, LOW, 300000);
    if (low_time > 0) {
      return floor(constrain(map(floor(1000000 / (high_time + low_time)), 0, 100, 0, 600), 0, 600));
    }
  }
  return 0;
}

