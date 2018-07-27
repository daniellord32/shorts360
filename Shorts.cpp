//Copyright (c) Daniel Lord.  All rights reserved. 

#include "Short.h"
#include "Global_variables.h"
#include "dragonflight.h"
#include "gauge_extensions.h"
/******************GLOBAL VARIABLES***************************/

PELEMENT_STATIC_IMAGE	pstat = NULL;	//Mouse background data
//incoming lights on for all gauges.
UINT8 lights_on = 0;


/////////////////////////////////////////////////////////////////////////////
// XML Handler
/////////////////////////////////////////////////////////////////////////////
#define		GAUGE_NAME			"xml_handler\0"
#define		GAUGEHDR_VAR_NAME	gaugehdr_xml_handler
#define		GAUGE_W				38

#include "XML_Handler.cpp"

#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W

/////////////////////////////////////////////////////////////////////////////
// Systems Handler
/////////////////////////////////////////////////////////////////////////////
// Action code held completely separate from both the C gauge and the XML gauge
#define		GAUGE_NAME			"systems_handler\0"
#define		GAUGEHDR_VAR_NAME	gaugehdr_systems_handler
#define		GAUGE_W				38

#include "Systems_Handler.cpp"

#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W


/////////////////////////////////////////////////////////////////////////////
// Fuel Left (working no issues)
/////////////////////////////////////////////////////////////////////////////
#define     GAUGE_NAME          "Fuel"
#define     GAUGEHDR_VAR_NAME   gaugehdr_fuel
#define     GAUGE_W             100

#include "Short.Fuel.cpp"

/////////////////////////////////////////////////////////////////////////////
// Fuel Left (working no issues)
/////////////////////////////////////////////////////////////////////////////

#define		GAUGE_NAME			"Fuel_Right"
#define		GAUGEHDR_VAR_NAME	gaugehdr_fuelRight
#define		GAUGE_W				100

#include "Short.Fuel_Right.cpp"

/////////////////////////////////////////////////////////////////////////////
// Whiskey (need to implement)
/////////////////////////////////////////////////////////////////////////////
#define     GAUGE_NAME          "Whiskey"
#define     GAUGEHDR_VAR_NAME   gaugehdr_whiskey
#define     GAUGE_W             100

#include "Short.Whiskey.cpp"

/////////////////////////////////////////////////////////////////////////////
// Voltmeter (need to fix xml script)
/////////////////////////////////////////////////////////////////////////////

#define		GAUGE_NAME			"Voltmeter"
#define		GAUGEHDR_VAR_NAME	gaugehdr_voltmeter
#define		GAUGE_W				100

#include "short.Voltmeter.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 1 RPM percent (working no issues)
/////////////////////////////////////////////////////////////////////////////
#define		GAUGE_NAME			"Engine1RPM"
#define		GAUGEHDR_VAR_NAME	gaugehdr_engine1rpm
#define		GAUGE_W				100

#include	"Shorts.RpmPct.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 2 RPM percent (working no issues)
/////////////////////////////////////////////////////////////////////////////
#define		GAUGE_NAME			"Engine2RPM"
#define		GAUGEHDR_VAR_NAME	gaugehdr_engine2rpm
#define		GAUGE_W				100

#include	"Short.PpmPCTe2.cpp"

/////////////////////////////////////////////////////////////////////////////
// Oil PSI/Temp (working no issues)(implementing custom effects)
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME				"OilPSI"
#define GAUGEHDR_VAR_NAME		gaugehdr_oilpsi
#define GAUGE_W					100

#include "Short.Oil.cpp"

/////////////////////////////////////////////////////////////////////////////
// Oil PSI/Temp (working no issues) (implementing custom effects)
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME				"OilPSIE2"
#define GAUGEHDR_VAR_NAME		gaugehdr_oilpsie2
#define GAUGE_W					100

#include "Short.OilE2.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 1 Torque (needs work)
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME			"Engine1Torque"
#define GAUGEHDR_VAR_NAME	gaugehdr_torquee1
#define GAUGE_W				100

#include "Short.TorqueE1.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 1 Fuel Flow (needs work)
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME			"FuelFlowE1"
#define GAUGEHDR_VAR_NAME	gaugehdr_fuelflowe1
#define GAUGE_W				100

#include "Short.Fuel_FlowE1.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 2 Fuel Flow (needs work)
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME			"FuelFlowE2"
#define GAUGEHDR_VAR_NAME	gaugehdr_fuelflowe2
#define GAUGE_W				100

#include "Shorts.Fuel_FlowE2.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 1 Prop RPM (need to fix needle movement)
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME			"PropRPM"
#define GAUGEHDR_VAR_NAME	gaugehdr_proprpm
#define GAUGE_W				100

#include "Short.Prop_RPM.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 2 Prop RPM (need to fix needle movement)
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME			"PropRPMe2"
#define GAUGEHDR_VAR_NAME	gaugehdr_proprpme2
#define GAUGE_W				100

#include "Short.Prop_RPME2.cpp"

/////////////////////////////////////////////////////////////////////////////
// HSI gauge
/////////////////////////////////////////////////////////////////////////////

//#define GAUGE_NAME			"Hsi"
//#define GAUGEHDR_VAR_NAME	gaugehdr_hsi
//#define GAUGE_W				100
//
//#include "Short.HSI.cpp"

/////////////////////////////////////////////////////////////////////////////
// Flight Map
/////////////////////////////////////////////////////////////////////////////
//#define GAUGE_NAME			"Flightmap"
//#define GAUGEHDR_VAR_NAME	gaugehdr_flightmap
//#define GAUGE_W				100
//
//#include "Shorts.FlightMap.cpp"

/////////////////////////////////////////////////////////////////////////////
// Com1 (align text correctly)
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME			"Com1"
#define GAUGEHDR_VAR_NAME	gaugehdr_com1
#define GAUGE_W				100

#include "Shorts.Com1.cpp"

//add rest of comms here after text alignment on first is complete.

/////////////////////////////////////////////////////////////////////////////
// Gauge table entries
/////////////////////////////////////////////////////////////////////////////
GAUGE_TABLE_BEGIN()
    GAUGE_TABLE_ENTRY(&gaugehdr_fuel)
    GAUGE_TABLE_ENTRY(&gaugehdr_whiskey)
	GAUGE_TABLE_ENTRY(&gaugehdr_voltmeter)
	GAUGE_TABLE_ENTRY(&gaugehdr_engine1rpm)
	GAUGE_TABLE_ENTRY(&gaugehdr_engine2rpm)
	GAUGE_TABLE_ENTRY(&gaugehdr_oilpsi)
	GAUGE_TABLE_ENTRY(&gaugehdr_oilpsie2)
	GAUGE_TABLE_ENTRY(&gaugehdr_torquee1)
	GAUGE_TABLE_ENTRY(&gaugehdr_fuelflowe1)
	GAUGE_TABLE_ENTRY(&gaugehdr_proprpm)
	GAUGE_TABLE_ENTRY(&gaugehdr_fuelflowe2)
	GAUGE_TABLE_ENTRY(&gaugehdr_proprpme2)
	//GAUGE_TABLE_ENTRY(&gaugehdr_flightmap)
	GAUGE_TABLE_ENTRY(&gaugehdr_xml_handler)
	GAUGE_TABLE_ENTRY(&gaugehdr_systems_handler)
	GAUGE_TABLE_ENTRY(&gaugehdr_com1)
GAUGE_TABLE_END()

