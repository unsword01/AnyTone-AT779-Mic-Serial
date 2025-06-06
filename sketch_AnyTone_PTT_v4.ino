// Translate PTT from an input pin to serial data for AnyTone AT-779UV Transceiver 
// Use LED on board as a 'Tally light' for the PTT state

// Based on info in https://melik.cz/posts/sstv-first-steps/
// Serial Port config is 115200 Baud, 8 bits data frame, 1 stop bit, No Parity with no flow control
// PTT activate:   0x41 0x01 0x00 0x00 0x00 0x00 0x00 0x06
// PTT deactivate: 0x41 0x00 0x00 0x00 0x00 0x00 0x00 0x06
// also needs 0x60 to be sent as keepalive after PTT activated to avoid 5 sec timeout

#include <Arduino.h>
#include <SoftwareSerial.h>

// Define the pins for Serial Port use (Rx, Tx)
SoftwareSerial anytoneSerial(10, 3); 

// Declarations for AnyTone Command Strings 
byte PTT_ON[]        = {0x41, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
byte PTT_OFF[]       = {0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
byte PTT_KEEPALIVE[] = {0x06};

int sleepTime = 50;              // sleep delay for loop in ms
int keepaliveTime = 2;           // time between keepalive messages in seconds
int counter = 1;                 // initialize the counter at one
int countMax = (keepaliveTime * 1000) / sleepTime; // Max value for counter before keepalive is sent
int pttPin = 7;                  // PTT line uses digital pin 7
int ledPin = 13;                 // LED conected to pin 13
bool pttState;                   // state of PTT line
bool lastPttState = true;        // init PTT state (true = off)

void setup() {
  pinMode(pttPin, INPUT_PULLUP); // Configure digital pin as input for PTT (active low)
  pinMode(ledPin, OUTPUT);       // Configure digital pin as an output for LED
  digitalWrite(ledPin, LOW);     // Set the inital LED state to off
  anytoneSerial.begin(115200);
}

// Macro to compute size of a byte array
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

// function to write byte array to Serial
void writeSer(byte* data, int size) {
  for (int i = 0; i < size; i++) {
    anytoneSerial.write(data[i]);
  }
}

void loop() {
   // read the state of the PTT input pin
   // It is Active Low so will be value of FALSE or 0 when active and TRUE or 1 when inactive
   pttState = digitalRead(pttPin);

  // Test to see if the state of the PTT input has changed
  if (pttState != lastPttState) {
    // handle the PTT state change
    if (pttState == false){
        writeSer(PTT_ON, ARRAY_SIZE(PTT_ON)); 
        digitalWrite(ledPin, HIGH); // sets the LED on
      } else {
        writeSer(PTT_OFF, ARRAY_SIZE(PTT_OFF));
        digitalWrite(ledPin, LOW); // sets the LED off
      }
    // update the state tracking variable
    lastPttState = pttState; 
  } else {
    // was previous state PTT active ?
    if(pttState == false) {
    // decide if we need to send a keepalive 
      if(counter == countMax) {
        // send a keepalive and reset the counter
        writeSer(PTT_KEEPALIVE, ARRAY_SIZE(PTT_KEEPALIVE));
        // Reset the counter
        counter = 1;
      } else {
        // sleep and increment the counter
        delay(sleepTime);
        counter++; 
      } 

    } else {
      // make sure the counter is reset
      counter = 1;
    }
    // update the state tracking variable
    lastPttState = pttState;
  }
}