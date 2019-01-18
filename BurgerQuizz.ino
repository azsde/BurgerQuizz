#include <MsTimer2.h>

// Constant definitions
const byte interruptPinTeam1 = 2;
const byte interruptPinTeam2 = 3;
const byte team1RedPin = 5;
const byte team1GreenPin = 6;
const byte team2RedPin = 10;
const byte team2GreenPin = 11;
const byte resetPin = 9;

#define DEBOUNCE_DELAY 110

// Global variables
volatile boolean ignore = false;

void setup() {
    Serial.begin(9600);

    // Team one assignements:
    pinMode(interruptPinTeam1, INPUT);
    pinMode(team1RedPin, OUTPUT);
    pinMode(team1GreenPin, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPinTeam1), team1Press, RISING);

    // Team two assignements:
    pinMode(interruptPinTeam2, INPUT);
    pinMode(team2RedPin, OUTPUT);
    pinMode(team2GreenPin, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPinTeam2), team2Press, RISING);

    // Reset timer
    MsTimer2::set(5000, reset); // 5000ms period
}

void loop() {
    if (digitalRead(resetPin) == 1) {
        reset();
    }
}

void team1Press() {
    if (!ignore) {
        static unsigned long last_interrupt_time = 0;
        unsigned long interrupt_time = millis();
        if (interrupt_time - last_interrupt_time > DEBOUNCE_DELAY)
        {
            Serial.println("Team one pressed !");
            ignore = true;
            //TODO: turn on LEDs
            MsTimer2::start();
        }
        last_interrupt_time = interrupt_time;
    }
}

void team2Press() {
   static unsigned long last_interrupt_time = 0;
   unsigned long interrupt_time = millis();
   if (interrupt_time - last_interrupt_time > DEBOUNCE_DELAY)
   {
       Serial.println("Team two pressed !");
       ignore = true;
       //TODO: turn on LEDs
       MsTimer2::start();
   }
   last_interrupt_time = interrupt_time;
}

void reset() {
    Serial.println("Resetting...");
    MsTimer2::stop();
    ignore = false;
    //TODO: turn off LEDs
}