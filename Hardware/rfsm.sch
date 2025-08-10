EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 3
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
L MCU_Module:NUCLEO144-F439ZI U1
U 1 1 60D9ADA7
P 3750 5500
F 0 "U1" H 4050 9350 50  0000 C CNN
F 1 "NUCLEO144-F439ZI" H 4050 9200 50  0000 C CNN
F 2 "Module:ST_Morpho_Connector_144_STLink" H 4600 1850 50  0001 L CNN
F 3 "https://www.st.com/resource/en/user_manual/dm00244518-stm32-nucleo144-boards-stmicroelectronics.pdf" H 2850 5800 50  0001 C CNN
	1    3750 5500
	1    0    0    -1  
$EndComp
$Sheet
S 10400 10700 1000 300 
U 60DA40F8
F0 "SheetLcdKey" 50
F1 "lcdkey.sch" 50
$EndSheet
$Comp
L power:GND #PWR?
U 1 1 60EAB069
P 11500 1450
AR Path="/60DA40F8/60EAB069" Ref="#PWR?"  Part="1" 
AR Path="/60EAB069" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 11500 1200 50  0001 C CNN
F 1 "GND" H 11505 1277 50  0000 C CNN
F 2 "" H 11500 1450 50  0001 C CNN
F 3 "" H 11500 1450 50  0001 C CNN
	1    11500 1450
	-1   0    0    1   
$EndComp
Text GLabel 11500 1650 3    50   Input ~ 0
GND
Text GLabel 11750 1650 3    50   Input ~ 0
3V3
$Comp
L power:+3.3V #PWR?
U 1 1 60EAB072
P 11750 1500
AR Path="/60DA40F8/60EAB072" Ref="#PWR?"  Part="1" 
AR Path="/60EAB072" Ref="#PWR03"  Part="1" 
F 0 "#PWR03" H 11750 1350 50  0001 C CNN
F 1 "+3.3V" H 11765 1673 50  0000 C CNN
F 2 "" H 11750 1500 50  0001 C CNN
F 3 "" H 11750 1500 50  0001 C CNN
	1    11750 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	11750 1500 11750 1600
$Comp
L power:PWR_FLAG #FLG?
U 1 1 60EAB07A
P 12100 1600
AR Path="/60DA40F8/60EAB07A" Ref="#FLG?"  Part="1" 
AR Path="/60EAB07A" Ref="#FLG03"  Part="1" 
F 0 "#FLG03" H 12100 1675 50  0001 C CNN
F 1 "PWR_FLAG" H 12100 1773 50  0000 C CNN
F 2 "" H 12100 1600 50  0001 C CNN
F 3 "~" H 12100 1600 50  0001 C CNN
	1    12100 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	12100 1600 11750 1600
Connection ~ 11750 1600
Wire Wire Line
	11750 1600 11750 1650
Wire Wire Line
	11500 1450 11500 1550
$Comp
L power:PWR_FLAG #FLG?
U 1 1 60EAB08E
P 11250 1350
AR Path="/60DA40F8/60EAB08E" Ref="#FLG?"  Part="1" 
AR Path="/60EAB08E" Ref="#FLG01"  Part="1" 
F 0 "#FLG01" H 11250 1425 50  0001 C CNN
F 1 "PWR_FLAG" H 11250 1523 50  0000 C CNN
F 2 "" H 11250 1350 50  0001 C CNN
F 3 "~" H 11250 1350 50  0001 C CNN
	1    11250 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	11250 1350 11250 1550
Wire Wire Line
	11250 1550 11500 1550
Connection ~ 11500 1550
Wire Wire Line
	11500 1550 11500 1650
Text GLabel 5150 6400 2    50   Input ~ 0
LCD_RS
Text GLabel 5150 6200 2    50   Input ~ 0
LCD_D4
Text GLabel 5150 4700 2    50   Input ~ 0
LCD_D5
Text GLabel 5150 4100 2    50   Input ~ 0
LCD_D6
Text GLabel 5150 4800 2    50   Input ~ 0
LCD_D7
Text GLabel 5150 6500 2    50   Input ~ 0
LCD_E
Wire Wire Line
	5150 4100 5050 4100
Wire Wire Line
	5150 4700 5050 4700
Wire Wire Line
	5150 4800 5050 4800
Wire Wire Line
	5150 6200 5050 6200
Wire Wire Line
	5150 6400 5050 6400
Wire Wire Line
	5150 6500 5050 6500
Text GLabel 5150 8100 2    50   Input ~ 0
KR1
Text GLabel 5150 2700 2    50   Input ~ 0
KR2
Text GLabel 5150 3400 2    50   Input ~ 0
KR3
Text GLabel 5150 2800 2    50   Input ~ 0
KR4
Text GLabel 5150 3300 2    50   Input ~ 0
KC1
Text GLabel 5150 5000 2    50   Input ~ 0
KC2
Text GLabel 5150 5100 2    50   Input ~ 0
KC3
Text GLabel 5150 4300 2    50   Input ~ 0
KC4
Wire Wire Line
	5150 2700 5050 2700
Wire Wire Line
	5150 2800 5050 2800
Wire Wire Line
	5150 3300 5050 3300
Wire Wire Line
	5150 3400 5050 3400
Wire Wire Line
	5150 4300 5050 4300
Wire Wire Line
	5150 5000 5050 5000
Wire Wire Line
	5150 5100 5050 5100
Wire Wire Line
	5150 8100 5050 8100
Text GLabel 5150 7800 2    50   Input ~ 0
LCD_DIS_EN
$Comp
L Regulator_Linear:L7805 U2
U 1 1 60ED1231
P 11750 2700
F 0 "U2" H 11750 2942 50  0000 C CNN
F 1 "L7805" H 11750 2851 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 11775 2550 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 11750 2650 50  0001 C CNN
	1    11750 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 60ED1F4E
P 11250 2900
F 0 "C1" H 11365 2946 50  0000 L CNN
F 1 "0.1uf" H 11365 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 11288 2750 50  0001 C CNN
F 3 "~" H 11250 2900 50  0001 C CNN
	1    11250 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 60ED27B9
P 12250 2900
F 0 "C2" H 12368 2946 50  0000 L CNN
F 1 "22uf" H 12368 2855 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-12_Kemet-R_Pad1.30x1.05mm_HandSolder" H 12288 2750 50  0001 C CNN
F 3 "~" H 12250 2900 50  0001 C CNN
	1    12250 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	11250 2750 11250 2700
Wire Wire Line
	11250 2700 11450 2700
Wire Wire Line
	12050 2700 12250 2700
Wire Wire Line
	12250 2700 12250 2750
Text GLabel 11750 3250 3    50   Input ~ 0
GND
Wire Wire Line
	11250 3150 11250 3050
Wire Wire Line
	12250 3150 12250 3050
$Comp
L Connector:Barrel_Jack_Switch_Pin3Ring J1
U 1 1 60EDBA4C
P 14800 1550
F 0 "J1" H 14570 1500 50  0000 R CNN
F 1 "Barrel_Jack_Switch_Pin3Ring" H 15050 1250 50  0000 R CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 14850 1510 50  0001 C CNN
F 3 "~" H 14850 1510 50  0001 C CNN
	1    14800 1550
	-1   0    0    1   
$EndComp
Text GLabel 14400 1200 1    50   Input ~ 0
GND
Wire Wire Line
	14500 1450 14400 1450
Wire Wire Line
	14400 1450 14400 1350
Wire Wire Line
	14500 1550 14400 1550
Wire Wire Line
	14400 1550 14400 1450
Connection ~ 14400 1450
Wire Wire Line
	13750 1650 13750 1400
$Comp
L power:+12V #PWR04
U 1 1 60EDFC8C
P 13750 1350
F 0 "#PWR04" H 13750 1200 50  0001 C CNN
F 1 "+12V" H 13765 1523 50  0000 C CNN
F 2 "" H 13750 1350 50  0001 C CNN
F 3 "" H 13750 1350 50  0001 C CNN
	1    13750 1350
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 60EE04EA
P 13400 1350
AR Path="/60DA40F8/60EE04EA" Ref="#FLG?"  Part="1" 
AR Path="/60EE04EA" Ref="#FLG04"  Part="1" 
F 0 "#FLG04" H 13400 1425 50  0001 C CNN
F 1 "PWR_FLAG" H 13400 1523 50  0000 C CNN
F 2 "" H 13400 1350 50  0001 C CNN
F 3 "~" H 13400 1350 50  0001 C CNN
	1    13400 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	13400 1350 13400 1400
Wire Wire Line
	13400 1400 13750 1400
Connection ~ 13750 1400
Wire Wire Line
	13750 1400 13750 1350
Text GLabel 13650 1650 0    50   Input ~ 0
12V
Wire Wire Line
	13650 1650 13750 1650
Text GLabel 11250 2650 1    50   Input ~ 0
12V
Wire Wire Line
	11250 2650 11250 2700
Connection ~ 11250 2700
Wire Wire Line
	11750 3000 11750 3150
Wire Wire Line
	11750 3150 11250 3150
Wire Wire Line
	12250 3150 11750 3150
Connection ~ 11750 3150
Wire Wire Line
	11750 3250 11750 3150
Wire Notes Line
	15700 850  15700 3550
Wire Notes Line
	15700 3550 11050 3550
Wire Notes Line
	11050 3550 11050 850 
Wire Notes Line
	11050 850  15700 850 
Text Notes 12850 950  0    50   ~ 0
POWER SUPPLY SECTION
$Sheet
S 9250 10700 950  250 
U 60E71644
F0 "logic_conversion" 50
F1 "logic_conversion.sch" 50
$EndSheet
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 60EEC563
P 9650 1150
F 0 "J4" V 9758 1294 50  0000 L CNN
F 1 "Conn_01x04_Male" V 9803 1294 50  0001 L CNN
F 2 "Connector_JST:JST_EH_B4B-EH-A_1x04_P2.50mm_Vertical" H 9650 1150 50  0001 C CNN
F 3 "~" H 9650 1150 50  0001 C CNN
	1    9650 1150
	0    1    1    0   
$EndComp
Text GLabel 5150 4500 2    50   Input ~ 0
UART_TX
Text GLabel 5150 4600 2    50   Input ~ 0
UART_RX
Text GLabel 9650 1450 3    50   Input ~ 0
UART_TX
Text GLabel 9550 1450 3    50   Input ~ 0
UART_RX
Text GLabel 9750 1450 3    50   Input ~ 0
GND
Text GLabel 9450 1450 3    50   Input ~ 0
5V
Wire Wire Line
	9450 1350 9450 1450
Wire Wire Line
	9550 1350 9550 1450
Wire Wire Line
	9650 1350 9650 1450
Wire Wire Line
	9750 1350 9750 1450
Wire Wire Line
	5050 4500 5150 4500
Wire Wire Line
	5050 4600 5150 4600
NoConn ~ 5050 2200
NoConn ~ 5050 2300
NoConn ~ 5050 2400
NoConn ~ 5050 2500
NoConn ~ 5050 2900
NoConn ~ 5050 3000
NoConn ~ 5050 3200
NoConn ~ 5050 3100
NoConn ~ 5050 3500
NoConn ~ 5050 3600
NoConn ~ 5050 4200
NoConn ~ 5050 5200
NoConn ~ 5050 5300
NoConn ~ 5050 5700
NoConn ~ 5050 6000
NoConn ~ 5050 6100
NoConn ~ 5050 6300
NoConn ~ 5050 7000
NoConn ~ 5050 7100
NoConn ~ 5050 8200
NoConn ~ 5050 8300
Text GLabel 3650 9550 3    50   Input ~ 0
GND
Wire Wire Line
	2950 9300 2950 9450
Wire Wire Line
	2950 9450 3050 9450
Wire Wire Line
	4550 9450 4550 9300
Wire Wire Line
	3050 9300 3050 9450
Connection ~ 3050 9450
Wire Wire Line
	3050 9450 3150 9450
Wire Wire Line
	3150 9300 3150 9450
Connection ~ 3150 9450
Wire Wire Line
	3150 9450 3250 9450
Wire Wire Line
	3250 9300 3250 9450
Connection ~ 3250 9450
Wire Wire Line
	3250 9450 3350 9450
Wire Wire Line
	3350 9300 3350 9450
Connection ~ 3350 9450
Wire Wire Line
	3350 9450 3450 9450
Wire Wire Line
	3450 9300 3450 9450
Connection ~ 3450 9450
Wire Wire Line
	3450 9450 3550 9450
Wire Wire Line
	3550 9300 3550 9450
Connection ~ 3550 9450
Wire Wire Line
	3550 9450 3650 9450
Wire Wire Line
	3650 9300 3650 9450
Connection ~ 3650 9450
Wire Wire Line
	3650 9450 3750 9450
Wire Wire Line
	3750 9300 3750 9450
Connection ~ 3750 9450
Wire Wire Line
	3750 9450 3850 9450
Wire Wire Line
	3850 9300 3850 9450
Connection ~ 3850 9450
Wire Wire Line
	3850 9450 3950 9450
Wire Wire Line
	3950 9300 3950 9450
Connection ~ 3950 9450
Wire Wire Line
	3950 9450 4050 9450
Wire Wire Line
	4050 9300 4050 9450
Connection ~ 4050 9450
Wire Wire Line
	4050 9450 4150 9450
Wire Wire Line
	4150 9300 4150 9450
Connection ~ 4150 9450
Wire Wire Line
	4150 9450 4250 9450
Wire Wire Line
	4250 9300 4250 9450
Connection ~ 4250 9450
Wire Wire Line
	4250 9450 4350 9450
Wire Wire Line
	4350 9300 4350 9450
Connection ~ 4350 9450
Wire Wire Line
	4350 9450 4550 9450
NoConn ~ 2450 7900
NoConn ~ 2450 7300
NoConn ~ 2450 8000
NoConn ~ 2450 8100
NoConn ~ 2450 8200
NoConn ~ 2450 8300
NoConn ~ 2450 8400
NoConn ~ 2450 8500
NoConn ~ 2450 8600
NoConn ~ 2450 8700
NoConn ~ 2450 8800
NoConn ~ 2450 7100
NoConn ~ 2450 7000
NoConn ~ 2450 6900
NoConn ~ 2450 6800
NoConn ~ 2450 6700
NoConn ~ 2450 5600
NoConn ~ 2450 5700
NoConn ~ 2450 5900
NoConn ~ 2450 5400
NoConn ~ 2450 5300
NoConn ~ 2450 5200
NoConn ~ 2450 5100
NoConn ~ 2450 5000
NoConn ~ 2450 4900
NoConn ~ 2450 4800
NoConn ~ 2450 4700
NoConn ~ 2450 4600
NoConn ~ 2450 4500
NoConn ~ 2450 4400
NoConn ~ 2450 4300
NoConn ~ 2450 3700
NoConn ~ 2450 3600
NoConn ~ 2450 2200
NoConn ~ 2450 2300
Wire Wire Line
	3650 9550 3650 9450
Wire Notes Line
	10200 850  10200 2100
Wire Notes Line
	10200 2100 9050 2100
Wire Notes Line
	9050 2100 9050 850 
Wire Notes Line
	9050 850  10200 850 
Text Notes 9200 950  0    50   ~ 0
TTL TO USB CONNECTOR
Wire Wire Line
	3050 1700 3050 1450
Wire Wire Line
	3050 1450 3250 1450
Wire Wire Line
	3450 1450 3450 1700
Wire Wire Line
	3250 1350 3250 1450
Connection ~ 3250 1450
Wire Wire Line
	3250 1450 3450 1450
Wire Wire Line
	5050 4400 5150 4400
Wire Wire Line
	5150 4900 5050 4900
Wire Wire Line
	5150 5400 5050 5400
Wire Wire Line
	5150 5600 5050 5600
Wire Wire Line
	5150 5800 5050 5800
Wire Wire Line
	5150 5900 5050 5900
Text GLabel 2350 6100 0    50   Input ~ 0
SW_5_PIN_2
Text GLabel 5150 8400 2    50   Input ~ 0
SW_8_PIN_2
Text GLabel 5150 8700 2    50   Input ~ 0
SW_8_PIN_3
Wire Wire Line
	2350 5800 2450 5800
Text GLabel 2350 5800 0    50   Input ~ 0
SW_7_PIN_1
Wire Wire Line
	2450 6200 2350 6200
Wire Wire Line
	2450 6300 2350 6300
Wire Wire Line
	2350 6400 2450 6400
Wire Wire Line
	2350 6500 2450 6500
Text GLabel 2350 6500 0    50   Input ~ 0
SW_7_PIN_3
Text GLabel 2350 6400 0    50   Input ~ 0
SW_7_PIN_2
Text GLabel 2350 6300 0    50   Input ~ 0
SW_2_PIN_2
Text GLabel 2350 6200 0    50   Input ~ 0
SW_2_PIN_1
Wire Wire Line
	2350 7600 2450 7600
Wire Wire Line
	2450 7700 2350 7700
Wire Wire Line
	2450 7800 2350 7800
Text GLabel 2350 7800 0    50   Input ~ 0
SW_6_PIN_4
Text GLabel 2350 7700 0    50   Input ~ 0
SW_6_PIN_2
Text GLabel 2350 7600 0    50   Input ~ 0
SW_6_PIN_3
Text GLabel 2350 6600 0    50   Input ~ 0
SW_5_PIN_4
Text GLabel 5150 8800 2    50   Input ~ 0
SW_8_PIN_4
Wire Wire Line
	5050 7400 5150 7400
Wire Wire Line
	5050 7500 5150 7500
Wire Wire Line
	5050 7700 5150 7700
Wire Wire Line
	5150 8000 5050 8000
Text GLabel 5150 8000 2    50   Input ~ 0
SW_6_PIN_1
Text GLabel 2350 6000 0    50   Input ~ 0
SW_5_PIN_3
Text GLabel 5150 8600 2    50   Input ~ 0
SW_5_PIN_1
Text GLabel 5150 7700 2    50   Input ~ 0
SW_4_PIN_3
Text GLabel 5150 7500 2    50   Input ~ 0
SW_1_PIN_3
Text GLabel 5150 7400 2    50   Input ~ 0
SW_7_PIN_4
Text GLabel 5150 8500 2    50   Input ~ 0
SW_8_PIN_1
Wire Wire Line
	5150 6900 5050 6900
Wire Wire Line
	5050 6800 5150 6800
Wire Wire Line
	5050 6700 5150 6700
Wire Wire Line
	5050 6600 5150 6600
Text GLabel 5150 6900 2    50   Input ~ 0
SW_2_PIN_4
Text GLabel 5150 6800 2    50   Input ~ 0
SW_1_PIN_4
Text GLabel 5150 6700 2    50   Input ~ 0
SW_1_PIN_1
Text GLabel 5150 6600 2    50   Input ~ 0
SW_1_PIN_2
Text GLabel 5150 5900 2    50   Input ~ 0
SW_4_PIN_2
Text GLabel 5150 5800 2    50   Input ~ 0
SW_4_PIN_4
Text GLabel 5150 5600 2    50   Input ~ 0
SW_4_PIN_1
Text GLabel 5150 5400 2    50   Input ~ 0
SW_3_PIN_4
Text GLabel 5150 4900 2    50   Input ~ 0
SW_3_PIN_3
Text GLabel 5150 4400 2    50   Input ~ 0
SW_3_PIN_2
Wire Wire Line
	5050 3700 5150 3700
Wire Wire Line
	5050 4000 5150 4000
Text GLabel 5150 4000 2    50   Input ~ 0
SW_3_PIN_1
Text GLabel 5150 3700 2    50   Input ~ 0
SW_2_PIN_3
NoConn ~ 5050 7900
Wire Wire Line
	5150 7800 5050 7800
Wire Wire Line
	5150 8400 5050 8400
Wire Wire Line
	5150 8500 5050 8500
Wire Wire Line
	5150 8600 5050 8600
Wire Wire Line
	5150 8700 5050 8700
Wire Wire Line
	5150 8800 5050 8800
Wire Wire Line
	2350 6000 2450 6000
Wire Wire Line
	2350 6100 2450 6100
NoConn ~ 2450 3900
NoConn ~ 2450 4000
NoConn ~ 2450 4100
NoConn ~ 2450 4200
NoConn ~ 2450 7400
NoConn ~ 2450 7500
NoConn ~ 5050 7300
NoConn ~ 5050 7600
Text GLabel 2800 1400 1    50   Input ~ 0
3V3
Wire Wire Line
	2800 1400 2800 1650
Wire Wire Line
	2800 1650 3250 1650
Wire Wire Line
	3250 1650 3250 1700
NoConn ~ 4550 1700
NoConn ~ 3650 1700
NoConn ~ 3550 1700
NoConn ~ 3350 1700
NoConn ~ 3150 1700
NoConn ~ 2950 1700
$Comp
L Regulator_Linear:L7805 U11
U 1 1 60F1C698
P 14200 2600
F 0 "U11" H 14200 2842 50  0000 C CNN
F 1 "L7805" H 14200 2751 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 14225 2450 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 14200 2550 50  0001 C CNN
	1    14200 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 60F1C69E
P 13700 2800
F 0 "C7" H 13815 2846 50  0000 L CNN
F 1 "0.1uf" H 13815 2755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 13738 2650 50  0001 C CNN
F 3 "~" H 13700 2800 50  0001 C CNN
	1    13700 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C8
U 1 1 60F1C6A4
P 14700 2800
F 0 "C8" H 14818 2846 50  0000 L CNN
F 1 "22uf" H 14818 2755 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-12_Kemet-R_Pad1.30x1.05mm_HandSolder" H 14738 2650 50  0001 C CNN
F 3 "~" H 14700 2800 50  0001 C CNN
	1    14700 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	13700 2650 13700 2600
Wire Wire Line
	13700 2600 13900 2600
Wire Wire Line
	14500 2600 14700 2600
Wire Wire Line
	14700 2600 14700 2650
Text GLabel 14200 3150 3    50   Input ~ 0
GND
Wire Wire Line
	13700 3050 13700 2950
Wire Wire Line
	14700 3050 14700 2950
Connection ~ 14700 2600
Text GLabel 13700 2550 1    50   Input ~ 0
12V
Wire Wire Line
	13700 2550 13700 2600
Connection ~ 13700 2600
Wire Wire Line
	14200 2900 14200 3050
Wire Wire Line
	14200 3050 13700 3050
Wire Wire Line
	14700 3050 14200 3050
Connection ~ 14200 3050
Wire Wire Line
	14200 3150 14200 3050
Text GLabel 14700 2350 1    50   Input ~ 0
5VD
Text GLabel 3250 1350 1    50   Input ~ 0
5VD
NoConn ~ 5050 2600
NoConn ~ 5050 3900
Wire Wire Line
	2350 6600 2450 6600
$Comp
L power:+5VD #PWR0101
U 1 1 6112461E
P 12800 1400
F 0 "#PWR0101" H 12800 1250 50  0001 C CNN
F 1 "+5VD" H 12815 1573 50  0000 C CNN
F 2 "" H 12800 1400 50  0001 C CNN
F 3 "" H 12800 1400 50  0001 C CNN
	1    12800 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 61125463
P 12500 1450
F 0 "#PWR0102" H 12500 1300 50  0001 C CNN
F 1 "+5V" H 12515 1623 50  0000 C CNN
F 2 "" H 12500 1450 50  0001 C CNN
F 3 "" H 12500 1450 50  0001 C CNN
	1    12500 1450
	1    0    0    -1  
$EndComp
Text GLabel 13100 2350 1    50   Input ~ 0
5V
Text GLabel 12500 1850 3    50   Input ~ 0
5V
Text GLabel 12800 1800 3    50   Input ~ 0
5VD
Wire Wire Line
	14700 2350 14700 2600
Wire Wire Line
	12500 1450 12500 1850
Wire Wire Line
	12800 1400 12800 1800
$Comp
L Device:CP C17
U 1 1 612BC360
P 14200 1500
F 0 "C17" H 14318 1546 50  0000 L CNN
F 1 "22uf" H 14318 1455 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-2012-12_Kemet-R_Pad1.30x1.05mm_HandSolder" H 14238 1350 50  0001 C CNN
F 3 "~" H 14200 1500 50  0001 C CNN
	1    14200 1500
	-1   0    0    1   
$EndComp
Connection ~ 13750 1650
Wire Wire Line
	14200 1650 14500 1650
Wire Wire Line
	14200 1350 14400 1350
Wire Wire Line
	14400 1200 14400 1350
Connection ~ 14400 1350
Wire Wire Line
	13750 1650 14200 1650
Connection ~ 14200 1650
$Comp
L Connector:Conn_01x02_Male J13
U 1 1 60F4510A
P 12700 2350
F 0 "J13" V 12762 2394 50  0000 L CNN
F 1 "Conn_01x02_Male" V 12853 2394 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 12700 2350 50  0001 C CNN
F 3 "~" H 12700 2350 50  0001 C CNN
	1    12700 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	12250 2700 12250 2550
Wire Wire Line
	12250 2550 12600 2550
Connection ~ 12250 2700
Wire Wire Line
	12700 2550 13100 2550
Wire Wire Line
	13100 2550 13100 2350
$EndSCHEMATC
