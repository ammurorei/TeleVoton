/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */
 
char values[24] = {
'C', //C
'3', // 3
'2', // 2
'1', // 1
'D',//D
'E', //E
'0', // 0
'F',//F
'B', //B
'6', // 6
'5', // 5
'4', // 4
'A', //A,cancel
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

  for(int i = 2; i <= 5; i++) {
    pinMode(i, INPUT);//INPUT_PULLUP
    digitalWrite(i, HIGH);
  }
   for(int i = 8; i <= 11; i++) {
    pinMode(i, INPUT);//INPUT_PULLUP
    digitalWrite(i, HIGH);
  }
  for(int i = 22; i <= 36; i+=2) {
     pinMode(i, INPUT);//INPUT_PULLUP
    digitalWrite(i, HIGH);
  }
  pinMode(38, OUTPUT);
  pinMode(40, OUTPUT);
  digitalWrite(38, HIGH); 
  digitalWrite(40, HIGH);
  pinMode(6, OUTPUT);
  pinMode(12, OUTPUT); 
  digitalWrite(6, LOW);
  digitalWrite(12, LOW);  
  
}

void loop() {

  digitalWrite(38, LOW); 
  
  keyNumber = - 1;
  
  for(int i = 0; i <= 7; i++) {
    if (digitalRead(22+(i*2)) == LOW) {
       // Key pressed
       keyNumber = i;
       
       /*
       Serial.print("Row ");
       Serial.print(12);
       Serial.print("Col ");
       Serial.println(i);
       */
    }
  }
  digitalWrite(38, HIGH);  

  digitalWrite(40, LOW); 
  for(int i = 0; i <= 7; i++) {
    if (digitalRead(22+(i*2)) == LOW) {
       // Key pressed
       keyNumber = 8+i;
       /*
       Serial.print("Row ");
       Serial.print(13);
       Serial.print("Col ");
       Serial.println(i);
       */       
    }
  }
  digitalWrite(40, HIGH);  
  
  for(int i = 0; i <= 3; i+=1) {
    if (digitalRead(2+i) == LOW) {
       // Key pressed
       keyNumber = 16+i;  
    }
  }
  
   for(int i = 0; i <= 3; i+=1) {
    if (digitalRead(8+i) == LOW) {
       // Key pressed
       keyNumber = 20+i;  
    }
  }
 
  if (keyNumber != lastKey && keyNumber != -1) {
       Serial.println(values[keyNumber]);
  }

  lastKey = keyNumber;
  
  
}



