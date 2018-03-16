// Copyright (c) Daniel Lord

// This is for engine 2 Fuel Flow Pounds per hour (PPH)

//Set up the gauge header

char fuelflowe2_gauge_name[]	=	GAUGE_NAME;
extern PELEMENT_HEADER			fuelflowe2_list;
extern MOUSERECT				fuelflowe2_mouse_rect[];

GAUGE_HEADER_FS700(GAUGE_W, fuelflowe2_gauge_name, &fuelflowe2_list, fuelflowe2_mouse_rect, 0, 0, 0, 0);

// end of gauge header

MOUSE_BEGIN( fuelflowe2_mouse_rect, 0, 0, 0 )
MOUSE_END

/////////////////////////////////////////////////////////////////////////////
FAILURE_RECORD fuelflowe2_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_ZERO},
	{FAIL_NONE, FAIL_ACTION_NONE}
};
/////////////////////////////////////////////////////////////////////////////

//Variables to be used in gauge.

MODULE_VAR fuelFlowE2 = {ENGINE2_FF_PPH}; //Engine 2 Fuel Flow Pounds per hour (PPH).

UINT8 flow1 = 0;
#define MAX_FLOW 4500
#define MIN_FLOW 0

NONLINEARITY engine2FuelFlow_nonlinearity[] =
{
	{{66,	220},	 0.00000, 0},
	{{27,	155},	 5.00000, 0},
	{{41,	 80},	15.00000, 0},
	{{98,	 32},	20.00000, 0},
	{{172,	 33},	30.00000, 0},
	{{230,	 81},	35.00000, 0},
	{{244,	156},	40.00000, 0},
	{{206,	219},	45.00000, 0}
};

FLOAT64 FSAPI e2FuelFlow_cb( PELEMENT_NEEDLE pelement )
{
	lookup_var(&fuelFlowE2); //look up var as it constantly changing.
	flow1 = fuelFlowE2.var_value.n; //set value to variable.

	if(flow1 >= 500)
		flow1 = MAX_FLOW;
	if(flow1 <= 0)
		flow1 = MIN_FLOW;

	return flow1;
}

//-----------------------------------------------------------
//			Image draw perameters
//-----------------------------------------------------------

MAKE_NEEDLE
	(
		FF_Engine2,
		BMP_FFENGINE_NEEDLE2,
		NULL,
		fuelflowe2_fail,
		IMAGE_USE_TRANSPARENCY|IMAGE_USE_ERASE|IMAGE_BILINEAR_COLOR,
		0,
		137,131,
		53,10,
		MODULE_VAR_NONE,
		e2FuelFlow_cb,
		engine2FuelFlow_nonlinearity,
		0

	)

	PELEMENT_HEADER FF_Engine2_list[] =
{
	&FF_Engine2.header,
	NULL
};

MAKE_STATIC
	(
		FF_Background2,
		BMP_FF_BACKGROUND,
		&FF_Engine2_list,
		&fuelflowe2_fail,
		IMAGE_USE_TRANSPARENCY,
		0,
		0,0
	)

	PELEMENT_HEADER fuelflowe2_list = &FF_Background2.header;

///////////////////////////////////////////////////////////////////////
//				Undefine for memory managment
//////////////////////////////////////////////////////////////////////
#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W

