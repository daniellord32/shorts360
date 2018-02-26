// Copyright (c) Daniel Lord

// This is for engine 1 revolutions per minute (RPM)

//Set up the gauge header

char torquee1_gauge_name[]	=	GAUGE_NAME;
extern PELEMENT_HEADER			torquee1_list;
extern MOUSERECT				torquee1_mouse_rect[];

GAUGE_HEADER_FS700(GAUGE_W, torquee1_gauge_name, &torquee1_list,torquee1_mouse_rect, 0, 0, 0, 0);

// end of gauge header

MOUSE_BEGIN( torquee1_mouse_rect, 0, 0, 0 )
MOUSE_END

/////////////////////////////////////////////////////////////////////////////
FAILURE_RECORD torquee1_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_ZERO},
	{FAIL_NONE, FAIL_ACTION_NONE}
};
/////////////////////////////////////////////////////////////////////////////

MODULE_VAR torque = {ENGINE1_TORQUE};

UINT8 tNum = 0;

#define MAX_TORQUE 6
#define MIN_TORQUE 0

NONLINEARITY engine1Torque_nonlinearity[]= //defines needle movement to gauge readout
{
	{{40, 104}, 0.00000, 0},
	{{34, 96},  1.00000, 0},
	{{15, 61},	2.00000, 0},
	{{30, 29},	3.00000, 0},
	{{61, 16},	4.00000, 0},
	{{90, 29},	5.00000, 0},
	{{100, 60}, 6.00000, 0}
};

FLOAT64 FSAPI E1Torque_cb(PELEMENT_NEEDLE pelement)
{
	lookup_var(&torque);
	tNum = torque.var_value.n/163;

	if(tNum > 6)
		tNum = MAX_TORQUE; //crops to 6 on the gauge readout.
	if(tNum <= 0)
		tNum = MIN_TORQUE; //crops to below 1 or no torque on gauge readout.

	return tNum;
}

//-----------------------------------------------------------
//			Image draw perameters
//-----------------------------------------------------------

MAKE_NEEDLE
	(
		Engine1_Torque_needle,
		BMP_TORQUE_NEEDLE,
		NULL,
		torquee1_fail,
		IMAGE_USE_TRANSPARENCY|IMAGE_USE_ERASE|IMAGE_BILINEAR_COLOR,
		0,
		58, 61,
		72, 10,
		MODULE_VAR_NONE,
		E1Torque_cb,
		engine1Torque_nonlinearity,
		0
	)

PELEMENT_HEADER		Torque_needle_list[] =
{
	&Engine1_Torque_needle.header,
	NULL
};

MAKE_STATIC
	(
		Engine1_background,
		BMP_TORQUE_BACKGROUND,
		&Torque_needle_list,
		&torquee1_fail,
		IMAGE_USE_TRANSPARENCY,
		0,
		0,0
	)

PELEMENT_HEADER		torquee1_list = &Engine1_background.header;

///////////////////////////////////////////////////////////////////////
//				Undefine for memory managment
//////////////////////////////////////////////////////////////////////
#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W