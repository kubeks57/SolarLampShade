//////////////////////////////////////////Volatge sensing
#define ANALOG_PV_IN_PIN A0 // PV
#define ANALOG_BATT_IN_PIN A1 // BATT

float ref_voltage = 5.0;

float adc_PV_voltage = 0.0;
float in_PV_voltage = 0;
int adc_PV_value = 0;

float adc_BATT_voltage = 0.0;
float in_BATT_voltage = 0;
int adc_BATT_value = 0;

//LEDs
const int red = 2;
const int blue = 3;
const int green = 4;

//SYSTEMs
const int light = 5; //light turn ON/OFF
const int lampbatt = 6;
const int usbbatt = 7;
const int PVcharge = 8;
const int lampsock = 9;
const int usbpv = 10;
const int wifiinput = 11;
const int soccharge = 13;

int lightstate = LOW;
int lastlightstate = LOW;
int powermode = 1;
int battledstate = LOW;
int battled;
int battlev;
int wifiinputstate = 1;
int lastwifiinputstate = 1;
int ledoff = 0;
int lastbattlev = 1;
int lastbattled = blue;
int PVfail = 0;
int WiFis = 0;
int bonr;
int lastbonr;
int inter;

unsigned long timer_1;
unsigned long timer_2;
unsigned long timer_3;
unsigned long currenttime = 0;
unsigned long currenttime2 = 0;
unsigned long currenttime3 = 0;
unsigned long currenttime_1;
unsigned long currenttime_2;
unsigned long lastpowermode;

enum { None, SingleClick, DoubleClick, YesSingle};
const byte pinBut = 12;
byte butLst;
// -----------------------------------------------------------------------------
int
chkButton (void)
{
  const  unsigned long ButTimeout  = 250;
  static unsigned long msecLst;
  unsigned long msec = millis ();

  const int debDuration = 100;
  static unsigned long  debStartTime = 0;

  if (msecLst && (msec - msecLst) > ButTimeout)  {
    msecLst = 0;
    return YesSingle;
  }

  byte but = digitalRead (pinBut);
  if (butLst != but)  {
    if (millis() - debStartTime < debDuration) {
      return None;
    }
    debStartTime = millis();

    butLst = but;

    if (LOW == but)  {   // press
      if (msecLst)  { // 2nd press
        msecLst = 0;
        return DoubleClick;
      }
      else {
        msecLst = 0 == msec ? 1 : msec;
        return SingleClick; //SINGLE?
      }
    }
  }
  return None;
}

// -----------------------------------------------------------------------------
void loop () {

  timer_3 = millis();
  inter = timer_3 - currenttime3;

  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  if (inter >= 1000) {
    currenttime3 = millis();
    adc_PV_value = analogRead(ANALOG_PV_IN_PIN);
    adc_PV_voltage  = (adc_PV_value * ref_voltage) / 1024.0;
    in_PV_voltage = adc_PV_voltage;

    adc_BATT_value = analogRead(ANALOG_BATT_IN_PIN);
    adc_BATT_voltage  = (adc_BATT_value * ref_voltage) / 1024.0;
    in_BATT_voltage = adc_BATT_voltage;
  }
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  if (lightstate == HIGH) {// LIGHT ON
    if (powermode == 0) { //powermode OFF
      if (battlev == 0) {  //BATT LOW
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, HIGH);
        digitalWrite(usbbatt, LOW);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, HIGH);
        digitalWrite(soccharge, LOW);
      }
      else if (battlev == 1) {      //MEDIUM
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, HIGH);
        digitalWrite(usbbatt, LOW);
        digitalWrite(usbpv, HIGH);
        //digitalWrite(PVcharge, HIGH);
        digitalWrite(soccharge, LOW);
      }
      else if (battlev == 2) {      //HIGH
        digitalWrite(lampbatt, HIGH);
        digitalWrite(lampsock, LOW);
        digitalWrite(usbbatt, LOW);
        digitalWrite(usbpv, HIGH);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, LOW);
      }
      else if (battlev == 3) {      //very low
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, HIGH);
        digitalWrite(usbbatt, LOW);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, LOW);
        digitalWrite(red, HIGH);
      }
    }
    else { // powermode ON
      if (battlev == 0) {  //BATT LOW
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, HIGH);
        digitalWrite(usbbatt, HIGH);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, HIGH);
      }
      else if (battlev == 1) {      //MEDIUM
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, HIGH);
        digitalWrite(usbbatt, HIGH);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, HIGH);
        digitalWrite(soccharge, LOW);
      }
      else if (battlev == 2) {      //HIGH
        digitalWrite(lampbatt, HIGH);
        digitalWrite(lampsock, LOW);
        digitalWrite(usbbatt, HIGH);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, LOW);
      }
      else if (battlev == 3) {      //very low
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, HIGH);
        digitalWrite(usbbatt, LOW);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, LOW);
        digitalWrite(red, HIGH);
      }
    }
  }
  else {//LIGHT OFF
    if (powermode == 0) { //powermode OFF
      if (battlev == 0) {  //LOW
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, LOW);
        digitalWrite(usbbatt, LOW);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, LOW);
      }
      else if (battlev == 1) {     //MEDIUM
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, LOW);
        digitalWrite(usbbatt, HIGH);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, LOW);
      }
      else if (battlev == 2) {    //HIGH
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, LOW);
        digitalWrite(usbbatt, HIGH);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, LOW);
      }
      else if (battlev == 3) {      //very low
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, LOW);
        digitalWrite(usbbatt, LOW);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, HIGH);
        digitalWrite(red, HIGH);
      }
    }
    else { //powermode ON
      if (battlev == 0) {  //BATT LOW
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, LOW);
        digitalWrite(usbbatt, HIGH);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, HIGH);
      }
      else if (battlev == 1) {      //MEDIUM
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, LOW);
        digitalWrite(usbbatt, HIGH);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, LOW);
      }
      else if (battlev == 2) {      //HIGH
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, LOW);
        digitalWrite(usbbatt, HIGH);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, LOW);
      }
      else if (battlev == 3) {      //very low
        digitalWrite(lampbatt, LOW);
        digitalWrite(lampsock, LOW);
        digitalWrite(usbbatt, LOW);
        digitalWrite(usbpv, LOW);
        //digitalWrite(PVcharge, LOW);
        digitalWrite(soccharge, LOW);
        digitalWrite(red, HIGH);
      }
    }
  }

  if (wifiinputstate != lastwifiinputstate) {
    if (lightstate == 1) {
      WiFis = 1;
    }
    else if (lightstate == 0) {
      WiFis = 2;
    }
  }

  if (in_BATT_voltage >= 4.12) { //BATTFULL
    bonr = 1;
    lastbonr = 1;
  }
  else if (in_BATT_voltage >= 3 && in_BATT_voltage <= 3.1) { //BATTLOW
    bonr = 2;
    lastbonr = 2;
  }
  else if (in_BATT_voltage >= 3.4 && in_BATT_voltage <= 3.5) {
    bonr = 0;
    lastbonr = 0;
  }
  else if (in_BATT_voltage < 3 ) {
    bonr = 3;
  }
  else if (in_BATT_voltage > 3.5 && in_BATT_voltage < 4.12) {
    bonr = lastbonr;
  }
  else if (in_BATT_voltage > 3.1 && in_BATT_voltage < 3.4) {
    bonr = lastbonr;
  }


  switch (bonr) {
    case 0:
      battled = blue;
      battlev = 1;
      break;
    case 1:
      battled = green;
      battlev = 2;
      break;
    case 2:
      battled = red;
      battlev = 0;
      break;
    case 3:
      battled = red;
      battlev = 3;
      break;
  }

  digitalWrite(light, lightstate);
  wifiinputstate = digitalRead(wifiinput);
  timer_1 = millis();
  timer_2 = millis();

  switch (chkButton ())  {
    case SingleClick:
      break;

    case DoubleClick:
      currenttime2 = 1;
      if (powermode == 0) {
        powermode = 1; // Power saving mode OFF
      }
      else {
        powermode = 0; // Power saving mode ON
      }
      break;

    case YesSingle:
      currenttime = 1;
      if (lightstate == HIGH) {
        lightstate = LOW; // LIGHT OFF
      }
      else {
        lightstate = HIGH; //LIGHT ON
      }
      break;
  }

  switch (currenttime) {
    case 0:
      break;
    case 1:
      currenttime_1 = timer_1;
      currenttime++;
      break;
    case 2:
      currenttime = 0;
      break;
  }

  switch (currenttime2) {
    case 0:
      break;
    case 1:
      currenttime_2 = timer_2;
      currenttime2++;
      break;
    case 2:
      currenttime2 = 0;
      break;
  }

  if (lightstate != lastlightstate) {
    if (battled == red) {
      digitalWrite(red, HIGH);
    }
    else if (battled == blue) {
      digitalWrite(blue, HIGH);
    }
    else if (battled == green) {
      digitalWrite(green, HIGH);
    }
  }
  if (timer_1 - currenttime_1 >= 1000) {
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    lastlightstate = lightstate;
  }

  if (powermode != lastpowermode) {
    if (powermode == 0){ //yellow
      digitalWrite(green, HIGH);
      digitalWrite(red, HIGH);
    }
    else { //violet
      digitalWrite(blue, HIGH);
      digitalWrite(red, HIGH);
    }
    ledoff++;
  }

  switch (ledoff) {
    case 0:
      break;
    case 1:
      if (timer_2 - currenttime_2 >= 1000) {
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
        lastpowermode = powermode;
        ledoff++;
      }
      break;
    case 2:
      ledoff = 0;
      break;
  }

  switch (WiFis) {
    case 0:
      break;
    case 1:
      lightstate = 0;
      lastwifiinputstate = wifiinputstate;
      currenttime = 1;
      WiFis = 0;
      break;
    case 2:
      lightstate = 1;
      lastwifiinputstate = wifiinputstate;
      currenttime = 1;
      WiFis = 0;
      break;
  }

//  if (in_PV_voltage <= 1.5 && lightstate == HIGH) { //PV disconnected / too low power
//    PVfail++;
//  }
//  switch (PVfail) {
//    case 0:
//      break;
//    case 1:
//      if (lightstate = HIGH) {
//        PVfail = 1;
//        digitalWrite(red, HIGH);
//        digitalWrite(green, HIGH);
//        digitalWrite(blue, HIGH);
//      }
//      else if (lightstate == LOW) {
//        PVfail = 2;
//      }
//      break;
//  }
}
// -----------------------------------------------------------------------------
void setup ()
{
  Serial.begin (9600);
  pinMode (pinBut, INPUT_PULLUP);
  pinMode (wifiinput, INPUT_PULLUP);
  pinMode(light, OUTPUT);
  pinMode(lampbatt, OUTPUT);
  pinMode(usbbatt, OUTPUT);
  pinMode(PVcharge, OUTPUT);
  pinMode(lampsock, OUTPUT);
  pinMode(usbpv, OUTPUT);
  pinMode(soccharge, OUTPUT);

  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  butLst = digitalRead (pinBut);
}
