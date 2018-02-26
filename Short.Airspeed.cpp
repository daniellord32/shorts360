//airspeed indication

//Set up the gauge header

char airspeed_gauge_name[]	=	GAUGE_NAME;
extern PELEMENT_HEADER			airspeed_list;
extern MOUSERECT				airspeed_mouse_rect[];

GAUGE_HEADER_FS700(GAUGE_W, airspeed_gauge_name, &airspeed_list,airspeed_mouse_rect, 0, 0, 0, 0);

// end of gauge header

MOUSE_BEGIN( airspeed_mouse_rect, 0, 0, 0 )
MOUSE_END

FAILURE_RECORD airspeed_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_AVIONICS, FAIL_ACTION_NONE},
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_NONE},
	{FAIL_NONE, FAIL_ACTION_NONE}
};

#define MAX_AIRSPEED 260
#define MIN_AIRSPEED 50

NONLINEARITY airspeed_NonLinearity[] = //the more entries made the more accurate the info would be on the gauge.
{
	{{230, 190},	0.00000, 0},
	{{220, 210},	50.0000, 0},
	{{150, 233},	70.0000, 0},
	{{74,  201},	90.0000, 0},
	{{50,  166},   100.0000, 0},
	{{41,  134},   110.0000, 0},
	{{41,  105},   120.0000, 0},
	{{50,   76},   130.0000, 0},
	{{69,   50},   140.0000, 0},
	{{117,  14},   160.0000, 0},
	{{177,  13},   180.0000, 0},
	{{222,  38},   200.0000, 0},
	{{249,  73},   220.0000, 0},
	{{258, 117},   240.0000, 0},
	{{248, 169},   260.0000, 0}
};

FLOAT64 FSAPI needle_src_cb(PELEMENT_NEEDLE pelement)
{
	//Restrict airspeed from 50 knots to 260 knots
	FLOAT64 val = pelement->source_var.var_value.n;

	if ( val > MAX_AIRSPEED ) 
		val = MAX_AIRSPEED;
	if ( val < MIN_AIRSPEED ) 
		val = MIN_AIRSPEED;

	return val;
}

//-----------------------------------------------------------
//			Image draw parameters
//-----------------------------------------------------------

MAKE_NEEDLE
	(
		airspeed_needle,
		BMP_AIRSPEED_NEEDLE,
		NULL,
		airspeed_fail,
		IMAGE_USE_TRANSPARENCY | IMAGE_USE_ERASE | IMAGE_BILINEAR_COLOR,
		0,
		150, 122,
		37, 7,
		AIRSPEED,
		needle_src_cb,
		airspeed_NonLinearity,
		0

	)

PELEMENT_HEADER		airspeed_needle_list[] =
{
	&airspeed_needle.header,
	NULL
};

MAKE_STATIC
	(
		airspeed_background,
		BMP_AIRSPEED_BACKGROUND,
		&airspeed_needle_list,
		&airspeed_fail,
		IMAGE_USE_TRANSPARENCY,
		0,
		0,0
	)

	PELEMENT_HEADER		airspeed_list = &airspeed_background.header;