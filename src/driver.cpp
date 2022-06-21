#include "../include/driver.h"

Driver::Driver()
{

}

Driver::~Driver()
{

}

void Driver::Activate()
{

}

int Driver::Reset()
{
	return 0;
}

void Driver::Deactivate()
{

}

DriverManager::DriverManager()
{
	driverNumbers = 0;
}

DriverManager::~DriverManager()
{

}

void DriverManager::AddDriver(Driver* driver)
{
	drivers[driverNumbers] = driver;
	driverNumbers++;
}

void DriverManager::ActivateAll()
{
	for (int i = 0; i < driverNumbers; i++)
	{
		drivers[i]->Activate();
	}
}
