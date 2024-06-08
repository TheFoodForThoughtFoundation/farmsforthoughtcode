int float_switch_pin = 2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(float_switch_pin, INPUT_PULLUP); //uses arduino's internal pullup resistor - so we don't have to put one in
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(float_switch_pin));
  delay(500);
}
