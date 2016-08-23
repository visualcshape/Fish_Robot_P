#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "AbstractSerialPort.h"
class FishRobotSerialPort{
private:
	HANDLE _comHandle;

	LPCWSTR _portName;

	bool _isOpen;
	
	void configuration();
public:
	FishRobotSerialPort(LPCWSTR portName);

	virtual ~FishRobotSerialPort();

	bool open();

	///<summary> Writes 4(Default) bytes command to serial port 
	///<para name="buffer">4 bytes Command buffer.</para>
	///<para name="nbChar">Size of buffer, default is 4. </para>
	///</summary>
	bool write(char* buffer, unsigned int nbChar = 4);

	///<summary> Stub function </summary>
	int read(char* buffer, unsigned int nbChar);

	///<summary>Close a port</summary>
	bool close();

	///<summary>
	///<returns>Port open status</returns>
	///</summary>
	bool isPortOpen();
};

#endif