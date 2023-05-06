#include "arduino_secrets.h"
#include "thingProperties.h"
#define pin0 0
#define pin2 2

int input;
int lastinput = 0;
int lastlamp_Switch = 0;
int state2 = 0;
int state1 = 0;

void setup() {
  Serial.begin(9600);

  pinMode (pin0, OUTPUT);
  pinMode (pin2, INPUT);

  digitalWrite (pin0, LOW);

  delay(1500);

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  input = digitalRead (pin2);


  if (input != lastinput) {
    lastinput = input;
    state2++;
  }

  switch (state2) {
    case 0:
      break;

    case 1:
      if (lastinput == 1) {
        lamp_Switch = 1;
        lastlamp_Switch = 1;
        state2 = 0;
      }
      else {
        lamp_Switch = 0;
        lastlamp_Switch = 0;
        state2 = 0;
      }
  }

  if (lamp_Switch != lastlamp_Switch) {
    state1++;
    lastlamp_Switch = lamp_Switch;
  }

  switch (state1) {
    case 0:
      digitalWrite(pin0, LOW);
      break;
    case 1:
      digitalWrite(pin0, HIGH);
      break;
    case 2:
      state1 = 0;
      break;
  }


  ArduinoCloud.update();
}

void onLampSwitchChange()  {

}