//Com 1 gauge

//Set up the gauge header

char com1_gauge_name[] =		GAUGE_NAME;
extern PELEMENT_HEADER			com1_list;
extern MOUSERECT				com1_mouse_rect[];
GAUGE_CALLBACK					com1_update;
GAUGE_HEADER_FS700(GAUGE_W, com1_gauge_name, &com1_list, com1_mouse_rect, 0, 0, 0, 0);

MOUSE_BEGIN(com1_mouse_rect, 0, 0, 0)
MOUSE_END

FAILURE_RECORD com1_fail[] =
{
	{ FAIL_SYSTEM_ELECTRICAL_AVIONICS, FAIL_ACTION_NONE },
	{ FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_NONE },
	{ FAIL_NONE, FAIL_ACTION_NONE }
};



int dimbrt = 0;
int asi_pwr = 0;

//Allows access to Avar variables (XML).
FLOAT64 AVar(PCSTRINGZ szName, UINT32 iIndex, PCSTRINGZ szUnits)
{
	return aircraft_varget(get_aircraft_var_enum(szName),
		get_units_enum(szUnits), iIndex);
}

//gets AVar and prints formated
FLOAT64 FSAPI com1_active_cb(PELEMENT_STRING pelement)
{
	FLOAT64 com1_active = AVar("COM ACTIVE FREQUENCY", 1, "Mhz");
	sprintf(pelement->string, "%3.2f", com1_active);
	return com1_active;
}

FLOAT64 FSAPI com1_stby_cb(PELEMENT_STRING pelement)
{
	FLOAT64 com1_stby = AVar("COM STANDBY FREQUENCY", 1, "Mhz");
	sprintf(pelement->string, "%3.2f", com1_stby);
	return com1_stby;
}

FLOAT64 FSAPI lightstate_cb(PELEMENT_ICON pelement)
{
	return dimbrt;
}

void FSAPI com1_update(PGAUGEHDR pgauge, int service_id, UINT32 extra_data)
{
	switch (service_id)
	{
		/* "install_routine()" */

	case    PANEL_SERVICE_PRE_INSTALL:
		break;

		/* "initialize_routine()" */

	case    PANEL_SERVICE_PRE_INITIALIZE:

		break;

		/* "update_routine()" */

	case    PANEL_SERVICE_PRE_UPDATE:

		if (power_on != 0)
		{
			if (dimbrt == 1)
			{
				//sets backlighting to dim.
				LUMINOUS_LISTELEMENT(pgauge->elements_list[0], 1);
				LUMINOUS_LISTELEMENT(pgauge->elements_list[0], 2);
				LUMINOUS_LISTELEMENT(pgauge->elements_list[0], 3);

			}
			else
				if (dimbrt == 2)
				{
					//set backligting to bright.
					LIGHT_LISTELEMENT(pgauge->elements_list[0], 1);
					LIGHT_LISTELEMENT(pgauge->elements_list[0], 2);
					LIGHT_LISTELEMENT(pgauge->elements_list[0], 3);
				}

		}
		else
		{
			//if no power turn off lighting.
			DARKEN_LISTELEMENT(pgauge->elements_list[0], 1);
			DARKEN_LISTELEMENT(pgauge->elements_list[0], 2);
			DARKEN_LISTELEMENT(pgauge->elements_list[0], 3);
			DELUMINOUS_LISTELEMENT(pgauge->elements_list[0], 1);
			DELUMINOUS_LISTELEMENT(pgauge->elements_list[0], 2);
			DELUMINOUS_LISTELEMENT(pgauge->elements_list[0], 3);
		}
		break;
	}
}

//-----------------------------------------------------------
//			Image draw parameters
//-----------------------------------------------------------
MAKE_STRING
	(
		com1_active_7seg,
		NULL,
		&com1_fail,
		IMAGE_USE_ERASE | IMAGE_USE_BRIGHT | IMAGE_USE_TRANSPARENCY,
		0,
		100, 175,
		80, 50,
		5,
		MODULE_VAR_NONE,
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
		com1_active_cb
	)

PELEMENT_HEADER		com1_active_7seg_list[] =
{
	&com1_active_7seg.header,
	NULL
};

MAKE_STRING
(
	com1_stby_7seg,
	&com1_active_7seg_list,
	&com1_fail,
	IMAGE_USE_ERASE | IMAGE_USE_BRIGHT | IMAGE_USE_TRANSPARENCY,
	0,
	100, 175,
	80, 50,
	5,
	MODULE_VAR_NONE,
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
	com1_stby_cb
)

PELEMENT_HEADER		com1_stby_7seg_list[] =
{
	&com1_stby_7seg.header,
	NULL
};

MAKE_ICON
(
	com1_night,
	BMP_COM1_NIGHT,
	&com1_stby_7seg_list,
	NULL,
	IMAGE_USE_ERASE | IMAGE_USE_BRIGHT | IMAGE_USE_TRANSPARENCY,
	0,
	0, 0,
	MODULE_VAR_NONE,lightstate_cb,
	NULL,
	1,
	0,
	0
)

PELEMENT_HEADER com1_night_list[] =
{
	&com1_night.header,
	NULL
};

MAKE_STATIC
	(
		com1_background,
		BMP_COM1_BACKGROUND,
		&com1_night,
		&com1_fail,
		IMAGE_USE_TRANSPARENCY,
		0,
		0, 0
	)

PELEMENT_HEADER com1_list = &com1_background.header;


//to do list
// Com variable from VC matches display on gauge,[X]
// Change from current to new freq.
//set up string to use 7seg display.[X]
//display current and temp freq. [X]
//get background image (off) when battery is off.
//use on background image when battery is on.