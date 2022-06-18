#include "../include/console.h"
#include "../include/gdt.h"
#include "../include/interrupts.h"

extern "C" void kernel_main(const void* multibootStructure, uint32_t)
{
	Console	console;
	
	console.clearScreen();
	
	console.print("Hello, World! --- Created by D4SuCE\n");

	GlobalDescriptorTable gdt;

	InterruptManager interrupts(&gdt);
	interrupts.Activate();

	while(true);
}
