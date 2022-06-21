#pragma once

class Driver
{
public:
	Driver();
	~Driver();
	virtual void Activate();
	virtual void Deactivate();
	virtual int Reset();
};

class DriverManager
{
private:
	Driver* drivers[255];
	int driverNumbers;

public:
	DriverManager();
	~DriverManager();
	void AddDriver(Driver*);
	void ActivateAll();
};
