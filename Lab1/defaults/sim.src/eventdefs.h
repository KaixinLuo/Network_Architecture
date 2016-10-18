/* eventdefs.h,v 1.0 1993/10/21 19:11:20 NIST */
/* SHIV : cleaned up for CISE */
/*
 *
 * $Log: eventdefs.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:20  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:20  goyal
 * Lab1
 * 
 * Revision 1.0  96/04/24  15:01:36  shivkuma
 * Lab 1
 * 
 * Revision 1.1  96/04/21  23:59:56  shivkuma
 * Version Before Putting in User-Friendly names
 * 
 * Revision 0.0  96/02/21  00:43:58  goyal
 * Initial Revision
 * 
 *
 *
 */

#ifndef EVENTDEFS_H
#define EVENTDEFS_H
/** Define types of events. */

/* Classes of events */
/* SHIV : CISE : not clear on what EV_CLASS_EVENT,EV_CLASS_PRIVATE, EV_CLASS_CMD  are for */

#define EV_CLASS_EVENT	0x01000000	/* Normal event-- eg RECEIVE */
#define EV_CLASS_PRIVATE 0x02000000	/* Event sent to self */
#define EV_CLASS_CMD	0x04000000	/* Command-- eg INITIALIZE */

/* Events: */

/* Commands: all components must accept these (don't have to actually
   do anything with them, but shouldn't complain about them). */
#define EV_RESET (EV_CLASS_CMD | 1)	/* Reset the component */
#define EV_CREATE (EV_CLASS_CMD | 2)	/* Initialize and create the component.
					   Must be sent to a component before
					   any other events are received, and
					   never again. */
#define EV_DEL (EV_CLASS_CMD | 3)	/* Clean up before deletion.
					   Must be received only once, and
					   the action routine must not be
					   called again afterward.  */
#define EV_NEIGHBOR (EV_CLASS_CMD | 4)	/* Make passed comp. your neighbor */
#define EV_UNEIGHBOR (EV_CLASS_CMD | 5)	/* Detach self from passed comp. */

/* SHIV : CISE : dont' know whether EV_LEGAL_NEXT_HOPS is necessary */
#define EV_LEGAL_NEXT_HOPS (EV_CLASS_CMD | 6) /* Return list of legal n'bors */

#define EV_START (EV_CLASS_CMD | 7)	/* Start going */

/* SHIV : CISE : dont' know whether EV_MAKE_ROUTE is necessary */
#define EV_MAKE_ROUTE (EV_CLASS_CMD | 8) /* Passed a pointer to self in a 
					     list of components,
					     update routing info.  */
/* SHIV: CISE: leaky bucket stuff : #define EV_MORE_TOKEN_POOL (EV_CLASS_CMD | 9)  
#define EV_OK (EV_CLASS_CMD | 10) 
#define EV_GEN (EV_CLASS_CMD | 11)  
*/

/* SHIV: CISE: Defining update activity event to update the route
   activity on the screen
   */
#define EV_UPDATE_ROUTE_ACTIVITY (EV_CLASS_CMD | 9) 

/* Events that have to do with running the simulator */
#define EV_RECEIVE (EV_CLASS_EVENT | 1)	/* Receive a packet event*/
#define EV_READY (EV_CLASS_EVENT | 2)	/* Component ready signal */
#define EV_BUSY (EV_CLASS_EVENT | 3)	/* Component busy signal */
#define EV_COLLISION (EV_CLASS_EVENT | 4) /* A collision has occurred. */

/* SHIV : CISE :  A bunch of TCP related events : #define EV_SEND_BUF (EV_CLASS_EVENT | 5)
#define EV_RECEIVE_BUF (EV_CLASS_EVENT | 6)
#define EV_SEND_UPCALL (EV_CLASS_EVENT | 7)
#define EV_RECEIVE_UPCALL (EV_CLASS_EVENT | 8)
#define EV_SND_OK (EV_CLASS_EVENT | 9)
#define EV_RCV_OK (EV_CLASS_EVENT | 10)
#define EV_OPEN (EV_CLASS_EVENT | 11)  
#define EV_CLOSE_SND (EV_CLASS_EVENT | 12) 
#define EV_CLOSE_RCV (EV_CLASS_EVENT | 13)
#define EV_RCVD_PKT (EV_CLASS_EVENT | 14)
#define EV_GET_SOCKET (EV_CLASS_CMD | 15)
#define EV_GET_MY_SOCKET (EV_CLASS_CMD | 16)

*/

#endif   /* EVENTDEFS_H   */
