#include "Systems.h"

char systems_handler_gauge_name[] = GAUGE_NAME;
extern PELEMENT_HEADER		systems_handler_list;
GAUGE_CALLBACK				systems_handler_update;
GAUGE_HEADER_FS900(gaugehdr_systems_handler, GAUGE_W, systems_handler_gauge_name, &systems_handler_list, 0, systems_handler_update, 0, 0);

MAKE_STATIC(systems_handler_static,
	NULL,
	NULL,
	NULL,
	NULL,
	0,
	0, 0)

	PELEMENT_HEADER	systems_handler_list = &systems_handler_static.header;

//-------------------------------------------------------------------------------
void FSAPI	systems_handler_update(PGAUGEHDR pgauge, int service_id, UINT_PTR extra_data)
{
	switch (service_id)
	{
	case    PANEL_SERVICE_PRE_UPDATE:

		// Check the state of the switch toggle (systems.h)
		power_toggle();


		break;
	}
}