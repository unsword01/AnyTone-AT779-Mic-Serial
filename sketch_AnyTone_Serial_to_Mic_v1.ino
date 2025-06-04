// Translate PTT from an input pin to serial data for AnyTone AT779UV Mic 

#include <Arduino.h>
#include <SoftwareSerial.h>

// Define the pins for Serial Port use (Rx, Tx)
SoftwareSerial anytoneSerial(10, 3); 

// Declarations for AnyTone Command Strings 
byte PTT_ON[]        = {0x41, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
byte PTT_OFF[]       = {0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
byte TX_LED_ON[]     = {0x53, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
byte TX_LED_OFF[]    = {0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
byte SQ_LED_ON[]     = {0x53, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
byte SQ_LED_OFF[]    = {0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
byte PTT_KEEPALIVE[] = {0x06};

#define serial_spd 115200        // Serial Port Speed

int sleepTime = 50;              // sleep delay for loop in ms
int keepaliveTime = 2;           // time between keepalive messages in seconds
int counter = 1;                 // initialize the counter at one
int countMax = (keepaliveTime * 1000) / sleepTime; // Max value for counter before keepalive is sent
int TxPin = 7;                   // TX connected to digital pin 7
int SqPin = 8;                   // SQ connected to digital pin 8
int ledPin = 13;                 // LED conected to pin 13
bool TxState;                    // state of PTT line
bool lastTxState = true;          // init PTT state (true = off)
bool SqState;                    // state of PTT line
bool lastSqState = true;          // init PTT state (true = off)

void setup() {
  pinMode(TxPin, INPUT_PULLUP);  // Configure digital pin as input for TX (active low)
  pinMode(SqPin, INPUT_PULLUP);  // Configure digital pin as input for SQ (active low)
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
   TxState = digitalRead(TxPin);

  // Test to see if the state of the PTT input has changed
  if (TxState != lastTxState) {
    // handle the PTT state change
    if (TxState == false){
        writeSer(TX_LED_ON, ARRAY_SIZE(TX_LED_ON)); 
        //Serial.println(" TX ON ");
        digitalWrite(ledPin, HIGH); // sets the LED on
      } else {
        writeSer(TX_LED_OFF, ARRAY_SIZE(TX_LED_OFF));
        //Serial.println(" TX OFF ");
        digitalWrite(ledPin, LOW); // sets the LED off
      }
    // update the state tracking variable
    lastTxState = TxState; 
  } else {    
    // update the state tracking variable
    lastTxState = TxState;
  }


  // read the state of the SQ input pin
  // It is Active Low so will be value of FALSE or 0 when active and TRUE or 1 when inactive
   SqState = digitalRead(SqPin);
  // Test to see if the state of the SQ input has changed
  if (SqState != lastSqState) {
    // handle the PTT state change
    if (SqState == false){
        writeSer(SQ_LED_ON, ARRAY_SIZE(SQ_LED_ON)); 
        //Serial.println(" TX ON ");
        digitalWrite(ledPin, HIGH); // sets the LED on
      } else {
        writeSer(SQ_LED_OFF, ARRAY_SIZE(SQ_LED_OFF));
        //Serial.println(" TX OFF ");
        digitalWrite(ledPin, LOW); // sets the LED off
      }
    // update the state tracking variable
    lastSqState = SqState; 
  } else {    
    // update the state tracking variable
    lastSqState = SqState;
  }




}