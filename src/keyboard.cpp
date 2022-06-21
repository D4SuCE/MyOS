#include "../include/keyboard.h"

KeyboardDriver::KeyboardDriver(InterruptManager* interruptManager)
	: InterruptHandler(0x21, interruptManager),
	dataport(0x60),
	commandport(0x64)
{	
}

KeyboardDriver::~KeyboardDriver()
{
}

void KeyboardDriver::Activate()
{
	while (commandport.Read() & 0x1)
	{
		dataport.Read();
	}
	commandport.Write(0xAE);
	commandport.Write(0x20);
	uint8_t status = (dataport.Read() | 1) & ~0x10;
	commandport.Write(0x60);
	dataport.Write(status);
	dataport.Write(0xF4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
	uint8_t key = dataport.Read();
	static bool Shift = false;

	Console console;
	switch (key)
	{
	case 0x02: if (Shift) console.print("!"); else console.print("1"); break;	
	case 0x03: if (Shift) console.print("@"); else console.print("2"); break;	
	case 0x04: if (Shift) console.print("#"); else console.print("3"); break;	
	case 0x05: if (Shift) console.print("$"); else console.print("4"); break;	
	case 0x06: if (Shift) console.print("%"); else console.print("5"); break;	
	case 0x07: if (Shift) console.print("^"); else console.print("6"); break;	
	case 0x08: if (Shift) console.print("&"); else console.print("7"); break;	
	case 0x09: if (Shift) console.print("*"); else console.print("8"); break;	
	case 0x0A: if (Shift) console.print("("); else console.print("9"); break;	
	case 0x0B: if (Shift) console.print(")"); else console.print("0"); break;	
	case 0x0C: if (Shift) console.print("_"); else console.print("-"); break;	
	case 0x0D: if (Shift) console.print("+"); else console.print("="); break;	
	
	case 0x10: if (Shift) console.print("Q"); else console.print("q"); break;	
	case 0x11: if (Shift) console.print("W"); else console.print("w"); break;	
	case 0x12: if (Shift) console.print("E"); else console.print("e"); break;	
	case 0x13: if (Shift) console.print("R"); else console.print("r"); break;	
	case 0x14: if (Shift) console.print("T"); else console.print("t"); break;	
	case 0x15: if (Shift) console.print("Y"); else console.print("y"); break;	
	case 0x16: if (Shift) console.print("U"); else console.print("u"); break;
	case 0x17: if (Shift) console.print("I"); else console.print("i"); break;
	case 0x18: if (Shift) console.print("O"); else console.print("o"); break;
	case 0x19: if (Shift) console.print("P"); else console.print("p"); break;
	case 0x1A: if (Shift) console.print("{"); else console.print("["); break;
	case 0x1B: if (Shift) console.print("}"); else console.print("]"); break;
	case 0x2B: if (Shift) console.print("|"); else console.print("\\"); break;

	case 0x1E: if (Shift) console.print("A"); else console.print("a"); break;	
	case 0x1F: if (Shift) console.print("S"); else console.print("s"); break;	
	case 0x20: if (Shift) console.print("D"); else console.print("d"); break;	
	case 0x21: if (Shift) console.print("F"); else console.print("f"); break;	
	case 0x22: if (Shift) console.print("G"); else console.print("g"); break;	
	case 0x23: if (Shift) console.print("H"); else console.print("h"); break;	
	case 0x24: if (Shift) console.print("J"); else console.print("j"); break;	
	case 0x25: if (Shift) console.print("K"); else console.print("k"); break;	
	case 0x26: if (Shift) console.print("L"); else console.print("l"); break;	
	case 0x27: if (Shift) console.print(":"); else console.print(";"); break;	
	case 0x28: if (Shift) console.print("\""); else console.print("\'"); break;	
	
	case 0x2C: if (Shift) console.print("Z"); else console.print("z"); break;	
	case 0x2D: if (Shift) console.print("X"); else console.print("x"); break;	
	case 0x2E: if (Shift) console.print("C"); else console.print("c"); break;	
	case 0x2F: if (Shift) console.print("V"); else console.print("v"); break;	
	case 0x30: if (Shift) console.print("B"); else console.print("b"); break;	
	case 0x31: if (Shift) console.print("N"); else console.print("n"); break;	
	case 0x32: if (Shift) console.print("M"); else console.print("m"); break;	
	case 0x33: if (Shift) console.print("<"); else console.print(","); break;	
	case 0x34: if (Shift) console.print(">"); else console.print("."); break;	
	case 0x35: if (Shift) console.print("?"); else console.print("\/"); break;	

	case 0x3B: console.print("F1"); break;	
	case 0x3C: console.print("F2"); break;	
	case 0x3D: console.print("F3"); break;	
	case 0x3E: console.print("F4"); break;	
	case 0x3F: console.print("F5"); break;	
	case 0x40: console.print("F6"); break;	
	case 0x41: console.print("F7"); break;	
	case 0x42: console.print("F8"); break;	
	case 0x43: console.print("F9"); break;	
	case 0x44: console.print("F10"); break;	
	case 0x57: console.print("F11"); break;	
	case 0x58: console.print("F12"); break;

	case 0x3A: console.print("CAPSLOCK"); break;	
	case 0x01: console.print("ESC"); break;	
	case 0x29: if (Shift) console.print("~"); else console.print("\`"); break;	
	case 0x1D: console.print("CTRL"); break;	
	case 0x5B: console.print("WIN"); break;	
	case 0x38: console.print("ALT"); break;	
	case 0x5D: console.print("APPS"); break;	
	case 0x0F: console.print("TAB"); break;	
	case 0x0E: console.print("DELETE"); break;

	case 0x1C: console.print("\n"); break;
	case 0x39: console.print(" "); break;
	case 0x2A: case 0x36: Shift = true; break;
	case 0xAA: case 0xB6: Shift = false; break;
	default:
		if (key < 0x80)
		{
			char* mes = "\nKEYBOARD 0x00";
			char* hex = "0123456789ABCDEF";
			mes[12] = hex[(key >> 4) & 0x0F];
			mes[13] = hex[key & 0x0F];
			console.print(mes);
		}
		break;
	}
	return esp;
}
