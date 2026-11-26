#pragma once
#include "esphome.h"
#include <cstring>
#include <cmath>
#include <cstdio>
#include <string>

namespace pixoo_gfx {

using esphome::Color;

// Colors
const Color C_WHITE_BRIGHT(255, 255, 255);
const Color C_WHITE_MID(200, 205, 215);
const Color C_GRAY_SUBDUED(125, 130, 142);
const Color C_CLOCK_RED(255, 30, 30);
const Color C_TEMP_MIN(40, 140, 255);
const Color C_TEMP_MAX(255, 150, 30);
const Color C_RAIN_BLUE(80, 210, 255);
const Color C_WARMER_CORAL(255, 85, 50);
const Color C_COLDER_BLUE(60, 160, 255);

// 9x15 Rounded Sans Clock Digits (2px uniform stroke, rounded corners)
static const uint16_t DIGITS_9X15[10][15] = {
  {0b001111100,0b011111110,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b011111110,0b001111100},
  {0b000011000,0b000111000,0b001111000,0b011011000,0b000011000,0b000011000,0b000011000,0b000011000,0b000011000,0b000011000,0b000011000,0b000011000,0b000011000,0b001111110,0b001111110},
  {0b001111100,0b011111110,0b110000011,0b000000011,0b000000011,0b000000110,0b000001100,0b000011000,0b000110000,0b001100000,0b011000000,0b110000000,0b110000000,0b111111111,0b111111111},
  {0b001111100,0b011111110,0b110000011,0b000000011,0b000000011,0b000000011,0b001111110,0b001111110,0b000000011,0b000000011,0b000000011,0b000000011,0b110000011,0b011111110,0b001111100},
  {0b000001100,0b000011100,0b000111100,0b001101100,0b011001100,0b110001100,0b110001100,0b111111111,0b111111111,0b000001100,0b000001100,0b000001100,0b000001100,0b000001100,0b000001100},
  {0b111111111,0b111111111,0b110000000,0b110000000,0b110000000,0b111111100,0b000000110,0b000000011,0b000000011,0b000000011,0b000000011,0b000000011,0b110000011,0b011111110,0b001111100},
  {0b001111100,0b011111110,0b110000000,0b110000000,0b110000000,0b110111100,0b111111110,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b011111110,0b001111100},
  {0b111111111,0b111111111,0b000000011,0b000000110,0b000000110,0b000001100,0b000001100,0b000011000,0b000011000,0b000110000,0b000110000,0b001100000,0b001100000,0b001100000,0b001100000},
  {0b001111100,0b011111110,0b110000011,0b110000011,0b110000011,0b011111110,0b001111100,0b011111110,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b011111110,0b001111100},
  {0b001111100,0b011111110,0b110000011,0b110000011,0b110000011,0b110000011,0b110000011,0b011111111,0b001111011,0b000000011,0b000000011,0b000000011,0b000000011,0b011111110,0b001111100}
};

template<typename DisplayT>
void draw_clock_digit(DisplayT &it, int x, int y, int d, Color color) {
  if (d < 0 || d > 9) return;
  for (int r = 0; r < 15; r++) {
    uint16_t row = DIGITS_9X15[d][r];
    for (int c = 0; c < 9; c++) {
      if ((row >> (8 - c)) & 1) {
        it.draw_pixel_at(x + c, y + r, color);
      }
    }
  }
}

template<typename DisplayT>
void draw_hero_clock(DisplayT &it, int x, int y, int h, int m, Color color) {
  draw_clock_digit(it, x, y, h / 10, color);
  draw_clock_digit(it, x + 11, y, h % 10, color);
  draw_clock_digit(it, x + 11 + 9 + 5, y, m / 10, color);
  draw_clock_digit(it, x + 11 + 9 + 5 + 11, y, m % 10, color);
}

// 5x7 Pixel Font Glyph Lookup (Each row is 5 bits in uint8_t)
inline bool get_glyph_5x7(char ch, uint8_t out[7], int &width) {
  width = 5;
  switch (ch) {
    case '0': { uint8_t g[7]={0b01110,0b10001,0b10011,0b10101,0b11001,0b10001,0b01110}; memcpy(out,g,7); return true; }
    case '1': { uint8_t g[7]={0b00100,0b01100,0b00100,0b00100,0b00100,0b00100,0b01110}; memcpy(out,g,7); return true; }
    case '2': { uint8_t g[7]={0b01110,0b10001,0b00001,0b00010,0b00100,0b01000,0b11111}; memcpy(out,g,7); return true; }
    case '3': { uint8_t g[7]={0b01110,0b10001,0b00001,0b00110,0b00001,0b10001,0b01110}; memcpy(out,g,7); return true; }
    case '4': { uint8_t g[7]={0b00010,0b00110,0b01010,0b10010,0b11111,0b00010,0b00010}; memcpy(out,g,7); return true; }
    case '5': { uint8_t g[7]={0b11111,0b10000,0b11110,0b00001,0b00001,0b10001,0b01110}; memcpy(out,g,7); return true; }
    case '6': { uint8_t g[7]={0b01110,0b10000,0b11110,0b10001,0b10001,0b10001,0b01110}; memcpy(out,g,7); return true; }
    case '7': { uint8_t g[7]={0b11111,0b00001,0b00010,0b00100,0b01000,0b01000,0b01000}; memcpy(out,g,7); return true; }
    case '8': { uint8_t g[7]={0b01110,0b10001,0b10001,0b01110,0b10001,0b10001,0b01110}; memcpy(out,g,7); return true; }
    case '9': { uint8_t g[7]={0b01110,0b10001,0b10001,0b01111,0b00001,0b00001,0b01110}; memcpy(out,g,7); return true; }
    case 'A': { uint8_t g[7]={0b01110,0b10001,0b10001,0b11111,0b10001,0b10001,0b10001}; memcpy(out,g,7); return true; }
    case 'B': { uint8_t g[7]={0b11110,0b10001,0b10001,0b11110,0b10001,0b10001,0b11110}; memcpy(out,g,7); return true; }
    case 'C': { uint8_t g[7]={0b01110,0b10001,0b10000,0b10000,0b10000,0b10001,0b01110}; memcpy(out,g,7); return true; }
    case 'D': { uint8_t g[7]={0b11100,0b10010,0b10001,0b10001,0b10001,0b10010,0b11100}; memcpy(out,g,7); return true; }
    case 'E': { uint8_t g[7]={0b11111,0b10000,0b10000,0b11110,0b10000,0b10000,0b11111}; memcpy(out,g,7); return true; }
    case 'F': { uint8_t g[7]={0b11111,0b10000,0b10000,0b11110,0b10000,0b10000,0b10000}; memcpy(out,g,7); return true; }
    case 'G': { uint8_t g[7]={0b01110,0b10001,0b10000,0b10111,0b10001,0b10001,0b01110}; memcpy(out,g,7); return true; }
    case 'H': { uint8_t g[7]={0b10001,0b10001,0b10001,0b11111,0b10001,0b10001,0b10001}; memcpy(out,g,7); return true; }
    case 'I': { uint8_t g[7]={0b01110,0b00100,0b00100,0b00100,0b00100,0b00100,0b01110}; memcpy(out,g,7); return true; }
    case 'L': { uint8_t g[7]={0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,0b11111}; memcpy(out,g,7); return true; }
    case 'M': { uint8_t g[7]={0b10001,0b11011,0b10101,0b10101,0b10001,0b10001,0b10001}; memcpy(out,g,7); return true; }
    case 'N': { uint8_t g[7]={0b10001,0b11001,0b10101,0b10011,0b10001,0b10001,0b10001}; memcpy(out,g,7); return true; }
    case 'O': { uint8_t g[7]={0b01110,0b10001,0b10001,0b10001,0b10001,0b10001,0b01110}; memcpy(out,g,7); return true; }
    case 'P': { uint8_t g[7]={0b11110,0b10001,0b10001,0b11110,0b10000,0b10000,0b10000}; memcpy(out,g,7); return true; }
    case 'R': { uint8_t g[7]={0b11110,0b10001,0b10001,0b11110,0b10100,0b10010,0b10001}; memcpy(out,g,7); return true; }
    case 'S': { uint8_t g[7]={0b01111,0b10000,0b10000,0b01110,0b00001,0b00001,0b11110}; memcpy(out,g,7); return true; }
    case 'T': { uint8_t g[7]={0b11111,0b00100,0b00100,0b00100,0b00100,0b00100,0b00100}; memcpy(out,g,7); return true; }
    case 'U': { uint8_t g[7]={0b10001,0b10001,0b10001,0b10001,0b10001,0b10001,0b01110}; memcpy(out,g,7); return true; }
    case 'V': { uint8_t g[7]={0b10001,0b10001,0b10001,0b10001,0b10001,0b01010,0b00100}; memcpy(out,g,7); return true; }
    case 'W': { uint8_t g[7]={0b10001,0b10001,0b10001,0b10101,0b10101,0b11011,0b10001}; memcpy(out,g,7); return true; }
    case 'Y': { uint8_t g[7]={0b10001,0b10001,0b01010,0b00100,0b00100,0b00100,0b00100}; memcpy(out,g,7); return true; }
    case '+': { uint8_t g[7]={0b00000,0b00100,0b00100,0b11111,0b00100,0b00100,0b00000}; memcpy(out,g,7); return true; }
    case '-': { uint8_t g[7]={0b00000,0b00000,0b00000,0b11111,0b00000,0b00000,0b00000}; memcpy(out,g,7); return true; }
    case '%': { uint8_t g[7]={0b11001,0b11010,0b00100,0b01000,0b01011,0b10011,0b00000}; memcpy(out,g,7); return true; }
    case ' ': { memset(out, 0, 7); return true; }
    default: return false;
  }
}

template<typename DisplayT>
int draw_text_5x7(DisplayT &it, int x, int y, const char *text, Color color, int kerning = 1) {
  int curr_x = x;
  for (int i = 0; text[i] != 0; i++) {
    uint8_t g[7];
    int w = 5;
    if (get_glyph_5x7(text[i], g, w)) {
      for (int r = 0; r < 7; r++) {
        for (int c = 0; c < w; c++) {
          if ((g[r] >> (w - 1 - c)) & 1) {
            it.draw_pixel_at(curr_x + c, y + r, color);
          }
        }
      }
      curr_x += w + kerning;
    }
  }
  return curr_x;
}

// 3x5 Subscript Digits for Decimal Tenth in Live Temp (e.g. 31.3°)
static const uint8_t DIGITS_3X5[10][5] = {
  {0b111,0b101,0b101,0b101,0b111}, // 0
  {0b010,0b110,0b010,0b010,0b111}, // 1
  {0b111,0b001,0b111,0b100,0b111}, // 2
  {0b111,0b001,0b111,0b001,0b111}, // 3
  {0b101,0b101,0b111,0b001,0b001}, // 4
  {0b111,0b100,0b111,0b001,0b111}, // 5
  {0b111,0b100,0b111,0b101,0b111}, // 6
  {0b111,0b001,0b010,0b010,0b010}, // 7
  {0b111,0b101,0b111,0b101,0b111}, // 8
  {0b111,0b101,0b111,0b001,0b111}  // 9
};

template<typename DisplayT>
void draw_hollow_deg_3x3(DisplayT &it, int x, int y, Color color) {
  it.draw_pixel_at(x + 1, y + 0, color);
  it.draw_pixel_at(x + 0, y + 1, color);
  it.draw_pixel_at(x + 2, y + 1, color);
  it.draw_pixel_at(x + 1, y + 2, color);
}

// Dynamically centered draw_tight_temp_5x7 (without leading space padding!)
template<typename DisplayT>
void draw_tight_temp_5x7(DisplayT &it, int x, int y, float temp, Color color_bright, Color color_sub) {
  int t10 = (int) roundf(temp * 10.0f);
  int t_int = t10 / 10;
  int t_dec = abs(t10) % 10;
  char buf[16];
  snprintf(buf, sizeof(buf), "%d", t_int);
  int curr_x = draw_text_5x7(it, x, y, buf, color_bright, 1);
  // 1px decimal dot at baseline
  it.draw_pixel_at(curr_x, y + 6, color_sub);
  curr_x += 2;
  // 3x5 subscript decimal digit at y + 2
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 3; c++) {
      if ((DIGITS_3X5[t_dec][r] >> (2 - c)) & 1) {
        it.draw_pixel_at(curr_x + c, y + 2 + r, color_sub);
      }
    }
  }
  curr_x += 4;
  // 3x3 hollow degree diamond at y
  draw_hollow_deg_3x3(it, curr_x, y, color_sub);
}

// True 4x6 Micro Font (pixoo_micro.bdf exact bitmaps, including flat-left 3 and 1px-shorter m)
inline bool get_glyph_micro_4x6(char ch, uint8_t out[6], int &width, int &dwidth) {
  width = 4; dwidth = 5;
  switch (ch) {
    case '0': { uint8_t g[6]={0b0110,0b1001,0b1001,0b1001,0b1001,0b0110}; memcpy(out,g,6); return true; }
    case '1': { uint8_t g[6]={0b0010,0b0110,0b0010,0b0010,0b0010,0b0111}; memcpy(out,g,6); return true; }
    case '2': { uint8_t g[6]={0b0110,0b1001,0b0010,0b0100,0b1000,0b1111}; memcpy(out,g,6); return true; }
    case '3': { uint8_t g[6]={0b1110,0b0001,0b0110,0b0001,0b0001,0b1110}; memcpy(out,g,6); return true; }
    case '4': { uint8_t g[6]={0b0010,0b0110,0b1010,0b1111,0b0010,0b0010}; memcpy(out,g,6); return true; }
    case '5': { uint8_t g[6]={0b1111,0b1000,0b1110,0b0001,0b1001,0b0110}; memcpy(out,g,6); return true; }
    case '6': { uint8_t g[6]={0b0110,0b1000,0b1110,0b1001,0b1001,0b0110}; memcpy(out,g,6); return true; }
    case '7': { uint8_t g[6]={0b1111,0b0001,0b0010,0b0100,0b0100,0b0100}; memcpy(out,g,6); return true; }
    case '8': { uint8_t g[6]={0b0110,0b1001,0b0110,0b1001,0b1001,0b0110}; memcpy(out,g,6); return true; }
    case '9': { uint8_t g[6]={0b0110,0b1001,0b1001,0b0111,0b0001,0b0110}; memcpy(out,g,6); return true; }
    case '+': { uint8_t g[6]={0b0000,0b0100,0b1110,0b0100,0b0000,0b0000}; memcpy(out,g,6); return true; }
    case '-': { uint8_t g[6]={0b0000,0b0000,0b1111,0b0000,0b0000,0b0000}; memcpy(out,g,6); return true; }
    case 'm': { width = 5; dwidth = 6; uint8_t g[6]={0b00000,0b00000,0b01010,0b10101,0b10101,0b10101}; memcpy(out,g,6); return true; }
    case '*': { width = 3; dwidth = 4; uint8_t g[6]={0b010,0b101,0b010,0b000,0b000,0b000}; memcpy(out,g,6); return true; }
    case ' ': { memset(out, 0, 6); return true; }
    default: return false;
  }
}

template<typename DisplayT>
int draw_text_micro(DisplayT &it, int x, int y, const char *text, Color color) {
  int curr_x = x;
  for (int i = 0; text[i] != 0; i++) {
    uint8_t g[6];
    int w = 4, dw = 5;
    if (get_glyph_micro_4x6(text[i], g, w, dw)) {
      for (int r = 0; r < 6; r++) {
        for (int c = 0; c < w; c++) {
          if ((g[r] >> (w - 1 - c)) & 1) {
            it.draw_pixel_at(curr_x + c, y + r, color);
          }
        }
      }
      curr_x += dw;
    }
  }
  return curr_x;
}

// 5x8 Outlined Two-Tone Laboratory Tube Thermometer
template<typename DisplayT>
void draw_flat_thermometer(DisplayT &it, int x, int y, Color color) {
  Color C_GLASS(190, 200, 215);
  static const char *grid[8] = {
    ".WWW.",
    ".WRW.",
    ".WRW.",
    ".WRW.",
    "WWRWW",
    "WRRRW",
    "WRRRW",
    ".WWW."
  };
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 5; c++) {
      char ch = grid[r][c];
      if (ch == 'W') it.draw_pixel_at(x + c, y + r, C_GLASS);
      else if (ch == 'R') it.draw_pixel_at(x + c, y + r, color);
    }
  }
}

template<typename DisplayT>
void draw_organic_droplet(DisplayT &it, int x, int y, Color color) {
  static const uint8_t p[7] = {0b00100, 0b00100, 0b01110, 0b11111, 0b11111, 0b11111, 0b01110};
  for (int r = 0; r < 7; r++) {
    for (int c = 0; c < 5; c++) {
      if ((p[r] >> (4 - c)) & 1) it.draw_pixel_at(x + c, y + r, color);
    }
  }
}

template<typename DisplayT>
void draw_chevron(DisplayT &it, int x, int y, bool up, Color color) {
  if (up) {
    // Solid 5x3 upward triangle vertically centered at y+1..y+3 (aligned with '+')
    it.draw_pixel_at(x + 2, y + 1, color);
    for (int c = 1; c <= 3; c++) it.draw_pixel_at(x + c, y + 2, color);
    for (int c = 0; c <= 4; c++) it.draw_pixel_at(x + c, y + 3, color);
  } else {
    // Solid 5x3 downward triangle vertically centered at y+1..y+3
    for (int c = 0; c <= 4; c++) it.draw_pixel_at(x + c, y + 1, color);
    for (int c = 1; c <= 3; c++) it.draw_pixel_at(x + c, y + 2, color);
    it.draw_pixel_at(x + 2, y + 3, color);
  }
}

template<typename DisplayT>
void draw_cedar_tree_7x7(DisplayT &it, int x, int y) {
  Color G(35, 185, 75);
  Color C_TRUNK(150, 90, 40);
  Color Y(255, 215, 25);
  it.draw_pixel_at(x + 2, y + 0, G); it.draw_pixel_at(x + 6, y + 0, Y);
  it.draw_pixel_at(x + 1, y + 1, G); it.draw_pixel_at(x + 2, y + 1, G); it.draw_pixel_at(x + 3, y + 1, G); it.draw_pixel_at(x + 7, y + 1, Y);
  for (int i = 0; i < 5; i++) it.draw_pixel_at(x + i, y + 2, G);
  it.draw_pixel_at(x + 6, y + 2, Y);
  it.draw_pixel_at(x + 1, y + 3, G); it.draw_pixel_at(x + 2, y + 3, G); it.draw_pixel_at(x + 3, y + 3, G); it.draw_pixel_at(x + 7, y + 3, Y);
  for (int i = 0; i < 5; i++) it.draw_pixel_at(x + i, y + 4, G);
  it.draw_pixel_at(x + 6, y + 4, Y);
  it.draw_pixel_at(x + 2, y + 5, C_TRUNK); it.draw_pixel_at(x + 5, y + 5, Y); it.draw_pixel_at(x + 7, y + 5, Y);
  it.draw_pixel_at(x + 2, y + 6, C_TRUNK);
}

// Software RGB Dimming Wrapper (stacks with hardware 1% floor for ultra-dim night viewing)
template<typename DisplayT>
struct DimmingDisplay {
  DisplayT &inner;
  float scale;
  Color dim(Color c) const {
    if (scale >= 0.999f) return c;
    // Below 15% RGB, apply a warm night-shift (attenuate G/B faster than R) and avoid
    // clamping minor channels to 1, which causes the panel's 1% PWM floor to turn colors white.
    float r_s = scale;
    float g_s = (scale < 0.15f) ? (scale * 0.45f) : scale;
    float b_s = (scale < 0.15f) ? (scale * 0.30f) : scale;
    uint8_t r = (uint8_t) std::min(255, (int) floorf(c.r * r_s));
    uint8_t g = (uint8_t) std::min(255, (int) floorf(c.g * g_s));
    uint8_t b = (uint8_t) std::min(255, (int) floorf(c.b * b_s));
    if (r == 0 && g == 0 && b == 0 && (c.r > 0 || c.g > 0 || c.b > 0)) {
      if (c.r >= c.g && c.r >= c.b) r = 1;
      else if (c.g >= c.b) g = 1;
      else b = 1;
    }
    return Color(r, g, b);
  }
  void draw_pixel_at(int x, int y, Color c) {
    inner.draw_pixel_at(x, y, dim(c));
  }
};

// Shared Grid Sprite Renderer
template<typename DisplayT, typename PaletteFn>
void draw_grid_sprite(DisplayT &it, int x, int y, const char *const *rows, int n_rows, PaletteFn pal) {
  for (int r = 0; r < n_rows; r++) {
    const char *row = rows[r];
    for (int c = 0; row[c] != '\0'; c++) {
      Color col(0, 0, 0);
      if (pal(row[c], col)) {
        it.draw_pixel_at(x + c, y + r, col);
      }
    }
  }
}

// 1x14px Smooth Gradient Vertical Bar (Rain or UV intensity)
template<typename DisplayT>
void draw_gradient_bar(DisplayT &it, int x, int bottom_y, int height, bool is_rain) {
  if (height <= 0) return;
  if (height > 14) height = 14;
  struct RGB { uint8_t r, g, b; };
  static const RGB RAIN_STOPS[4] = {{70, 220, 255}, {40, 145, 255}, {75, 90, 245}, {165, 65, 245}};
  static const RGB UV_STOPS[4]   = {{60, 210, 120}, {235, 215, 45}, {255, 130, 30}, {245, 45, 165}};
  const RGB *stops = is_rain ? RAIN_STOPS : UV_STOPS;

  for (int i = 0; i < height; i++) {
    float t = (float) i / 13.0f; // 0..1 across full 14px scale
    float seg = t * 3.0f;
    int idx = (int) seg;
    if (idx > 2) idx = 2;
    float frac = seg - idx;
    uint8_t r = (uint8_t) roundf(stops[idx].r + (stops[idx + 1].r - stops[idx].r) * frac);
    uint8_t g = (uint8_t) roundf(stops[idx].g + (stops[idx + 1].g - stops[idx].g) * frac);
    uint8_t b = (uint8_t) roundf(stops[idx].b + (stops[idx + 1].b - stops[idx].b) * frac);
    it.draw_pixel_at(x, bottom_y - i, Color(r, g, b));
  }
}

// Weather Icon Palette
inline bool weather_palette(char ch, Color &out) {
  switch (ch) {
    case 'c': out = Color(255, 235, 120); return true;
    case 'o': out = Color(255, 205,  30); return true;
    case 'r': out = Color(255, 145,  15); return true;
    case 'M': out = Color(255, 235, 130); return true;
    case 'm': out = Color(225, 195,  80); return true;
    case 'S': out = Color(180, 210, 255); return true;
    case 's': out = Color( 95, 135, 185); return true;
    case 'H': out = Color(235, 242, 250); return true;
    case 'T': out = Color(195, 210, 228); return true;
    case 'B': out = Color(135, 155, 180); return true;
    case 'D': out = Color( 85, 102, 128); return true;
    case 't': out = Color(135, 148, 168); return true;
    case 'b': out = Color( 90, 102, 122); return true;
    case 'd': out = Color( 55,  65,  82); return true;
    case 'R': out = Color( 80, 210, 255); return true;
    case 'h': out = Color( 50, 175, 255); return true;
    case 'Y': out = Color(255, 240,  90); return true;
    case 'y': out = Color(255, 185,  20); return true;
    case 'W': out = Color(220, 245, 255); return true;
    case 'I': out = Color(170, 235, 255); return true;
    case 'F': out = Color(165, 180, 200); return true;
    case 'f': out = Color(105, 120, 140); return true;
    default: return false;
  }
}

// Wind Badge Palette (motion gradient: dim slate -> sky blue -> bright ice cyan)
inline bool wind_palette(char ch, Color &out) {
  switch (ch) {
    case 'w': out = Color(190, 235, 255); return true;
    case 'v': out = Color(105, 185, 240); return true;
    case 'd': out = Color( 55, 110, 155); return true;
    default: return false;
  }
}

template<typename DisplayT>
void draw_wind_badge_12x10(DisplayT &it, int x, int y) {
  static const char *const WIND_12X10[10] = {
    ".....w......",
    "....w.w.....",
    "......v..ww.",
    "ddvvvv..w..w",
    "...........v",
    "...ddvvvvvv.",
    "..ddvvvvv...",
    ".........v..",
    "......w..w..",
    ".......ww..."
  };
  draw_grid_sprite(it, x, y, WIND_12X10, 10, wind_palette);
}

// All 12 Primary 14x14 Weather Icons
template<typename DisplayT>
void draw_weather_icon_14x14(DisplayT &it, int x, int y, const std::string &cond, bool is_night) {
  static const char *const SUN[14] = {
    "......rr......",".r....rr....r.","..r........r..","..............",
    ".....oooo.....","....occcco....","rr..occcco..rr","rr..occcco..rr",
    "....oooooo....",".....oooo.....","..............","..r........r..",
    ".r....rr....r.","......rr......"
  };
  static const char *const MOON[14] = {
    "..............","......mMm.....","....mMMM......","...MMMM....S..",
    "..MMMM........","..MMMM...s....","..MMMM..sSs...","..MMMM...s....",
    "..MMMM........","...MMMM.......","....mMMM......","......mMm.....",
    "..............",".............."
  };
  static const char *const PARTLY_DAY[14] = {
    "........r.....","....r..ooo..r.","......occco...",".....rocccor..",
    "...HHH.ooo....","..HTTTT.r.....",".HTTTTTTT.....","HBBBBBBBBBB...",
    "BBBBBBBBBBBB..","DDDDDDDDDDDD..",".DDDDDDDDDD...","..............",
    "..............",".............."
  };
  static const char *const PARTLY_NIGHT[14] = {
    ".........mmm..",".......mmMMm..","......mMM.....","......mMM..S..",
    "...HHH.mm.....","..HTTTT.mmm...",".HTTTTTTT.....","HBBBBBBBBBB...",
    "BBBBBBBBBBBB..","DDDDDDDDDDDD..",".DDDDDDDDDD...","..............",
    "..............",".............."
  };
  static const char *const CLOUDY[14] = {
    "..............","......TTTT....",".....TTTTTT...","...HHBBBBBB...",
    "..HTTTTBBBB...",".HTTTTTTTBBB..","HBBBBBBBBBBBB.","BBBBBBBBBBBBB.",
    "DDDDDDDDDDDDD.",".DDDDDDDDDDD..","..............","..............",
    "..............",".............."
  };
  static const char *const FOG[14] = {
    "..............","....TTTT......","..TTTTTTTT....",".BBBBBBBBBB...",
    ".DDDDDDDDDDD..","..............",".FFFFFFFFFF...","..............",
    "..ffffffffff..","..............",".FFFFFFFFFF...","..............",
    "..ffffffffff..",".............."
  };
  static const char *const RAIN[14] = {
    "..............","....TTTTT.....","..TTTTTTTTT...",".BBBBBBBBBBBB.",
    ".BBBBBBBBBBBB.",".DDDDDDDDDDDD.","..DDDDDDDDDD..","..............",
    "..R...R...R...",".R...R...R....","..............","....R...R...R.",
    "...R...R...R..",".............."
  };
  static const char *const POURING[14] = {
    "....ttttt.....","..ttttttttt...",".bbbbbbbbbbbb.",".bbbbbbbbbbbb.",
    ".dddddddddddd.","..dddddddddd..","..............",".R..R..R..R...",
    "h..h..h..h....","..............","..R..R..R..R..",".h..h..h..h...",
    "h..h..h..h....",".............."
  };
  static const char *const THUNDER[14] = {
    "....ttttt.....","..ttttttttt...",".bbbbbbbbbbbb.",".dddddddddddd.",
    "..dddddddddd..","......YY......",".....YY.......","..R.YYYY..R...",
    ".R...YY..R....","....YY........","...y..........","..............",
    "..............",".............."
  };
  static const char *const SNOW[14] = {
    "...W..........",".W.B.W........","..BBB.....W...",".W.B.W..W.B.W.",
    "...W.....BBB..","........W.B.W.","..........W...","..............",
    "....W.........","..W.B.W.......","...BBB........","..W.B.W.......",
    "....W.........",".............."
  };
  static const char *const HAIL[14] = {
    "....ttttt.....","..ttttttttt...",".bbbbbbbbbbbb.",".dddddddddddd.",
    "..dddddddddd..","..............","..II....II....","..II....II....",
    ".....II.......",".....II.......","..II....II....","..II....II....",
    "..............",".............."
  };

  if (cond == "windy" || cond == "windy-variant") {
    draw_wind_badge_12x10(it, x + 1, y + 2);
  } else if (cond == "lightning" || cond == "lightning-rainy") {
    draw_grid_sprite(it, x, y, THUNDER, 14, weather_palette);
  } else if (cond == "pouring") {
    draw_grid_sprite(it, x, y, POURING, 14, weather_palette);
  } else if (cond == "rainy") {
    draw_grid_sprite(it, x, y, RAIN, 14, weather_palette);
  } else if (cond == "snowy") {
    draw_grid_sprite(it, x, y, SNOW, 14, weather_palette);
  } else if (cond == "hail" || cond == "snowy-rainy") {
    draw_grid_sprite(it, x, y, HAIL, 14, weather_palette);
  } else if (cond == "fog") {
    draw_grid_sprite(it, x, y, FOG, 14, weather_palette);
  } else if (cond == "cloudy") {
    draw_grid_sprite(it, x, y, CLOUDY, 14, weather_palette);
  } else if (cond == "partlycloudy") {
    draw_grid_sprite(it, x, y, is_night ? PARTLY_NIGHT : PARTLY_DAY, 14, weather_palette);
  } else if (cond == "clear-night" || is_night) {
    draw_grid_sprite(it, x, y, MOON, 14, weather_palette);
  } else {
    draw_grid_sprite(it, x, y, SUN, 14, weather_palette);
  }
}

// Shiba Inu Palette & 8-Frame Day/Night Animations
inline bool shiba_palette(char ch, Color &out) {
  switch (ch) {
    case 'O': out = Color(235, 138,  42); return true;
    case 'D': out = Color(185,  95,  22); return true;
    case 'W': out = Color(255, 240, 210); return true;
    case 'E': out = Color( 35,  25,  20); return true;
    case 'P': out = Color(240, 120, 130); return true;
    case 'Z': out = Color(130, 170, 220); return true;
    case 'z': out = Color( 80, 110, 155); return true;
    case 'G': out = Color( 45, 110,  55); return true;
    default: return false;
  }
}

template<typename DisplayT>
void draw_shiba_day_frame(DisplayT &it, int x, int y, int frame) {
  // 14x12 sitting Shiba (alert, ear twitch, happy blink, tail wag, pink blep, idle bounce)
  static const char *const FRAMES[8][12] = {
    {"....D...D.....","....OO.OO.....","...OOOOOOO....","...OEOOOEO....","...WWOEOWW....","....WWWWW..OO.","...OOOOOO.O..O","...OOWWWOOO.O.","...OOWWWOOOO..","...OOOOOOO....","...WW..WW.....","..GGGGGGGGGG.."},
    {"...D....D.....","....OO.OO.....","...OOOOOOO....","...OEOOOEO....","...WWOEOWW.OO.","....WWWWW.O..O","...OOOOOO.O.O.","...OOWWWOOOO..","...OOWWWOOO...","...OOOOOOO....","...WW..WW.....","..GGGGGGGGGG.."},
    {"....D...D.....","....OO.OO.....","...OOOOOOO....","...OOOOOOO.OO.","...WWOEOWWO..O","....WWWWW.O..O","...OOOOOO.O.O.","...OOWWWOOOO..","...OOWWWOOO...","...OOOOOOO....","...WW..WW.....","..GGGGGGGGGG.."},
    {"....D...D.....","....OO.OO.....","...OOOOOOO....","...OEOOOEO....","...WWOEOWW....","....WWWWW..OO.","...OOOOOO.O..O","...OOWWWOOO.O.","...OOWWWOOOO..","...OOOOOOO....","...WW..WW.....","..GGGGGGGGGG.."},
    {"....D...D.....","....OO.OO.....","...OOOOOOO....","...OEOOOEO....","...WWOEOWW.OO.","....WWPWW.O..O","...OOOPOO.O.O.","...OOWWWOOOO..","...OOWWWOOO...","...OOOOOOO....","...WW..WW.....","..GGGGGGGGGG.."},
    {"....D...D.....","....OO.OO.....","...OOOOOOO....","...OOOOOOO.OO.","...WWOEOWWO..O","....WWPWW.O..O","...OOOPOO.O.O.","...OOWWWOOOO..","...OOWWWOOO...","...OOOOOOO....","...WW..WW.....","..GGGGGGGGGG.."},
    {"..............","....D...D.....","....OO.OO.....","...OOOOOOO....","...OEOOOEO....","...WWOEOWW....","....WWWWW..OO.","...OOOOOO.O..O","...OOWWWOOOOO.","...OOWWWOOOO..","...WW..WW.....","..GGGGGGGGGG.."},
    {"....D...D.....","....OO.OO.....","...OOOOOOO....","...OEOOOEO....","...WWOEOWW.OO.","....WWWWW.O..O","...OOOOOO.O.O.","...OOWWWOOOO..","...OOWWWOOO...","...OOOOOOO....","...WW..WW.....","..GGGGGGGGGG.."}
  };
  draw_grid_sprite(it, x, y, FRAMES[frame & 7], 12, shiba_palette);
}

template<typename DisplayT>
void draw_shiba_walk_frame(DisplayT &it, int x, int y, int frame, bool flip_x) {
  // 14x10 side-profile Shiba Inu (facing left by default; flip_x=true faces right)
  static const char *const WALK[4][10] = {
    { // F0: stride A
      "..D.D.........",
      ".OOOOO........",
      "OEOOOEO.......",
      "WWWEWOOOOO..OO",
      ".WWOOOOOOOOO.O",
      "..OOOOOOOOOOO.",
      "..OOOOOOOOOO..",
      "..WW.....WW...",
      ".WW.......WW..",
      ".............."
    },
    { // F1: passing
      "..............",
      "..D.D.........",
      ".OOOOO........",
      "OEOOOEO....OO.",
      "WWWEWOOOOOO..O",
      ".WWOOOOOOOOOO.",
      "..OOOOOOOOOO..",
      "...WW....WW...",
      "...WW....WW...",
      ".............."
    },
    { // F2: stride B
      "..D.D.........",
      ".OOOOO........",
      "OEOOOEO.......",
      "WWWEWOOOOO..OO",
      ".WWOOOOOOOOO.O",
      "..OOOOOOOOOOO.",
      "..OOOOOOOOOO..",
      "...WW...WW....",
      "....WW.WW.....",
      ".............."
    },
    { // F3: passing
      "..............",
      "..D.D.........",
      ".OOOOO........",
      "OEOOOEO....OO.",
      "WWWEWOOOOOO..O",
      ".WWOOOOOOOOOO.",
      "..OOOOOOOOOO..",
      "...WW....WW...",
      "...WW....WW...",
      ".............."
    }
  };
  const char *const *grid = WALK[frame & 3];
  for (int r = 0; r < 10; r++) {
    for (int c = 0; c < 14; c++) {
      Color col(0, 0, 0);
      if (shiba_palette(grid[r][c], col)) {
        int px = flip_x ? (x + 13 - c) : (x + c);
        it.draw_pixel_at(px, y + r, col);
      }
    }
  }
}

template<typename DisplayT>
void draw_shiba_night_frame(DisplayT &it, int x, int y, int frame) {
  // 15x10 curled sleeping Shiba with Zzz floating above his HEAD (left side)
  static const char *const FRAMES[8][10] = {
    {".ZZ............","..Z............",".ZZ............",".D..D..........",".OOOOO.........","OEOOOEOOOOO....","WWWEWOOOOOOO...",".WWOOOOOOOOO...","..OOOOOOOOO....","..WW....WW....."},
    {"ZZ.............",".Z.............","ZZ.............",".D..D..........",".OOOOO.........","OEOOOEOOOOO....","WWWEWOOOOOOO...",".WWOOOOOOOOO...","..OOOOOOOOO....","..WW....WW....."},
    {".zz............",".z.............","...............","...............",".D..D..........",".OOOOO.OOOO....","OEOOOEOOOOOO...","WWWEWOOOOOOO...",".WWOOOOOOOOO...","..WW....WW....."},
    {"...............","...............","...............",".D..D..........",".OOOOO.OOOO....","OEOOOEOOOOOO...","WWWEWOOOOOOO...",".WWOOOOOOOOO...","..OOOOOOOOO....","..WW....WW....."},
    {"...............","..ZZ...........","...Z...........",".D..D..........",".OOOOO.........","OEOOOEOOOOO....","WWWEWOOOOOOO...",".WWOOOOOOOOO...","..OOOOOOOOO....","..WW....WW....."},
    {".ZZ............","..Z............",".ZZ............",".D..D..........",".OOOOO.........","OEOOOEOOOOO....","WWWEWOOOOOOO...",".WWOOOOOOOOO...","..OOOOOOOOO....","..WW....WW....."},
    {"ZZ.............",".Z.............","...............","...............",".D..D..........",".OOOOO.OOOO....","OEOOOEOOOOOO...","WWWEWOOOOOOO...",".WWOOOOOOOOO...","..WW....WW....."},
    {"...............","...............","...............",".D..D..........",".OOOOO.........","OEOOOEOOOOO....","WWWEWOOOOOOO...",".WWOOOOOOOOO...","..OOOOOOOOO....","..WW....WW....."}
  };
  draw_grid_sprite(it, x, y, FRAMES[frame & 7], 10, shiba_palette);
}

} // namespace pixoo_gfx
