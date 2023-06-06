/*
  Candle example
  Runs only on SAMD boards (Nano 33 IoT, MKR series)
  uses Adafruit's NeoPixel library and the ColorHSV function therein
  Also uses Scheduler library, which runs only on SAMD boards.

  created  6 Jun 2020
  modified 6 Feb 2023
  by Tom Igoe
*/
/*Mod of candle  by S muller*/

#include <Adafruit_NeoPixel.h>
#include <Scheduler.h>

const int neoPixelPin = 5;   // control pin
const int pixelCount = 8;    // number of pixels

// set up strip:
Adafruit_NeoPixel candle = Adafruit_NeoPixel(pixelCount, neoPixelPin, NEO_GRBW + NEO_KHZ800);

int hues[pixelCount];
int saturations[pixelCount];
int intensities[pixelCount];
int changeValues[] = {1, 1, 1, 1, 1, 1, 1, 1};

int highPixels[] = {6, 3, 7};
int lowPixels[] = {1, 4};
int bluePixel = 0;
int yellowPixel = 7;

int lightPixels[] = {2, 5};


void setup() {
  Serial.begin(9600);

  candle.begin();    // initialize pixel strip
  candle.clear();    // turn all LEDs off
  candle.show();     // update strip

  // set all initial hues, sats, intensities, and colorConverters
  for (int p = 0; p < 2; p++) {
    int thisPixel = highPixels[p];
    hues[thisPixel] = random(1200) + 5000;
    saturations[thisPixel] = random(10) + 240;
    intensities[thisPixel] = random(20) + 100;
  }

  for (int p = 0; p < 2; p++) {
    int thisPixel = lowPixels[p];
    hues[thisPixel] = random(300) + 30000;
    saturations[thisPixel] = 205;
    intensities[thisPixel] = random(20) + 80;
  }

  for (int p = 0; p < 2; p++) {
    int thisPixel = lightPixels[p];
    hues[thisPixel] = random(200) + 3500;
    saturations[thisPixel] = random(20) + 200;
    intensities[thisPixel] = random(40) + 90;
  }


  hues[bluePixel] = random(200) + 10000;
  saturations[bluePixel] = random(10) + 230;
  intensities[bluePixel] = random(20) + 30;


  hues[yellowPixel] = random(100) + 10000;
  saturations[yellowPixel] = random(10) + 130;
  intensities[yellowPixel] = random(20) + 80;
  // set up some loops for timing:
  Scheduler.startLoop(fastLoop);
  Scheduler.startLoop(medLoop);
  Scheduler.startLoop(slowLoop);
  Scheduler.startLoop(lentoLoop);
}

void loop() {
  for (int p = 0; p < 2; p++) {
    int thisPixel = highPixels[p];

    // change the hue:
    hues[thisPixel] = hues[thisPixel] + changeValues[thisPixel];
    // keep the change within the min/max range,
    // but change directions at the extremes:
    if (hues[thisPixel] < 8 || hues[thisPixel] > 18) {
      changeValues[thisPixel] = -changeValues[thisPixel];
    }
    long thisColor = candle.ColorHSV(hues[thisPixel],
                                     saturations[thisPixel],
                                     intensities[thisPixel]);
    candle.setPixelColor(thisPixel, thisColor);
  }
  candle.show();
  delay(30);
  yield();
}


void fastLoop() {
  for (int p = 0; p < 2; p++) {
    int thisPixel = lowPixels[p];
    // change the hue:
    hues[thisPixel] = hues[thisPixel] + changeValues[thisPixel];
  intensities[thisPixel] += (random(3) - 1);
  intensities[thisPixel] = constrain(intensities[thisPixel], 0, 20);       
    
    // keep the change within the min/max range,
    // but add a random -1 to 2:
    hues[thisPixel] += (random(3) - 1);
    hues[thisPixel] = constrain(hues[thisPixel], 4, 16);

    long thisColor = candle.ColorHSV(hues[thisPixel],
                                     saturations[thisPixel],
                                     intensities[thisPixel]);
    candle.setPixelColor(thisPixel, thisColor);
  }
  candle.show();
  delay(30);
}


void medLoop() {
  for (int p = 0; p < 2; p++) {
    int thisPixel = lightPixels[p];

    // change the hue:
    hues[thisPixel] = hues[thisPixel] + changeValues[thisPixel];
    // keep the change within the min/max range,
  // change the intensity and constrain it:
  intensities[thisPixel] += (random(3) - 1);
  intensities[thisPixel] = constrain(intensities[thisPixel], 0, 10);   
  // but change directions at the extremes:
    if (hues[thisPixel] < 10 || hues[thisPixel] > 20) {
      changeValues[thisPixel] = -changeValues[thisPixel];
    }
    long thisColor = candle.ColorHSV(hues[thisPixel],
                                     saturations[thisPixel],
                                     intensities[thisPixel]);
    candle.setPixelColor(thisPixel, thisColor);
  }
  candle.show();
  delay(60);
  yield();
}

void slowLoop() {
  // change the hue:
  hues[bluePixel] = hues[bluePixel] + changeValues[bluePixel];
  // change the intensity and constrain it:
  intensities[bluePixel] += (random(3) - 1);
  intensities[bluePixel] = constrain(intensities[bluePixel], 0, 20);

  // keep the change within the min/max range,
  // but change directions at the extremes:
  if (hues[bluePixel] < 200 || hues[bluePixel] > 280) {
    changeValues[bluePixel] = -changeValues[bluePixel];
  }
  long thisColor = candle.ColorHSV(hues[bluePixel],
                                   saturations[bluePixel],
                                   intensities[bluePixel]);
  candle.setPixelColor(bluePixel, thisColor);
  candle.show();
  delay(20);
  yield();
}

void lentoLoop() {
  // change the hue:
  hues[yellowPixel] = hues[yellowPixel] + changeValues[yellowPixel];
  // change the intensity and constrain it:
  intensities[yellowPixel] += (random(3) - 1);
  intensities[yellowPixel] = constrain(intensities[yellowPixel], 0, 20);

  // keep the change within the min/max range,
  // but change directions at the extremes:
  if (hues[yellowPixel] < 200 || hues[yellowPixel] > 280) {
    changeValues[yellowPixel] = -changeValues[yellowPixel];
  }
  long thisColor = candle.ColorHSV(hues[yellowPixel],
                                   saturations[yellowPixel],
                                   intensities[yellowPixel]);
  candle.setPixelColor(yellowPixel, thisColor);
  candle.show();
  delay(50);
  yield();
}