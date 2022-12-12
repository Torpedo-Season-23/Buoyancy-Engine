#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

int input = 0;
int instruction =0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  
  Serial.println("Enter any instruction to start sequence... ");
  Serial.println("0 Stop ");
  Serial.println("1 Fill Tank");
  Serial.println("2 Empty Tank");
  
  // Stays in setup until the first instruction is sent
  while(!Serial.available());
}

void loop() {
  if(Serial.available() > 0){
    input = Serial.parseInt();
    if(input == 0 || input == 1 || input == 2){
      instruction = input;
    } else {
      Serial.println("Invalid instruction, falling back to previous instruction");
      delay(3000);
    }
    
  }
  Serial.print("Sending instruction: ");
  Serial.println(instruction);
  radio.write(&instruction, sizeof(instruction));
  
}
