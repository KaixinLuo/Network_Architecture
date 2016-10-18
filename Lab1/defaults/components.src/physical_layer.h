/* $Log: physical_layer.h,v $
 * Revision 4.0  1996/08/23 20:06:37  tlin
 * bump to mickey mouse version
 *
 * Revision 3.1  1996/06/01 02:54:17  tlin
 * XComponent    *cn_picture to each entity
 * the dependency on component and component.h is dangerout
 * dangerous. should be removed. who'll do it?
 *
 * Revision 3.0  1996/05/30 14:42:17  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.3  1996/05/30 11:20:32  tlin
 * use subr.h and action.h
 *
 * Revision 2.2  1996/05/29 00:35:46  tlin
 * remove XCOMPONENT and DisplayMask
 *
 * Revision 2.1  1996/05/28 05:59:37  tlin
 * y
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.0  1996/04/26 15:37:30  goyal
 * Lab1
 *
 * Revision 0.0  96/04/26  15:01:48  goyal
 * Lab1
 * 
 * Revision 0.0  96/04/26  14:57:38  goyal
 * Lab1
 * 
 * Revision 0.0  96/04/26  14:46:14  goyal
 * Lab1
 * 
 * Revision 1.1  96/04/25  16:19:12  tlin
 * LOAD fixed
 * 
 * Revision 1.0  96/04/24  14:54:47  shivkuma
 * Lab 1
 * */

#ifndef PHYSICAL_LAYER_H
#define PHYSICAL_LAYER_H


#include "cisePort.h"
#include "sim.h"
#include "q.h"
#include "list.h"
#include "eventdefs.h"
#include "log.h"
#include "comptypes.h"
#include "event.h"
#include "route.h"
#include "subr.h"
#include "action.h"
#include "component.h"
#include "pdu.h"
#include "sim_tk.h"

#include "r_table.h"
#define GetNodeID(cn) get_number(cn->cn_name)
#define GetReceiverID(cn) get_receiver(GetNodeID(cn))

typedef struct _PHYConnectiont{
    struct _PHYConnectiont *cn_next, *cn_prev;
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

    int           cn_iq_length;    /* get the current input q length here */
    int           cn_iq_limit;    /* get the current input q length here */

    int           cn_flash;
    Param         *cn_Name;

    list	  *cn_crt;
} PHYConnectiont;


typedef struct cise_route_table {
    int	dest;
    int  	path_id;
    char 	link[10];
} CRT;

/* ------------------- MACRO DEFINITIONS/WRAPPERS -------------- */
#include "physical_layer_wrappers.c"

#endif 
  
