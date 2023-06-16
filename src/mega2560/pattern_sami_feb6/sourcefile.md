# MD-file for the source code.

```ino
/* https://wokwi.com/projects/367677638707044353
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
#define PAUSE_TIME3 20
#define PAUSE_TIME4 10



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

unsigned long timer = 0; // millis() % 100000;
unsigned long timer2 = timer; // Information counter
unsigned long timerMax = 110000;
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
void loop() {
  // Etter 100 sekund så nullstilles det. Alle tider kan endres slik en ønsker.
  // Det er lagt til rette for ca 20 sekun for hvert del.
  // Se også farger langt nede i koden for ulike fargeforslag. Her kommer noen for å gi et lite inntrykk
  // Svært mye av koden er ekstra i denne versjonen. Det er tatt med så en har noen alternativer til å teste med.

  timer = millis() % 100000;
  timer2 = timer;
  if (timer2 > 1e5) {
    timer2 = timer;
  }

  statetester();

  // Farger
  CRGB(218, 20, 20);
  CRGB(201, 153, 32);
  CRGB(57, 203, 28);
  CRGB(79, 203, 211);
  CRGB(29, 128, 189);
  CRGB(169, 165, 213);
  CRGB(216, 46, 197);
  CRGB(215, 42, 123);
  // Farger 2
  CRGB(218, 20, 20);
  CRGB(201, 153, 32);
  CRGB(57, 203, 28);
  CRGB(79, 203, 211);
  CRGB(29, 128, 189);
  CRGB(169, 165, 213);
  CRGB(216, 46, 197);
  CRGB(215, 42, 123);

  // Regnbuefarger, som er benytttet flere steder. Det virker som OK valg med LED/stripene
  // NB ikke testet på ordinær Mega eller ESP32
  CRGB(255, 0,   0);  // Rød
  CRGB(180, 85,  0);  // Oransje lys CRGB(75, 55, 0);  // Oransje mørk
  CRGB(255, 255, 0);  // Gul
  CRGB(0,  70,  20);  // Grønn
  CRGB(0, 0, 255  );  // Blå      // CRGB(238, 130, 238); // Hvit
  CRGB(46, 0, 46  );  // Lilla    // CRGB(149, 88, 184);   // Rosa


  if (timer < 20000) {
    statetester();
    Serial.print("1/4");
    Serial.print(" \t\t\t" + String(timer * 1e-3) + " sek \n" );
    // CRGB(255,0,0);  CRGB(180, 85, 0);  CRGB(255,255,0);
    // CRGB(0,128,0);  CRGB(0, 0, 255); CRGB(46, 0, 46  );
    // CRGB(238, 130, 238);  CRGB(149, 88, 184)  CRGB(44, 43, 43);
    // Design04RB2(80, 110,   0, 2, 6); // Mørkere gul      CRGB(80,100,0);

    // Her er ulike design blandet litt "tilfeldig" for å eksperimentere med ulike mønster.
    // Det er ikke meningen endelig versjon skal se slik ut, og fyrverkerikanppen lager det norske flagget pr nå.

    // Seksjon 1
    delay(PAUSE_TIME1);    Design01(255, 0, 0);    // Rød
    // delay(PAUSE_TIME1);    Design01(0, 10 , 0);    // Grøn
    wrapperResetFlag();
    delay(PAUSE_TIME1*4);    

/*
delay(PAUSE_TIME1);    Design01(0, 60, 10);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 15);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 20);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 25);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 30);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 35);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 40);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 45);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70, 10);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70, 15);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70, 20);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70, 25);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70, 30);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70, 35);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70, 40);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70, 45);    // Grøn

delay(PAUSE_TIME1);    Design01(0, 20 , 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 30 , 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 40 , 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 50 , 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60 , 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70 , 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 80 , 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 90 , 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 100, 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 110, 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 120, 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 130, 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 140, 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 150, 0);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 160, 0);    // Grøn

delay(PAUSE_TIME1);    Design04(0, 40, 10);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 40, 15);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 40, 20);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 40, 25);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 50, 30);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 50, 35);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 50, 40);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 50, 45);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 50, 50);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 55);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 60);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 65);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 70);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 60, 75);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70, 80);    // Grøn
delay(PAUSE_TIME1);    Design01(0, 70, 85);    // Grøn
*/
    
    
    // delay(PAUSE_TIME1);    Design01(180, 85, 0);   // Oransje lys delay(PAUSE_TIME1); Design01(75, 55, 0);  // Oransje mørk
    // delay(PAUSE_TIME1);    Design01(46, 0, 46  );  // Lilla

    // Seksjon 1.5
    statetester(); Design04RB1(255,   0,   0, 0, 4); // Rød
    // statetester(); Design04RB1(180,  85,   0, 1, 6); // Oransje
    statetester(); Design04RB1(  0,  70,  20, 1, 4); // Grønn
    statetester(); Design04RB1( 80, 110,   0, 2, 4); // Gul
        statetester(); Design04RB1(  0,   0, 255, 3, 4); // Blå
    // Design04RB1( 46,   0,  46, 5, 6); // Lilla Dersom siste Design01 var lilla over
    delay(PAUSE_TIME1*2); 

    // Test med Design05(). Kommenteres bort etterhvert og kan plasseres i en annen tids.seksjon med tanke på timer
    // NB slik koden er nå kan dette føre til ikke alle deler kjøres. 1/4, 2/4, 3/4, 4/4 og 5 av 4. Fikse logikken senere
    Design05wrapper();
    statetester();


    // Seksjon 2
    delay(PAUSE_TIME1);    Design01(80, 110,   0);  // Gul
    delay(PAUSE_TIME1);    Design01(0,  70,  20);    //Grønn

    // Seksjon 2.5
    delay(PAUSE_TIME1); Design04RB2(255,   0,   0, 0, 4); // Rød      CRGB(255, 0, 0);
    // delay(PAUSE_TIME1); Design04RB2(180,  85,   0, 1, 4); // Oransje
    delay(PAUSE_TIME1); Design04RB2(  0,  70,  20, 1, 4); // Grønn    CRGB(0,128,0);
    delay(PAUSE_TIME1); Design04RB2( 80, 110,   0, 2, 4); // Gul      CRGB(80,100,0);    
    delay(PAUSE_TIME1); Design04RB2(  0,   0, 255, 3, 4); // Blå      CRGB(0, 0, 255);
    // delay(PAUSE_TIME1); Design04RB2( 46,   0,  46, 5, 4); // Lilla
    statetester();
    delay(PAUSE_TIME1 * 8);
    // Seksjon 3
    // Design03RB10();
    statetester();
    //delay(PAUSE_TIME1);    Design01(0, 0, 255);    // Blå    delay(PAUSE_TIME1);    //Design01(238, 130, 238); // Hvit
    delay(PAUSE_TIME1);    Design01(46, 96, 46);   // Eksperimentere med denne. Planen er å lage et lerret til neste sekvens (Grå bakgrunn??)
    delay(PAUSE_TIME1 * 2);

    // Seksjon 3.5
    statetester(); Design04RB3(255,   0,   0, 0, 4); // Rød
    // statetester(); Design04RB3(180,  85,   0, 1, 6); // Oransje
    statetester(); Design04RB3(  0,  70,  20, 1, 4); // Grønn
    statetester(); Design04RB3( 80, 110,   0, 2, 4); // Gul
        statetester(); Design04RB3(  0,   0, 255, 3, 4); // Blå
    // statetester(); Design04RB3( 46,   0,  46, 5, 6); // Lilla

    /* Bruk av koden, kommentert bort for nå.
        Design04RBx(int R, int G, int B, int start, int step); // Rød
        Design04RB2(int R, int G, int B, int start, int step); // Oransje
        Design04RB2(int R, int G, int B, int start, int step); // Gul
        Design04RB2(int R, int G, int B, int start, int step); // Grønn
        Design04RB2(int R, int G, int B, int start, int step); // Blå
        Design04RB2(int R, int G, int B, int start, int step); // Lilla
    */

    delay(PAUSE_TIME1 * 3); // ca 1200 ms pause (test)
    statetester();
    Design03RB10(); // Denne  Lager de 4 fargene med 15 og 15 LED.
    statetester();
    delay(PAUSE_TIME1 * 4);

    /* Koden med Design05 trenger muligens litt mer arbeid før den virker.
      se på Serial Print for litt mer informasjon, hva den gjør.
        delay(PAUSE_TIME1);
        Design05(127,   0, 255, 155, 127,   0); // Rosa, Gul
        delay(PAUSE_TIME1);
        Design05(250,   0,   0,   0, 250,   0); // Rød, Grønn
        delay(PAUSE_TIME1);
        Design05(238, 130, 238, 255, 165, 0); //
        delay(PAUSE_TIME1);
        Design05(0,  70,  20, 0, 0, 255); //
        delay(PAUSE_TIME1);
        Design05(255, 0, 0, 255, 255, 0); //
        delay(PAUSE_TIME1);
        Design05(0,  70,  20, 238, 130, 238); // Rød til Rosa? // CRGB(0,  70,  20); CRGB(238, 130, 238);


    */
  }

  if ( (20000 < timer) && (timer < 40000) ) {
    statetester();
    // Design02 er en av funksjonen som kan legges til knappen. Og noen pauser bør justeres for ønsket effekt.
    // Design05 kan også benyttes, men denne krever nok litt mer arbeid, for å vise noe som er bedre pr nå
    // Det bør lages en "wrapper-funksjon" for fyrverkeri-knappen slik at ikke all logikk er i loop.

    Serial.print("2/4");
    Serial.print(" \t\t\t" + String(timer * 1e-3) + " sek \n" ); // Serial.print("\n == Design02 1== ");
    statetester(); Design02( 80, 110,   0);   // Gul
    Design03RB10(); // Denne  Lager de seks fargene med ti og ti LED.
    delay(PAUSE_TIME1 * 4);
    // statetester(); Design02(180, 85, 0);   // Oransje
    // delay(PAUSE_TIME1 * 1);
    statetester(); Design02(255, 0, 0);   // Rød
    delay(PAUSE_TIME1);    // Serial.print("\n == Design02 2== ");
    statetester(); Design02(0,  70,  20);   // Grønn
    delay(PAUSE_TIME1);    //Serial.print("\n == Design02 3== ");
    statetester(); Design02(0, 0, 255);   // Blå
    delay(PAUSE_TIME1);
    Design03RB10();
  }

  if ( (40000 < timer) && (timer < 55000) ) {
    statetester();

    Serial.print("3/4");
    Serial.print(" \t\t\t" + String(timer * 1e-3) + " sek \n" );
    /*
      Design03( 80, 110,   0); // Gul
      Design03(0, 255, 255); // Cyan
      Design03(255, 0, 255); // Rosa
    */

    Design03(255, 0,   0);  // Rød
    // Design03(180, 85,  0);  // Oransje lys delay(PAUSE_TIME1); Design03(75, 55, 0);  // Oransje mørk    
    Design03(0,  70,  20);  // Grønn
    Design03(80, 110,   0);  // Gul
    Design03(0, 0, 255  );  // Blå    delay(PAUSE_TIME1);  // Design03(238, 130, 238); // Hvit
    // Design03(46, 0, 46  );  // Lilla  delay(PAUSE_TIME1);  // Design03(149, 88, 184);   // Rosa


  }

  if ( (55000 < timer) && (timer < 70000) ) {
    Serial.print("4/4");
    Serial.print(" \t\t\t" + String(timer * 1e-3) + " sek \n" );
    /*  Noen tester med andre farger
        Design04(255, 0, 0);   // Rød        Design04(255, 127, 0); // Gul
        Design04(255, 255, 0); // Gul        Design04(127, 255, 0); // Gul

        Design04(0,  70,  20);   // Grønn        Design04(0, 255, 127); // Cyan
        Design04(0, 255, 255); // Cyan        Design04(0, 127, 255); // Cyan
        Design04(0, 0, 255);   // Blå

        Design04(127, 0, 255); // Rosa        Design04(255, 0, 255); // Rosa
        Design04(255, 0, 127); // Rosa
    */

    Design04(255, 0,   0);  // Rød
    // Design04(180, 85,  0);  // Oransje lys delay(PAUSE_TIME1); Design03(75, 55, 0);  // Oransje mørk
    Design04(0,  70,  20);  // Grønn
        Design04(80, 110,   0);  // Gul
    Design04(0, 0, 255  );  // Blå    delay(PAUSE_TIME1);  // Design03(238, 130, 238); // Hvit
    // Design04(46, 0, 46  );  // Lilla  delay(PAUSE_TIME1);  // Design03(149, 88, 184);   // Rosa

    // Design03RB10();

  }

  if (75000 < timer && (timer < 99000) ) {
    Serial.print("5/4");
    Serial.print(" \t\t\t" + String(timer * 1e-3) + " sek \n" );

    CRGB(127, 0, 0); CRGB(0, 127, 0);
    //Design 05(127,   0, 255, 255, 127,   0); // Rosa, Gul
    //Design 05(250,   0,   0,   0, 250,   0); // Rød, Grønn

    CRGB(255, 0, 0);    // Rød
    CRGB(180, 85, 0);   // Oransje lys  Design01(75, 55, 0);  // Oransje mørk
    CRGB(80, 110,   0);  // Gul
    CRGB(0,  70,  20);    // Grønn
    CRGB(0, 0, 255);    // Blå
    CRGB(46, 0, 46);    // Lilla

    Design03RB10();
    delay(PAUSE_TIME1 * 4);
    Design02(255, 0, 0);   // Rød
    delay(PAUSE_TIME1 * 4);
    Design03RB10();
    Design02(80, 110,   0);   // Gul
    delay(PAUSE_TIME1 * 4);
    Design02(0, 0, 255);   // Blå
    delay(PAUSE_TIME1 * 4);
    Design03RB10();
    delay(PAUSE_TIME1 * 8);

    Serial.print(" S \t\t\t" + String(timer * 1e-3) + " sek \n" );
    if ( timer2 > 1.02e5) timer2 = timer;
    // Uten denne endringen kan timer2 brukes til å telle videre etter syklus er resatt, som kan være interessant.
    Serial.print(" E \t\t\t" + String(timer * 1e-3) + " sek \n" );
  }


} // end loop



void statetester ()  {
  // This function is added all over the program to let the program react to any button press
  // with as little delay as possible. After this the program continues the current section, and then restarts
  // state is set as low all othere places than in the changestate ISR function
  // timer2 = millis() % 1e5;
  timer2 = millis() % 100000;

  if (state == HIGH) {
    FWRounds++;
    // Check if button has been pressed giving an interrrupt
    // Initiates the "fireworks"
    state = LOW;
    Serial.print("\nLoop \"fireworks\" ");
    Serial.print("nr:\t"); Serial.print(FWRounds); Serial.print("\t");
    mai17();
    state = LOW;
    // firework(4);

  }

}


void Design01(int R, int G, int B) { // Normal
  statetester();
  Serial.print(" == Design01 == "); // En og en farge
  Serial.print("RGB: " + String(R) +   ", " + String (G)  +   ", " + String (B) +   " \t== " + String (timer2 * 1e-3) + " sek\n");
  for (int k = 0; k < strips; k++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[k][i] = CRGB(R, G, B);// FastLED.show();
    }// FastLED.show();
  }
  FastLED.show();
}

void Design02(int R, int G, int B) { // Dissolve
  statetester();
  Serial.print(" == Design02 == "); // Oppløsing av det som ble vist før. Muligens bruke andre farger i loop.
  Serial.print("RGB: " + String(R) +   ", " + String (G)  +   ", " + String (B) +   " \t== " + String (timer2 * 1e-3) + " sek\n");
  for (int y = 20; y > 0; y--) {
    for (int a = 30; a > 0; a--) {
      leds[random(0, strips)][random(0, NUM_LEDS)] = CRGB(R, G, B);
    }
    FastLED.show();
    delay(PAUSE_TIME3); // 20 ms
  }
}

void Design03(int R, int G, int B) { // Swipe CCW (slow)
  statetester();
  Serial.print(" == Design03 == "); // Vifte. Retning med klokken. Evt legge inn lengre pauser
  Serial.print("RGB: " + String(R) +   ", " + String (G)  +   ", " + String (B) +   " \t== " + String (timer2 * 1e-3) + " sek\n");

  for (int k = strips - 1; k > -1; k--) {
    for (int i = 0; i < NUM_LEDS; i += 1) {
      leds[k][i] = CRGB(R, G, B);
      // FastLED.show();
      // delay(PAUSE_TIME4 / 4); // 10 ms
    } FastLED.show();
  }
  // delay(PAUSE_TIME4 / 4); // 10 ms
}

void Design03RB10() {
  statetester();

  Serial.print(" == Design03RB10 == Rainbow colours \t== " + String (timer2 * 1e-3) + " sek\n"); // En og en farge utover
  // Serial.print("" + String(R2) +   ", " + String (G2)  +   ", " + String (B2) +   " == \n");

  CRGB(255, 0, 0);    // Rød
  CRGB(180, 85, 0);   // Oransje lys  Design01(75, 55, 0);  // Oransje mørk
  CRGB(80, 110,   0);  // Gul
  CRGB(0,  70,  20);    // Grønn
  CRGB(0, 0, 255);    // Blå
  CRGB(46, 0, 46);    // Lilla

  int startLed = 0;
  int endLed = 60 / 4;
  int step = 15; // (60 LED / 6 farger)
  int factor = 1;

  // Kan lage tre for-løkker men da må fargene legges inn i en tabell som en lager CRGB-verdier av.
  // Lettere og kanskje enklere å forstå når en har sek for-løkker etterhverandre. Kost nytte.

  for (int i = startLed; i < endLed; i++) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CRGB(255, 0, 0);    // Rød
    }
    FastLED.show();
    //delay(delayShort);
  }
  /*
    startLed += step;
    endLed += step; // Alternativ endLed = startLed + step;

    for (int i = startLed; i < endLed; i++) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CRGB(180, 85, 0);  // Oransje lys  Design01(75, 55, 0);  // Oransje mørk
    }
    FastLED.show();
    //delay(delayShort);
    }
  */
    startLed += step;
  endLed += step; // Alternativ endLed = startLed + step;

  for (int i = startLed; i < endLed; i++) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CRGB(0,  70,  20);    //Grønn
    }
    FastLED.show();
    //delay(delayShort);
  }

  startLed += step;
  endLed += step; // Alternativ endLed = startLed + step;

  for (int i = startLed; i < endLed; i++) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CRGB(80, 110,   0);  // Gul
    }
    FastLED.show();
    //delay(delayShort);
  }
  startLed += step;
  endLed += step; // Alternativ endLed = startLed + step;

  for (int i = startLed; i < endLed; i++) {
    for (int k = 0; k < 16; k++) {
      leds[k][i] = CRGB(0, 0, 255);    // Blå
    }
    FastLED.show();
    //delay(delayShort);
  }
  startLed += step;
  endLed += step; // Alternativ endLed = startLed + step;

  /*
    for (int i = startLed; i < endLed; i++) {
      for (int k = 0; k < 16; k++) {
        leds[k][i] = CRGB(46, 0, 46);   // Lilla
      }
      FastLED.show();
      //delay(delayShort);
    }
  */

  if (state == true) {
    return;
  }

}

void Design04(int R, int G, int B) { // Swipe fast
  statetester();
  Serial.print(" == Design04 == "); // Vifte. Retning med klokken. Ingen pause
  Serial.print("RGB: " + String(R) +   ", " + String (G)  +   ", " + String (B) +   " \t== " + String (timer2 * 1e-3) + " sek\n");
  for (int k = 0; k < strips; k++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[k][i] = CRGB(R, G, B);
      // FastLED.show();
    } FastLED.show();
  }
  // delay(PAUSE_TIME4*5);
}

void Design04RB1(int R, int G, int B, int start, int step) { // Spiler
  statetester();
  // NB, ikke helt som tenkt, men artig møsnter så beholder denne
  Serial.print(" == Design04RB1 == ");
  Serial.print("RGB: " + String(R) +   ", " + String (G)  +   ", " + String (B) +   " \t== " + String (timer2 * 1e-3) + " sek\n");

  for (int i = 0; i < NUM_LEDS; i++) {
    statetester();
    for (int k = start; k < strips; k += step) {

      leds[k][i] = CRGB(R, G, B);
      // FastLED.show();
    } FastLED.show();
  } // FastLED.show();
  delay(PAUSE_TIME4 * 1);

}

void Design04RB2(int R, int G, int B, int start, int step) { // Swipe fast
  statetester();
  // NB, ikke helt som tenkt, men artig møsnter så beholder denne
  // Og enda en variant
  Serial.print(" == Design04RB2 == ");
  Serial.print("RGB: " + String(R) +   ", " + String (G)  +   ", " + String (B) +   " \t== " + String (timer2 * 1e-3) + " sek\n");

  for (int k = start; k < strips; k += step) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[k][i] = CRGB(R, G, B);
      // FastLED.show();
    } FastLED.show();
  }
  // delay(PAUSE_TIME4*5);
}

void Design04RB3(int R, int G, int B, int start, int step) { // LED spread
  Serial.print(" == Design04RB3 == "); // Hver sjette LED lyses opp
  Serial.print("RGB: " + String(R) +   ", " + String (G)  +   ", " + String (B) +   " \t== " + String (timer2 * 1e-3) + " sek\n");

  for (int i = start; i < NUM_LEDS; i += step) {
    statetester();
    for (int k = 0; k < strips; k++ ) {
      statetester();
      leds[k][i] = CRGB(R, G, B);
      // FastLED.show();
    } FastLED.show();
  }
  // delay(PAUSE_TIME4*5);
}

void Design05wrapper() {
  statetester();
  // NB dette er slik det ser ut med LED, ikke RGB-fargene som er tastet inn
  //delay(PAUSE_TIME1);
  // Design05(127,   0, 255, 155, 127,   0); // Rosa, Gul (lilla variasjon til turkis)
  //delay(PAUSE_TIME1);
  Design05(250,   0,   0,   0, 250,   0); // Rød, Grønn (rød variasjon til oransje, gul grønn)
  //delay(PAUSE_TIME1);
  Design05(238, 130, 238, 255, 165, 0); // (lilla variasjon til violet)
  //delay(PAUSE_TIME1);
  // Design05(0,  70,  20, 0, 0, 255); // (lilla variasjon til turkis)
  //delay(PAUSE_TIME1);
  Design05(255, 0, 0, 255, 255, 0); // (brun variasjon til grønn)
  //delay(PAUSE_TIME1);
  Design05(0,  70,  20, 238, 130, 238); // (rød, rosa til blå )
  // Rød til Rosa // CRGB(0,  70,  20); CRGB(238, 130, 238);

}

String  fTPrint(int tallet, int decimals = 0) {
  // Denne legger til 00 eller "  " før hvert tall om det er mindre enn 10 eller 100
  String pad = "";

  if (tallet < 100)  pad = "  ";
  if (tallet <  10)  pad = "  ";

  String printedText = (pad + String(tallet, decimals) );
  //Serial.print(tallet);
  //Serial.print(printedText);
  return pad;


}

void Design05(int R, int G, int B, int R2, int G2, int B2) { // Fade half
  statetester();
  Serial.print(" == Design05 == Trenger nok litt mer arbeid for å være effektfull " + String (timer2 * 1e-3) + " sek\n");

  //Denne funskjonen er fin til å finne RGB-verdier som gir ønskede farger, og så har den en litt interessant effekt

  float R_Increment = abs(R - R2) / 10;
  float G_Increment = abs(G - G2) / 10;
  float B_Increment = abs(B - B2) / 10;

  Serial.print("RGB fra:     " + String(R) +  "  \t" + String (G)  +   "  \t" + String (B) +   " \t== " + String (timer2 * 1e-3) + " sek\n");
  Serial.print("RGB til:     " + String(R2) + "  \t" + String (G2)  +  "  \t" + String (B2) +   " \t== " + String (timer2 * 1e-3) + " sek\n");
  Serial.print("Differanse:  " + String(R_Increment, 0) +   "  \t" + String (G_Increment, 0)  +   "  \t" + String (B_Increment, 0) +   " \t== " + String (timer2 * 1e-3) + " sek\n");


  /* Serial.print("\n\n"); // Test med pad om tallene er mindre enn 10 og 100. Ikke i mål enda
    Serial.print("RGB fra:     " + fTPrint(R) +  "  \t" + fTPrint (G)  +   "  \t" + fTPrint (B) +   " \t==  \n");
    Serial.print("RGB til:     " + fTPrint(R2) + "  \t" + fTPrint (G2)  +  "  \t" + fTPrint (B2) +   " \t== " + String (timer2*1e-3) + " sek\n");
    Serial.print("Differanse:  " + fTPrint(R_Increment,0) +   "  \t" + fTPrint (G_Increment,0)  +   "  \t" + fTPrint (B_Increment,0) +   " \t== " + String (timer2*1e-3) + " sek\n");
  */
  // Kan starte på RGB-verdier som er 0, men det gir svart farge i starten.
  float currentR = 0;
  float currentG = 0;
  float currentB = 0;

  // Eksperimenter med disse verdiene slik at ønsket effet blir oppnådd.
  // Her kan det være vanskelig å "styre" R, G og B siden LED fargene ikke er helt like
  // med tanke på spenninger og gammaverdier
  currentR = 40;
  currentG = 0;
  currentB = 0;


  // NB eksperimenter litt med start og stoppverdier i for-løkkene for ulike effekter.
  // En kan også endre litt på step-verdier (inkrementeringsverdier)
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
    delay(PAUSE_TIME2 * 4); // 50 ms
    Serial.print("RGB: " + String(currentR) +   ", " + String (currentG)  +   ", " + String (currentB) +   " ==  \n");
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

  delay(1000);
  Design6(160, 255, 170, 0, 255, 170, 0, 0, 220); Serial.print("\tD6 1 B H R | B R H");
  //Design6(0, 255, 170, 0, 0, 220, 160, 255, 170); Serial.print("\tD6 2 R B H | R H B");
  Design6(0, 0, 220, 160, 255, 170, 0, 255, 220); Serial.print("\tD6 3 H R B | H B R");

  //Design6(0, 0, 220, 0, 255, 170, 160, 255, 170);Serial.println("\nD6 a H B R | H R B"); // B H R
  //Design6(160, 255, 170, 0, 0, 220, 0, 255, 170);Serial.println("\nD6 b B R H | B H R"); // R B H
  Design6(0, 255, 170, 160, 255, 170, 0, 0, 220); Serial.println("\nD6 c R H B | R B H"); // H R B

  //wrapperResetFlag();

  FastLED.show();
  delay(3000);
  // dissolve();
  Serial.print("\nFyrverkeri er over\n");
  // FastLED.clear();
  state = LOW;

}

// Mye gammel kode fra tidligere versjoner av stjerne. kanskje noe inspirasjon kan hentes herfra.

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
    leds[launch_strip][stage]      = CHSV(10,  0, 100);
    leds[launch_strip][laststage]  = CHSV(10, 20, 100);
    leds[launch_strip][laststage2] = CHSV(10, 10, 100);
    leds[launch_strip][laststage3] = CHSV(10,  0, 100);
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
        leds[currentstrip][stage].red   = palettefireworks[stage / (firework_range / 4)][0] + random(-10, 10);
        leds[currentstrip][stage].green = palettefireworks[stage / (firework_range / 4)][1] + random(-10, 10);
        leds[currentstrip][stage].blue  = palettefireworks[stage / (firework_range / 4)][2] + random(-10, 10);
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
    delay(PAUSE_TIME4);
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
    delay(PAUSE_TIME4);
  }
}


// Ved knappetrykk så legge inn state-testing flere steder så evt kode kan avbrytes.
// Noen av kjøringene tar litt lang tid å kjøre før evt interrrupt blir benyttet.


///// OLD
/* old files


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



//////// FARGER
/* Mengder av farger som kan benyttes. NB alle virker ikke som de skal med LED-striper.
  Tidvis blir fargen hvit, og oransje er vanskelig å skape, det samme kan lilla være.
*/
void farger() {

  // Regnbuefarger, som er benytttet flere steder. Det virker som OK valg med LED/stripene
  // NB ikke testet på ordinær Mega eller ESP32
  // Ignorer hvordan fargen vises i kode, og sjekk om ønsket resultat er på LED-striper.

  CRGB(255, 0,   0);  // Rød
  CRGB(180, 85,  0);  // Oransje lys CRGB(75, 55, 0);  // Oransje mørk
  CRGB(255, 255, 0);  // Gul
  CRGB(0,  70,  20);  // Grønn
  CRGB(0, 0, 255  );  // Blå      // CRGB(238, 130, 238); // Hvit
  CRGB(46, 0, 46  );  // Lilla    // CRGB(149, 88, 184);   // Rosa


  // CRGB(75,0,130);
  // CRGB(233, 18, 18);  CRGB(235, 113, 21); B
  // CRGB(229, 233, 15); CRGB(26, 225, 26); G
  // CRGB(18, 18, 228)B; // CRGB::Brown

  // CRGB::Red CRGB::Orange CRGB::Yellow
  // CRGB::Green CRGB::Blue CRGB::Violet

  // CRGB(127, 0, 0);   CRGB(0, 127, 0);
  // CRGB(127, 0, 255); CRGB(255, 127, 0);
  // CRGB(250, 0, 0);   CRGB(0, 250, 0);


  // CRGB(255,0,0);
  // CRGB(255,165,0);
  // CRGB(255,255,0);
  // CRGB(0,128,0);
  // CRGB(0, 0, 255);
  // CRGB(238, 130, 238);  // CRGB(149, 88, 184)

  // CRGB(0, 127, 0); CRGB(26, 225, 26); G

  // CRGB(0, 0, 127); CRGB(0, 0, 127); B
  // CRGB(0, 127, 0); CRGB(0, 127, 0); G
  // CRGB(127, 0, 0); CRGB(127, 0, 0); R
  // CRGB(195, 78, 218); CRGB(255, 100, 100)
  // CRGB(0, 0, 255);
  // CRGB(0, 0, 255);   // Blå
  // CRGB(0, 127, 255); // Cyan
  // CRGB(0,  70,  20);
  // CRGB(0,  70,  20);   // Grønn
  // CRGB(0, 255, 127); // Cyan
  // CRGB(0, 255, 255); // Cyan
  // CRGB(0, 255, 255); // Cyan
  // CRGB(100, 100, 155);
  // CRGB(100, 155, 100);
  // CRGB(124, 10, 2);
  // CRGB(127, 0, 0); CRGB(0, 127, 0);
  // CRGB(127, 0, 255); // Rosa
  // CRGB(127, 255, 0); // Gul
  // CRGB(155, 100, 100); CRGB(155, 100, 100);
  // CRGB(169, 165, 213);
  // CRGB(169, 165, 213);
  // CRGB(178, 34, 34);
  // CRGB(201, 153, 32);
  // CRGB(201, 153, 32);
  // CRGB(215, 42, 123);
  // CRGB(215, 42, 123);
  // CRGB(216, 46, 197);
  // CRGB(216, 46, 197);
  // CRGB(218, 20, 20);
  // CRGB(218, 20, 20);
  // CRGB(226, 88, 34);
  // CRGB(241, 188, 49);
  // CRGB(246, 240, 82);
  // CRGB(255, 0, 0);
  // CRGB(255, 0, 0);   // Rød
  // CRGB(255, 0, 127); // Rosa
  // CRGB(255, 0, 255); // Rosa
  // CRGB(255, 0, 255); // Rosa
  // CRGB(255, 127, 0); // Gul
  // CRGB(255, 255, 0); // Gul
  // CRGB(255, 255, 0); // Gul
  // CRGB(29, 128, 189);
  // CRGB(29, 128, 189);
  // CRGB(57, 203, 28);
  // CRGB(57, 203, 28);
  // CRGB(79, 203, 211);
  // CRGB(79, 203, 211);

  // Design05(127,   0, 255, 255, 127,   0); // Rosa, Gul
  // Design05(250,   0,   0,   0, 250,   0); // Rød, Grønn
  // Design2(0, 0, 220);
  // Design2(0, 255, 170);
  // Design2(160, 255, 170);
  // Design3(0, 255, 170, 160, 255, 170, 0, 0, 220);
  // Design5(0, 0, 220, 0, 255, 170, 160, 255, 170);
  // Design5(0, 255, 170, 160, 255, 170, 0, 0, 220);
  // Design5(160, 255, 170, 0, 0, 220, 0, 255, 170);
  // Flagg(0, 255, 155, 160, 255, 170, 0, 0, 220);
  // Flagg(0, 255, 170, 160, 255, 170, 0, 0, 220);


}

```
