
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //set brightness integer variable
  int brightness = analogRead(A0)/4;
  if (brightness >20) {
    //analog write is a range vs on/off
    analogWrite(2,brightness);
  } else {
    analogWrite(2,0);
  }
    delay(2);
//digitalWrite(2, HIGH);
//delay(2);
//digitalWrite(2, LOW);
//delay(8);
}
