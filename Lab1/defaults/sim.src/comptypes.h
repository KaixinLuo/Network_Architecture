/* comptypes.h,v 1.0 1993/10/21 19:10:58 NIST */

/*
 *
 * $Log: comptypes.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.6  1996/07/14 06:41:11  tlin
 * class -> _class, typename -> _typename
 *
 * Revision 3.5  1996/06/02 17:30:36  tlin
 * icon(Component *) instead of Nchar *name
 *
 * Revision 3.4  1996/06/01 05:48:36  tlin
 * add char *name to icon_xxx()
 *
 * Revision 3.3  1996/06/01 01:55:13  tlin
 * fix (*icon)
 *
 * Revision 3.2  1996/06/01 01:44:05  tlin
 * XComponent  *icon() in Component_type
 *
 * Revision 3.1  1996/06/01 01:21:36  tlin
 * enum {APPLICATION_LAYER_TYPE=0 ...
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.2  1996/05/30 09:53:47  tlin
 * foo
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:12  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:18  goyal
 * Lab1
 * 
 * Revision 1.0  96/04/24  15:01:30  shivkuma
 * Lab 1
 * 
 * Revision 1.1  96/04/21  23:59:54  shivkuma
 * Version Before Putting in User-Friendly names
 * 
 * Revision 0.0  96/02/21  00:43:56  goyal
 * Initial Revision
 * 
 *
 *
 */



#ifndef COMPTYPES_H
#define COMPTYPES_H
/* SHIV : cleaned up for CISE */
/* File that defines the different types of components in the particular
   model being implemented.  Will vary with different implementations.  */

#include "sim.h"
#include "sim_tk.h"

typedef struct {
    char	_typename[40];
    short	_class;		/* What class this component is */
    PFP		action;
    XComponent* (*icon)(Component *co, int x, int y);
} Component_type;

/* SHIV: CISE: New additions */

enum {APP_CLASS=0, DLC_CLASS, PHY_CLASS, LINK_CLASS};

enum {APPLICATION_LAYER_TYPE=0, DLC_LAYER_TYPE, 
      PHYSICAL_LAYER_TYPE, LINK_TYPE};

extern Component_type component_types[];

#endif   /* COMPTYPES_H   */

