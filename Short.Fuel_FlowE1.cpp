// Copyright (c) Daniel Lord

// This is for engine 1 revolutions per minute (RPM)

//Set up the gauge header

char fuelflowe1_gauge_name[]	=	GAUGE_NAME;
extern PELEMENT_HEADER			fuelflowe1_list;
extern MOUSERECT				fuelflowe1_mouse_rect[];

GAUGE_HEADER_FS700(GAUGE_W, fuelflowe1_gauge_name, &fuelflowe1_list, fuelflowe1_mouse_rect, 0, 0, 0, 0);

// end of gauge header

MOUSE_BEGIN( fuelflowe1_mouse_rect, 0, 0, 0 )
MOUSE_END

/////////////////////////////////////////////////////////////////////////////
FAILURE_RECORD fuelflowe1_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_ZERO},
	{FAIL_NONE, FAIL_ACTION_NONE}
};
/////////////////////////////////////////////////////////////////////////////

//Variables to be used in gauge.

MODULE_VAR fuelFlowE1 = {ENGINE1_FF_PPH}; //Engine 1 Fuel Flow Pounds per hour (PPH).

UINT8 flow = 0;
#define MAX_FLOW 4500
#define MIN_FLOW 0

NONLINEARITY engine1FuelFlow_nonlinearity[] =
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

FLOAT64 FSAPI e1FuelFlow_cb( PELEMENT_NEEDLE pelement )
{
	lookup_var(&fuelFlowE1); //look up var as it constantly changing.
	flow = fuelFlowE1.var_value.n; //set value to variable.

	if(flow >= 500)
		flow = MAX_FLOW;
	if(flow <= 0)
		flow = MIN_FLOW;

	return flow;
}

//-----------------------------------------------------------
//			Image draw perameters
//-----------------------------------------------------------

MAKE_NEEDLE
	(
		FF_Engine1,
		BMP_FFENGINE_NEEDLE1,
		NULL,
		fuelflowe1_fail,
		IMAGE_USE_TRANSPARENCY|IMAGE_USE_ERASE|IMAGE_BILINEAR_COLOR,
		0,
		137,131,
		53,10,
		MODULE_VAR_NONE,
		e1FuelFlow_cb,
		engine1FuelFlow_nonlinearity,
		0

	)

	PELEMENT_HEADER FF_Engine1_list[] =
{
	&FF_Engine1.header,
	NULL
};

MAKE_STATIC
	(
		FF_Background,
		BMP_FF_BACKGROUND,
		&FF_Engine1_list,
		&fuelflowe1_fail,
		IMAGE_USE_TRANSPARENCY,
		0,
		0,0
	)

	PELEMENT_HEADER fuelflowe1_list = &FF_Background.header;

///////////////////////////////////////////////////////////////////////
//				Undefine for memory managment
//////////////////////////////////////////////////////////////////////
#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W

