//Copyright (c) Microsoft Corporation.  All rights reserved. 
// SDK.Attitude.h
//

#define         VERSION_MAJOR           1
#define         VERSION_MINOR           0
#define         VERSION_BUILD           0

// magic to get the preprocessor to do what we want
#define		lita(arg) #arg
#define		xlita(arg) lita(arg)
#define		cat3(w,x,z) w##.##x##.##z##\000
#define		xcat3(w,x,z) cat3(w,x,z)
#define		VERSION_STRING xlita(xcat3(VERSION_MAJOR,VERSION_MINOR,VERSION_BUILD))

#ifndef		VS_VERSION_INFO
#define		VS_VERSION_INFO		0x0001
#endif

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS


/////////////////////////////////////////////////////////////////////////////
//
// Attitude Bitmaps
//
#define		BMP_ATTITUDE_BACKGROUND				0x1000
#define		BMP_ATTITUDE_CARD_INSIDE			0x1001
#define		BMP_ATTITUDE_CARD_OUTSIDE_MASK		0x1002
#define		BMP_ATTITUDE_CARD_OUTSIDE			0x1003
#define		BMP_ATTITUDE_CARD_INSIDE_MASK		0x1004

/////////////////////////////////////////////////////////////////////////////
//
// Fuel Gauge Bitmaps
//
#define		BMP_FUEL_BACKGROUND			0x1800
#define		BMP_FUEL_NEEDLE				0x2000

/////////////////////////////////////////////////////////////////////////////
//
// Fuel Selector Bitmaps
//
#define		BMP_FUEL_SELECTOR_OFF				0x2100
#define		BMP_FUEL_SELECTOR_LEFT				0x2101
#define		BMP_FUEL_SELECTOR_BOTH				0x2102
#define		BMP_FUEL_SELECTOR_RIGHT				0x2103

/////////////////////////////////////////////////////////////////////////////
//
// Temperature Gauge Bitmaps
//
#define		BMP_TEMPERATURE_SMALL_BACKGROUND	0x2200
#define		BMP_TEMPERATURE_SMALL_F				0x2300
#define		BMP_TEMPERATURE_SMALL_C				0x2301

/////////////////////////////////////////////////////////////////////////////
//
// Whiskey CompassBitmaps
//
#define		BMP_COMPASS_SMALL_BACKGROUND		0x2400
#define		BMP_COMPASS_SMALL_CARD				0x2500
#define		BMP_COMPASS_SMALL_MASK				0x2501

/////////////////////////////////////////////////////////////////////////////
//
// FlightMap Bitmaps
//
#define		BMP_FLIGHT_MAP_BACKGROUND		0x2600
#define		BMP_FLIGHT_MAP_BLANK			0x2601

/////////////////////////////////////////////////////////////////////////////
//
// Voltmeter Bitmaps
//
#define		BMP_VOLTMETER_BACKGROUND		0x2800
#define		BMP_VOLTMETER_MASK				0x2801
#define		BMP_VOLTMETER_NEEDLE			0x2802

/////////////////////////////////////////////////////////////////////////////
//
// Engine data Bitmaps
//
#define		BMP_RPM_BACKGROUND				0x2900
#define		BMP_RPM_NEEDLELG				0x2901
#define		BMP_RPM_NEEDLESM				0x2902

/////////////////////////////////////////////////////////////////////////////
//
// Airspeed Bitmaps
//
#define BMP_AIRSPEED_BACKGROUND				0x3100
#define BMP_AIRSPEED_NEEDLE					0x3101

/////////////////////////////////////////////////////////////////////////////
//
// Altimeter Bitmaps
//
#define BMP_ALT_BACKGROUND					0x2700
#define BMP_ALT_NEEDLE						0x2701
#define BMP_ALT_HUN_TAPE					0x2703
#define BMP_ALT_TENTHOU_TAPE				0x2706
#define BMP_ALT_THOU_TAPE					0x2709
#define BMP_ALT_HUN_MASK					0x2711
#define BMP_ALT_THOU_MASK					0x2713
#define BMP_ALT_TENTHOU_MASK				0x2716

/////////////////////////////////////////////////////////////////////////////
//
// Engine Oil/PSI Bitmaps
//
#define BMP_OIL_BACKGROUND					0x1300
#define BMP_OIL_NEEDLE						0x1301

/////////////////////////////////////////////////////////////////////////////
//
// Engine1 Torque Bitmaps
//
#define BMP_TORQUE_BACKGROUND				0X1400
#define BMP_TORQUE_NEEDLE					0X1401

/////////////////////////////////////////////////////////////////////////////
//
// Engine1 FuelFlow Bitmaps
//

#define BMP_FF_BACKGROUND					0x1500
#define BMP_FFENGINE_NEEDLE1				0x1501
#define BMP_FFENGINE_NEEDLE2				0x1502

/////////////////////////////////////////////////////////////////////////////
//
// Prop1 RPM Bitmaps
//

#define BMP_PROP_RPM						0x1600
#define BMP_RPM_NEEDLE1						0x1601
#define BMP_RPM_NEEDLE2						0x1602
