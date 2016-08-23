// TestConsole.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "FishRobotSerialPort.h"

int main()
{

	FishRobotSerialPort* serialPort = new FishRobotSerialPort(L"COM4");

	serialPort->open();

	char input[8];
	while (scanf_s("%7s", input, (unsigned)_countof(input)) == 1) {
		if (strcmp(input, "w")==0) {
			char byte_arr[8] = { 0xaa,0x91,0xee,0xfc };
			serialPort->write(byte_arr, 4);
		}
		else {
			break;
		}
	}

	//printf("%d", sizeof(unsigned long));
	system("pause");
    return 0;
}

