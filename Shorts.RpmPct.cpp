// Copyright (c) Daniel Lord

// This is for engine 1 revolutions per minute (RPM)

//Set up the gauge header

char rpmpct_gauge_name[]	=	GAUGE_NAME;
extern PELEMENT_HEADER			rpmpct_list;
extern MOUSERECT				rpmpct_mouse_rect[];

GAUGE_HEADER_FS700(GAUGE_W, rpmpct_gauge_name, &rpmpct_list,rpmpct_mouse_rect, 0, 0, 0, 0);

// end of gauge header

//MOUSE_BEGIN( rpmpct_mouse_rect, 0, 0, 0 )
//MOUSE_END

/////////////////////////////////////////////////////////////////////////////
FAILURE_RECORD rpmpct_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_ZERO},
	{FAIL_NONE, FAIL_ACTION_NONE}
};
/////////////////////////////////////////////////////////////////////////////



MODULE_VAR generator1 = {ENGINE1_N1_RPM};

UINT8 rpm1 = 0;

#define MAX_RPM 100
#define MIN_RPM 0

NONLINEARITY Engine1PCT_nonlinearity[] = //exact location of needle movement from 0% to 100%
{
	{{55,  194},  0.00000, 0},
	{{32,  153}, 10.00000, 0},
	{{28,  109}, 20.00000, 0},
	{{47,   66}, 30.00000, 0},
	{{82,   36}, 40.00000, 0},
	{{126,  27}, 50.00000, 0},
	{{170,  38}, 60.00000, 0},
	{{204,  68}, 70.00000, 0},
	{{224, 109}, 80.00000, 0},
	{{219, 156}, 90.00000, 0},
	{{201, 190}, 100.00000, 0}
};

NONLINEARITY Engine1Tens_nonlinearity[] = //exact needle movement for smaller tens percentage from 0% to 100%
{
	{{120, 173}, 0.00000, 0},
	{{132, 176}, 1.00000, 0},
	{{141, 188}, 2.00000, 0},
	{{139, 201}, 3.00000, 0},
	{{132, 212}, 4.00000, 0},
	{{120, 216}, 5.00000, 0},
	{{107, 212}, 6.00000, 0},
	{{ 99, 203}, 7.00000, 0},
	{{ 99, 187}, 8.00000, 0},
	{{106, 176}, 9.00000, 0}
};

FLOAT64 FSAPI Engine1_cb( PELEMENT_NEEDLE pelement )
{
	lookup_var(&generator1);
	rpm1 = generator1.var_value.n/160;
	

	if(rpm1 >= 100)
		rpm1 = MAX_RPM; //crop to 100%
	if(rpm1 <= MIN_RPM)
		rpm1 = MIN_RPM; // crop to 0

	return rpm1;
}

//-----------------------------------------------------------
//			Image draw perameters
//-----------------------------------------------------------

MAKE_NEEDLE
	(
		Engine1_RPM_SML,
		BMP_RPM_NEEDLESM,
		NULL,
		rpmpct_fail,
		IMAGE_USE_TRANSPARENCY|IMAGE_USE_ERASE|IMAGE_BILINEAR_COLOR,
		0,
		119, 195,
		5, 5,
		MODULE_VAR_NONE, //need to change to conpensate for smaller range.
		Engine1_cb,
		Engine1Tens_nonlinearity,
		0
	)

	PELEMENT_HEADER		RPM_needle_SML_list[] =
{
	&Engine1_RPM_SML.header,
	NULL
};

MAKE_NEEDLE
	(
		Engine1_RPM,
		BMP_RPM_NEEDLELG,
		&RPM_needle_SML_list,
		rpmpct_fail,
		IMAGE_USE_TRANSPARENCY|IMAGE_USE_ERASE|IMAGE_BILINEAR_COLOR,
		0,
		125, 125,
		21, 8,
		MODULE_VAR_NONE,
		Engine1_cb,
		Engine1PCT_nonlinearity,
		0)

PELEMENT_HEADER		RPM_needle_list[] =
{
	&Engine1_RPM.header,
	NULL
};

MAKE_STATIC
	(
		rpm_background,
		BMP_RPM_BACKGROUND,
		&RPM_needle_list,
		&rpmpct_fail,
		IMAGE_USE_TRANSPARENCY,
		0,
		0,0
	)

	PELEMENT_HEADER		rpmpct_list	= &rpm_background.header;
///////////////////////////////////////////////////////////////////////
MOUSE_BEGIN( rpmpct_mouse_rect, rpm1, 0, 0 )
MOUSE_END

///////////////////////////////////////////////////////////////////////
//				Undefine for memory managment
//////////////////////////////////////////////////////////////////////
#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W