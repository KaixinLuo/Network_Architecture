#ifndef ROUTE_H
#define ROUTE_H
/* route.h,v 1.0 1993/10/21 19:07:47 NIST */
/* SHIV : cleaned up for CISE */

/*
 *
 * $Log: route.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.3  1996/05/29 17:24:11  tlin
 * ptrototype rt_create()
 *
 * Revision 2.2  1996/05/29 01:25:45  tlin
 * remove function prototype of route_activity()
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:41  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:31  goyal
 * Lab1
 * 
 * Revision 1.1  96/04/25  16:58:43  tlin
 * different colors for packets from different layers
 * 
 * Revision 1.0  96/04/24  15:02:02  shivkuma
 * Lab 1
 * 
 * Revision 1.1  96/04/22  00:00:07  shivkuma
 * Version Before Putting in User-Friendly names
 * 
 * Revision 0.0  96/02/21  00:44:03  goyal
 * Initial Revision
 * 
 *
 *
 */

#include "list.h"
#include "pdu.h"
#include "component.h"
/*#include "simx.h"*/

/* Header file for routes */
/*
typedef struct _route_key {
  Socket rk_socket;
  Component *rk_current_comp;
} Route_key;

typedef struct _Route_info {
  Component *next_link, *next_hop;
} Route_info;

typedef struct _route_rec {
  list *rr_route;
  Route_info rr_info;
} Route_rec;
*/

typedef struct _route_key {
/* SHIV : CISE : VPI rk_vpi; */
Component *rk_last_link;
} Route_key;

typedef struct _route_info{
Component *next_link,*next_hop;

/* SHIV : CISE : unsure */int connection_type;

}Route_info;

typedef struct _route_rec{
list *rr_route;
Route_info rr_info;
}Route_rec;

/* End Additions */


int         rt_create();
void        rt_destroy();
Route_info *rt_lookup();
list       *rt_find_route(), *rt_is_in_route();

#endif   /* ROUTE_H   */
