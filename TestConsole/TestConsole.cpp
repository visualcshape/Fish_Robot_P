// TestConsole.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "FishRobotSerialPort.h"

int main()
{
	//SerialPort* serialPort = new SerialPort(L"COM4");
	//bool isSuccessOpen = serialPort->open();

	FishRobotSerialPort* serialPort = new FishRobotSerialPort(L"COM4");

	serialPort->open();

	//printf("%d", sizeof(unsigned long));
	system("pause");
    return 0;
}

