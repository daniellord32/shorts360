//***************************************************************************
// Communication with the virtual cockpit
//***************************************************************************
char xml_handler_gauge_name[] = GAUGE_NAME;
extern PELEMENT_HEADER		xml_handler_list;
GAUGE_CALLBACK				xml_handler_update;
GAUGE_HEADER_FS900(gaugehdr_xml_handler, GAUGE_W, xml_handler_gauge_name, &xml_handler_list, 0, xml_handler_update, 0, 0);

MAKE_STATIC(xml_handler_static,
	NULL,
	NULL,
	NULL,
	erase | transparent | hidden,
	0,
	0, 0)

	PELEMENT_HEADER	xml_handler_list = &xml_handler_static.header;

//XML pointers

ID xPowerOn;

//-------------------------------------------------------------------------------
void FSAPI	xml_handler_update(PGAUGEHDR pgauge, int service_id, UINT_PTR extra_data)
{

	switch (service_id)
	{
	case PANEL_SERVICE_PRE_INITIALIZE:

		// Register the L:var contained in the xml_switch.xml file (stored in the xml_switch.cab archive)
		xPowerOn = register_named_variable("MstrBatt");

		break;

	}
}