/* 
   $Log: application_layer.h,v $
   Revision 4.0  1996/08/23 20:06:37  tlin
   bump to mickey mouse version

   Revision 3.3  1996/07/14 06:32:01  tlin
   foo

   Revision 3.2  1996/07/14 06:29:58  tlin
   move the wrapper.c to .c


   */

#ifndef APPLICATION_LAYER_H
#define APPPLICATION_LAYER_H

#include "cisePort.h"
#include "sim.h"
#include "q.h"
#include "list.h"
#include "eventdefs.h"
#include "log.h"
#include "comptypes.h"
#include "event.h"
#include "route.h"
#include "component.h"
#include "pdu.h"
#include "subr.h"
#include "action.h"
#include "sim_tk.h"


typedef struct _APPConnectiont{
    struct _APPConnectiont *cn_next, *cn_prev;
    short         cn_class;
    short         cn_type;
    char          cn_name[40];    /* Name of component (appears on screen) */
    PFP           cn_action;      /* Main function of component.  */
    XComponent    *cn_picture;    /* Graphics object that displays this thing */
    list          *cn_neighbors;  /* List of neighbors of this thing */

    /* Parameters-- data that will be displayed on screen */
    short         cn_menu_up;     /* If true, then the text window is up */
    short         cn_big_menu;     /* not used */
    queue         *cn_params;     /* Variable-length queue of parameters */

    int		j1,j2;          /* junk values : DONT remove this : 
				   I cast this structure somewhere -SHIV */

    int           cn_flash;
    Param         *cn_Name;     /* Turn packet logging on & off */
    Param         *cn_bit_rate;
    Param         *cn_start_time;
    Param         *cn_trans_size;
    Param 	*cn_pkts_recvd;
    Param 	*cn_stop_time;
    Param		*cn_destination;

    int cn_num_sent;


} APPConnectiont;

#define MY_SEND_A_PDU (Evtype)(EV_CLASS_PRIVATE | 1) 

#endif
  
