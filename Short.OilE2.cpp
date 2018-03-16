#include <time.h>

//Oil PSI and Temp gauge

//set up the gauge header

char	oile2_gauge_name[] =		GAUGE_NAME;
extern	PELEMENT_HEADER			oile2_list;
extern	MOUSERECT				oile2_mouse_rect[];

GAUGE_HEADER_FS700(GAUGE_W, oile2_gauge_name, &oile2_list,oile2_mouse_rect, 0, 0, 0, 0);

//end of gauge header

MOUSE_BEGIN( oile2_mouse_rect, 0, 0, 0 )
MOUSE_END

FAILURE_RECORD oile2_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_FREEZE},
	{FAIL_NONE, FAIL_ACTION_NONE}
};

NONLINEARITY oile2_psi[] =
{
	{{34,	86},   0.00000,	0},
	{{62,	47},  50.00000,	0},
	{{103,	27}, 100.00000,	0},
	{{148,	29}, 150.00000, 0},
	{{188,	50}, 200.00000, 0},
	{{218,	86}, 250.00000, 0}
};

NONLINEARITY oile2_temp[] =
{
	{{203,	184}, -20.00000,	0},
	{{186,	203},	0.00000,	0},
	{{168,	215},  20.00000,	0},
	{{123,	224},  60.00000,	0},
	{{ 79,	213}, 100.00000,	0},
	{{ 43,	182}, 140.00000,	0}
};

// varibles used within gauge
 time_t timer1;

 UINT8 fuelPsi2,oilTemp2;
 MODULE_VAR temp2 = {ENGINE2_OIL_TEMPERATURE};
 MODULE_VAR PSI2 = {ENGINE2_OIL_PRESSURE};

#define PSI_MAX 200
#define PSI_MIN 0
#define TEMP_MAX 140
#define TEMP_MIN -20

FLOAT64 FSAPI oile2_psi_cb(PELEMENT_NEEDLE pelement)
{
	lookup_var(&PSI2);
	fuelPsi2 = PSI2.var_value.n/160;

	if(fuelPsi2 > PSI_MAX)
	{
		fuelPsi2 = PSI_MAX;
		//Warning to show here on anumicator, if not solved engine can fail
		//need to find out if it is possible to do.
	}
	if( fuelPsi2 < PSI_MIN)
	{
		fuelPsi2 = PSI_MIN;
		//Warning to show here on anumicator
		//need to find out if it is possible to do.
	}

	return fuelPsi2;
}

FLOAT64 FSAPI oile2_temp_cb(PELEMENT_NEEDLE pelement)
{
	lookup_var(&temp2);
	oilTemp2 = temp2.var_value.n/160;
	//idea is if it takes longer then 15 minutes to respond to high temp warning, engine will catch fire.
	if(oilTemp2 >= TEMP_MAX)
	{
		oilTemp2 = TEMP_MAX;
		int maxTime = 15*60;
		time(&timer1);
		double mins = difftime(timer1,maxTime);
		if(mins > maxTime)
		{
			ENGINE2_ON_FIRE:1;
		}
		//Warning to show here on anumicator, if not solved can start engine fire!
		//need to find out if it is possible to do.
	}
	if(oilTemp2 < TEMP_MIN)
	{
		oilTemp2 = TEMP_MIN;
		//Warning to show here on anumicator, if not solved engine can fail!
		//need to find out if it is possible to do.
	}
	return oilTemp2;
}

//-----------------------------------------------------------
//			Image draw parameters
//-----------------------------------------------------------

MAKE_NEEDLE
	(
		oile2_psi_needle,
		BMP_RPM_NEEDLELG,
		NULL,
		oile2_fail,
		IMAGE_USE_TRANSPARENCY | IMAGE_USE_ERASE | IMAGE_BILINEAR_COLOR,
		0,
		124,117,
		21,8,
		MODULE_VAR_NONE,
		oile2_psi_cb,
		oile2_psi,
		0
	)

	PELEMENT_HEADER		oile2_psi_needle_list[] =
{
	&oile2_psi_needle.header,
	NULL
};

MAKE_NEEDLE
	(
		oile2_temp_needle,
		BMP_RPM_NEEDLELG,
		&oile2_psi_needle_list,
		oile2_fail,
		IMAGE_USE_TRANSPARENCY | IMAGE_USE_ERASE | IMAGE_BILINEAR_COLOR,
		0,
		124,117,
		21,8,
		MODULE_VAR_NONE,
		oile2_temp_cb,
		oile2_temp,
		0
	)

		PELEMENT_HEADER		oile2_temp_needle_list[] =
{
	&oile2_temp_needle.header,
	NULL
};

MAKE_STATIC
	(
		oile2_background,
		BMP_OIL_BACKGROUND,
		&oile2_temp_needle_list,
		&oile2_fail,
		IMAGE_USE_TRANSPARENCY,
		0,
		0,0
	)

	PELEMENT_HEADER		oile2_list = &oile2_background.header;


///////////////////////////////////////////////////////////////////////
//				Undefine for memory managment
//////////////////////////////////////////////////////////////////////
#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W