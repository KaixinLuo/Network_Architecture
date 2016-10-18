#ifndef EVENT_H
#define EVENT_H
/* event.h,v 1.0 1993/10/21 19:11:18 NIST */
/* SHIV : cleaned up for CISE */
/*
 *
 * $Log: event.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.5  1996/05/30 13:55:58  tlin
 * prototype
 *
 * Revision 2.4  1996/05/29 17:46:10  tlin
 * remove duplicate variables due to inline
 *
 * Revision 2.3  1996/05/29 17:30:32  tlin
 * foo
 *
 * Revision 2.2  1996/05/29 17:14:52  tlin
 * remove lininlines
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:19  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:20  goyal
 * Lab1
 * 
 * Revision 1.0  96/04/24  15:01:35  shivkuma
 * Lab 1
 * 
 * Revision 1.1  96/04/21  23:59:56  shivkuma
 * Version Before Putting in User-Friendly names
 * 
 * Revision 0.0  96/02/21  00:43:57  goyal
 * Initial Revision
 * 
 *
 *
 */


#include "sim.h"
#include "heap.h"
#include "mempool.h"
#include "pdu.h"
#include "component.h"

#define EVENT_POOL_SIZE 100

typedef int Evtype;

typedef struct _event {
    struct _event *ev_next;
    Evtype        ev_type;
    tick_t	  ev_time;
    PFP		  ev_rtn;
    Component     *ev_src;
    Component     *ev_dest;
    PDU_TYPE  *ev_pu;

    caddr_t	  ev_arg;
} Event;

/*#define EVDATA(q_elt) ((Event *) (q_elt->qe_data))*/
/*#define EVQ_HEAD(q) (q->q_head)*/

Event *ev_member(), *ev_dequeue();
void ev_toggle_debug(), 
  ev_fire_with_time(), 
  //ev_fire_before_time(),
  ev_dequeue_by_type(),
  ev_dequeue_by_comp_and_type(),
  ev_dequeue_by_time(),
  ev_set_delay();
tick_t ev_get_delay();

#ifdef _EVENT_
    tick_t event_standard_time = 0L;
#else   /* if not _EVENT_ */
    extern tick_t event_standard_time;
#endif  /* _EVENT_ */




int ev_init();
int ev_reset();
int ev_adda(register Event *ev);
int ev_fire_first();
int ev_fire_all_first();
int ev_fire(Event *ev);
Event *ev_enqueue(Evtype type, Component *src, Component *dest,
		  tick_t time, PFP rtn, PDU_TYPE *pu, caddr_t arg);
int ev_set_time(Event *ev, tick_t newtime);
void ev_fire_before_time(tick_t	t);
#define ev_alloc()    ((Event *)mp_alloc(event_mempool))
#define ev_now()      event_standard_time



#endif   /* EVENT_H   */
