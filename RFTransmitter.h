#ifndef RF_TRANSMITTER_H
#define RF_TRANSMITTER_H

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

class RFTransmitter {
private:
    RF24 radio; 
    const byte address1[6];
    const byte address2[6];

public:
    RFTransmitter(int ce, int csn) : radio(ce, csn, 1000000), address1("00001"), address2("00002") {} // CE, CSN

    void setup() {
      radio.begin();
      radio.setRetries(15,15);
      radio.setPayloadSize(32);
      radio.setDataRate(RF24_1MBPS);
      radio.setPALevel(RF24_PA_MAX);
      //radio.setChannel(0x4c);
      //radio.setAutoAck(1);
      //radio.enableDynamicPayloads();
      radio.openWritingPipe(address1);    // "1Node"
      //radio.openReadingPipe(1, address2); // "2Node"
    }

    void loop(String command) {  
      delay(40);

      char txt_sent[32];// = "OK";
      command.toCharArray(txt_sent, command.length() + 1);
  
      radio.stopListening();
      radio.write(&txt_sent, sizeof(txt_sent));  
      Serial.print("Sent: "); Serial.println(txt_sent);
      
      //delay(10);

      //radio.startListening();
      //if (radio.available()) {                // Receive
      //  Serial.println("Receving...");
      //  char txt_received[3] = "";
      //  radio.read(&txt_received, sizeof(txt_received)); 
      //  Serial.print("Received: "); Serial.println(txt_received);
      //}
    }
};

#endif
