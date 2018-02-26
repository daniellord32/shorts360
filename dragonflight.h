//Visual Studio includes
#define DIRECTINPUT_VERSION 0x0800
#define INITGUID
#include <math.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <initguid.h>
#include <dsound.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <time.h>

//Functions files
#include "fsxgauges_sp2.h"
#include "fs_functions.h"

//Uncomment this section only if you are using the DirectSound module
/*
//DirectSound includes
#include "dfdsnd.h"
#include "waveread.h"
#include "sound.h"

//Sound data
char PlaySnd[256];
*/
//===========================================================================
//Debug log information
//===========================================================================
/*
FILE *debugdata;
#define debuglog "gauges/dxdebug.log"
*/

//lazy alias
#define NOVAR MODULE_VAR_NONE

//Make_string colours
//Original flags for compatibility with first attempts
#define red								RGB(255,0,0)
#define green							RGB(0,255,0)
#define yellow						RGB(255,255,0)
#define transp						RGB(0,0,0)
#define string_trans			BIT15

//Preferred flags
#define collins						RGB(255,64,0)
#define bright_red				RGB(255,0,0)
#define orange						RGB(255,128,0)
#define amber							RGB(255,192,0)
#define dkamber						RGB(235,145,0)
#define bright_green			RGB(0,255,0)
#define blue							RGB(0,0,255)
#define bright_yellow			RGB(255,255,0)
#define trans_black				RGB(0,0,0)
#define cyan							RGB(0,255,255)
#define white							RGB(255,255,255)
#define magenta						RGB(255,0,255)
#define black							RGB(8,8,8)
#define ltgrey						RGB(208,208,208)

//Shortened macro flags
#define transparent				BIT0
#define erase							BIT1
#define bright						BIT2
#define no_static					BIT4
#define anti_alias				BIT7
#define alpha_mask				BIT12
#define alpha							BIT13
#define luminous					BIT14
#define p_luminous				BIT15
#define hidden_tree				BIT25
#define no_dim						BIT29
#define hidden						BIT30

//Font flags - backwards compatibility
#define GAUGE_CHARSET           DEFAULT_CHARSET
#define GAUGE_FONT_DEFAULT      "arial"
#define GAUGE_WEIGHT_DEFAULT    FW_NORMAL

//Font flags - preferred
#define def_char					DEFAULT_CHARSET
#define arial							"ARIAL"
#define courier_new				"COURIER_NEW"
#define tnr								"TIMES_NEW_ROMAN"
#define trb								"TREBUCHET MS"
#define helvetica					"HELVETICA"
#define quartz						"QUARTZ"
#define glass							"GLASS GAUGE"
#define anbi							"ARIAL NARROW BOLD ITALIC"
#define normal						FW_NORMAL
#define bold							FW_BOLD
