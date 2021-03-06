﻿#FishRobot Control Example Program

###Requirements
These code can only be run on Windows System since it uses the serial port library which bounds to Windows.

-----
###Compilation
1. Open .sln using VS.
2. Compile it.

-----
###Usage
1. Change COM port name string at constructor of `FishRobotSerialPort`, default is COM4
	* If your COM port name of the WPA300C is *COM3*, you can change
	```C++
	FishRobotSerialPort serialPort(L"COM4");
	```
	to
	```C++
	FishRobotSerialPort serialPort(L"COM3");
	```
2. If there isn't any presnted message on the screen that means you opened serial port successfully.
3. Now support these command, you can control the fish by input specific command.
	* Speed
	Example(Set fish speed to level 15 (the highest speed))
	```
	fishRobot.setSpeed(FishSpeed::LEVEL_14)
	```
	* Direction
	Example (Set fish direction to middle)
	```
	fishRobot.setDirection(FishDirections::MID)
	```
----------------

#Robot Fish Control Commandss

####Universal command Pattern
```
aa 9x yy fc
```
`aa`: Head byte.
`9x`: Fish ID, 1 <= x <= 8
`xx`: Command_2 byte.
`fc`: Final byte.

-----------
#####Direction Command Pattern:
```
aa 9(Fish ID F(1 ~ 8)) e(Direction Left(0~6)Mid(7)Right(8~e)) fc
```
__Example__
To adjsut the direction to the most left on fish ID#1, send these data...
```
aa 91 e0 fc
```

--------------
#####Speed Commadn Pattern:
```
aa 9(Fish ID F(1 ~ 8)) d(Speed (0~f)) fc
```
__Example__
To speed up the swimming speed to level 15 on fish ID#1, send these data...
```
aa 91 df fc
```

---------------
#####Enable a Joint

Joint1_enabled = `0x8`

Joint2_enabled = `0x4`

Joint3_enabled = `0x2`

Joint4_enabled = `0x1`

For example, if you want to enable joint #1 and #3 ( on the other hand, disable joint #2 and #4)...

```
calculated_reault = 0x08 OR 0x02
aa 9(Fish ID(1 ~ 8)) 6(calculated_result) fc
````

-----------------
#####Depth Control
Range(Decimal): 11 ~ 150 (cm)
Depth: 11cm = 4b, 12cm = 4c, 13cm = 4d ..., 150cm = d6

```
aa 9(Fish ID(1~8)) (4b(DEC: 75) ~ d6(DEC 214)) fc
```
__Example__:
To control depth at 149 cm on fish ID#1, send these data...
```
aa 91 d5 fc
```
