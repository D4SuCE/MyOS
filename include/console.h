#pragma once

#include "color.h"
#include <stddef.h>
#include <stdint.h>

class Console
{
private:
	uint16_t* memory = reinterpret_cast<uint16_t*>(0xb8000);
	uint8_t color;
	const size_t windowWidth;
	const size_t windowHeight;

private:
	uint16_t printColorful(char c);

public:
	Console();
	Console(const size_t windowWidth, const size_t windowHeight);
	~Console();
	size_t strlen(const char* str);
	void setColor(Color foreground, Color background);
	void clearScreen();
	void print(char* str);
	const size_t getWindowWidth();
	const size_t getWindowHeight();
};
