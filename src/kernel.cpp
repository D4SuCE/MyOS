#include "../include/console.h"
#include "../include/gdt.h"
#include "../include/interrupts.h"
#include "../include/keyboard.h"
#include "../include/mouse.h"
#include "../include/driver.h"

extern "C" void kernel_main(const void* multibootStructure, uint32_t)
{
	Console	console;
	
	console.clearScreen();
	
	console.print("Hello, World! --- Created by D4SuCE\n");

	GlobalDescriptorTable gdt;

	InterruptManager interrupts(&gdt);

	console.print("Initializing Hardware, Stage 1\n");
	
	DriverManager driverManager;

	KeyboardDriver keyboard(&interrupts);
	driverManager.AddDriver(&keyboard);

	MouseDriver mouse(&interrupts);
	driverManager.AddDriver(&mouse);
	
	console.print("Initializing Hardware, Stage 2\n");
	driverManager.ActivateAll();

	console.print("Initializing Hardware, Stage 3\n");
	interrupts.Activate();

	while(true);
}
