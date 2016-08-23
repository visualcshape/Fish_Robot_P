##Control Fish Command Pattern

####Universal command Pattern
```
aa xx xx fc
```
`aa`: Head byte.
`xx`: Command_1 byte.
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
#####Disable a Joint

```
aa 9(Fish ID(1 ~ 8)) 6(Joint 1: 7, Joint 2: 3, Joint 3: 1, Joint4: 0) fc
````
__Example__ 
To disable joint#1 on fish ID#1, send these data...
```
aa 91 67 fc
```
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
