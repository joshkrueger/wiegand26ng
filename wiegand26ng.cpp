#include "wiegand26ng.h"
#include "Arduino.h"

Wiegand26ng::Wiegand26ng(uint8_t p1, uint8_t p2){
  begin(p1, p2);
}

Wiegand26ng::~Wiegand26ng(){
  end();
}

void Wiegand26ng::begin(uint8_t p1, uint8_t p2) {
  readerPins[0] = p1;
  readerPins[1] = p2;
#ifdef MCU328
  pcattach.PCattachInterrupt(readerPins[0], this->readerZero, CHANGE);
  pcattach.PCattachInterrupt(readerPins[1], this->readerOne,  CHANGE);
#endif
}

void Wiegand26ng::end(){
#ifdef MCU328
  pcattach.PCdetachInterrupt(readerPins[0]);
  pcattach.PCdetachInterrupt(readerPins[1]);
#endif
}

void Wiegand26ng::initReader(void) {
  for(byte i=0; i<2; i++){
    pinMode(readerPins[i], OUTPUT);
    digitalWrite(readerPins[i], HIGH); // enable internal pull up causing a one
    digitalWrite(readerPins[i], LOW); // disable internal pull up causing zero and thus an interrupt
    pinMode(readerPins[i], INPUT);
    digitalWrite(readerPins[i], HIGH); // enable internal pull up
  }
  delay(10);
  readerCount=0;
  reader=0;
}

void Wiegand26ng::readerOne() {
  if(digitalRead(readerPins[1]) == LOW){
    readerCount++;
    reader = reader << 1;
    reader |= 1;
  }
}

void  Wiegand26ng::readerZero() {
  if(digitalRead(readerPins[0]) == LOW){
    readerCount++;
    reader = reader << 1;
   
  }
}
