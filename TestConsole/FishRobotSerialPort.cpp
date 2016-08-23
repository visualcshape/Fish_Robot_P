#include "FishRobotSerialPort.h"
#include "SerialPortConstants.h"
#include <ntddser.h>
//Referenced from http://playground.arduino.cc/Interfacing/CPPWindows

void FishRobotSerialPort::configuration()
{
	//Declares
	DWORD dwOutput;
	//Set up some param before set serial params
	//queue size
	SERIAL_QUEUE_SIZE serialQueueSize;
	serialQueueSize.InSize = SERIAL_QUEUE_SIZE_IN;
	serialQueueSize.OutSize = SERIAL_QUEUE_SIZE_OUT;

	//FIXED VALUE
	SERIAL_TIMEOUTS serialTimeouts;
	serialTimeouts.ReadIntervalTimeout = ULONG_MAX;
	serialTimeouts.ReadTotalTimeoutMultiplier = 0;
	serialTimeouts.ReadTotalTimeoutConstant = 0;
	serialTimeouts.WriteTotalTimeoutMultiplier = 0;
	serialTimeouts.WriteTotalTimeoutConstant = SERIAL_TIMEOUT_WRITE_TOTAL_TIMEOUT_CONSTANT;

	//wait mask
	ULONG waitMask = 0x81;

	//Purge mask
	ULONG purgeMask = 0x0f;

	//Baud rate
	SERIAL_BAUD_RATE baudRate;
	baudRate.BaudRate = 9600;

	//Line control
	SERIAL_LINE_CONTROL lineControl;
	lineControl.Parity = NO_PARITY;
	lineControl.StopBits = STOP_BIT_1;
	lineControl.WordLength = 8;

	//Char
	SERIAL_CHARS chars;
	chars.EofChar = 0x00;
	chars.ErrorChar = 0x00;
	chars.BreakChar = 0x00;
	chars.EventChar = 0x00;
	chars.XonChar = 0x11;
	chars.XoffChar = 0x13;

	//Handflow
	SERIAL_HANDFLOW handflow;
	handflow.ControlHandShake = 0;
	handflow.FlowReplace = 0;
	handflow.XonLimit = 32768;
	handflow.XoffLimit = 8192;

	//These commands have no return data.
	DeviceIoControl(this->_comHandle, IOCTL_SERIAL_SET_QUEUE_SIZE, &serialQueueSize, sizeof(serialQueueSize), NULL, NULL, &dwOutput, NULL);
	DeviceIoControl(this->_comHandle, IOCTL_SERIAL_SET_TIMEOUTS, &serialTimeouts, sizeof(serialTimeouts), NULL, NULL, &dwOutput, NULL);
	//0f purge
	DeviceIoControl(this->_comHandle, IOCTL_SERIAL_PURGE, &purgeMask, sizeof(purgeMask), NULL, NULL, &dwOutput, NULL);
	DeviceIoControl(this->_comHandle, IOCTL_SERIAL_SET_WAIT_MASK, &waitMask, sizeof(waitMask), NULL, NULL, &dwOutput, NULL);
	DeviceIoControl(this->_comHandle, IOCTL_SERIAL_SET_BAUD_RATE, &baudRate, sizeof(baudRate), NULL, NULL, &dwOutput, NULL);
	DeviceIoControl(this->_comHandle, IOCTL_SERIAL_CLR_RTS, NULL, NULL, NULL, NULL, &dwOutput, NULL);
	DeviceIoControl(this->_comHandle, IOCTL_SERIAL_CLR_DTR, NULL, NULL, NULL, NULL, &dwOutput, NULL);
	DeviceIoControl(this->_comHandle, IOCTL_SERIAL_SET_LINE_CONTROL, &lineControl, sizeof(lineControl), NULL, NULL, &dwOutput, NULL);
	DeviceIoControl(this->_comHandle, IOCTL_SERIAL_SET_CHARS, &chars, sizeof(chars), NULL, NULL, &dwOutput, NULL);
	DeviceIoControl(this->_comHandle, IOCTL_SERIAL_SET_HANDFLOW, &handflow, sizeof(handflow), NULL, NULL, &dwOutput, NULL);
}

FishRobotSerialPort::FishRobotSerialPort(LPCWSTR portName):_portName(portName),_isOpen(false)
{
	
}

FishRobotSerialPort::~FishRobotSerialPort()
{
	this->close();
}

bool FishRobotSerialPort::open()
{
	this->_comHandle = CreateFile(this->_portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!this->_isOpen) {
		if (this->_comHandle == INVALID_HANDLE_VALUE) {
			printf("An error was occurred. Error code is: %u\n", GetLastError());
			return false;
		}
		this->configuration();
		this->_isOpen = true;
	}
	return true;
}

bool FishRobotSerialPort::write(char * buffer, unsigned int nbChar)
{
	DWORD byteSend;

	if (!this->_isOpen)
		return false;

	if (!WriteFile(this->_comHandle, buffer, nbChar, &byteSend, NULL)) {

	}

	return true;
}

int FishRobotSerialPort::read(char * buffer, unsigned int nbChar)
{
	return 0;
}

bool FishRobotSerialPort::close()
{
	if (this->_isOpen) {
		this->_isOpen = false;
		ULONG closeWaitMask = 0x00;
		DWORD dwOutput;
		DeviceIoControl(this->_comHandle, IOCTL_SERIAL_SET_WAIT_MASK, &closeWaitMask, sizeof(closeWaitMask), NULL, NULL, &dwOutput, NULL);
		CloseHandle(this->_comHandle);
	}

	//return stub here for future use
	return false;
}

bool FishRobotSerialPort::isPortOpen()
{
	return this->_isOpen;
}
