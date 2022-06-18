#include "../include/console.h"

Console::Console()
	: color(static_cast<int>(Color::COLOR_WHITE) | static_cast<int>(Color::COLOR_BLACK) << 4),
	windowWidth(80),
	windowHeight(26)
{
}

Console::Console(const size_t windowWidth, const size_t windowHeight)
	: color(static_cast<int>(Color::COLOR_WHITE) | static_cast<int>(Color::COLOR_BLACK) << 4),
	windowWidth(windowWidth),
	windowHeight(windowHeight)
{
}

uint16_t Console::printColorful(char c)
{
	return c | color << 8;
}

size_t Console::strlen(const char *str)
{
	size_t len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return len;
}

void Console::setColor(Color foreground, Color background)
{
	color = static_cast<int>(foreground) | static_cast<int>(background) << 4;
}

void Console::clearScreen()
{
	for (size_t row = 0; row < windowHeight; row++)
	{
		for (size_t column = 0; column < windowWidth; column++)
		{
			memory[windowWidth * row + column] = printColorful(' ');
		}
	}
}

void Console::print(char* str)
{
	static uint8_t row = 0;
	static uint8_t column = 0;
	for (size_t i = 0; i < strlen(str); i++)
	{
		switch (str[i])
		{
		case '\n':
			row++;
			column = 0;
			break;
		default:
			memory[windowWidth * row + column] = printColorful(str[i]);
			column++;
			break;
		}

		if (column > windowWidth)
		{
			row++;
			column = 0;
		}

		if (row > windowHeight)
		{
			clearScreen();
			row = 0;
			column = 0;
		}
	}
}
