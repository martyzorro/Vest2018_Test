
#pragma once

#include <FastLED.h>
#include "Matrix.h"
#include "Effect.h"

#define COOLING 100
#define SPARKING 20

class Fire : public Effect {
  
  private:
   uint8_t column;
    CRGBPalette16 palette;
    uint8_t heats[kMatrixWidth][kMatrixHeight];


	public:
      Fire(CRGB *leds) : Effect(leds),
        column(column),
        palette(HeatColors_p)   
        {}
   
   virtual void draw(Controls controls){
        
        for (int columnIdx = 0; columnIdx < kMatrixWidth; columnIdx++) {
        
            random16_add_entropy(random());
            
            // Step 1.  Cool down every cell a little  
            for (int i = 0; i < kMatrixHeight; i++) {
                heats[columnIdx][i] = qsub8(heats[columnIdx][i], random8(0, ((COOLING * 15) / kMatrixHeight) + 2));
            }
        
            // Step 2.  Heat from each cell drifts 'up' and diffuses a little
            for (int k = kMatrixHeight - 1; k > 1; k--) {
                heats[columnIdx][k] = (heats[columnIdx][k - 1] + heats[columnIdx][k - 2] + heats[columnIdx][k - 2] ) / 3;
            }
            
            // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
//            if (controls.volume > controls.SpeedPot && controls.volume - controls.SpeedPot > random8()) 
            {
                int y = random8(5);
                heats[columnIdx][y] = qadd8(heats[columnIdx][y], random8(160, 255));
            }
            
            // Step 4.  Map from heat cells to LED colors
            for (int j = 0; j < kMatrixHeight; j++) {
                // Scale the heat value from 0-255 down to 0-240
                // for best results with color palettes.
                byte colorindex = scale8(heats[columnIdx][j], 140);
                leds[XY(columnIdx, j)] = ColorFromPalette(palette, colorindex);
            }
        }
     }

};
