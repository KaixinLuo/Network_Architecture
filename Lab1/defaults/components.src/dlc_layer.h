/* 
   $Log: dlc_layer.h,v $
   Revision 4.0  1996/08/23 20:06:37  tlin
   bump to mickey mouse version

   Revision 3.2  1996/06/03 06:03:40  tlin
   fix syntax errors

 * Revision 3.1  1996/06/01 02:54:17  tlin
 * XComponent    *cn_picture to each entity
 * the dependency on component and component.h is dangerout
 * dangerous. should be removed. who'll do it?
 *
 * Revision 3.0  1996/05/30 14:42:17  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.5  1996/05/30 13:57:28  tlin
 * foo
 *
 * Revision 2.4  1996/05/30 11:20:32  tlin
 * use subr.h and action.h
 *
 * Revision 2.3  1996/05/30 11:12:39  tlin
 * use port.h
 *
 * Revision 2.2  1996/05/29 00:35:46  tlin
 * remove XCOMPONENT and DisplayMask
 *
 * Revision 2.1  1996/05/28 05:59:37  tlin
 * y
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.0  1996/04/26 15:37:28  goyal
 * Lab1
 *
 * Revision 0.0  96/04/26  15:01:45  goyal
 * Lab1
 * 
 * Revision 0.0  96/04/26  14:57:35  goyal
 * Lab1
 * 
 * Revision 0.0  96/04/26  14:46:12  goyal
 * Lab1
 * 
 * Revision 1.1  96/04/25  16:19:02  tlin
 * LOAD fixed
 * 
 * Revision 1.0  96/04/24  14:54:42  shivkuma
 * Lab 1
 *  */

#ifndef DLC_LAYER_H
#define DLC_LAYER_H

#include "r_table.h"
#define GetNodeID(cn) get_number(cn->cn_name)
#define GetReceiverID(cn) get_receiver(GetNodeID(cn))

typedef struct _DLCConnectiont{
    struct _DLCConnectiont *cn_next, *cn_prev;
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
} DLCConnectiont;

/* ------------------- MACRO DEFINITIONS/WRAPPERS -------------- */


#include "dlc_layer_wrappers.c"

#endif
  
