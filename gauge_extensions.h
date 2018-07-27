//**************************************
//Image definitions and macros
//**************************************
#define	IMAGE_ANTI_ALIAS																IMAGE_BILINEAR_COLOR	// added for backward compability

#define	LIGHT_IMAGE(element)														((element)->image_flags |=IMAGE_USE_BRIGHT)
#define	DARKEN_IMAGE(element)														((element)->image_flags &=~IMAGE_USE_BRIGHT)

#define	GET_USE_LUMINOUS(element)												((element)->image_flags & IMAGE_USE_LUMINOUS)
#define	LUMINOUS_IMAGE(element)													((element)->image_flags |=IMAGE_USE_LUMINOUS)
#define	DELUMINOUS_IMAGE(element)												((element)->image_flags &=~IMAGE_USE_LUMINOUS)

#define	FORCE_LIGHT(element)														SET_OFF_SCREEN(element);LIGHT_IMAGE(element)
#define	FORCE_DARKEN(element)														SET_OFF_SCREEN(element);DARKEN_IMAGE(element)
#define	FORCE_LUMINOUS(element)													SET_OFF_SCREEN(element);LUMINOUS_IMAGE(element)
#define	FORCE_DELUMINOUS(element)												SET_OFF_SCREEN(element);DELUMINOUS_IMAGE(element)

#define	TOGGLE_IMAGE_DATA(element,IMAGE_FLAGS)					((element)->image_flags ^=IMAGE_FLAGS)
#define	ADD_IMAGE_DATA(element,IMAGE_FLAGS)							((element)->image_flags |=IMAGE_FLAGS)
#define	REMOVE_IMAGE_DATA(element,IMAGE_FLAGS)					((element)->image_flags &=~IMAGE_FLAGS)

#define	REDRAW_IMAGE(element)														SET_OFF_SCREEN(element)

#define	HIDE_LISTELEMENT(pelement,pos_element)					add_imagedata_to_listelement(pelement,pos_element,IMAGE_HIDDEN)
#define	SHOW_LISTELEMENT(pelement,pos_element)					remove_imagedata_from_listelement(pelement,pos_element,IMAGE_HIDDEN)

#define	LIGHT_LISTELEMENT(pelement,pos_element)					add_imagedata_to_listelement(pelement,pos_element,IMAGE_USE_BRIGHT)
#define	DARKEN_LISTELEMENT(pelement,pos_element)				remove_imagedata_from_listelement(pelement,pos_element,IMAGE_USE_BRIGHT)

#define	LIGHT_LISTELEMENT(pelement,pos_element)					add_imagedata_to_listelement(pelement,pos_element,IMAGE_USE_BRIGHT)
#define	DARKEN_LISTELEMENT(pelement,pos_element)				remove_imagedata_from_listelement(pelement,pos_element,IMAGE_USE_BRIGHT)

#define	LUMINOUS_LISTELEMENT(pelement,pos_element)			add_imagedata_to_listelement(pelement,pos_element,IMAGE_USE_LUMINOUS)
#define	DELUMINOUS_LISTELEMENT(pelement,pos_element)		remove_imagedata_from_listelement(pelement,pos_element,IMAGE_USE_LUMINOUS)

#define	SET_OFFSCREEN_LISTELEMENT(pelement,pos_element)	add_imagedata_to_listelement(pelement,pos_element,IMAGE_ON_SCREEN)
#define	SET_ONSCREEN_LISTELEMENT(pelement,pos_element)	remove_imagedata_from_listelement(pelement,pos_element,IMAGE_ON_SCREEN)

// backwards compatibility for SET_ONSCREEN_LISTELEMENT
#define	REDRAW_LISTELEMENT(pelement,pos_element)				remove_imagedata_from_listelement(pelement,pos_element,IMAGE_ON_SCREEN)

//*****************************
// bitfield macros
//*****************************

#define	GET_BIT(value,filtermask)						((value)&(filtermask))
#define	CHECK_BIT(value,filtermask)					(((value)&(filtermask))!=FLAGS0)
#define	CHECK_BIT_STRICT(value,filtermask)	(((value)&(filtermask))==(filtermask))
#define	ADD_BIT(value,bit)									((value)|=(bit))
#define	REMOVE_BIT(value,bit)								((value)&=~(bit))

//*****************************
// LISTELEMENT macros
//*****************************
PELEMENT_HEADER FSAPI get_listelement_pointer(PELEMENT_HEADER pelement,UINT32	pos_element)\
{
	UINT32	index;
	if(pelement==NULL)return	NULL;									// invalid start

	for(index=0;index<pos_element;index++)					// advance pointer to desired element
	{
		if(pelement->next_element==NULL)return	NULL;	// stop if linked list is ending
		pelement=pelement->next_element[0];						// advance pointer to next_element[0]
	}
	return	pelement;
}
// ----------------------------
void FSAPI add_imagedata_to_listelement(PELEMENT_HEADER	pelement,UINT32	pos_element,FLAGS image_flags)
{
	if((pelement=get_listelement_pointer(pelement,pos_element))==NULL)return;
	ADD_IMAGE_DATA(pelement,image_flags);
}
// ----------------------------
void FSAPI remove_imagedata_from_listelement(PELEMENT_HEADER	pelement,UINT32	pos_element,FLAGS image_flags)
{
	if((pelement=get_listelement_pointer(pelement,pos_element))==NULL)return;
	REMOVE_IMAGE_DATA(pelement,image_flags);
}

//*****************************
// Mouse rectangle
//*****************************
#define PMOUSERECT_FOR_MOUSE_CALLBACK(PIXPOINT) ((PIXPOINT) ? ((PMOUSERECT)(((PMOUSECALLBACK)(PIXPOINT))->mouse))	 : NULL)

//**************************************
// defines for GPS_FLAGS
//**************************************
#define GPS_FLAG_ACTIVE_FLIGHT_PLAN					BIT1    //bit1 = 0x0002 1 = there is an active flight plan
#define GPS_FLAG_ACTIVE_WAY_POINT						BIT2    //bit2 = 0x0004 1 = there is an active way point
#define GPS_FLAG_ARRIVED										BIT3    //bit3 = 0x0008 1 = last waypoint reached
#define GPS_FLAG_UNKNOWN_1									BIT4
#define GPS_FLAG_DIRECTTO_FLIGHTPLAN				BIT5    //bit5 = 0x0020 1 = manual direct to flight plan active
#define GPS_FLAG_UNKNOWN_2									BIT6
#define GPS_FLAG_UNKNOWN_3									BIT7
#define GPS_FLAG_UNKNOWN_4									BIT8
