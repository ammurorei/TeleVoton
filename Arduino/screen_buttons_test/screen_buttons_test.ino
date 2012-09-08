/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

char values[24] = {
'C', //enter
'3', // 3
'2', // 2
'1', // 1
'D',
'E',
'0', // 0
'F',
'B', //cleR
'6', // 6
'5', // 5
'4', // 4
'A', //cancel
'9',  // 9
'8',  // 8
'7',  // 7
'G',  // 7
'H',  // 7
'I',  // 7
'J',  // 7
'K',  // 7
'L',  // 7
'M',  // 7
'N'  // 7
};

int keyNumber = 0;
int lastKey = 0;

void setup() {

  Serial.begin(9600);

  for(int i = 4; i <= 11; i++) {
    pinMode(i, INPUT);//INPUT_PULLUP
    digitalWrite(i, HIGH);
  }
  for(int i = 22; i <= 29; i++) {
    pinMode(i, INPUT);//INPUT_PULLUP
    digitalWrite(i, HIGH);
  }
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

}

void loop() {

  digitalWrite(12, LOW);

  keyNumber = - 1;

  for(int i = 4; i <= 11; i++) {
    if (digitalRead(i) == LOW) {
       // Key pressed
       keyNumber = i - 4;

       /*
       Serial.print("Row ");
       Serial.print(12);
       Serial.print("Col ");
       Serial.println(i);
       */
    }
  }
  digitalWrite(12, HIGH);

  digitalWrite(13, LOW);
  for(int i = 4; i <= 11; i++) {
    if (digitalRead(i) == LOW) {
       // Key pressed
       keyNumber = i - 4 + 8;
       /*
       Serial.print("Row ");
       Serial.print(13);
       Serial.print("Col ");
       Serial.println(i);
       */
    }
  }
  digitalWrite(13, HIGH);

  for(int i = 22; i <= 29; i++) {
    if (digitalRead(i) == LOW) {
       // Key pressed
       keyNumber = i-6;
    }
  }

  if (keyNumber != lastKey && keyNumber != -1) {
       Serial.println(values[keyNumber]);
  }

  lastKey = keyNumber;


}
