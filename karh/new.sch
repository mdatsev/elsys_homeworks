EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
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
L R R?
U 1 1 5A2A4A7E
P 3750 1900
F 0 "R?" V 3830 1900 50  0000 C CNN
F 1 "220" V 3750 1900 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0411_L9.9mm_D3.6mm_P25.40mm_Horizontal" V 3680 1900 50  0001 C CNN
F 3 "" H 3750 1900 50  0001 C CNN
F 4 "Comet" V 3750 1900 60  0001 C CNN "Source"
F 5 "\\][poiuytrewqazxcvbnm,./';lkjhgfdsa" V 3750 1900 60  0000 C CNN "VendorID"
	1    3750 1900
	0    1    -1   0   
$EndComp
$Comp
L LED D?
U 1 1 5A2A4AB3
P 4100 1900
F 0 "D?" H 4100 2000 50  0000 C CNN
F 1 "LED" H 4100 1800 50  0000 C CNN
F 2 "" H 4100 1900 50  0001 C CNN
F 3 "" H 4100 1900 50  0001 C CNN
	1    4100 1900
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 5A2A4B10
P 4300 2300
F 0 "#PWR?" H 4300 2050 50  0001 C CNN
F 1 "GND" H 4300 2150 50  0000 C CNN
F 2 "" H 4300 2300 50  0001 C CNN
F 3 "" H 4300 2300 50  0001 C CNN
	1    4300 2300
	1    0    0    -1  
$EndComp
$Comp
L CP C?
U 1 1 5A2A4C07
P 3550 2100
F 0 "C?" H 3575 2200 50  0000 L CNN
F 1 "CP" H 3575 2000 50  0000 L CNN
F 2 "" H 3588 1950 50  0001 C CNN
F 3 "" H 3550 2100 50  0001 C CNN
	1    3550 2100
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5A2A524C
P 3550 1850
F 0 "#PWR?" H 3550 1700 50  0001 C CNN
F 1 "+5V" H 3550 1990 50  0000 C CNN
F 2 "" H 3550 1850 50  0001 C CNN
F 3 "" H 3550 1850 50  0001 C CNN
	1    3550 1850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5A2A537F
P 3550 2300
F 0 "#PWR?" H 3550 2050 50  0001 C CNN
F 1 "GND" H 3550 2150 50  0000 C CNN
F 2 "" H 3550 2300 50  0001 C CNN
F 3 "" H 3550 2300 50  0001 C CNN
	1    3550 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1850 3550 1950
Wire Wire Line
	3550 1900 3600 1900
Connection ~ 3550 1900
Wire Wire Line
	3550 2250 3550 2300
Wire Wire Line
	3900 1900 3950 1900
Wire Wire Line
	4250 1900 4300 1900
Wire Wire Line
	4300 1900 4300 2300
$EndSCHEMATC
