//Copyright (c) Microsoft Corporation.  All rights reserved. 

#include "..\inc\gauges.h"
#include "dragonflight.h"
#include "Short.h"

/******************GLOBAL VARIABLES***************************/
//incoming power signal for all gauges.
UINT8 power_on = 0;
//incoming lights on for all gauges.
UINT8 lights_on = 0;


/***************** SHOW/HIDE functions ***********************/

void FSAPI	add_imagedata_to_listelement(PELEMENT_HEADER	pelement,UINT32	pos_element,FLAGS image_flags);
void FSAPI	remove_imagedata_from_listelement(PELEMENT_HEADER	pelement,UINT32	pos_element,FLAGS image_flags);


/////////////////////////////////////////////////////////////////////////////
// Attitude
/////////////////////////////////////////////////////////////////////////////
#define     GAUGE_NAME          "Attitude"
#define     GAUGEHDR_VAR_NAME   gaugehdr_attitude
#define     GAUGE_W             100

#include "Short.Attitude.cpp"

/////////////////////////////////////////////////////////////////////////////
// Fuel Left
/////////////////////////////////////////////////////////////////////////////
#define     GAUGE_NAME          "Fuel"
#define     GAUGEHDR_VAR_NAME   gaugehdr_fuel
#define     GAUGE_W             100

#include "Short.Fuel.cpp"

/////////////////////////////////////////////////////////////////////////////
// Fuel Left
/////////////////////////////////////////////////////////////////////////////

#define		GAUGE_NAME			"Fuel_Right"
#define		GAUGEHDR_VAR_NAME	gaugehdr_fuelRight
#define		GAUGE_W				100

#include "Short.Fuel_Right.cpp"

/////////////////////////////////////////////////////////////////////////////
// Whiskey
/////////////////////////////////////////////////////////////////////////////
#define     GAUGE_NAME          "Whiskey"
#define     GAUGEHDR_VAR_NAME   gaugehdr_whiskey
#define     GAUGE_W             100

#include "Short.Whiskey.cpp"

/////////////////////////////////////////////////////////////////////////////
// Voltmeter
/////////////////////////////////////////////////////////////////////////////

/************** Mouse Background Data ***********************/
PELEMENT_STATIC_IMAGE	pstat=NULL;

#define		GAUGE_NAME			"Voltmeter"
#define		GAUGEHDR_VAR_NAME	gaugehdr_voltmeter
#define		GAUGE_W				100

#include "short.Voltmeter.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 1 RPM percent
/////////////////////////////////////////////////////////////////////////////
#define		GAUGE_NAME			"Engine1RPM"
#define		GAUGEHDR_VAR_NAME	gaugehdr_engine1rpm
#define		GAUGE_W				100

#include	"Shorts.RpmPct.cpp"

/////////////////////////////////////////////////////////////////////////////
// Airspeed
/////////////////////////////////////////////////////////////////////////////

#define		GAUGE_NAME				"Airspeed"
#define		GAUGEHDR_VAR_NAME		gaugehdr_airspeed
#define		GAUGE_W					100

#include "Short.Airspeed.cpp"

/////////////////////////////////////////////////////////////////////////////
// Altimeter
/////////////////////////////////////////////////////////////////////////////

#define		GAUGE_NAME				"Altimeter"
#define		GAUGEHDR_VAR_NAME		gaugehdr_altimeter
#define		GAUGE_W					100

#include "Short.Altimeter.cpp"

/////////////////////////////////////////////////////////////////////////////
// Oil PSI/Temp
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME				"OilPSI"
#define GAUGEHDR_VAR_NAME		gaugehdr_oilpsi
#define GAUGE_W					100

#include "Short.Oil.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 1 Torque
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME			"Engine1Torque"
#define GAUGEHDR_VAR_NAME	gaugehdr_torquee1
#define GAUGE_W				100

#include "Short.TorqueE1.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 1 Torque
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME			"FuelFlowE1"
#define GAUGEHDR_VAR_NAME	gaugehdr_fuelflowe1
#define GAUGE_W				100

#include "Short.Fuel_FlowE1.cpp"

/////////////////////////////////////////////////////////////////////////////
// Engine 1 Prop RPM
/////////////////////////////////////////////////////////////////////////////

#define GAUGE_NAME			"PropRPM"
#define GAUGEHDR_VAR_NAME	gaugehdr_proprpm
#define GAUGE_W				100

#include "Short.Prop_RPM.cpp"

/////////////////////////////////////////////////////////////////////////////
// Gauge table entries
/////////////////////////////////////////////////////////////////////////////
GAUGE_TABLE_BEGIN()
    GAUGE_TABLE_ENTRY(&gaugehdr_attitude)
    GAUGE_TABLE_ENTRY(&gaugehdr_fuel)
    GAUGE_TABLE_ENTRY(&gaugehdr_whiskey)
	GAUGE_TABLE_ENTRY(&gaugehdr_voltmeter)
	GAUGE_TABLE_ENTRY(&gaugehdr_engine1rpm)
	GAUGE_TABLE_ENTRY(&gaugehdr_airspeed)
	GAUGE_TABLE_ENTRY(&gaugehdr_altimeter)
	GAUGE_TABLE_ENTRY(&gaugehdr_oilpsi)
	GAUGE_TABLE_ENTRY(&gaugehdr_torquee1)
	GAUGE_TABLE_ENTRY(&gaugehdr_fuelflowe1)
	GAUGE_TABLE_ENTRY(&gaugehdr_proprpm)
GAUGE_TABLE_END()

