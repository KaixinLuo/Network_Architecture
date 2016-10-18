/*
 *
 * $Log: sim.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.2  1996/06/03 06:18:07  tlin
 * forward reference Param, Component in sim.h
 *
 * Revision 3.1  1996/06/02 21:09:03  tlin
 * works again.
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.6  1996/05/30 13:23:33  tlin
 * foo
 *
 * Revision 2.5  1996/05/30 12:58:24  tlin
 * foo
 *
 * Revision 2.4  1996/05/30 12:57:25  tlin
 * remove MIN()... etc
 *
 * Revision 2.3  1996/05/29 23:03:26  tlin
 * remove malloc(), etc
 *
 * Revision 2.2  1996/05/29 17:41:35  tlin
 * PFP)(vPFP -> (void *src, ...); not sure if works
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:42  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:32  goyal
 * Lab1
 * 
 * Revision 1.0  96/04/24  15:02:05  shivkuma
 * Lab 1
 * 
 * Revision 1.1  96/04/22  00:00:07  shivkuma
 * Version Before Putting in User-Friendly names
 * 
 * Revision 0.0  96/02/21  00:44:04  goyal
 * Initial Revision
 * 
 *
 *
 */

#ifndef SIM_H
#define SIM_H
 /* sim.h,v 1.0 1993/10/21 19:07:52 NIST */


/* remember to #include "cisePort.h" before #include "sim.h".
   This is unavoidable because sim.h maybe included as 
   extern "C" {} while cisePort.h cannot in C++ files.
   -- tlin@cis                                               */
#ifndef CISEPORT_H
    error "Must include cisePort.h before include sim.h"
#endif

/* Things for all simulator routines */

#define TRUE 1
#define FALSE 0
#define OFF 0
#define ON 1
#define ERROR -1
#define OK 1

typedef double Rate_t;

/* Tick better be unsigned long !! */
typedef unsigned long tick_t;
typedef double usec_t;
typedef double nsec_t;


/* Define time elapsed per simulator clock tick either in USECS_PER_TICK 
   or NSECS_PER_TICK.  Either USECS_PER_TICK or NSECS_PER_TICK should be
   defined, but not both.
   NSECS_PER_TICK must divide 1000 or else you will get some strange
   roundoff errors. */

/* tick = 1 ns = 0.001 usec */
/* SHIV : version 13 */

#define USECS_PER_TICK	 0.001

/* infinity : */
//define INFINITY 10000

#ifdef NSECS_PER_TICK
# define  NSECS_TO_TICKS(time) ((tick_t)  ((time) / NSECS_PER_TICK) )
# define  TICKS_TO_NSECS(ticks) (((nsec_t) (ticks)) * NSECS_PER_TICK)
# define  USECS_TO_TICKS(time) ((tick_t) ((time) * (1000 / NSECS_PER_TICK)) )
# define  TICKS_TO_USECS(ticks) (((nsec_t) (ticks)) / (1000 / NSECS_PER_TICK))
# define  SECSD_TO_TICKS(time) ((tick_t) (((time) * 1000000000) / NSECS_PER_TICK))
# define  TICKS_TO_SECSD(ticks) ((((nsec_t) (ticks)) * NSECS_PER_TICK) / 1000000000)
#else
# ifdef USECS_PER_TICK
#  define NSECS_TO_TICKS(time) ((tick_t) ((time) / (USECS_PER_TICK * 1000)))
#  define TICKS_TO_NSECS(ticks)  (((usec_t)(ticks)) * (USECS_PER_TICK * 1000))
#  define USECS_TO_TICKS(time) ((tick_t) ((time) / USECS_PER_TICK))
#  define TICKS_TO_USECS(ticks)  (((usec_t) (ticks)) * USECS_PER_TICK)
#  define SECSD_TO_TICKS(time) ((tick_t) (((time) * 1000000) / USECS_PER_TICK))
/* $Revision: 4.0 $ */
#  define SECSD_TO_USECS(time) ((tick_t) ((time) * 1000000))
#  define TICKS_TO_SECSD(ticks) ((((usec_t) (ticks)) * USECS_PER_TICK) / 1000000)
# endif
#endif


#define UNIX_4_2    1
#define UNIX_4_3    2

#define DBG_INFO	1
#define DBG_ERR		2

#ifdef __STDC__
#define CONST const
#else  /* __STDC__ */
#define CONST
#endif  /* __STDC__ */


/** Largest number returned by random(). (2**31)-1   From RANDOM(3) */
#define MAX_RANDOM_NUMBER 2147483647

/* Oft-used item:  Pointer to a Function that returns an Integer */
typedef int (*PFI)();
/* Pointer to Function that returns a Double.  */
typedef double (*PFD)();
/* Pointer to Function that returns a Pointer */
typedef caddr_t (*PFP)();


#define uint  unsigned int
#define uchar unsigned char
#define ulong unsigned long


/* defined in component.h */
typedef struct _Param     Param;        /* we need these forward reference  */
typedef struct _Component Component;    /* so that other #include files can */
typedef struct _Neighbor  Neighbor;     /* refer to them. -- tlin@cis       */
typedef Component COMPONENT;            /* historical burden from netsim    */
typedef Param     PARAM;
typedef Neighbor  NEIGHBOR;



#endif   /* SIM_H   */

