#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define fillPump 6
#define releasePump 7

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

int instruction = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    // Reads in the instruction coming in
    radio.read(&instruction, sizeof(instruction));

    // Instruction 0: Stop both Pumps 
    // Instruction 1: Fill Tank
    // Instruction 2: Empty Tank
    if(instruction == 1){
      Serial.println("Decreasing Buoyancy");
      digitalWrite(fillPump, HIGH);
      digitalWrite(releasePump, LOW);
      
    } else if (instruction == 2){
      Serial.println("Increasing Buoyancy");
      digitalWrite(releasePump, HIGH);
      digitalWrite(fillPump, LOW);
      
    } else {
      Serial.println("Stop");
      digitalWrite(releasePump, LOW);
      digitalWrite(fillPump, LOW);
    }
  }
}
