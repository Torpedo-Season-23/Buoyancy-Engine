#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
int instruction = 0;

unsigned long currentTime, startTime;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.println("Enter any character to start sequence... ");
  while(!Serial.available()){};
  startTime = millis();
}

void loop() {
  currentTime = millis();
  if(currentTime - startTime < 10000){
    instruction = 1;
  } else if (currentTime - startTime < 20000) {
    instruction = 2;
  } else {
    instruction = 0;
  }

  Serial.println(instruction);
  radio.write(&instruction, sizeof(instruction));
  
}
