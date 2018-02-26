//Copyright (c) Microsoft Corporation.  All rights reserved. 

//	Set up gauge header
char fuelrt_gauge_name[]		= GAUGE_NAME;
extern PELEMENT_HEADER		fuelrt_list;
extern MOUSERECT			fuelrt_mouse_rect[];

GAUGE_HEADER_FS700( GAUGE_W, fuel_gauge_name, &fuel_list, \
						fuel_mouse_rect, 0, 0, 0, 0 );


/////////////////////////////////////////////////////////////////////////////
FAILURE_RECORD	fuelrt_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_ZERO},
	{FAIL_GAUGE_FUEL_INDICATORS, FAIL_ACTION_FREEZE},
	{FAIL_NONE, FAIL_ACTION_NONE}
};


/////////////////////////////////////////////////////////////////////////////
#define	GAUGE_MIN_FUEL	0
#define	GAUGE_MAX_FUEL	75

NONLINEARITY  fuelrt_nonlinearity[] =
{
	{{30,	182},	 0, 0},
	{{119,	 47},	25, 0},
	{{246,	 93},	50, 0},
	{{241,	221},	75, 0}
};

//-------------------------------------------------------
//			Custom code for needle manipulation
//-------------------------------------------------------

FLOAT64 FSAPI fuelrt_needle_cb( PELEMENT_NEEDLE pelement )
{
	FLOAT64	val = pelement->source_var.var_value.n;

	if (val > GAUGE_MAX_FUEL)
		val = GAUGE_MAX_FUEL;
	else if (val < GAUGE_MIN_FUEL)
		val = GAUGE_MIN_FUEL;

	return val;
}

//------------------------------------------------------
//		Image draw perameters
//------------------------------------------------------

MAKE_NEEDLE
(
	fuelrt_needle,		
	BMP_FUEL_NEEDLE,	
	NULL,				
	fuelrt_fail,			
	IMAGE_USE_TRANSPARENCY|IMAGE_USE_ERASE|IMAGE_BILINEAR_COLOR,
	0,
	125, 125,			// location on backgroudn image where needle rotates. x = x/2 y = y/2
	6, 12,
	FUEL_TANK_RIGHT_MAIN_LEVEL,
	fuelrt_needle_cb,
	fuelrt_nonlinearity,
	6
)


PELEMENT_HEADER		fuelrt_needle_list[] =
{
	(PELEMENT_HEADER)&fuelrt_needle,
	NULL
};


/////////////////////////////////////////////////////////////////////////////
MAKE_STATIC
(
	fuelrt_background,
	BMP_FUEL_BACKGROUND,
	&fuel_needle_list,
	fuelrt_fail,
	IMAGE_USE_TRANSPARENCY,
	0,
	9, 0
)

PELEMENT_HEADER		fuelrt_list	= &fuelrt_background.header;

/////////////////////////////////////////////////////////////////////////////
MOUSE_BEGIN( fuelrt_mouse_rect, HELPID_GAUGE_FUEL, 0, 0 )
MOUSE_END


//---------------------------------------------------------------------------
//			Undefine for memory management
//---------------------------------------------------------------------------
#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W

