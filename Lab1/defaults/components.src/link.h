/* 
   $Log:	link.h,v $
 * Revision 4.0  96/08/23  20:06:37  tlin
 * bump to mickey mouse version
 * 
   Revision 3.1  1996/06/01 02:54:17  tlin
   XComponent    *cn_picture to each entity
   the dependency on component and component.h is dangerout
   dangerous. should be removed. who'll do it?

   Revision 3.0  1996/05/30 14:42:17  tlin
   bump to 3.0; before Tk adition

   Revision 2.7  1996/05/30 11:30:54  tlin
   #include "link_wrappers.c"

   Revision 2.6  1996/05/30 11:28:12  tlin
   foo

   Revision 2.5  1996/05/30 11:24:17  tlin
   link.h was included in action.h

   Revision 2.4  1996/05/30 11:20:32  tlin
   use subr.h and action.h

 * Revision 2.3  1996/05/30 11:16:53  tlin
 * port.h
 *
 * Revision 2.2  1996/05/29 00:35:46  tlin
 * remove XCOMPONENT and DisplayMask
 *
 * Revision 2.1  1996/05/28 05:59:37  tlin
 * y
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.0  1996/04/26 15:37:29  goyal
 * Lab1
 *
 * Revision 0.0  96/04/26  15:01:47  goyal
 * Lab1
 * 
 * Revision 0.0  96/04/26  14:57:37  goyal
 * Lab1
 * 
 * Revision 0.0  96/04/26  14:46:13  goyal
 * Lab1
 * 
 * Revision 1.1  96/04/25  16:19:08  tlin
 * LOAD fixed
 * 
 * Revision 1.0  96/04/24  14:54:44  shivkuma
 * Lab 1
 *  */

#ifndef LINK_H
#define LINK_H


#include "cisePort.h"
#include "sim.h"
#include "q.h"
#include "list.h"
#include "eventdefs.h"
#include "component.h"
#include "log.h"
#include "comptypes.h"
#include "pdu.h"
#include "event.h"
#include "route.h"
#include "subr.h"
#include "sim_tk.h"

typedef struct _LINKConnectiont{
    struct _LINKConnectiont *cn_next, *cn_prev;
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

    Param		*cn_delay;
    Param		*cn_err;



} LINKConnectiont;


caddr_t link_action(Component *src, LINKConnectiont *cn, int type, PDU_TYPE *pdu, caddr_t arg);

#endif
  
