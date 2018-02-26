#include "fsxgauges_sp2.h"

//**************************************************************************
// Get VOR type
//**************************************************************************
// Input VOR1_CODE or VOR2_CODE 
// Flags to check
//		VOR_CODE_IS_LOCALIZER					0= VOR  1= Localizer
//		VOR_CODE_GLIDESLOPE						1= Glideslope Available
//		VOR_CODE_BACKCOURSE_UNAVAIL		1= no localizer backcourse
//		VOR_CODE_DME_AT_GLIDE_SLOPE		1= DME transmitter at Glide Slope Transmitter
//		VOR_CODE_NAV_UNAVAILABLE			1= no nav signal available
//		VOR_CODE_VOICE_AVAILABLE			1= Voice Available
//		VOR_CODE_TACAN								1= TACAN
//		VOR_CODE_DME_AVAILABLE		    1= DME
//
// Sample code to access this function - check for localiser available:
//
//	lookup_var(&vor2_code);
//	if (VorType(vor2_code,VOR_CODE_IS_LOCALIZER))
//	{
//		Do code here; 
//	}

BOOL VorType(MODULE_VAR vorfield, FLAGS vorflag)
{
	if ((vorfield.var_value.b&vorflag)!= FLAGS0) return TRUE;
	else return FALSE;
}

//**************************************************************************
//Get ILS state
//**************************************************************************
// Input VOR1_BACK_COURSE_FLAGS or VOR2_BACK_COURSE_FLAGS_CODE 
//	BC_FLAG_BACKCOURSE_AVAILABLE	BIT0
//	BC_FLAG_LOCALIZER_TUNED_IN		BIT1
//	BC_FLAG_ON_BACKCOURSE					BIT2
//	BC_FLAG_STATION_ACTIVE				BIT7
//
// Sample code to access this function - check for back course station active:
//
//	lookup_var(&vor1_code);
//	if (VorType(vor1_code,BC_FLAG_STATION_ACTIVE)
//	{
//		Do code here; 
//	}

BOOL BCType(MODULE_VAR bcfield, FLAGS bcflag)
{
	if ((bcfield.var_value.b&bcflag)!= FLAGS0) return TRUE;
	else return FALSE;
}

//**************************************************************************
//Get GPS flags
//**************************************************************************
// Input GPS_FLAGS
// Flags to check
//		GPS_FLAG_ACTIVE_FLIGHT_PLAN
//		GPS_FLAG_ACTIVE_WAY_POINT
//		GPS_FLAG_ARRIVED
//		GPS_FLAG_DIRECTTO_FLIGHTPLAN
//
// Sample code to access this function - same structure as the two above!

BOOL GPSFlags(MODULE_VAR gpsfield, FLAGS gpsflag)
{
	if ((gpsfield.var_value.b&gpsflag)!= FLAGS0) return TRUE;
	else return FALSE;
}
//**************************************************************************
//Get the time of day (1=day, 3=anything else! for FS9)
//	Sample usage: iTimeOfDay=GetTimeOfDay(iTimeOfDay);
//**************************************************************************
int GetTimeOfDay (SINT32 iToD)
{
	SINT32 time_of_day;
	execute_calculator_code("(E:TIME OF DAY,Enum)",NULL,&time_of_day,NULL);
	iToD=time_of_day;
	return iToD;
}
//**************************************************************************
//Get the runway surface type and surface conditions - useful to create an antiskid system
//	Sample usage: 
//		iSurfaceType=GetRunwayType(iSurfaceType);
//		iSurfaceCond=GetRunwayCond(iSurfaceCond);
//**************************************************************************
int GetRunwayType(SINT32 iRwyType)
{
	SINT32 state;
	execute_calculator_code("(A:SURFACE TYPE, Enum)",NULL,&state,NULL);
	iRwyType=state;
	return iRwyType;
}

int GetRunwayCond(SINT32 iRwyCond)
{
	SINT32 state;
	execute_calculator_code("(A:SURFACE CONDITION, Enum)",NULL,&state,NULL);
	iRwyCond=state;
	return iRwyCond;
}

//**************************************************************************
// Get remaining fuel in gallons / lbs / kilos / user-defined
// Acceptable parameters:	tank=left_aux, left_tip, right_aux, right_tip, centre, centre2, left_main, right_main
//												fueltype (OPTIONAL) = jeta, avgas. If fueltype missing, returnweight will be ignored
//												returnweight=lbs, kilos. If returnweight is missing then the default is kilos.
//												useweight = user-defined. If useweight exists then fueltype and returnweight will be ignored.
//												Why useweight? Because it provides the possibility to return weight based on temperature.
//												Default weights: JetA = 6.84 lbs per gallon, avgas = 6.02 lbs per gallon ISA at 15 degrees C.
//
//	Sample usage to return left aux remaining JetA fuel in lbs:
//		iLeftFuelRemaining=GetFuel("left_aux","jeta","lbs",0,0)
//**************************************************************************
#define		GALLON_TO_KILO_JETA(val)					(((val)*6.84)/2.24)
#define		KILO_TO_GALLON_JETA(val)					(((val)*2.24)/6.84)

#define		GALLON_TO_KILO_AVGAS(val)					(((val)*6.02)/2.24)
#define		KILO_TO_GALLON_AVGAS(val)					(((val)*2.24)/6.02)

#define		GALLON_TO_POUND_JETA(val)					((val)*6.84)
#define		POUND_TO_GALLON_JETA(val)					((val)/6.84)

#define		GALLON_TO_POUND_AVGAS(val)				((val)*6.02)
#define		POUND_TO_GALLON_AVGAS(val)				((val)/6.02)

//double GetFuel(char tank[],char fueltype[],char returnweight[],double useweight,double dblfuelstate)
//{
//	if(tank=="left_aux")
//	{
//		lookup_var(&fuel_level_leftaux);
//		lookup_var(&fuel_cap_leftaux);
//		dblfuelstate=fuel_level_leftaux.var_value.n/8388608.0;
//		dblfuelstate=fuel_cap_leftaux.var_value.n * dblfuelstate;
//	}
//
//	if(tank=="left_tip")
//	{
//		lookup_var(&fuel_level_lefttip);
//		lookup_var(&fuel_cap_lefttip);
//		dblfuelstate=fuel_level_lefttip.var_value.n/8388608.0;
//		dblfuelstate=fuel_cap_lefttip.var_value.n * dblfuelstate;
//	}
//
//	if(tank=="right_aux")
//	{
//		lookup_var(&fuel_level_rightaux);
//		lookup_var(&fuel_cap_rightaux);
//		dblfuelstate=fuel_level_rightaux.var_value.n/8388608.0;
//		dblfuelstate=fuel_cap_rightaux.var_value.n * dblfuelstate;
//	}
//
//	if(tank=="right_tip")
//	{
//		lookup_var(&fuel_level_righttip);
//		lookup_var(&fuel_cap_righttip);
//		dblfuelstate=fuel_level_righttip.var_value.n/8388608.0;
//		dblfuelstate=fuel_cap_righttip.var_value.n * dblfuelstate;
//	}
//
//	if(tank=="center2")
//	{
//		lookup_var(&fuel_level_centre2);
//		lookup_var(&fuel_cap_centre2);
//		dblfuelstate=fuel_level_centre2.var_value.n/8388608.0;
//		dblfuelstate=fuel_cap_centre2.var_value.n * dblfuelstate;
//	}
//
//	if(tank=="center")
//	{
//		lookup_var(&fuel_level_centre);
//		lookup_var(&fuel_cap_centre);
//		dblfuelstate=fuel_level_centre.var_value.n/8388608.0;
//		dblfuelstate=fuel_cap_centre.var_value.n * dblfuelstate;
//	}
//
//	if(tank=="left_main")
//	{
//		lookup_var(&fuel_level_leftmain);
//		lookup_var(&fuel_cap_leftmain);
//		dblfuelstate=fuel_level_leftmain.var_value.n/8388608.0;
//		dblfuelstate=fuel_cap_leftmain.var_value.n * dblfuelstate;
//	}
//
//	if(tank=="right_main")
//	{
//		lookup_var(&fuel_level_rightmain);
//		lookup_var(&fuel_cap_rightmain);
//		dblfuelstate=fuel_level_rightmain.var_value.n/8388608.0;
//		dblfuelstate=fuel_cap_rightmain.var_value.n * dblfuelstate;
//	}
//
//	if(useweight!=0)
//	{
//		dblfuelstate=dblfuelstate*useweight;
//	}
//	else
//	{
//		if(strcmp(fueltype,"")==0 && strcmp(returnweight,"")==0)returnweight="gallons";
//		if(strcmp(fueltype,"jeta")==0 && strcmp(returnweight,"kilos")==0)dblfuelstate=GALLON_TO_KILO_JETA(dblfuelstate);
//		if(strcmp(fueltype,"jeta")==0 && strcmp(returnweight,"lbs")==0)dblfuelstate=GALLON_TO_POUND_JETA(dblfuelstate);
//		if(strcmp(fueltype,"avgas")==0 && strcmp(returnweight,"kilos")==0)dblfuelstate=GALLON_TO_KILO_AVGAS(dblfuelstate);
//		if(strcmp(fueltype,"avgas")==0 && strcmp(returnweight,"lbs")==0)dblfuelstate=GALLON_TO_POUND_AVGAS(dblfuelstate);
//	}
//
//	return dblfuelstate;
//}
//***************************************************************************
// ADF function ##1	
//	Get the current ADF frequency and parse it ready for display.
//	This function splits down the current frequency into four integers (adf_hun, adf_ten, adf_unit and adf_dec)
//	which are used for driving the onscreen display (tape or string).
//	These four integers must be declared in a shared-data header file so that the shared display data is
//	updated on each pass. 
//
//	Sample usage: update ADF2 display variables
//		GetADFFrequencyParts(2);
//
//***************************************************************************
//void GetADFFrequencyParts(int adf_number)
//{
//	double adf_current=0;
//
//// Variable adf_number allows us to use one function for both ADFs.
//	if(adf_number==1)execute_calculator_code("(A:ADF ACTIVE FREQUENCY:1, KHz)",&adf_current,NULL,NULL);
//	if(adf_number==2)execute_calculator_code("(A:ADF ACTIVE FREQUENCY:2, KHz)",&adf_current,NULL,NULL);
//	adf_hun=(int)adf_current/100;
//	adf_ten=((int)adf_current-(adf_hun*100))/10;
//	adf_unit=(int)adf_current-((adf_hun*100)+(adf_ten*10));
//	adf_dec=(adf_current-((adf_hun*100)+(adf_ten*10)+adf_unit))*10;
//
//	return;
//}
//***************************************************************************
// ADF function ##2
//	Get the current ADF frequency and return it to the calling subroutine
//
//	Sample usage: get the current ADF1 frequency
//		iAdf1Frequency=GetADFFrequency(1);
//
//***************************************************************************
int GetADFFrequency(int adf_number)
{
	double adf_current=0;

// Variable adf_number allows us to use one function for both ADFs.
	if(adf_number==1)execute_calculator_code("(A:ADF ACTIVE FREQUENCY:1, KHz)",&adf_current,NULL,NULL);
	if(adf_number==2)execute_calculator_code("(A:ADF ACTIVE FREQUENCY:2, KHz)",&adf_current,NULL,NULL);
	return (int)adf_current;
}

//***************************************************************************
// Set Nav radio new frequency
//	Sample usage: set new nav2 frequency
//		SetNavFreq(iUnits,iDecimals,2);
//***************************************************************************
void SetNavFreq(int nav_unit, int nav_dec, int nav_number)
{
	float i=0; float j=0; float k=0; int nav_set_freq=0;

//Get BCD unit frequency
	if(nav_unit==108)nav_set_freq=2048;
	if(nav_unit==109)nav_set_freq=2304;
	if(nav_unit==110)nav_set_freq=4096;
	if(nav_unit==111)nav_set_freq=4352;
	if(nav_unit==112)nav_set_freq=4608;
	if(nav_unit==113)nav_set_freq=4864;
	if(nav_unit==114)nav_set_freq=5120;
	if(nav_unit==115)nav_set_freq=5376;
	if(nav_unit==116)nav_set_freq=5632;
	if(nav_unit==117)nav_set_freq=5888;

//Calculate BCD fractionals
	j = 0;
	i = 0;
	k = 0;
	if (nav_dec!=0)
	{
		do
		{
			j+=5;
			if(i==0)
			{
				i=1;
				k+=5;
			}
			else
			if (i==1)
			{
				i=0;
				k+=11;
			}
		}
		while (j!= nav_dec);
	}
	nav_set_freq = nav_set_freq + (int)k;

// Variable nav_number allows us to use one function for both navradios.
	if(nav_number==1)trigger_key_event(KEY_NAV1_RADIO_SET,nav_set_freq);
	if(nav_number==2)trigger_key_event(KEY_NAV2_RADIO_SET,nav_set_freq);

	return;
}
