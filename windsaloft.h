//windsaloft.h Winds Aloft Simulations (c) 2018

//Includes

#include <math.h>
#include <string.h>
#include <windows.h>
#include <initguid.h>
#include <dsound.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

//Make String Colours

#define bright_red		RGB(255,64,0)
#define orange			RGB(255,128,0)
#define amber			RGB(255,192,0)
#define dkamber			RGB(235,145,0)
#define bright_green	RGB(0,255,0)
#define blue			RGB(0,0,255)
#define bright_yellow	RGB(255,255,0)
#define trans_black		RGB(0,0,0)
#define cyan			RGB(0,255,255)
#define white			RGB(255,255,255)
#define magenta			RGB(255,0,255)
#define black 			RGB(8,8,8)
#define ltgrey 			RGB(208,208,208)

//Font

#define def_char					DEFAULT_CHARSET
#define arial							"ARIAL"
#define courier_new						"COURIER_NEW"
#define tnr								"TIMES_NEW_ROMAN"
#define trb								"TREBUCHET MS"
#define helvetica						"HELVETICA"
#define quartz							"QUARTZ"
#define glass							"GLASS GAUGE"
#define anbi							"ARIAL NARROW BOLD ITALIC"
#define dseg7							"DSEG7 Modern"							
#define normal							FW_NORMAL
#define bold							FW_BOLD

//backwards Compatability

#define GAUGE_CHARSET           DEFAULT_CHARSET
#define GAUGE_FONT_DEFAULT      "arial"
#define GAUGE_WEIGHT_DEFAULT    FW_NORMAL