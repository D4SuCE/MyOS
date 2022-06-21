#include "../include/mouse.h"
#include <bits/stdint-intn.h>

MouseDriver::MouseDriver(InterruptManager* interruptManager)
	: InterruptHandler(0x2C, interruptManager),
	dataport(0x60),
	commandport(0x64)
{
}

MouseDriver::~MouseDriver()
{
}

void MouseDriver::Activate()
{
	offset = 0;
	buttons = 0;

	int8_t x = console.getWindowWidth() / 2, y = console.getWindowHeight() / 2;
	
	static uint16_t* memory = reinterpret_cast<uint16_t*>(0xb8000);
	memory[console.getWindowWidth() * y + x] = ((memory[console.getWindowWidth() * y + x] & 0xF000) >> 4) |
											   ((memory[console.getWindowWidth() * y + x] & 0x0F00) << 4) |
												(memory[console.getWindowWidth() * y + x] & 0x00FF);	
	commandport.Write(0xAB);
	commandport.Write(0x20);
	uint8_t status = dataport.Read() | 2;
	commandport.Write(0x60);
	dataport.Write(status);
	commandport.Write(0xD4);
	dataport.Write(0xF4);
	dataport.Read();
}

uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
	uint8_t status = commandport.Read();
	
	if (!(status & 0x20))
	{
		return esp;	
	}

	static int8_t x = 80 / 2, y = 25 / 2;

	buffer[offset] = dataport.Read();
	offset = (offset + 1) % 3;
	
	if (!offset)
	{
		uint16_t* memory = reinterpret_cast<uint16_t*>(0xb8000);
		memory[console.getWindowWidth() * y + x] = ((memory[console.getWindowWidth() * y + x] & 0xF000) >> 4) |
												   ((memory[console.getWindowWidth() * y + x] & 0x0F00) << 4) |
													(memory[console.getWindowWidth() * y + x] & 0x00FF);
		
		x += buffer[1];

		if (x < 0)
		{
			x = 0;
		}
		if (x >= console.getWindowWidth())
		{
			x = console.getWindowWidth() - 1;
		}

		y -= buffer[2];

		if (y < 0)
		{
			y = 0;
		}
		if (y >= console.getWindowHeight())
		{
			y = console.getWindowHeight() - 1;
		}

		memory[console.getWindowWidth() * y + x] = ((memory[console.getWindowWidth() * y + x] & 0xF000) >> 4) |
												   ((memory[console.getWindowWidth() * y + x] & 0x0F00) << 4) |
													(memory[console.getWindowWidth() * y + x] & 0x00FF);
		
		for (int8_t i = 0; i < 3; i++)
		{
			if ((buffer[0] & (0x01 << i)) != buttons & (0x01 << i))
			{

			}
		}
		buttons = buffer[0];
	}

	return esp;
}
