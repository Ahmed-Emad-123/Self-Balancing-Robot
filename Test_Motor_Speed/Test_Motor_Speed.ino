// Set Motor Varaiables
const int IN1 = 13;
const int IN2 = 12;
const int IN3 = 7;
const int IN4 = 8;
const int ENA = 11;
const int ENB = 6;

void setup() {
  // Pins Initialization
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

}

void loop() {

  // Forward Motion
  forward();

  delay(3000);

  // Backward Motion
  backward();

  delay(3000);

}

// Movement Functions
void backward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 100);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 100);
}

void forward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 100);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 100);
}
