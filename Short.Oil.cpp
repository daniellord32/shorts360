#include <time.h>

//Oil PSI and Temp gauge

//set up the gauge header

char	oil_gauge_name[] =		GAUGE_NAME;
extern	PELEMENT_HEADER			oil_list;
extern	MOUSERECT				oil_mouse_rect[];

GAUGE_HEADER_FS700(GAUGE_W, oil_gauge_name, &oil_list,oil_mouse_rect, 0, 0, 0, 0);

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
 MODULE_VAR temp = {ENGINE1_OIL_TEMPERATURE};
 MODULE_VAR PSI = {ENGINE1_OIL_PRESSURE};

#define PSI_MAX 200
#define PSI_MIN 0
#define TEMP_MAX 140
#define TEMP_MIN -20

FLOAT64 FSAPI oil_psi_cb(PELEMENT_NEEDLE pelement)
{
	lookup_var(&PSI);
	fuelPsi = PSI.var_value.n/160;

	if(fuelPsi > PSI_MAX)
	{
		fuelPsi = PSI_MAX;
		//Warning to show here on anumicator, if not solved engine can fail
		//need to find out if it is possible to do.
	}
	if( fuelPsi < PSI_MIN)
	{
		fuelPsi = PSI_MIN;
		//Warning to show here on anumicator
		//need to find out if it is possible to do.
	}

	return fuelPsi;
}

FLOAT64 FSAPI oil_temp_cb(PELEMENT_NEEDLE pelement)
{
	lookup_var(&temp);
	oilTemp = temp.var_value.n/160;
	//idea is if it takes longer then 15 minutes to respond to high temp warning, engine will catch fire.
	if(oilTemp >= TEMP_MAX)
	{
		oilTemp = TEMP_MAX;
		int maxTime = 15*60;
		time(&timer);
		double mins = difftime(timer,maxTime);
		if(mins > maxTime)
		{
			ENGINE1_ON_FIRE:1;
		}
		//Warning to show here on anumicator, if not solved can start engine fire!
		//need to find out if it is possible to do.
	}
	if(oilTemp < TEMP_MIN)
	{
		oilTemp = TEMP_MIN;
		//Warning to show here on anumicator, if not solved engine can fail!
		//need to find out if it is possible to do.
	}
	return oilTemp;
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