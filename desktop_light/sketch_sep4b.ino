#define BLYNK_TEMPLATE_ID "TMPLVvilcO5O"
#define BLYNK_TEMPLATE_NAME "Desktop ligh"
#define BLYNK_AUTH_TOKEN "QhaFG16Dt9ms1MBQeb4WSU7E-jMA5lb-"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <FastLED.h>

char auth[] = "QhaFG16Dt9ms1MBQeb4WSU7E-jMA5lb-";
char ssid[] = "Anon Progers";  //Enter your WIFI Name
char pass[] = "an0n_pr0gers";  //Enter your WIFI Password

#define NUM_LEDS 30  // number of leds
#define PIN 4 //pin of led
CRGB leds[NUM_LEDS];
 
/******developer options******/
byte counter; //effect 2
short button;
short color;
short mod;
short brightness;
short speed;
short lenghtEffect;

//tool
bool flag=0;
unsigned long last_time;
int old_Brightness=0;
int old_color=250;

//obtaining data from blynk app
BLYNK_WRITE(V0) { lenghtEffect = param.asInt(); }
BLYNK_WRITE(V1) { brightness = param.asInt(); }
BLYNK_WRITE(V2) { button = param.asInt(); }
BLYNK_WRITE(V3) { color = param.asInt(); }
BLYNK_WRITE(V4) { mod = param.asInt(); }
BLYNK_WRITE(V5) { speed = param.asInt(); }
  
void setup() {
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  Blynk.begin(auth, ssid, pass);

  button=0;
  color=255;
  old_Brightness=0;
  brightness=200;
  mod=0;
  lenghtEffect=4;
  speed=45;
}
void loop() {
//smooth turn off
    if(button==0 && flag==0){
      for (int i = 0; i < NUM_LEDS; i++ ) {         
        leds[i] = CHSV(color, 255, 255); 
      }
      for(int i=brightness; i>=0; i-=2){ 
        if(i<2)i=0;
        FastLED.setBrightness(i);
        FastLED.show();
      }
      flag=1;
      old_Brightness=0;
    }
    if(button==1){
      if(old_Brightness!=brightness){
        if(old_Brightness<brightness){
          for(int i=old_Brightness; i<=brightness; i+=2){
            FastLED.setBrightness(i);
            FastLED.show();
          }
        }else{
          for(int i=old_Brightness; i>=brightness; i-=2){
            FastLED.setBrightness(i);
            FastLED.show();
          }
        }
        old_Brightness=brightness;
      }
      if(mod==0){
          if(old_color!=color){
            if(old_color<color){
              for(int c=old_color; c<=color; c+=1){
                for (int i = 0; i < NUM_LEDS; i++ ) {         
                  leds[i] = CHSV(c, 255, 255); 
                }
                FastLED.show();
              }
            }else{
              for(int c=old_color; c>=color; c-=1){
                for (int i = 0; i < NUM_LEDS; i++ ){         
                  leds[i] = CHSV(c, 255, 255); 
                }
                FastLED.show();
              } 
            }
            old_color=color;
          }
      }
      if(mod==1){
        if(millis()-last_time>speed){
          for (int i = 0; i < NUM_LEDS; i++ ) {         
            leds[i] = CHSV(counter + i * lenghtEffect, 255, 255);  
          }
          counter++;        
          FastLED.show();
          last_time=millis();
        } 
      }
      flag=0;
    }
    Blynk.run();
}
