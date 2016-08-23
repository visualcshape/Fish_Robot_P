#pragma once
//An abstract serial port class

class AbstractSerialPort {
protected:
	
public:
	virtual int read(char*, unsigned int) = 0;

	virtual bool write(char*, unsigned int) = 0;
};