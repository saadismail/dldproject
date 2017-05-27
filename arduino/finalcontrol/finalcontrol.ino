#include "IRremote.h"

int receiver = 5; // Signal Pin of IR receiver to Arduino Digital Pin 11
unsigned long last = millis();
char data = 0;                //Variable for storing received data

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(12, OUTPUT);        //Sets digital pin 13 as output pin
  pinMode(8, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    if (millis() - last > 250) {
      translateIR();
    }
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
  if (Serial.available() > 0) {
    translateBT();
  }
}

void translateIR() {
  switch(results.value) {
    case 0xFF6897: digitalWrite(8, LOW);    break;
    case 0xFF30CF: digitalWrite(8, HIGH);    break;
    case 0xFF18E7: digitalWrite(12, LOW);    break;
    case 0xFF7A85: digitalWrite(12, HIGH);    break;
  }
}

void translateBT() {
  data = Serial.read();
  if(data == '0')            //Checks whether value of data is equal to 1 
      digitalWrite(8, LOW);  //If value is 1 then LED turns ON
    else if(data == '1')       //Checks whether value of data is equal to 0
      digitalWrite(8, HIGH);   //If value is 0 then LED turns OFF
    else if (data == '2')
      digitalWrite(12, LOW);
    else if (data == '3')
      digitalWrite(12, HIGH);
}

