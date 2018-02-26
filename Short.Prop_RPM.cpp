// Copyright (c) Daniel Lord

// Gauge for Engine 1 prop shaft RPM

#include "windsaloft.h";

//Set up the gauge header

char proprpm_gauge_name[]	=	GAUGE_NAME;
extern PELEMENT_HEADER			proprpm_list;
extern MOUSERECT				proprpm_mouse_rect[];

GAUGE_HEADER_FS700(GAUGE_W, proprpm_gauge_name, &proprpm_list,proprpm_mouse_rect, 0, 0, 0, 0);

// end of gauge header

MOUSE_BEGIN( proprpm_mouse_rect, 0, 0, 0 )
MOUSE_END

/////////////////////////////////////////////////////////////////////////////
FAILURE_RECORD proprpm_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_ZERO},
	{FAIL_NONE, FAIL_ACTION_NONE}
};
////////////////////////////////////////////////////////////////////////////

//variables

MODULE_VAR propRPM = {PROPELLER_1_RPM};
UINT8 rpmProp1 = 0;

#define MAX_RPM 25520
#define MIN_RPM 0

NONLINEARITY propRPM_nonlinearity_list [] =
{
	{{41,	174},	0.00000, 0},
	{{26,	131},	2.00000, 0},
	{{35,	 86},	4.00000, 0},
	{{63,	 50},	6.00000, 0},
	{{102,	 29},	8.00000, 0},
	{{149,	 29},	10.00000,0},
	{{190,	 47},	12.00000,0},
	{{216,	 87},	14.00000,0},
	{{223,	133},	16.00000,0},
	{{207,	176},	20.00000,0}
};

FLOAT64 FSAPI prop_cb(PELEMENT_NEEDLE pelement)
{
	lookup_var(&propRPM);
	rpmProp1 = propRPM.var_value.n/100;

	if(rpmProp1 >= MAX_RPM)
		rpmProp1 = MAX_RPM;
	if(rpmProp1 <= MIN_RPM)
		rpmProp1 = MIN_RPM;

	return rpm;
}

FLOAT64 FSAPI prop1_7seg_cb(PELEMENT_STRING pelement)
{
	lookup_var(&propRPM);
	double val = propRPM.var_value.n/10;

	if(rpmProp1 >= MAX_RPM)
	{
		sprintf(pelement->string, "%2.1f",(FLOAT64)val);
	}
	if(rpmProp1 <= MIN_RPM)
	{
		sprintf(pelement->string, "%2.1f",(FLOAT64)val);
	}
	return val;
}

//-----------------------------------------------------------
//			Image draw perameters
//-----------------------------------------------------------



MAKE_NEEDLE
	(
		prop1_rpm,
		BMP_RPM_NEEDLE1,
		NULL,
		&proprpm_fail,
		IMAGE_USE_TRANSPARENCY|IMAGE_USE_ERASE|IMAGE_BILINEAR_COLOR,
		0,
		120,123,
		53,9,
		MODULE_VAR_NONE,
		prop_cb,
		propRPM_nonlinearity_list,
		0
	)

		PELEMENT_HEADER		prop1_needle_list[] =
{
	&prop1_rpm.header,
	NULL
};

MAKE_STRING
	(
		prop1_7seg,
		&prop1_needle_list,
		&proprpm_fail,
		IMAGE_USE_ERASE | IMAGE_USE_BRIGHT | IMAGE_USE_TRANSPARENCY,
		0,
		100, 175,
		80, 50,
		5,
		PROPELLER_1_RPM,
		MODULE_VAR_NONE,
		MODULE_VAR_NONE,
		bright_red,
		trans_black,
		bright_yellow,
		dseg7,
		normal,
		GAUGE_CHARSET,
		0,
		NULL,
		NULL,
		prop1_7seg_cb
		)

		PELEMENT_HEADER		prop1_7seg_list[] =
{
	&prop1_7seg.header,
	NULL
};

MAKE_STATIC
	(
		proprpm_background,
		BMP_PROP_RPM,
		&prop1_7seg_list,
		&proprpm_fail,
		IMAGE_USE_TRANSPARENCY,
		0,
		0,0
	)

	PELEMENT_HEADER proprpm_list = &proprpm_background.header;
///////////////////////////////////////////////////////////////////////
//				Undefine for memory managment
//////////////////////////////////////////////////////////////////////
#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W