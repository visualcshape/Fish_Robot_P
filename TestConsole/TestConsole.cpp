// TestConsole.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "FishRobot.h"
#include "Utility.h"

int main()
{
	char commandName[128];
	int commandArgs;
	RFTransmittorSerialPort serialPort(L"COM4");

	FishRobot fish1(1, &serialPort);
	fish1.connectFish();
	while (scanf_s("%s %d", commandName, (unsigned)_countof(commandName), &commandArgs) == 2) {
		Utility::toLowerCase(commandName);
		if (strcmp(commandName, "speed") == 0) {
			fish1.setSpeed((FishSpeed)commandArgs);
		}
		else if (strcmp(commandName, "direction") == 0){
			fish1.setDirection((FishDirections)commandArgs);
		}
		else {
			break;
		}
	}

	//printf("%d", sizeof(unsigned long));
	//system("pause");
    return 0;
}

