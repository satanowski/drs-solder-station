#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_I2CDevice.h>
#include <Fonts/FreeMono9pt7b.h>
#include <SPI.h>
#include <RotaryEncoder.h>
#include "img.h"
#include "main.h"


Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);  // hard SPI
RotaryEncoder *encoder = nullptr;
bool clicked = false;

void checkPosition() {
	encoder->tick();
}


uint16_t gradient(const Color *start, const Color *end, float position) {
	const Color destColor = {
		start->r + (int)round(position * (end->r - start->r)),
		start->g + (int)round(position * (end->g - start->g)),
		start->b + (int)round(position * (end->b - start->b))
	};

	return color565(&destColor);
}


void updateTemp(int temp) {
	const Pos pos = {15, 80};
	const Color startColor = WHITE;
	const Color endColor = RED;
	float percent = (temp - MIN_TEMP) * ((float)(MIN_TEMP) / (float)(MAX_TEMP - MIN_TEMP)) / 100;
	uint16_t color = gradient(&startColor, &endColor, percent);
	int16_t x1, y1;
	uint16_t w, h;

	const char *txt = (char*)malloc(3);
	sprintf(txt, "%03d", temp);

	tft.setTextColor(color);
	tft.setCursor(pos.x, pos.y);
	tft.setTextSize(2);

	tft.getTextBounds(txt, pos.x, pos.y, &x1, &y1, &w, &h);
	tft.fillRect(x1-2, y1-1, w+2, h+1, C_BLACK); // clean
	tft.print(txt);

	// Celsius sign
	tft.drawCircle(pos.x+70, pos.y-18, 3, color);
	tft.setCursor(pos.x+74, pos.y);
	tft.print("C");
	free(txt);
}


void init_screen() {
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(2); // pionowo!
	tft.setFont(&FreeMono9pt7b);
	tft.fillScreen(ST77XX_BLACK);
	tft.drawBitmap(0, 0, logo_1, 128, 40, C_RED);
	tft.drawBitmap(25, 17, logo_2, 79, 7, C_WHITE);
	updateTemp(0);
}

void blink() {
	for(int x=0; x<3; x++) {
		tft.invertDisplay(true);
		delay(100);
		tft.invertDisplay(false);
		delay(100);
	}
}

void setup() {
	encoder = new RotaryEncoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);
	attachInterrupt(digitalPinToInterrupt(PIN_IN1), checkPosition, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_IN2), checkPosition, CHANGE);

	pinMode(led, OUTPUT);
	pinMode(click, INPUT);
	init_screen();
}


void loop() {
	clicked = digitalRead(click);
	static int encPos = 0;
	encoder->tick();
	int newPos = encoder->getPosition();
	if (encPos != newPos) {
		switch((int)encoder->getDirection()) {
			case 1: 
				newPos = encPos + TEMP_STEP;
				encoder->setPosition(newPos);
				break;
			case -1:
				newPos = encPos - TEMP_STEP;
				encoder->setPosition(newPos);
				break;
		}

		if (newPos > MAX_TEMP) {
			newPos = MAX_TEMP;
			encoder->setPosition(MAX_TEMP);
		} else if (newPos < MIN_TEMP) {
			newPos = MIN_TEMP;
			encoder->setPosition(MIN_TEMP);
		}

		updateTemp(newPos);
		encPos = newPos;
	}

	if (!clicked) {
		blink();
	}
}
