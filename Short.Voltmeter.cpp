//	Set up gauge header
char dcvolts_gauge_name[]		= GAUGE_NAME;
extern PELEMENT_HEADER		dcvolts_list;
extern MOUSERECT			dcvolts_mouse_rect[];
GAUGE_CALLBACK				dcvolts_update;
GAUGE_HEADER_FS700(GAUGE_W, dcvolts_gauge_name, &dcvolts_list, dcvolts_mouse_rect, dcvolts_update, 0,0,0 );

FAILURE_RECORD	dcvolts_fail[] =
{
	{FAIL_SYSTEM_ELECTRICAL_PANELS, FAIL_ACTION_ZERO},
	{FAIL_NONE, FAIL_ACTION_NONE}
};

MOUSE_BEGIN( dcvolts_mouse_rect, 0, 0, 0 )
MOUSE_END

NONLINEARITY set_voltage[] =
{
	{{66,	 229},	  00.000000, 0},

	{{50,	 209},	  328.000000, 0},
	{{34,	 156},	  756.000000, 0},
	{{75,	 57},	  1012.000000, 0},

	{{180,	 34},	  1683.000000, 0}, //21 volts
	{{242,	 77},	  3000.000000, 0}, //24 volts
	{{264,	 124},	  16380.000000, 0}, //28 volts

};

MODULE_VAR		generator = {ENGINE1_N2_RPM};
MODULE_VAR		firing = {ENGINE1_COMBUSTION};

UINT8 spark = 0;
UINT8 rpm = 0;
UINT8 prev_rpm = 0;
UINT8 turn_on = 0;

UINT32 batt1_on;     //Battery master broadcast, Doesn't get broadcast if using XML
int MasterBatt = 0; //C++ variable to store xml variable
ID MasterBatt_id; // Pointer address to the xml variable in modeldef.xml


//-------------------------------------------------------------
//				custom code for needle manipulation
//-------------------------------------------------------------

FLOAT64 FSAPI rpm_src_cb(PELEMENT_NEEDLE pelement)

{
	prev_rpm = rpm;
	lookup_var(&generator);
	lookup_var(&firing);
	rpm = generator.var_value.n;
	spark = firing.var_value.n;

	if (MasterBatt == 1 && spark == 0 && rpm == 0)  //Battery on but no start engaged
	{
		turn_on = turn_on + 30;	//Set to 24 volts slowly up the gauge
		if (turn_on > 3000)		//Crop it at 24 volts
		{
			turn_on = 3000;
		}
		rpm = turn_on;
	}

	if (MasterBatt == 0)			//Battery master off - show zero
	{
		turn_on = turn_on - 30; //Slowly down the gauge
		if (turn_on < 0)		//Crop it at zero volts
		{
			turn_on = 0;
		}
		rpm = turn_on;
	}

	if (MasterBatt == 1 && (rpm < 1683 && rpm > 0) && spark == 1 )  //Set to 21 volts for start at 10% N1
	{
		rpm = 1683;
	}

	if (rpm > 8192 )			//Crop rpm return to 26 volts - maximum battery voltage
	{
		rpm = 8192;
	}

	if (MasterBatt == 1 && spark == 0 && rpm > 0 && turn_on == 3000)  //Battery on and engine turned off
	{
		rpm = turn_on;
	}
	
	if (MasterBatt == 1 && rpm > 1700 && spark == 1)	//Engine already on
	{
		turn_on = 3000;
	}

	return rpm;

}

void FSAPI	dcvolts_update (PGAUGEHDR pgauge, int service_id, UINT32 extra_data)
{
	switch(service_id)
	{

/* "install_routine()" */

		case    PANEL_SERVICE_PRE_INSTALL:

			register_var_by_name (&MasterBatt_id, TYPE_UINT32, "batt1_on");

		break;

/* "initialize_routine()" */

		case    PANEL_SERVICE_PRE_INITIALIZE:
			register_named_variable ("MstrBatt"); //Lets sim know I want a variable from modeldef.xml.
		break;

/* "update_routine()" */

		case    PANEL_SERVICE_PRE_UPDATE:
			MasterBatt_id = check_named_variable("MstrBatt"); //checks the status of the master battery.
			MasterBatt = get_named_variable_value(MasterBatt_id); //gets the value of MstrBatt.
		break;

/* "draw_routine()" */

		case    PANEL_SERVICE_PRE_DRAW:
		break;

/* "kill_routine()" */

		case    PANEL_SERVICE_PRE_KILL:

			unregister_var_by_name ("batt1_on");

		break;
	}

}


//-----------------------------------------------------------
//			Image draw perameters
//-----------------------------------------------------------

MAKE_NEEDLE(    batt_ind,
                BMP_VOLTMETER_NEEDLE,
                NULL,
                NULL,
                IMAGE_USE_TRANSPARENCY | IMAGE_USE_ERASE | IMAGE_USE_BRIGHT,
                0,
                151, 151,	// Location where the pin is to rotate
				23, 23,		// Center location for needle on background
				MODULE_VAR_NONE,
				rpm_src_cb,
                set_voltage,
                0 )

PELEMENT_HEADER		plist1[] =
{
	&batt_ind.header,
	NULL
};

////////////////////////////////////////////////////////////////////

MAKE_ICON(		batt_mask,
				BMP_VOLTMETER_MASK,
				&plist1,
				NULL,
				IMAGE_USE_TRANSPARENCY | IMAGE_USE_BRIGHT,
				0,
				0,0,
				MODULE_VAR_NONE, NULL,
				NULL,
				1,
				0,
				0, )

PELEMENT_HEADER		plist2[] =
{
	&batt_mask.header,
	NULL
};

///////////////////////////////////////////////////////////////////////

MAKE_STATIC(	background,
				BMP_VOLTMETER_BACKGROUND,
				&plist2,
				NULL,
				IMAGE_USE_TRANSPARENCY,
				0,
				{0, 0} )

PELEMENT_HEADER		dcvolts_list	= &background.header;



///////////////////////////////////////////////////////////////////////
//				Undefine for memory managment
//////////////////////////////////////////////////////////////////////
#undef GAUGE_NAME
#undef GAUGEHDR_VAR_NAME
#undef GAUGE_W