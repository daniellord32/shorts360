#include <time.h>

//Oil PSI and Temp gauge

//set up the gauge header

char	oil_gauge_name[] =		GAUGE_NAME;
extern	PELEMENT_HEADER			oil_list;
extern	MOUSERECT				oil_mouse_rect[];
GAUGE_CALLBACK					oil_temp_update;

GAUGE_HEADER_FS700(GAUGE_W, oil_gauge_name, &oil_list,oil_mouse_rect, oil_temp_update, 0, 0, 0, 0);

//end of gauge header

MOUSE_BEGIN( oil_mouse_rect, 0, 0, 0 )
MOUSE_END

FAILURE_RECORD oil_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_FREEZE},
	{FAIL_NONE, FAIL_ACTION_NONE}
};

NONLINEARITY oil_psi[] =
{
	{{34,	86},   0.00000,	0},
	{{62,	47},  50.00000,	0},
	{{103,	27}, 100.00000,	0},
	{{148,	29}, 150.00000, 0},
	{{188,	50}, 200.00000, 0},
	{{218,	86}, 250.00000, 0}
};

NONLINEARITY oil_temp[] =
{
	{{203,	184}, -20.00000,	0},
	{{186,	203},	0.00000,	0},
	{{168,	215},  20.00000,	0},
	{{123,	224},  60.00000,	0},
	{{ 79,	213}, 100.00000,	0},
	{{ 43,	182}, 140.00000,	0}
};

// varibles used within gauge
 time_t timer;

 UINT8 fuelPsi,oilTemp;
 MODULE_VAR temp = {ENGINE1_OIL_TEMPERATURE}; //gets engine 1 temperature.
 MODULE_VAR PSI = {ENGINE1_OIL_PRESSURE}; //gets engine 1 oil pressure.

#define PSI_MAX 200
#define PSI_MIN 0
#define TEMP_MAX 140
#define TEMP_MIN -20
double oil_warn = 0;
double psu_warn = 0;
ID oil_warningId;
ID psu_warningId;

//basic needle max and min values to configure needle movement.
FLOAT64 FSAPI oil_psi_cb(PELEMENT_NEEDLE pelement)
{
	lookup_var(&PSI);
	fuelPsi = PSI.var_value.n/160;

	if(fuelPsi > PSI_MAX)
	{
		fuelPsi = PSI_MAX;
		
	}
	if( fuelPsi < PSI_MIN)
	{
		fuelPsi = PSI_MIN;
		set_named_variable_value(psu_warningId, (FLOAT64)psu_warn); //send c++ data to XML file.
	}

	return fuelPsi;
}

//basic needle max and min values to configure needle movement.
FLOAT64 FSAPI oil_temp_cb(PELEMENT_NEEDLE pelement)
{
	lookup_var(&temp);
	oilTemp = temp.var_value.n / 160;

	if (oilTemp > PSI_MAX)
	{
		oilTemp = PSI_MAX;
		
	}
	if (oilTemp < PSI_MIN)
	{
		oilTemp = PSI_MIN;
	}

	return oilTemp;
	
}

void FSAPI oil_temp_update(PGAUGEHDR pgauge, int service_id, UINT32 extra_data)
{
	switch (service_id)
	{

	case PANEL_SERVICE_PRE_INSTALL:
		break;
	case PANEL_SERVICE_POST_INSTALL:
		break;
	case PANEL_SERVICE_PRE_INITIALIZE:
		break;
	case PANEL_SERVICE_PRE_UPDATE: //checks 18 times a second.
		//oil temp Init
		oilTemp = TEMP_MAX;
		lookup_var(&temp);
		oilTemp = temp.var_value.n / 160;

		//oil pressure Init
		fuelPsi = PSI_MAX;
		lookup_var(&PSI);
		oilTemp = PSI.var_value.n / 160;

		//timer Init
		int maxTime = 15 * 60;
		time(&timer);
		double mins = difftime(timer, maxTime);

		//Oil temp alogritim
		//if it takes longer then 15 minutes to respond to high temp warning, engine will catch fire.
		if (oilTemp >= TEMP_MAX)
		{
			if (mins > maxTime)
			{
				ENGINE1_ON_FIRE : 1;
			}
			set_named_variable_value(oil_warningId, (FLOAT64)oil_warn); //send c++ data to XML file.
		}
		if (oilTemp < TEMP_MIN)
		{
			oilTemp = TEMP_MIN;
			set_named_variable_value(oil_warningId, (FLOAT64)oil_warn); //send c++ data to XML file.
			if (mins > maxTime)
			{
				ENGINE1_FUEL_PUMP_ON : 0; //shuts down the engine (simulate engine seizure).
				//Will need to program a new way of shutting down engine that can not be restarted.
			}
		}

		//Oil Pressure Algoritim
		//if it takes longer then 15 minutes to respond to high temp warning, engine will catch fire.
		if (oilTemp >= TEMP_MAX)
		{
			if (mins > maxTime)
			{
				ENGINE1_ON_FIRE : 1;
			}
			set_named_variable_value(psu_warningId, (FLOAT64)psu_warn); //send c++ data to XML file. 
		}
		if (oilTemp < TEMP_MIN)
		{
			oilTemp = TEMP_MIN;
			set_named_variable_value(psu_warningId, (FLOAT64)psu_warn); //send c++ data to XML file.
			if (mins > maxTime)
			{
				ENGINE1_FUEL_PUMP_ON : 0; //shuts down the engine (simulate engine seizure).
				//Will need to program a new way of shutting down engine that can not be restarted.
			}
		}
		break;
	case PANEL_SERVICE_PRE_DRAW:
		break;
	case PANEL_SERVICE_PRE_KILL:
		break;
	case PANEL_SERVICE_DISCONNECT:
		break;
	}
}

//-----------------------------------------------------------
//			Image draw parameters
//-----------------------------------------------------------

MAKE_NEEDLE
	(
		oil_psi_needle,
		BMP_RPM_NEEDLELG,
		NULL,
		oil_fail,
		IMAGE_USE_TRANSPARENCY | IMAGE_USE_ERASE | IMAGE_BILINEAR_COLOR,
		0,
		124,117,
		21,8,
		MODULE_VAR_NONE,
		oil_psi_cb,
		oil_psi,
		0
	)

	PELEMENT_HEADER		oil_psi_needle_list[] =
{
	&oil_psi_needle.header,
	NULL
};

MAKE_NEEDLE
	(
		oil_temp_needle,
		BMP_RPM_NEEDLELG,
		&oil_psi_needle_list,
		oil_fail,
		IMAGE_USE_TRANSPARENCY | IMAGE_USE_ERASE | IMAGE_BILINEAR_COLOR,
		0,
		124,117,
		21,8,
		MODULE_VAR_NONE,
		oil_temp_cb,
		oil_temp,
		0
	)

		PELEMENT_HEADER		oil_temp_needle_list[] =
{
	&oil_temp_needle.header,
	NULL
};

MAKE_STATIC
	(
		oil_background,
		BMP_OIL_BACKGROUND,
		&oil_temp_needle_list,
		&oil_fail,
		IMAGE_USE_TRANSPARENCY,
		0,
		0,0
	)

	PELEMENT_HEADER		oil_list = &oil_background.header;


///////////////////////////////////////////////////////////////////////
//				Undefine for memory managment
//////////////////////////////////////////////////////////////////////
#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W