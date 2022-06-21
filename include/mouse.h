#pragma once

#include <stdint.h>
#include <stddef.h>
#include "interrupts.h"
#include "console.h"
#include "port.h"
#include "driver.h"

class MouseDriver : public InterruptHandler, public Driver
{
private:
	Port8Bit dataport;	
	Port8Bit commandport;	
	uint8_t buffer[3];
	uint8_t offset;
	uint8_t buttons;
	Console console;

public:
	MouseDriver(InterruptManager* interruptManager);
	~MouseDriver();

	virtual uint32_t HandleInterrupt(uint32_t esp);
	virtual void Activate();
};
