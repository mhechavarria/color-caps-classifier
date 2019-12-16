EESchema Schematic File Version 4
LIBS:JONICA-cache
EELAYER 26 0
EELAYER END
$Descr A3 16535 11693
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
L Regulator_Linear:L7805 U1
U 1 1 5BBD456B
P 4850 1650
F 0 "U1" H 4850 1892 50  0000 C CNN
F 1 "L7805" H 4850 1801 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 4875 1500 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 4850 1600 50  0001 C CNN
	1    4850 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR022
U 1 1 5BBD48CF
P 5450 1650
F 0 "#PWR022" H 5450 1500 50  0001 C CNN
F 1 "+5V" H 5465 1823 50  0000 C CNN
F 2 "" H 5450 1650 50  0001 C CNN
F 3 "" H 5450 1650 50  0001 C CNN
	1    5450 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1650 5300 1650
$Comp
L power:GND #PWR019
U 1 1 5BBD62A1
P 4850 2100
F 0 "#PWR019" H 4850 1850 50  0001 C CNN
F 1 "GND" H 4855 1927 50  0000 C CNN
F 2 "" H 4850 2100 50  0001 C CNN
F 3 "" H 4850 2100 50  0001 C CNN
	1    4850 2100
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR018
U 1 1 5BBD631E
P 4100 1650
F 0 "#PWR018" H 4100 1500 50  0001 C CNN
F 1 "+12V" H 4115 1823 50  0000 C CNN
F 2 "" H 4100 1650 50  0001 C CNN
F 3 "" H 4100 1650 50  0001 C CNN
	1    4100 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 1650 4300 1650
$Comp
L Device:C C2
U 1 1 5BBDB251
P 5300 1850
F 0 "C2" H 5415 1896 50  0000 L CNN
F 1 "100nF" H 5415 1805 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 5338 1700 50  0001 C CNN
F 3 "~" H 5300 1850 50  0001 C CNN
	1    5300 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2100 4850 2050
Wire Wire Line
	5300 2050 5300 2000
Wire Wire Line
	5300 2050 4850 2050
Connection ~ 4850 2050
Wire Wire Line
	4850 2050 4850 1950
Wire Wire Line
	5300 1700 5300 1650
Connection ~ 5300 1650
Wire Wire Line
	5300 1650 5150 1650
$Comp
L Device:C C1
U 1 1 5BBE7027
P 4300 1850
F 0 "C1" H 4415 1896 50  0000 L CNN
F 1 "330nF" H 4415 1805 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 4338 1700 50  0001 C CNN
F 3 "~" H 4300 1850 50  0001 C CNN
	1    4300 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1700 4300 1650
Connection ~ 4300 1650
Wire Wire Line
	4300 1650 4550 1650
Wire Wire Line
	4300 2000 4300 2050
Wire Wire Line
	4300 2050 4850 2050
$Comp
L MCU_Module:Arduino_UNO_R3 A3
U 1 1 5BCA58C6
P 2450 4000
F 0 "A3" H 2450 5178 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 2450 5087 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 2600 2950 50  0001 L CNN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 2250 5050 50  0001 C CNN
	1    2450 4000
	-1   0    0    -1  
$EndComp
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A1
U 1 1 5BCE6D7F
P 1700 6200
F 0 "A1" H 1750 7078 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 1750 6987 50  0000 C CNN
F 2 "Modules:Pololu_Breakout-16_15.2x20.3mm" H 1975 5450 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 1800 5900 50  0001 C CNN
	1    1700 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 3600 3200 3600
Wire Wire Line
	2950 3700 3200 3700
Text Label 3200 3800 0    50   ~ 0
M2_STEP
Text Label 3200 3900 0    50   ~ 0
M2_DIR
Text Label 3200 4100 0    50   ~ 0
M3_DIR
Text Label 3200 4000 0    50   ~ 0
M3_STEP
Text Label 3200 4600 0    50   ~ 0
M0_STEP
Text Label 3200 4700 0    50   ~ 0
M0_DIR
Wire Wire Line
	2950 4600 3200 4600
Wire Wire Line
	3200 4700 2950 4700
$Comp
L power:GND #PWR02
U 1 1 5BBCEED2
P 1700 7000
F 0 "#PWR02" H 1700 6750 50  0001 C CNN
F 1 "GND" H 1705 6827 50  0000 C CNN
F 2 "" H 1700 7000 50  0001 C CNN
F 3 "" H 1700 7000 50  0001 C CNN
	1    1700 7000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5BBCEF51
P 1900 7000
F 0 "#PWR06" H 1900 6750 50  0001 C CNN
F 1 "GND" H 1905 6827 50  0000 C CNN
F 2 "" H 1900 7000 50  0001 C CNN
F 3 "" H 1900 7000 50  0001 C CNN
	1    1900 7000
	1    0    0    -1  
$EndComp
Text Label 1250 6200 2    50   ~ 0
M1_STEP
Text Label 1200 6300 2    50   ~ 0
M1_DIR
Wire Wire Line
	1250 6200 1300 6200
Wire Wire Line
	1200 6300 1300 6300
$Comp
L power:+5V #PWR01
U 1 1 5BC4528C
P 1700 5450
F 0 "#PWR01" H 1700 5300 50  0001 C CNN
F 1 "+5V" H 1715 5623 50  0000 C CNN
F 2 "" H 1700 5450 50  0001 C CNN
F 3 "" H 1700 5450 50  0001 C CNN
	1    1700 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 5450 1700 5500
$Comp
L power:+12V #PWR05
U 1 1 5BC4F99E
P 1900 5450
F 0 "#PWR05" H 1900 5300 50  0001 C CNN
F 1 "+12V" H 1915 5623 50  0000 C CNN
F 2 "" H 1900 5450 50  0001 C CNN
F 3 "" H 1900 5450 50  0001 C CNN
	1    1900 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 5450 1900 5500
Wire Wire Line
	1300 5800 1250 5800
Wire Wire Line
	1250 5800 1250 5900
Wire Wire Line
	1250 5900 1300 5900
Text Label 2250 6100 0    50   ~ 0
M1_1A
Text Label 2250 6200 0    50   ~ 0
M1_1B
Text Label 2250 6300 0    50   ~ 0
M1_2A
Text Label 2250 6400 0    50   ~ 0
M1_2B
Wire Wire Line
	2200 6100 2250 6100
Wire Wire Line
	2200 6200 2250 6200
Wire Wire Line
	2200 6300 2250 6300
Wire Wire Line
	2200 6400 2250 6400
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A4
U 1 1 5BCB91E0
P 3350 6200
F 0 "A4" H 3400 7078 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 3400 6987 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 3625 5450 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 3450 5900 50  0001 C CNN
	1    3350 6200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5BCB91F4
P 3350 7000
F 0 "#PWR011" H 3350 6750 50  0001 C CNN
F 1 "GND" H 3355 6827 50  0000 C CNN
F 2 "" H 3350 7000 50  0001 C CNN
F 3 "" H 3350 7000 50  0001 C CNN
	1    3350 7000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5BCB91FA
P 3550 7000
F 0 "#PWR015" H 3550 6750 50  0001 C CNN
F 1 "GND" H 3555 6827 50  0000 C CNN
F 2 "" H 3550 7000 50  0001 C CNN
F 3 "" H 3550 7000 50  0001 C CNN
	1    3550 7000
	1    0    0    -1  
$EndComp
Text Label 2900 6200 2    50   ~ 0
M2_STEP
Text Label 2850 6300 2    50   ~ 0
M2_DIR
Wire Wire Line
	2900 6200 2950 6200
Wire Wire Line
	2850 6300 2950 6300
$Comp
L power:+5V #PWR010
U 1 1 5BCB9204
P 3350 5450
F 0 "#PWR010" H 3350 5300 50  0001 C CNN
F 1 "+5V" H 3365 5623 50  0000 C CNN
F 2 "" H 3350 5450 50  0001 C CNN
F 3 "" H 3350 5450 50  0001 C CNN
	1    3350 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 5450 3350 5500
$Comp
L power:+12V #PWR014
U 1 1 5BCB920B
P 3550 5450
F 0 "#PWR014" H 3550 5300 50  0001 C CNN
F 1 "+12V" H 3565 5623 50  0000 C CNN
F 2 "" H 3550 5450 50  0001 C CNN
F 3 "" H 3550 5450 50  0001 C CNN
	1    3550 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 5450 3550 5500
Wire Wire Line
	2950 5800 2900 5800
Wire Wire Line
	2900 5800 2900 5900
Wire Wire Line
	2900 5900 2950 5900
Text Label 3900 6100 0    50   ~ 0
M2_1A
Text Label 3900 6200 0    50   ~ 0
M2_1B
Text Label 3900 6300 0    50   ~ 0
M2_2A
Text Label 3900 6400 0    50   ~ 0
M2_2B
Wire Wire Line
	3850 6100 3900 6100
Wire Wire Line
	3850 6200 3900 6200
Wire Wire Line
	3850 6300 3900 6300
Wire Wire Line
	3850 6400 3900 6400
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A2
U 1 1 5BCC6A2E
P 1700 8200
F 0 "A2" H 1750 9078 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 1750 8987 50  0000 C CNN
F 2 "Modules:Pololu_Breakout-16_15.2x20.3mm" H 1975 7450 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 1800 7900 50  0001 C CNN
	1    1700 8200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5BCC6A42
P 1700 9000
F 0 "#PWR04" H 1700 8750 50  0001 C CNN
F 1 "GND" H 1705 8827 50  0000 C CNN
F 2 "" H 1700 9000 50  0001 C CNN
F 3 "" H 1700 9000 50  0001 C CNN
	1    1700 9000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5BCC6A48
P 1900 9000
F 0 "#PWR08" H 1900 8750 50  0001 C CNN
F 1 "GND" H 1905 8827 50  0000 C CNN
F 2 "" H 1900 9000 50  0001 C CNN
F 3 "" H 1900 9000 50  0001 C CNN
	1    1900 9000
	1    0    0    -1  
$EndComp
Text Label 1250 8200 2    50   ~ 0
M3_STEP
Text Label 1200 8300 2    50   ~ 0
M3_DIR
Wire Wire Line
	1250 8200 1300 8200
Wire Wire Line
	1200 8300 1300 8300
$Comp
L power:+5V #PWR03
U 1 1 5BCC6A52
P 1700 7450
F 0 "#PWR03" H 1700 7300 50  0001 C CNN
F 1 "+5V" H 1715 7623 50  0000 C CNN
F 2 "" H 1700 7450 50  0001 C CNN
F 3 "" H 1700 7450 50  0001 C CNN
	1    1700 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 7450 1700 7500
$Comp
L power:+12V #PWR07
U 1 1 5BCC6A59
P 1900 7450
F 0 "#PWR07" H 1900 7300 50  0001 C CNN
F 1 "+12V" H 1915 7623 50  0000 C CNN
F 2 "" H 1900 7450 50  0001 C CNN
F 3 "" H 1900 7450 50  0001 C CNN
	1    1900 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 7450 1900 7500
Wire Wire Line
	1300 7800 1250 7800
Wire Wire Line
	1250 7800 1250 7900
Wire Wire Line
	1250 7900 1300 7900
Text Label 2250 8100 0    50   ~ 0
M3_1A
Text Label 2250 8200 0    50   ~ 0
M3_1B
Text Label 2250 8300 0    50   ~ 0
M3_2A
Text Label 2250 8400 0    50   ~ 0
M3_2B
Wire Wire Line
	2200 8100 2250 8100
Wire Wire Line
	2200 8200 2250 8200
Wire Wire Line
	2200 8300 2250 8300
Wire Wire Line
	2200 8400 2250 8400
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A5
U 1 1 5BD07170
P 3350 8200
F 0 "A5" H 3400 9078 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 3400 8987 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 3625 7450 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 3450 7900 50  0001 C CNN
	1    3350 8200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5BD07184
P 3350 9000
F 0 "#PWR013" H 3350 8750 50  0001 C CNN
F 1 "GND" H 3355 8827 50  0000 C CNN
F 2 "" H 3350 9000 50  0001 C CNN
F 3 "" H 3350 9000 50  0001 C CNN
	1    3350 9000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5BD0718A
P 3550 9000
F 0 "#PWR017" H 3550 8750 50  0001 C CNN
F 1 "GND" H 3555 8827 50  0000 C CNN
F 2 "" H 3550 9000 50  0001 C CNN
F 3 "" H 3550 9000 50  0001 C CNN
	1    3550 9000
	1    0    0    -1  
$EndComp
Text Label 2900 8200 2    50   ~ 0
M0_STEP
Text Label 2850 8300 2    50   ~ 0
M0_DIR
Wire Wire Line
	2900 8200 2950 8200
Wire Wire Line
	2850 8300 2950 8300
$Comp
L power:+5V #PWR012
U 1 1 5BD07194
P 3350 7450
F 0 "#PWR012" H 3350 7300 50  0001 C CNN
F 1 "+5V" H 3365 7623 50  0000 C CNN
F 2 "" H 3350 7450 50  0001 C CNN
F 3 "" H 3350 7450 50  0001 C CNN
	1    3350 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 7450 3350 7500
$Comp
L power:+12V #PWR016
U 1 1 5BD0719B
P 3550 7450
F 0 "#PWR016" H 3550 7300 50  0001 C CNN
F 1 "+12V" H 3565 7623 50  0000 C CNN
F 2 "" H 3550 7450 50  0001 C CNN
F 3 "" H 3550 7450 50  0001 C CNN
	1    3550 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 7450 3550 7500
Wire Wire Line
	2950 7800 2900 7800
Wire Wire Line
	2900 7800 2900 7900
Wire Wire Line
	2900 7900 2950 7900
Text Label 3900 8100 0    50   ~ 0
M0_1A
Text Label 3900 8200 0    50   ~ 0
M0_1B
Text Label 3900 8300 0    50   ~ 0
M0_2A
Text Label 3900 8400 0    50   ~ 0
M0_2B
Wire Wire Line
	3850 8100 3900 8100
Wire Wire Line
	3850 8200 3900 8200
Wire Wire Line
	3850 8300 3900 8300
Wire Wire Line
	3850 8400 3900 8400
$Comp
L power:GND #PWR09
U 1 1 5BD59190
P 2450 5150
F 0 "#PWR09" H 2450 4900 50  0001 C CNN
F 1 "GND" H 2455 4977 50  0000 C CNN
F 2 "" H 2450 5150 50  0001 C CNN
F 3 "" H 2450 5150 50  0001 C CNN
	1    2450 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 5100 2350 5150
Wire Wire Line
	2350 5150 2450 5150
Wire Wire Line
	2450 5100 2450 5150
Connection ~ 2450 5150
Wire Wire Line
	2550 5100 2550 5150
Wire Wire Line
	2550 5150 2450 5150
Text Label 2950 8100 2    50   ~ 0
ENA0-POLOLU
Text Label 1300 6100 2    50   ~ 0
ENA1
Text Label 2950 6100 2    50   ~ 0
ENA2
Text Label 1300 8100 2    50   ~ 0
ENA3
NoConn ~ 1950 3400
NoConn ~ 1950 3600
NoConn ~ 1950 3800
NoConn ~ 1950 4800
NoConn ~ 1950 4700
NoConn ~ 1950 4500
Text Label 3200 3400 0    50   ~ 0
RX
Text Label 3200 3500 0    50   ~ 0
TX
Wire Wire Line
	2950 3400 3200 3400
Wire Wire Line
	3200 3500 2950 3500
Text Label 3900 3350 2    50   ~ 0
RX
Text Label 3900 3450 2    50   ~ 0
TX
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5BF0BC96
P 4250 3350
F 0 "J1" H 4330 3342 50  0000 L CNN
F 1 "UART" H 4330 3251 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-2_P5.08mm" H 4250 3350 50  0001 C CNN
F 3 "~" H 4250 3350 50  0001 C CNN
	1    4250 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3350 4050 3350
Wire Wire Line
	3900 3450 4050 3450
$Comp
L Connector:Screw_Terminal_01x04 J3
U 1 1 5BBD0CA4
P 5200 4350
F 0 "J3" H 5280 4342 50  0000 L CNN
F 1 "M1" H 5280 4251 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-4_P5.08mm" H 5200 4350 50  0001 C CNN
F 3 "~" H 5200 4350 50  0001 C CNN
	1    5200 4350
	1    0    0    -1  
$EndComp
Text Label 4850 4250 2    50   ~ 0
M1_1A
Text Label 4850 4350 2    50   ~ 0
M1_1B
Text Label 4850 4450 2    50   ~ 0
M1_2A
Text Label 4850 4550 2    50   ~ 0
M1_2B
Wire Wire Line
	4850 4250 5000 4250
Wire Wire Line
	5000 4350 4850 4350
Wire Wire Line
	4850 4450 5000 4450
Wire Wire Line
	5000 4550 4850 4550
$Comp
L Connector:Screw_Terminal_01x04 J4
U 1 1 5BC18F02
P 5200 4800
F 0 "J4" H 5280 4792 50  0000 L CNN
F 1 "M2" H 5280 4701 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-4_P5.08mm" H 5200 4800 50  0001 C CNN
F 3 "~" H 5200 4800 50  0001 C CNN
	1    5200 4800
	1    0    0    -1  
$EndComp
Text Label 4850 4700 2    50   ~ 0
M2_1A
Text Label 4850 4800 2    50   ~ 0
M2_1B
Text Label 4850 4900 2    50   ~ 0
M2_2A
Text Label 4850 5000 2    50   ~ 0
M2_2B
Wire Wire Line
	4850 4700 5000 4700
Wire Wire Line
	5000 4800 4850 4800
Wire Wire Line
	4850 4900 5000 4900
Wire Wire Line
	5000 5000 4850 5000
$Comp
L Connector:Screw_Terminal_01x04 J5
U 1 1 5BC2B621
P 5200 5250
F 0 "J5" H 5280 5242 50  0000 L CNN
F 1 "M3" H 5280 5151 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-4_P5.08mm" H 5200 5250 50  0001 C CNN
F 3 "~" H 5200 5250 50  0001 C CNN
	1    5200 5250
	1    0    0    -1  
$EndComp
Text Label 4850 5150 2    50   ~ 0
M3_1A
Text Label 4850 5250 2    50   ~ 0
M3_1B
Text Label 4850 5350 2    50   ~ 0
M3_2A
Text Label 4850 5450 2    50   ~ 0
M3_2B
Wire Wire Line
	4850 5150 5000 5150
Wire Wire Line
	5000 5250 4850 5250
Wire Wire Line
	4850 5350 5000 5350
Wire Wire Line
	5000 5450 4850 5450
$Comp
L Connector:Screw_Terminal_01x04 J6
U 1 1 5BC3F7E6
P 5200 5700
F 0 "J6" H 5280 5692 50  0000 L CNN
F 1 "M0-POLOLU" H 5280 5601 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-4_P5.08mm" H 5200 5700 50  0001 C CNN
F 3 "~" H 5200 5700 50  0001 C CNN
	1    5200 5700
	1    0    0    -1  
$EndComp
Text Label 4850 5600 2    50   ~ 0
M0_1A
Text Label 4850 5700 2    50   ~ 0
M0_1B
Text Label 4850 5800 2    50   ~ 0
M0_2A
Text Label 4850 5900 2    50   ~ 0
M0_2B
Wire Wire Line
	4850 5600 5000 5600
Wire Wire Line
	4850 5700 5000 5700
Wire Wire Line
	4850 5800 5000 5800
Wire Wire Line
	4850 5900 5000 5900
NoConn ~ 2250 3000
NoConn ~ 2350 3000
NoConn ~ 2550 3000
NoConn ~ 2950 8500
NoConn ~ 2950 8600
NoConn ~ 2950 8700
NoConn ~ 1300 8600
NoConn ~ 1300 8700
NoConn ~ 1300 8500
NoConn ~ 1300 6500
NoConn ~ 1300 6600
NoConn ~ 1300 6700
NoConn ~ 2950 6500
NoConn ~ 2950 6600
NoConn ~ 2950 6700
Wire Wire Line
	1950 4200 1750 4200
Wire Wire Line
	1950 4100 1750 4100
Wire Wire Line
	1750 4000 1950 4000
Text Label 1750 4200 2    50   ~ 0
ENA3
Text Label 1750 4100 2    50   ~ 0
ENA2
Text Label 1750 4000 2    50   ~ 0
ENA1
Text Label 1750 4300 2    50   ~ 0
ENA0-POLOLU
Wire Wire Line
	1750 4300 1950 4300
NoConn ~ 1950 4400
Text Label 3200 4300 0    50   ~ 0
M1_STEP
Text Label 3200 4200 0    50   ~ 0
M1_DIR
Wire Wire Line
	3200 4200 2950 4200
Wire Wire Line
	2950 4300 3200 4300
Text Label 3200 3700 0    50   ~ 0
SENSOR2
Text Label 3200 3600 0    50   ~ 0
SENSOR1
Text Label 4050 3600 2    50   ~ 0
SENSOR1
Text Label 4050 3700 2    50   ~ 0
SENSOR2
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5BC6D832
P 4250 3600
F 0 "J2" H 4330 3592 50  0000 L CNN
F 1 "SENSORES" H 4330 3501 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-2_P5.08mm" H 4250 3600 50  0001 C CNN
F 3 "~" H 4250 3600 50  0001 C CNN
	1    4250 3600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J7
U 1 1 5BC73789
P 5250 3600
F 0 "J7" H 5330 3592 50  0000 L CNN
F 1 "ALIM_SENSORES" H 5330 3501 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-2_P5.08mm" H 5250 3600 50  0001 C CNN
F 3 "~" H 5250 3600 50  0001 C CNN
	1    5250 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5BC7CCB1
P 5050 3700
F 0 "#PWR021" H 5050 3450 50  0001 C CNN
F 1 "GND" H 5055 3527 50  0000 C CNN
F 2 "" H 5050 3700 50  0001 C CNN
F 3 "" H 5050 3700 50  0001 C CNN
	1    5050 3700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR020
U 1 1 5BC7CCF8
P 5050 3600
F 0 "#PWR020" H 5050 3450 50  0001 C CNN
F 1 "+5V" H 5065 3773 50  0000 C CNN
F 2 "" H 5050 3600 50  0001 C CNN
F 3 "" H 5050 3600 50  0001 C CNN
	1    5050 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 3800 3200 3800
Wire Wire Line
	2950 3900 3200 3900
Wire Wire Line
	2950 4100 3200 4100
Wire Wire Line
	2950 4000 3200 4000
NoConn ~ 2950 4400
NoConn ~ 2950 4500
$Comp
L Connector:Screw_Terminal_01x02 J8
U 1 1 5BC86877
P 3650 2100
F 0 "J8" H 3730 2092 50  0000 L CNN
F 1 "ALIMENTACION" H 3730 2001 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-2_P5.08mm" H 3650 2100 50  0001 C CNN
F 3 "~" H 3650 2100 50  0001 C CNN
	1    3650 2100
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR023
U 1 1 5BC868F3
P 3850 1950
F 0 "#PWR023" H 3850 1800 50  0001 C CNN
F 1 "+12V" H 3865 2123 50  0000 C CNN
F 2 "" H 3850 1950 50  0001 C CNN
F 3 "" H 3850 1950 50  0001 C CNN
	1    3850 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2000 3850 1950
$Comp
L power:GND #PWR024
U 1 1 5BC89920
P 3850 2100
F 0 "#PWR024" H 3850 1850 50  0001 C CNN
F 1 "GND" H 3855 1927 50  0000 C CNN
F 2 "" H 3850 2100 50  0001 C CNN
F 3 "" H 3850 2100 50  0001 C CNN
	1    3850 2100
	1    0    0    -1  
$EndComp
$EndSCHEMATC
