// Altimeter indication gauge

//set up the gauge header

char altimeter_gauge_name[] =	GAUGE_NAME;
extern PELEMENT_HEADER			altimeter_list;
extern MOUSERECT				altimeter_mouse_rect[];

GAUGE_HEADER_FS700(GAUGE_W, altimeter_gauge_name, &altimeter_list, altimeter_mouse_rect, 0, 0, 0, 0);

// end of gauge header

MOUSE_BEGIN( altimeter_mouse_rect, 0, 0, 0 )
MOUSE_END

FAILURE_RECORD altimeter_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_ZERO},
	{FAIL_SYSTEM_PITOT_STATIC, FAIL_ACTION_FREEZE},
	{FAIL_NONE, FAIL_ACTION_NONE}
};
// varibles to be used in gauge.

MODULE_VAR	baro_height = {ALT_FROM_BAROMETRIC_PRESSURE};

UINT32		alt_pressure_mb = 1013;
FLOAT64		alt_pressure_in = 29.92;
FLOAT64		alt_atm = 0;
FLOAT64		alt_mb = 0;

FLOAT64 alt_fHun = 0;
FLOAT64 alt_fAlt = 0;
FLOAT64 alt_fThou = 0;
FLOAT64 alt_fVar = 0;
FLOAT64 alt_fTenThou = 0;
FLOAT64 alt_i = 0;
FLOAT64 alt_j = 0;
FLOAT64 alt_HunY = 0;
FLOAT64 alt_ThouY = 0;
FLOAT64 alt_TenThouY = 0;
//string character initilization

#define GAUGE_CHARSET						DEFAULT_CHARSET
#define GAUGE_FONT_DEFAULT					"Courier New"
#define GAUGE_WEIGHT_DEFAULT				FW_NORMAL

/* For baro mouse action I will need to get the xml data from the 3d model and plug into c++
 here
*/

NONLINEARITY alt_needle1[] =
{
	{{162,	 41},	 0.000000, 0},
	{{152,	 40},	 995.000000, 0},
};

NONLINEARITY alt_needle2[] = 
{
	{{162,	 41},	 0.000000, 0},
	{{152,	 40},	 995.000000, 0},
};

//custom controls

FLOAT64 FSAPI	alt_commonX_var(PELEMENT_MOVING_IMAGE pelement)
{
	return 1.0;
}

FLOAT64 FSAPI	alt_HunY_var(PELEMENT_MOVING_IMAGE pelement)
{
	lookup_var(&baro_height);
	alt_HunY = baro_height.var_value.n;
	while (alt_HunY > 1000) alt_HunY = alt_HunY - 1000;

	return alt_HunY;
}

FLOAT64 FSAPI	alt_ThouY_var(PELEMENT_MOVING_IMAGE pelement)
{
	lookup_var(&baro_height);
	alt_ThouY = baro_height.var_value.n;

	while (alt_ThouY > 10000) alt_ThouY = alt_ThouY - 10000;

	if (alt_ThouY < 1000) alt_ThouY = 0;
	else if (alt_ThouY > 8950) alt_ThouY = 9;
	else if (alt_ThouY > 7950) alt_ThouY = 8;
	else if (alt_ThouY > 6950) alt_ThouY = 7;
	else if (alt_ThouY > 5950) alt_ThouY = 6;
	else if (alt_ThouY > 4950) alt_ThouY = 5;
	else if (alt_ThouY > 3950) alt_ThouY = 4;
	else if (alt_ThouY > 2950) alt_ThouY = 3;
	else if (alt_ThouY > 1950) alt_ThouY = 2;
	else if (alt_ThouY > 950) alt_ThouY = 1;

	return alt_ThouY;
}

FLOAT64 FSAPI	alt_TenThouY_var(PELEMENT_MOVING_IMAGE pelement)
{
	lookup_var(&baro_height);
	alt_TenThouY = baro_height.var_value.n;

	while (alt_TenThouY > 100000) alt_TenThouY = alt_TenThouY - 100000;

	if (alt_TenThouY < 10000) alt_TenThouY = 0;
	else if (alt_TenThouY > 89950) alt_TenThouY = 9;
	else if (alt_TenThouY > 79950) alt_TenThouY = 8;
	else if (alt_TenThouY > 69950) alt_TenThouY = 7;
	else if (alt_TenThouY > 59950) alt_TenThouY = 6;
	else if (alt_TenThouY > 49950) alt_TenThouY = 5;
	else if (alt_TenThouY > 39950) alt_TenThouY = 4;
	else if (alt_TenThouY > 29950) alt_TenThouY = 3;
	else if (alt_TenThouY > 19950) alt_TenThouY = 2;
	else if (alt_TenThouY > 9950) alt_TenThouY = 1;

	return alt_TenThouY;
}

FLOAT64 FSAPI alt_huns_cb (PELEMENT_NEEDLE pelement)
{
	return alt_fHun;
}

FLOAT64 FSAPI	alt_update_baro_mb_day(PELEMENT_STRING pelement)
{
	FLOAT64 val=pelement->source_var[0].var_value.n;

	alt_pressure_mb = (UINT32) val;
	wsprintf(pelement->string, "%4d", alt_pressure_mb);
	return val;
}

FLOAT64 FSAPI	alt_update_baro_mb_night(PELEMENT_STRING pelement)
{
	FLOAT64 val=pelement->source_var[0].var_value.n;
	
	alt_pressure_mb = (UINT32) val;
	wsprintf(pelement->string, "%4d", alt_pressure_mb);
	return val;
}

FLOAT64 FSAPI	alt_update_day(PELEMENT_STRING pelement)
{
	FLOAT64 val=pelement->source_var[0].var_value.n;
	alt_mb = val;
	alt_atm = alt_mb/1013.25;
	alt_pressure_in = alt_atm * 29.92;
	sprintf(pelement->string, "%2.2f", alt_pressure_in);
	return val;
}

FLOAT64 FSAPI	alt_update_night(PELEMENT_STRING pelement)
{
	FLOAT64 val=pelement->source_var[0].var_value.n;
	alt_mb = val;
	alt_atm = alt_mb/1013.25;
	alt_pressure_in = alt_atm * 29.92;
	sprintf(pelement->string, "%2.2f", alt_pressure_in);
	return val;
}

MAKE_NEEDLE
	(
		alt_100,
        BMP_ALT_NEEDLE,
        NULL,
        altimeter_fail,
        transparent | erase | anti_alias,
        0,
        106, 93,
		10, 10,
		MODULE_VAR_NONE,
		alt_huns_cb,
        alt_needle1,
		0
	)

PELEMENT_HEADER		alt_plist1[] =
{
	&alt_100.header,
	NULL
};

MAKE_STRING
	(	
		alt_baro,
		&alt_plist1,
		NULL,
		IMAGE_USE_ERASE,
		0,
		135, 65,	// x and y co-ord
        50, 30,		//pixels width and height
		5,			//chars used
		KOHLSMAN_SETTING_MB,  //Enter variable to be checked on this line
        MODULE_VAR_NONE,
        MODULE_VAR_NONE,
		RGB(255,255,255),
		RGB(0,0,0),
		RGB(255,255,255),
		GAUGE_FONT_DEFAULT,
		GAUGE_WEIGHT_DEFAULT,
		GAUGE_CHARSET,
		0,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE,
		NULL,
		alt_update_day 
	)

PELEMENT_HEADER		alt_plist3[] =
{
	&alt_baro.header,
	NULL
};


MAKE_STRING
	(	
		alt_baro_mb,
		&alt_plist3,
		NULL,
		erase,
		0,
		135, 160, //x and y co-ord
        40, 30, // pixels width adn height
		4, // spaces to be used
		KOHLSMAN_SETTING_MB,  //Enter variable to be checked on this line
        MODULE_VAR_NONE,
        MODULE_VAR_NONE,
		RGB(255,255,255),
		RGB(0,0,0),
		RGB(255,255,255),
		GAUGE_FONT_DEFAULT,
		GAUGE_WEIGHT_DEFAULT,
		GAUGE_CHARSET,
		0,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE,
		NULL,
		alt_update_baro_mb_day 
	)

PELEMENT_HEADER		alt_plist5[] =
{
	&alt_baro_mb.header,
	NULL
};

MAKE_MOVING
	(	
		alt_hun_feet,
		BMP_ALT_HUN_TAPE,
		&alt_plist5,
		altimeter_fail,
		erase | transparent | anti_alias,
		0,
		144,70,
		MODULE_VAR_NONE, alt_commonX_var,
		0, 0,
		MODULE_VAR_NONE, alt_HunY_var,
		0, 999
	)

PELEMENT_HEADER		alt_plist7[] =
{
	&alt_hun_feet.header,
	NULL
};

MAKE_MOVING
	(	
		alt_hun_feet_night,
		BMP_ALT_HUN_TAPE,
		&alt_plist7,
		altimeter_fail,
        transparent | erase | anti_alias | bright,
		0,
		144,70,
		MODULE_VAR_NONE, alt_commonX_var,
		0, 0,
		MODULE_VAR_NONE, alt_HunY_var,
		0, 999
	)

PELEMENT_HEADER		alt_plist8[] =
{
	&alt_hun_feet_night.header,
	NULL
};

MAKE_MOVING
	(	
		alt_thou_feet,
		BMP_ALT_THOU_TAPE,
		&alt_plist8,
		altimeter_fail,
        transparent | erase | anti_alias,
		0,
		119,76,
		MODULE_VAR_NONE, alt_commonX_var,
		0, 0,
		MODULE_VAR_NONE, alt_ThouY_var,
		0, 10)

PELEMENT_HEADER		alt_plist9[] =
{
	&alt_thou_feet.header,
	NULL
};

MAKE_MOVING
	(	
		alt_thou_feet_night,
		BMP_ALT_THOU_TAPE,
		&alt_plist9,
		altimeter_fail,
        transparent | erase | anti_alias | hidden | bright,
		0,
		119,76,
		MODULE_VAR_NONE, alt_commonX_var,
		0, 0,
		MODULE_VAR_NONE, alt_ThouY_var,
		0, 10)

PELEMENT_HEADER		alt_plist10[] =
{
	&alt_thou_feet_night.header,
	NULL
};

MAKE_MOVING
	(	
		alt_ten_thou_feet,
		BMP_ALT_TENTHOU_TAPE,
		&alt_plist10,
		altimeter_fail,
        transparent | erase | anti_alias,
		0,
		102,76,
		MODULE_VAR_NONE, alt_commonX_var,
		0, 0,
		MODULE_VAR_NONE, alt_TenThouY_var,
		0, 10
	)

PELEMENT_HEADER		alt_plist11[] =
{
	&alt_ten_thou_feet.header,
	NULL
};


MAKE_MOVING
	(	
		alt_ten_thou_feet_night,
		BMP_ALT_TENTHOU_TAPE,
		&alt_plist11,
		altimeter_fail,
        transparent | erase | anti_alias | hidden | bright,
		0,
		102,76,
		MODULE_VAR_NONE, alt_commonX_var,
		0, 0,
		MODULE_VAR_NONE, alt_TenThouY_var,
		0, 10
	)

PELEMENT_HEADER		alt_plist12[] =
{
	&alt_ten_thou_feet_night.header,
	NULL
};

MAKE_STATIC
	(	
		alt_background,
		BMP_ALT_BACKGROUND,
		&alt_plist12,
		NULL,
		transparent | erase,
		0,
		0,0 
	)

PELEMENT_HEADER		altimeter_list	= &alt_background.header;

void FSAPI	alt_update (PGAUGEHDR pgauge, int service_id, UINT32 extra_data)
{
	switch(service_id)
	{

/* "install_routine()" */

		case    PANEL_SERVICE_PRE_INSTALL:
		break;

/* "initialize_routine()" */

		case    PANEL_SERVICE_PRE_INITIALIZE:
		break;

/* "update_routine()" */

		case    PANEL_SERVICE_PRE_UPDATE:

//Lighting

		//lookup_var(&avlights);
		//if (avlights.var_value.n != 0) alt_lights_on = 1;
		//else alt_lights_on = 0;

		//if (alt_lights_on == 1)
		//{
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],13);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],11);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],9);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],7);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],5);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],3);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],1);

		//	HIDE_LISTELEMENT(pgauge->elements_list[0],14);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],12);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],10);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],8);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],6);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],4);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],2);
		//}
		//else
		//{
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],14);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],12);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],10);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],8);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],6);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],4);
		//	SHOW_LISTELEMENT(pgauge->elements_list[0],2);	

		//	HIDE_LISTELEMENT(pgauge->elements_list[0],13);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],11);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],9);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],7);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],5);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],3);
		//	HIDE_LISTELEMENT(pgauge->elements_list[0],1);
		//}

// Get needle position - have to subtract height to get hundreds of feet

		lookup_var(&baro_height);
		alt_fAlt = baro_height.var_value.n;
		alt_fTenThou = alt_fAlt;

		alt_fVar = 10000;
		while (alt_fAlt >= alt_fVar)
		{
			alt_i = alt_fAlt - alt_fVar;
			alt_fAlt = alt_i;
		}
		alt_fThou = alt_fAlt;

		alt_fVar = 1000;
		while (alt_fAlt >= alt_fVar)
		{
			alt_i = alt_fAlt - alt_fVar;
			alt_fAlt = alt_i;
		}

		alt_fHun = alt_fAlt;

		break;

/* "draw_routine()" */

		case    PANEL_SERVICE_PRE_DRAW:
		break;

/* "kill_routine()" */

		case    PANEL_SERVICE_PRE_KILL:
		break;
	}

}