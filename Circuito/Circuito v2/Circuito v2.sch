EESchema Schematic File Version 4
LIBS:Circuito v2-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Sensor_Proximity:CNY70 U1
U 1 1 5BBED548
P 3000 1750
F 0 "U1" H 3000 2067 50  0000 C CNN
F 1 "CNY70" H 3000 1976 50  0000 C CNN
F 2 "Housings_DIP:DIP-4_W7.62mm_LongPads" H 3000 1550 50  0001 C CNN
F 3 "https://www.vishay.com/docs/83751/cny70.pdf" H 3000 1850 50  0001 C CNN
	1    3000 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 5BBED5C7
P 2600 1400
F 0 "R1" H 2668 1446 50  0000 L CNN
F 1 "220" H 2668 1355 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2640 1390 50  0001 C CNN
F 3 "~" H 2600 1400 50  0001 C CNN
	1    2600 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 5BBED61F
P 3400 2150
F 0 "R2" H 3332 2104 50  0000 R CNN
F 1 "39K" H 3332 2195 50  0000 R CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3440 2140 50  0001 C CNN
F 3 "~" H 3400 2150 50  0001 C CNN
	1    3400 2150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5BBED6B2
P 2650 2050
F 0 "#PWR02" H 2650 1800 50  0001 C CNN
F 1 "GND" H 2655 1877 50  0000 C CNN
F 2 "" H 2650 2050 50  0001 C CNN
F 3 "" H 2650 2050 50  0001 C CNN
	1    2650 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 2050 2650 1850
Wire Wire Line
	2650 1850 2700 1850
Wire Wire Line
	2700 1650 2600 1650
Wire Wire Line
	2600 1650 2600 1550
$Comp
L power:+5V #PWR01
U 1 1 5BBED717
P 2600 1250
F 0 "#PWR01" H 2600 1100 50  0001 C CNN
F 1 "+5V" H 2615 1423 50  0000 C CNN
F 2 "" H 2600 1250 50  0001 C CNN
F 3 "" H 2600 1250 50  0001 C CNN
	1    2600 1250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5BBED73D
P 3300 1450
F 0 "#PWR03" H 3300 1300 50  0001 C CNN
F 1 "+5V" H 3315 1623 50  0000 C CNN
F 2 "" H 3300 1450 50  0001 C CNN
F 3 "" H 3300 1450 50  0001 C CNN
	1    3300 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 1450 3300 1650
$Comp
L power:GND #PWR04
U 1 1 5BBED771
P 3400 2300
F 0 "#PWR04" H 3400 2050 50  0001 C CNN
F 1 "GND" H 3405 2127 50  0000 C CNN
F 2 "" H 3400 2300 50  0001 C CNN
F 3 "" H 3400 2300 50  0001 C CNN
	1    3400 2300
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM324 U2
U 1 1 5BBED7C3
P 4200 1950
F 0 "U2" H 4200 2317 50  0000 C CNN
F 1 "LM324" H 4200 2226 50  0000 C CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_LongPads" H 4150 2050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 4250 2150 50  0001 C CNN
	1    4200 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2050 3850 2050
Wire Wire Line
	3850 2050 3850 2300
Wire Wire Line
	3850 2300 4550 2300
Wire Wire Line
	4550 2300 4550 1950
Wire Wire Line
	4550 1950 4500 1950
Wire Wire Line
	3300 1850 3400 1850
Wire Wire Line
	3400 2000 3400 1850
Connection ~ 3400 1850
Wire Wire Line
	3400 1850 3900 1850
$Comp
L Amplifier_Operational:LM324 U2
U 2 1 5BBEDA0C
P 5400 1850
F 0 "U2" H 5400 1483 50  0000 C CNN
F 1 "LM324" H 5400 1574 50  0000 C CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_LongPads" H 5350 1950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 5450 2050 50  0001 C CNN
	2    5400 1850
	1    0    0    1   
$EndComp
$Comp
L Device:R_US R5
U 1 1 5BBEDC58
P 4800 1950
F 0 "R5" V 5005 1950 50  0000 C CNN
F 1 "1K6" V 4914 1950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4840 1940 50  0001 C CNN
F 3 "~" H 4800 1950 50  0001 C CNN
	1    4800 1950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4550 1950 4650 1950
Connection ~ 4550 1950
Wire Wire Line
	4950 1950 5050 1950
$Comp
L Device:R_US R6
U 1 1 5BBEDE1A
P 5450 2250
F 0 "R6" V 5655 2250 50  0000 C CNN
F 1 "10K" V 5564 2250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5490 2240 50  0001 C CNN
F 3 "~" H 5450 2250 50  0001 C CNN
	1    5450 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R3
U 1 1 5BBEDE4E
P 4750 1000
F 0 "R3" H 4818 1046 50  0000 L CNN
F 1 "47K" H 4818 955 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4790 990 50  0001 C CNN
F 3 "~" H 4750 1000 50  0001 C CNN
	1    4750 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R4
U 1 1 5BBEDE9F
P 4750 1450
F 0 "R4" H 4818 1496 50  0000 L CNN
F 1 "10K" H 4818 1405 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4790 1440 50  0001 C CNN
F 3 "~" H 4750 1450 50  0001 C CNN
	1    4750 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1300 4750 1200
Wire Wire Line
	5300 2250 5050 2250
Wire Wire Line
	5050 2250 5050 1950
Connection ~ 5050 1950
Wire Wire Line
	5050 1950 5100 1950
Wire Wire Line
	5700 1850 5700 2000
Wire Wire Line
	5700 2250 5600 2250
$Comp
L power:GND #PWR08
U 1 1 5BBEE1F8
P 4750 1600
F 0 "#PWR08" H 4750 1350 50  0001 C CNN
F 1 "GND" H 4755 1427 50  0000 C CNN
F 2 "" H 4750 1600 50  0001 C CNN
F 3 "" H 4750 1600 50  0001 C CNN
	1    4750 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5BBEE215
P 4750 850
F 0 "#PWR07" H 4750 700 50  0001 C CNN
F 1 "+5V" H 4765 1023 50  0000 C CNN
F 2 "" H 4750 850 50  0001 C CNN
F 3 "" H 4750 850 50  0001 C CNN
	1    4750 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1200 5100 1200
Wire Wire Line
	5100 1200 5100 1750
Connection ~ 4750 1200
Wire Wire Line
	4750 1200 4750 1150
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5BBEE44B
P 6200 2000
F 0 "J1" H 6280 2042 50  0000 L CNN
F 1 "SENSOR1" H 6280 1951 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-3_P5.08mm" H 6200 2000 50  0001 C CNN
F 3 "~" H 6200 2000 50  0001 C CNN
	1    6200 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5BBEE50B
P 5950 2200
F 0 "#PWR010" H 5950 1950 50  0001 C CNN
F 1 "GND" H 5955 2027 50  0000 C CNN
F 2 "" H 5950 2200 50  0001 C CNN
F 3 "" H 5950 2200 50  0001 C CNN
	1    5950 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2100 5950 2100
Wire Wire Line
	5950 2100 5950 2200
$Comp
L power:+5V #PWR09
U 1 1 5BBEE746
P 5950 1850
F 0 "#PWR09" H 5950 1700 50  0001 C CNN
F 1 "+5V" H 5965 2023 50  0000 C CNN
F 2 "" H 5950 1850 50  0001 C CNN
F 3 "" H 5950 1850 50  0001 C CNN
	1    5950 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 1850 5950 1900
Wire Wire Line
	5950 1900 6000 1900
Wire Wire Line
	5700 2000 6000 2000
Connection ~ 5700 2000
Wire Wire Line
	5700 2000 5700 2250
$Comp
L Amplifier_Operational:LM324 U2
U 5 1 5BBEEE81
P 4100 1000
F 0 "U2" H 4058 1046 50  0000 L CNN
F 1 "LM324" H 4058 955 50  0000 L CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_LongPads" H 4050 1100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2902-n.pdf" H 4150 1200 50  0001 C CNN
	5    4100 1000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5BBEEEFB
P 4000 700
F 0 "#PWR05" H 4000 550 50  0001 C CNN
F 1 "+5V" H 4015 873 50  0000 C CNN
F 2 "" H 4000 700 50  0001 C CNN
F 3 "" H 4000 700 50  0001 C CNN
	1    4000 700 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5BBEEF1C
P 4000 1300
F 0 "#PWR06" H 4000 1050 50  0001 C CNN
F 1 "GND" H 4005 1127 50  0000 C CNN
F 2 "" H 4000 1300 50  0001 C CNN
F 3 "" H 4000 1300 50  0001 C CNN
	1    4000 1300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
