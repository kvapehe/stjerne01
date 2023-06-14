/* Mulig kilde: https://wokwi.com/projects/367353720435774465
*/
#include <FastLED.h>

/* Preparing the program ************************************************************
   Declaring macros, constants, variables and arrays
 ********************************************************************************* */
#define strips 16
#define NUM_LEDS   60
// #define BRIGHTNESS 64
#define LED_TYPE   WS2811
#define COLOR_ORDER GRB
// All LED_pins are defined inside a function

#define BRIGHTNESS  80 // Max 80 (For safety)
#define PAUSE_TIME1 400
#define PAUSE_TIME2 50


const int BUTTONPIN = 3;
int knapp = 0;

// delays
const int delayShort = 50; // delay is 50 ms

CRGB leds[strips][NUM_LEDS];

//Firework
const int LEDS_IN_STRIP_USED = 16;
int range[LEDS_IN_STRIP_USED];
int palettefireworks[5][5] = {
  {246, 240, 82},
  {241, 188, 49},
  {226, 88, 34},
  {178, 34, 34},
  {124, 10, 2}
};

uint8_t laststage = 0;
uint8_t laststage2 = 0;
uint8_t laststage3 = 0;
//End of firework init

// Variable for ISR (Interrupt routine)
volatile byte state = LOW;

unsigned long timerRounds = 0;
unsigned long FWRounds = 0;
unsigned long timerDelay = 1000;


/* Declaring functions ************************************************************
*/

void addPinToFastLed();
void changestate(); // ISR
void firework(
  uint8_t launch_strip = 8,
  uint8_t firework_range = 50,
  uint8_t firework_differ = 6,
  int rise_delay = 20,
  int exp_delay = 1);
void dissolve();
void mai17();
void redDesign1(int Hue, int Sat, int Val);
void setFlag(int Hue, int Sat, int Val, int H, int S, int V, int Hue2, int Sat2, int Val2);
void Flagg(int Hue, int Sat, int Val, int H, int S, int V, int Hue2, int Sat2, int Val2);
void wrapperResetFlag();


/* setup function ************************************************************
*/
void setup() {

  Serial.begin(115200);
  //WiFi.mode(WIFI_STA); // Set Wi-Fi mode to STA
  //WiFi.begin("ssid", "pwd"); // Start Wi-Fi

  //ArduinoOTA.setHostname("name"); // Change OTA name
  //ArduinoOTA.setPassword("pwd"); // Change OTA passoword
  //ArduinoOTA.begin(); // Start OTA

  Serial.print("\n == Setup == ");
  pinMode(BUTTONPIN, INPUT_PULLUP);
  addPinToFastLed();
  attachInterrupt(digitalPinToInterrupt(BUTTONPIN), changestate, FALLING);

  // delay(50);
  Serial.print("\n == Setup completed\t\n");

} // end setup

/* loop function ************************************************************
*/

/* old loop
void loop() {
  if (state == HIGH) {
    FWRounds++;
    // Check if button has been pressed giving an interrrupt
    // Initiates the "fireworks"
    state = LOW;
    Serial.print("\nLoop firework ");
    Serial.print("nr:\t"); Serial.print(FWRounds); Serial.print("\t");
    mai17();
    // firework(4);


  }
  long timer = millis() % 47000;
  long lasttimer = 0;

  // Running once in loop after MCU is started or reset
  if (millis() < 500 ) {
    Serial.print("\nFlag first time "); Serial.print( millis() ); Serial.print(" ms ");
    // Prepare flag once, after MCU is reset
    // Design1(0, 255, 155, 160, 255, 170, 0, 0, 220);
    redDesign1(0, 255, 155); // Set to red as fast as possible
    setFlag(0, 255, 155, 160, 255, 170, 0, 0, 220);
    Serial.print("\nFlag ready "); Serial.print( millis() ); Serial.print(" ms\n");
  }

  // The regular sequence
  if (timer < 10000) {
    if (timer < timerDelay) {
      timerRounds++;
      Serial.print("Timer flagg\t");
      Serial.print(" Runde nr:\t"); Serial.print(timerRounds); Serial.print("\n");
      // Serial.print(timer); Serial.print(" * "); Serial.print(timerRounds);
      // Serial.print(" = "); Serial.print(timer * timerRounds); Serial.print(" ms\n");
    } // Serial.print(" ");Serial.print(timer);Serial.print(" ");

    // Endre tone på Rød farge slik at rød muligens blinker litt
    Flagg(0, 255, 155, 160, 255, 170, 0, 0, 220);

    // Runs the Flagg function with default colour setup
    wrapperResetFlag(); // Displays flag when all LED's are ready

    FastLED.show();
  }

  if ( (10000 < timer) && (timer < 20000) ) {
    if ( (10000 < timer) && (timer < 10000 + timerDelay) ) {
      Serial.print("Timer design 2\t");
    } // Serial.print(" 2 ");Serial.print(timer);Serial.print(" ");
    Design2(0, 255, 170);
    Design2(0, 0, 220);
    Design2(160, 255, 170);
  }

  if ( (20000 < timer) && (timer < 30000) ) {
    if ( (20000 < timer) && (timer < 20000 + timerDelay) ) {
      Serial.print("Timer design 3\t");
    } // Serial.print(" 3 ");Serial.print(timer);Serial.print(" ");
    Design3(0, 255, 170, 160, 255, 170, 0, 0, 220);
  }

  if ( (30000 < timer) && (timer < 45000) ) {
    if ( (30000 < timer) && (timer < 30000 + 700) ) {
      Serial.print("Timer design 5\t\n");
    } // Serial.print(" 5 ");Serial.print(timer);Serial.print(" ");
    Design5(0, 255, 170, 160, 255, 170, 0, 0, 220);
    Design5(0, 0, 220, 0, 255, 170, 160, 255, 170);
    Design5(160, 255, 170, 0, 0, 220, 0, 255, 170);
  }

  //Design3(0, 255, 170, 160, 255, 170, 0, 0, 220);
  // wrapperResetFlag();
  //FastLED.show();
  //dissolve();

  //Design1(160, 255, 170, 45, 200, 220);
  //Design1(45, 200, 220, 160, 255, 170);
  //Design2(160, 255, 170, 45, 200, 220);
  //Design2(45, 200, 220, 160, 255, 170);
  //Logo(45, 200, 220, 160, 255, 170);

} // end loop
*/



void loop() {
  unsigned long timer = millis() % 40000;

  if (timer < 10000) {
    Serial.println("1/4");
    Design01(255, 100, 100);
    delay(PAUSE_TIME1);
    Design01(100, 255, 100);
    delay(PAUSE_TIME1);
    Design01(100, 100, 255);
    delay(PAUSE_TIME1);
  }
  if ( (10000 < timer) && (timer < 20000) ) {
    Serial.println("2/4");
    Design02(255, 0, 0);
    delay(PAUSE_TIME1);
    Design02(0, 255, 0);
    delay(PAUSE_TIME1);
    Design02(0, 0, 255);
    delay(PAUSE_TIME1);
  }
  if ( (20000 < timer) && (timer < 30000) ) {
    Serial.println("3/4");
    Design03(255, 255, 0);
    Design03(0, 255, 255);
    Design03(255, 0, 255);
  }
  if (30000 < timer) {
    Serial.println("4/4");
    Design04(255, 0, 0);
    Design04(255, 127, 0);
    Design04(255, 255, 0);
    Design04(127, 255, 0);
    Design04(0, 255, 0);
    Design04(0, 255, 127);
    Design04(0, 255, 255);
    Design04(0, 127, 255);
    Design04(0, 0, 255);
    Design04(127, 0, 255);
    Design04(255, 0, 255);
    Design04(255, 0, 127);
  }
}

void Design01(int R, int G, int B) { // Normal
  for (int k = 0; k < strips; k++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[k][i] = CRGB(R, G, B);
    }
  }
  FastLED.show();
}

void Design02(int R, int G, int B) { // Dissolve
  for (int y = 20; y > 0; y--) {
    for (int a = 30; a > 0; a--) {
      leds[random(0, strips)][random(0, NUM_LEDS)] = CRGB(R, G, B);
    }
    FastLED.show();
    delay(20);
  }
}

void Design03(int R, int G, int B) { // Swipe slow
  for (int k = 0; k < strips; k++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[k][i] = CRGB(R, G, B);
      FastLED.show();
      delay(10);
    }
  }
}

void Design04(int R, int G, int B) { // Swipe fast
  for (int k = 0; k < strips; k++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[k][i] = CRGB(R, G, B);
      FastLED.show();
    }
  }
}

void Design05(int R, int G, int B, int R2, int G2, int B2) { // Fade half
  float R_Increment = abs(R - R2) / 10;
  float G_Increment = abs(G - G2) / 10;
  float B_Increment = abs(B - B2) / 10;
  float currentR = 0;
  float currentG = 0;
  float currentB = 0;
  for (int o = 0; o < 10; o++) {
    currentR += R_Increment;
    currentG += G_Increment;
    currentB += B_Increment;
    for (int k = 0; k < strips; k++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[k][i] = CRGB((byte)currentR, (byte)currentG, (byte)currentB);
      }
    }
    FastLED.show();
    delay(PAUSE_TIME2);
  }
}




/* Implementing functions ************************************************************
*/



void addPinToFastLed() {

  // An array is not compatible with FastLED.addLeds
  const int LEDARRAY[] = {
    5,  6,  7,  8,  9, 10, 11, 12, // First  8 pins
    22, 24, 26, 28, 30, 32, 34, 36  // Second 8 pins
  };
  // Every pin has to be a constant and added separetely
  // Pin configuration is for Arduino Mega

  // First 8 pins: 5 - 12
  const int LED1  =  5;
  const int LED2  =  6;
  const int LED3  =  7;
  const int LED4  =  8;
  const int LED5  =  9;
  const int LED6  = 10;
  const int LED7  = 11;
  const int LED8  = 12;

  // Next 8 pins 22 - 36 every second pin number
  const int LED9  = 22;
  const int LED10 = 24;
  const int LED11 = 26;
  const int LED12 = 28;
  const int LED13 = 30;
  const int LED14 = 32;
  const int LED15 = 34;
  const int LED16 = 36;

  // Not possible to add an array like so: LEDARRAY[0] instead of LED1 ...
  FastLED.addLeds<LED_TYPE, LED1,  COLOR_ORDER>(leds[0],  NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED2,  COLOR_ORDER>(leds[1],  NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED3,  COLOR_ORDER>(leds[2],  NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED4,  COLOR_ORDER>(leds[3],  NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED5,  COLOR_ORDER>(leds[4],  NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED6,  COLOR_ORDER>(leds[5],  NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED7,  COLOR_ORDER>(leds[6],  NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED8,  COLOR_ORDER>(leds[7],  NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED9,  COLOR_ORDER>(leds[8],  NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED10, COLOR_ORDER>(leds[9],  NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED11, COLOR_ORDER>(leds[10], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED12, COLOR_ORDER>(leds[11], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED13, COLOR_ORDER>(leds[12], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED14, COLOR_ORDER>(leds[13], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED15, COLOR_ORDER>(leds[14], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED16, COLOR_ORDER>(leds[15], NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

}


void changestate() {
  // ISR routine
  state = HIGH;
}

void mai17() {
  // Create a pattern
  Serial.print("\nFyrverkeri:\n");
  Design5(0, 255, 170, 160, 255, 170, 0, 0, 220); Serial.print("\tD5 1 R H B | R B H");
  Design5(0, 0, 220, 0, 255, 170, 160, 255, 170); Serial.print("\tD5 2 H B R | H R B");
  Design5(160, 255, 170, 0, 0, 220, 0, 255, 170); Serial.print("\tD5 3 B R H | B H R\n");

  Design6(160, 255, 170, 0, 255, 170, 0, 0, 220); Serial.print("\tD6 1 B H R | B R H");
  Design6(0, 255, 170, 0, 0, 220, 160, 255, 170); Serial.print("\tD6 2 R B H | R H B");
  Design6(0, 0, 220, 160, 255, 170, 0, 255, 220); Serial.print("\tD6 3 H R B | H B R");

  //Design6(0, 0, 220, 0, 255, 170, 160, 255, 170);Serial.println("\nD6 a H B R | H R B"); // B H R
  //Design6(160, 255, 170, 0, 0, 220, 0, 255, 170);Serial.println("\nD6 b B R H | B H R"); // R B H
  //Design6(0, 255, 170, 160, 255, 170, 0, 0, 220);Serial.println("\nD6 c R H B | R B H"); // H R B

  wrapperResetFlag();

  FastLED.show();
  delay(3000);
  dissolve();
  Serial.print("\nFyrverkeri er over\n");
  FastLED.clear();
}

void redDesign1(int Hue, int Sat, int Val) {
  // Eksperimenter med FastLED.show(); og verdier for å få ønsket effekt
  FastLED.clear();
  for (int i = 0; i < 60; i++) {
    int ledsrounds = 8; // 1 - 10 er ok verdier
    if (i % ledsrounds == 0 ) {
      FastLED.show();
    }

    for (int k = 0; k < 16; k++) {
      int steps = 16; // 16 - 30 er ok verdier (1 - 60 virker)
      leds[k][i] = CHSV(Hue, Sat, Val);
      if (i % steps == 0 ) {
        // FastLED.show();
      }

    }
  }
  FastLED.show();
  // delay(300);
}

void Design1(int Hue, int Sat, int Val) {
  for (int k = 0; k < 16; k++) {
    for (int i = 0; i < 60; i++) {
      leds[k][i] = CHSV(Hue, Sat, Val);
    }
    FastLED.show();
    delay(delayShort);
  }
}

void Design2 (int H, int S, int V, int Hue, int Sat, int Val) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[0][i] = CHSV(Hue, Sat, Val);
    leds[8][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[1][i] = CHSV(Hue, Sat, Val);
    leds[9][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[2][i] = CHSV(Hue, Sat, Val);
    leds[10][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[3][i] = CHSV(Hue, Sat, Val);
    leds[11][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[4][i] = CHSV(Hue, Sat, Val);
    leds[12][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[5][i] = CHSV(Hue, Sat, Val);
    leds[13][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[6][i] = CHSV(Hue, Sat, Val);
    leds[14][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[7][i] = CHSV(Hue, Sat, Val);
    leds[15][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[8][i] = CHSV(Hue, Sat, Val);
    leds[0][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[9][i] = CHSV(Hue, Sat, Val);
    leds[1][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[10][i] = CHSV(Hue, Sat, Val);
    leds[2][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[11][i] = CHSV(Hue, Sat, Val);
    leds[3][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[12][i] = CHSV(Hue, Sat, Val);
    leds[4][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[13][i] = CHSV(Hue, Sat, Val);
    leds[5][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[14][i] = CHSV(Hue, Sat, Val);
    leds[6][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[15][i] = CHSV(Hue, Sat, Val);
    leds[7][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
}

void Design2(int Hue, int Sat, int Val) {
  for (int i = 0; i < 60; i++) {
    leds[0][i] = CHSV(Hue, Sat, Val);
    leds[8][i] = CHSV(Hue, Sat, Val);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[1][i] = CHSV(Hue, Sat, Val);
    leds[9][i] = CHSV(Hue, Sat, Val);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[2][i] = CHSV(Hue, Sat, Val);
    leds[10][i] = CHSV(Hue, Sat, Val);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[3][i] = CHSV(Hue, Sat, Val);
    leds[11][i] = CHSV(Hue, Sat, Val);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[4][i] = CHSV(Hue, Sat, Val);
    leds[12][i] = CHSV(Hue, Sat, Val);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[5][i] = CHSV(Hue, Sat, Val);
    leds[13][i] = CHSV(Hue, Sat, Val);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[6][i] = CHSV(Hue, Sat, Val);
    leds[14][i] = CHSV(Hue, Sat, Val);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[7][i] = CHSV(Hue, Sat, Val);
    leds[15][i] = CHSV(Hue, Sat, Val);
  }
  FastLED.show();
  delay(delayShort);

}

void Design3(int Hue, int Sat, int Val, int H, int S, int V, int Hue2, int Sat2, int Val2) {
  for (int i = 0; i < 60; i++) {
    leds[0][i] = CHSV(Hue, Sat, Val);
    leds[1][i] = CHSV(Hue, Sat, Val);
    leds[6][i] = CHSV(Hue2, Sat2, Val2);
    leds[11][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[2][i] = CHSV(Hue, Sat, Val);
    leds[7][i] = CHSV(Hue2, Sat2, Val2);
    leds[12][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[3][i] = CHSV(Hue, Sat, Val);
    leds[8][i] = CHSV(Hue2, Sat2, Val2);
    leds[13][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[4][i] = CHSV(Hue, Sat, Val);
    leds[9][i] = CHSV(Hue2, Sat2, Val2);
    leds[14][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[5][i] = CHSV(Hue, Sat, Val);
    leds[10][i] = CHSV(Hue2, Sat2, Val2);
    leds[15][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[6][i] = CHSV(Hue, Sat, Val);
    leds[11][i] = CHSV(Hue2, Sat2, Val2);
    leds[0][i] = CHSV(H, S, V);
    leds[1][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[7][i] = CHSV(Hue, Sat, Val);
    leds[12][i] = CHSV(Hue2, Sat2, Val2);
    leds[2][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[8][i] = CHSV(Hue, Sat, Val);
    leds[13][i] = CHSV(Hue2, Sat2, Val2);
    leds[3][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[9][i] = CHSV(Hue, Sat, Val);
    leds[14][i] = CHSV(Hue2, Sat2, Val2);
    leds[4][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[10][i] = CHSV(Hue, Sat, Val);
    leds[15][i] = CHSV(Hue2, Sat2, Val2);
    leds[5][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[11][i] = CHSV(Hue, Sat, Val);
    leds[0][i] = CHSV(Hue2, Sat2, Val2);
    leds[1][i] = CHSV(Hue2, Sat2, Val2);
    leds[6][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[12][i] = CHSV(Hue, Sat, Val);
    leds[2][i] = CHSV(Hue2, Sat2, Val2);
    leds[7][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[13][i] = CHSV(Hue, Sat, Val);
    leds[3][i] = CHSV(Hue2, Sat2, Val2);
    leds[8][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[14][i] = CHSV(Hue, Sat, Val);
    leds[4][i] = CHSV(Hue2, Sat2, Val2);
    leds[9][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);
  for (int i = 0; i < 60; i++) {
    leds[15][i] = CHSV(Hue, Sat, Val);
    leds[5][i] = CHSV(Hue2, Sat2, Val2);
    leds[10][i] = CHSV(H, S, V);
  }
  FastLED.show();
  delay(delayShort);

}

void Design5(int Hue, int Sat, int Val, int H, int S, int V, int Hue2, int Sat2, int Val2) {
  for (int i = 0; i < 20; i++) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CHSV(Hue, Sat, Val);
    }
    FastLED.show();
    //delay(delayShort);
  }
  for (int i = 20; i < 40; i++) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CHSV(Hue2, Sat2, Val2);
    }
    FastLED.show();
    //delay(delayShort);
  }
  if (state == true) {
    return;
  }
  for (int i = 40; i < 60; i++) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CHSV(H, S, V);
    }
    FastLED.show();
    //delay(delayShort);
  }
}

void Design6(int Hue, int Sat, int Val, int H, int S, int V, int Hue2, int Sat2, int Val2) {
  for (int i = 60; i > 40; i--) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CHSV(Hue, Sat, Val);
    }
    FastLED.show();
    //delay(delayShort);
  }
  for (int i = 40; i > 20; i--) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CHSV(Hue2, Sat2, Val2);
    }
    FastLED.show();
    //delay(delayShort);
  }
  for (int i = 20; i >= 0; i--) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CHSV(H, S, V);
    }
    FastLED.show();
    //delay(delayShort);
  }
}

void Flagg(int Hue, int Sat, int Val, int H, int S, int V, int Hue2, int Sat2, int Val2) {
  for (int k = 0; k < 16; k++) {
    for (int i = 0; i < 20; i++) {
      leds[k][i] = CHSV(Hue, Sat, Val);
    }
    for (int i = 20; i < 25; i++) {
      leds[k][i] = CHSV(Hue2, Sat2, Val2);
    }
    for (int i = 25; i < 35; i++) {
      leds[k][i] = CHSV(H, S, V);
    }
    for (int i = 35; i < 40; i++) {
      leds[k][i] = CHSV(Hue2, Sat2, Val2);
    }
    for (int i = 40; i < 60; i++) {
      leds[k][i] = CHSV(Hue, Sat, Val);
    }
    FastLED.show();
    delay(delayShort);
  }
}

void wrapperResetFlag() {
  // Flagg(0, 255, 155, 160, 255, 170, 0, 0, 220); // Endre tone på Rød farge
  Flagg(0, 255, 170, 160, 255, 170, 0, 0, 220);
}

void setFlag(int Hue, int Sat, int Val, int H, int S, int V, int Hue2, int Sat2, int Val2) {

  for (int k = 0; k < 16; k++) {
    for (int i = 0; i < 20; i++) {
      leds[k][i] = CHSV(Hue, Sat, Val);
    }
    for (int i = 20; i < 25; i++) {
      leds[k][i] = CHSV(Hue2, Sat2, Val2);
    }
    for (int i = 25; i < 35; i++) {
      leds[k][i] = CHSV(H, S, V);
    }
    for (int i = 35; i < 40; i++) {
      leds[k][i] = CHSV(Hue2, Sat2, Val2);
    }
    for (int i = 40; i < 60; i++) {
      leds[k][i] = CHSV(Hue, Sat, Val);
    }

    // |delay(delayShort);
  }
  FastLED.show();


}

void firework(uint8_t launch_strip = 8, uint8_t firework_range = 50, uint8_t firework_differ = 6, int rise_delay = 20, int exp_delay = 1) {
  //Launch Firework Effect
  FastLED.clear();
  for (int stage = NUM_LEDS; int(stage) >= 0 ; stage--) {
    leds[launch_strip][stage] = CHSV(10, 0, 100);
    leds[launch_strip][laststage] = CHSV(10, 20, 100);
    leds[launch_strip][laststage2] = CHSV(10, 10, 100);
    leds[launch_strip][laststage3] = CHSV(10, 0, 100);
    FastLED.show();

    laststage3 = laststage2;
    laststage2 = laststage;
    laststage = stage;
    delay(rise_delay);

  }


  //Set random offset for each strip
  for (int currentstrip = strips - 1; currentstrip >= 0; currentstrip--) {
    range[currentstrip] = random((firework_range - firework_differ) / 2, firework_range / 2) * 2;
    delay(1);
  }

  //Do the thing
  for (int stage = 0; int(stage) / 55 < 1; stage++) {
    for (int currentstrip = strips - 1; currentstrip >= 0; currentstrip--) {
      if (range[currentstrip] >= stage) {
        leds[currentstrip][stage].red = palettefireworks[stage / (firework_range / 4)][0] + random(-10, 10);
        leds[currentstrip][stage].green = palettefireworks[stage / (firework_range / 4)][1] + random(-10, 10);
        leds[currentstrip][stage].blue = palettefireworks[stage / (firework_range / 4)][2] + random(-10, 10);
        //leds[currentstrip][stage] = CRGB::Red;
        //leds[i][laststage2] = CRGB::Black;
      }
    }
    FastLED.show();
    //Serial.println(int(stage));
    delay(exp_delay);
    laststage2 = laststage;
    laststage = stage;


  }
  /*for(int y = 40; y > 0; y--){
    for(int a = 10; a > 0; a--){
    leds[random(1,16)][random(20,50)] = CHSV(0, 0, 0);

    }
    FastLED.show();
    delay(10);
    }
  */
  dissolve();
  FastLED.clear();
}

void dissolve() {
  for (int y = 40; y > 0; y--) {
    for (int a = 30; a > 0; a--) {
      leds[random(0, 16)][random(0, 60)] = CHSV(0, 0, 0);

    }
    FastLED.show();
    delay(10);
  }
}
