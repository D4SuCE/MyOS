#pragma once

#include <stdint.h>
#include <stddef.h>
#include "interrupts.h"
#include "console.h"
#include "port.h"
#include "driver.h"

class KeyboardDriver : public InterruptHandler, public Driver
{
private:
	Port8Bit dataport;	
	Port8Bit commandport;	

public:
	KeyboardDriver(InterruptManager* interruptManager);
	~KeyboardDriver();

	virtual uint32_t HandleInterrupt(uint32_t esp);
	virtual void Activate();
};
