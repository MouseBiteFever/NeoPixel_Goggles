    // Low power NeoPixel goggles example. Makes a nice blinky display
    // with just a few LEDs on at any time...uses MUCH less juice than
    // rainbow display!
     
    #include <Adafruit_NeoPixel.h>
     
    #define PIN A3
    int swi = A2;
    int bright = 0;
    int neobright = 0;
    
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);
     
    uint8_t mode = 0, // Current animation effect
    offset = 0; // Position of spinny eyes
    uint32_t color = 0xFF0000; // Start red
    uint32_t prevTime;
     
    void setup() {
    pixels.begin();
    pixels.setBrightness(255); // 1/3 brightness 85
    prevTime = millis();
    }
     
    void loop() {
    uint8_t i;
    uint32_t t;
     
    switch(mode) {
     
//    case 0: // Random sparks - just one LED on at a time!
//    i = random(32);
//    pixels.setPixelColor(i, color);
//    pixels.show();
//    delay(10);
//    pixels.setPixelColor(i, 0);
//    break;
    case 1: // Spinny wheels (8 LEDs on at a time)
    pixels.setPixelColor(i, color);
    for(i=0; i<16; i++) {
    uint32_t c = 0;
    if(((offset + i) & 7) < 2) c = color; // 4 pixels on...
    pixels.setPixelColor( i, c); // First eye
    pixels.setPixelColor(31-i, c); // Second eye (flipped)
    }
    pixels.show();
    offset++;
    delay(50);
    break;
    }
     
    t = millis();
    //if((t - prevTime) > 8000) { // Every 8 seconds...
    if(digitalRead(swi) == HIGH) { // Read switch
    mode = 1; // Next mode
    if(mode = 1) { // End of modes?
    mode = 1; // Start modes over
    color >>= 8; // Next color R->G->B
    delay(200); //trying to add time as a debounce -works great, times lets you hold to select color
    //remember to add pull down resistor on switch
    if(!color) color = 0xFF0000; // Reset to red
    }
    for(i=0; i<32; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
    }
    if(digitalRead(bright) == HIGH) { // Read bright switch
      if(neobright >= 255) {
        neobright = 85;
      }
      else {
        neobright = neobright + 85;
      }
    pixels.setBrightness(neobright); // 1/3 brightness 85
    delay(200);
    }
    }
