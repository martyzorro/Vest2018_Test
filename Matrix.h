#pragma once

//
// Matrix.h
//
// Lookup table and coresponding XY() function for the vest.
// Technique cribbed from https://github.com/macetech/RGBShades/blob/master/XYmap.h
//

const uint8_t kMatrixWidth = 18;
const uint8_t kMatrixHeight = 13;
const uint16_t kNumLeds = kMatrixWidth * kMatrixHeight;

extern const uint16_t matrix[kNumLeds];

extern uint16_t XY(uint8_t x, uint8_t y);
