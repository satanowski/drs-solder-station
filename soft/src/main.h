
// TFT pins
const int cs=10;
const int dc=9;
const int rst=8;

// Encoder pins 
const int PIN_IN1=2;
const int PIN_IN2=3;

//Other pins
const int led=1;
const int click=0;

// Default settings
const int MIN_TEMP=50;
const int MAX_TEMP=400;
const int TEMP_STEP=5;

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct Pos {
  int16_t x;
  int16_t y;
};

uint16_t color565(const Color *c) {
	return ((c->r & 0xF8) << 8) | ((c->g & 0xFC) << 3) | ((c->b & 0xF8) >> 3);
}

const Color BLACK = {0, 0, 0};
const Color RED = {255, 0, 0};
const Color WHITE = {255, 255, 255};

const uint16_t C_RED = color565(&RED);
const uint16_t C_WHITE = color565(&WHITE);
const uint16_t C_BLACK = color565(&BLACK);
