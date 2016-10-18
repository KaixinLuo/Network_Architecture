#ifndef COMPONENT_H
#define COMPONENT_H
/* component.h,v 1.0 1993/10/24 20:49:38 NIST  golmie*/
/* SHIV : cleaned up for CISE */
/*
 *
 * $Log: component.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.4  1996/06/03 06:18:07  tlin
 * forward reference Param, Component in sim.h
 *
 * Revision 3.3  1996/06/02 17:28:32  tlin
 * reorganize _Param, Param so no more depencency
 *
 * Revision 3.2  1996/06/01 01:47:24  tlin
 * add XComponent  *co_picture to Component
 *
 * Revision 3.1  1996/06/01 01:39:20  tlin
 * indented
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.8  1996/05/30 11:45:51  tlin
 * move subr.h after Neighbor
 *
 * Revision 2.7  1996/05/30 10:24:22  tlin
 * remove init_...(); it's in subr.h
 *
 * Revision 2.6  1996/05/30 10:22:21  tlin
 * move subr.h to middle
 *
 * Revision 2.5  1996/05/30 10:17:21  tlin
 * use subr.h
 *
 * Revision 2.4  1996/05/29 02:40:34  tlin
 * typedef Component COMPONENT;
 *
 * Revision 2.3  1996/05/29 00:49:38  tlin
 * move DisplayMask etc for p_flags to component.h
 *
 * Revision 2.2  1996/05/29 00:43:28  tlin
 * remove tie from X
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:08  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:16  goyal
 * Lab1
 * 
 * Revision 1.1  96/04/25  15:51:23  tlin
 * LOAD fixed
 * 
 * Revision 1.0  96/04/24  15:00:40  shivkuma
 * Lab 1
 * 
 * Revision 1.1  96/04/21  23:59:53  shivkuma
 * Version Before Putting in User-Friendly names
 * 
 * Revision 0.0  96/02/21  00:43:55  goyal
 * Initial Revision
 * 
 *
 *
 */


/**********************************************
  The component structure.  
  Describes the structure used to store the hosts, switches, links, etc.
  This is a generic structure used to refer to a component when the
  differences don't matter.  The individual components (link, host, etc.)
  will have different data in the tail end of the component structure,
  (and may be different sizes), but the beginning is all the same.

  The list of components will be a doubly-linked list.  The links are used
  only for operations that need to access all the components (saving,
  broadcast events, etc).
*/



#include "sim.h"
#include "sim_tk.h"
#include "q.h"
#include "list.h"
#include "log.h"
#include "subr.h"


/* Structure to store parameters */
struct _Param  {
    struct _Param *p_next, *p_prev;	/* So these can be put in a queue */
    char		p_name[40];	/* Name of this param for display */
    PFD		p_calc_val;	/* Routine that computes a value to be 
				   displayed in a meter.  Used only for
				   parameters that can be metered.  Syntax:
				   double val = (*calc_val)(c, p)
				   Component *c;	This component
				   PARAM *p;	This parameter  */
    PFP		p_make_text;	/* Routine to make a string containing
				   some representation of the current value
				   of this parameter.  Needed for all
				   params that are displayed in an
				   infowindow.  Syntax:
				   char *text = (*make_text)(c, p)
				   Component *c;
				   PARAM *p;  */
    PFP		p_make_short_text; /* As p_make_text, but only the value.
				      eg, instead of "Processing delay: 1000",
				      just "1000".  Present in all parameters.
				      (Used to save the world in a file.) */
    PFI		p_input;	/* Routine to input this parameter. Passed
				   a string and the parameter--returns
				   TRUE if the string is a legal value,
				   FALSE otherwise.  p_make_short_text and
				   p_input are converses.  ie,
				   p_input(p, p_make_short_text(c, p)) ==>
				   no change to parameter.  Syntax:
				   (*p_input)(p, string, c)
				   Param *p;
				   char *string;
				   Component *c;  */
    /*GRAF_OBJECT	p_my_picture;	/* The graphics object that displays this */
    int		p_display_type;	/* Type of meter or whatever to display */
    int		p_flags;	/* Flags about how to display this, including:
				   Whether this is now displayed or not.
				   If it has been changed since last screen
				   update.    */
    int		p_log;		/* Integer associated with this param for log*/
    double	p_scale;	/* Scale to use for meters */
    struct {		/* Union to store whatever data in. */
	int i;			/* The graphics library should not muck */
	/* SHIV : CISE :    int vpi; */ 
	double d;			/* with this-- it is used & maintained by */
	caddr_t p;			/* the simulator.  */
	struct {
	    caddr_t p ;
	    /* SHIV : CISE :       int vpi; */
	    int i;
	} pi;
    } u;
};


struct _Component {
    struct _Component
    *co_next, *co_prev; /* Links to other components in the list */
    short	co_class;	/* Class of component            */
    short	co_type;	/* Type of component             */
    char	co_name[40];	/* Name of component             */
    PFP		co_action;	/* Main function of component.
				   Is called with each event that happens.
				   Syntax:  Many arguments needed.  */
    XComponent  *co_picture;	/* Graphics object that displays this thing */
    
    /* Doubly linked list of neighbors.  Data stored for each
       neighbor includes a PARAM structure, and possibly some other stuff.
       The graphics routines will have to follow this list if they are going
       to display any data associated with individual neighbors.  */
    list	*co_neighbors;

    /* Parameters-- data that will be displayed on screen */
    /* The number of parameters is fixed for each type of component. */
    short	co_menu_up;	/* If true, then the text window is up */
    short       co_big_menu;
    queue	*co_params;	/* Variable-length queue of parameters */

    int		iq_length;      /* put any public information here */
    int		iq_limit;       /* used for int packet trains */

    /* Any other info that component needs to keep-- will vary.
       .
       .
       .     */


};


/* Macro to reference parameters */

#define pval(comp, name)  ( comp->name )

#define pupdatei(comp, name, expr)  {  \
		pval(comp, name)->u.i = expr;  \
		log_param((Component *)(comp), pval(comp, name));  \
	}

#define pupdated(comp, name, expr)  {  \
		pval(comp, name)->u.d = expr;  \
		log_param((Component *)(comp), pval(comp, name));  \
	}


/* co_neighbors is list of these structures */
struct _Neighbor {
    struct _Neighbor *n_next, *n_prev;          /* Links for the list. */
    Component	*n_c;	       /* Pointer to the neighboring component */
    /* The next values will vary from network to network, and from
       component to component.  For example, only switches & hosts have
       queues in the current application. */
    queue	*n_pq;		       /* Queue of packets to be sent  */
    short	n_busy;		       /* True if the neighbor is busy */
    double      n_prev_sample;  /* Previous sample time used for utilization
				     calculation in links */
    Param	*n_p;		/* index of parameter to display whatever */
    Param       *n_pp;          /* index of parameter to display whatever */
    Param       *n_ppp;
    caddr_t	n_data;		/* If a component wants to store arbitrary
				   data for each neighbor, put it here. */
};


/* Flags that go in p_flags of parameters */

#define MeterMask 1
#define DisplayMask 2
#define ChangeMask 4
#define CanHaveMeterMask 8
#define InputMask 16
#define CanHaveLogMask 32
#define LogMask 64

/* Fields in the p_display_type of parameters.
   (Should really be a structure with bit fields, but we'll worry
   about that later.)  */

#define MeterColorMask 0xF0
#define MeterTypeMask 0xF

#define BINARY 1
#define BAR_GRAPH 2
#define LOG 3
#define TIME_HISTORY 4
#define TIME_HISTORY_D 5
#define DELTA 6
#define MULTI 7
#define HISTOGRAM 8


#endif   /* COMPONENT_H   */




