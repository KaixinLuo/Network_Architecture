/*
 *
 * $Log: log.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.3  1996/05/29 16:20:20  tlin
 * dgb_write() redo
 *
 * Revision 2.2  1996/05/29 01:24:54  tlin
 * remove inline version of log_param(c, p)
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:31  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:26  goyal
 * Lab1
 * 
 * Revision 1.0  96/04/24  15:01:47  shivkuma
 * Lab 1
 * 
 * Revision 1.1  96/04/22  00:00:00  shivkuma
 * Version Before Putting in User-Friendly names
 * 
 * Revision 0.0  96/02/21  00:44:00  goyal
 * Initial Revision
 * 
 *
 *
 */

#ifndef LOG_H
#define LOG_H
/* log.h,v 1.0 1993/10/21 19:11:55 NIST golmie */
/* SHIV : cleaned up for CISE */

#include "component.h"
#include "event.h"
#include "sim.h"

/* Header file describing structures used in the log cluster. */

typedef FILE *Log;


/* function prototype */
int dbg_set_level(int level);
int dbg_write(int level, Component *c, char *format, ...);
void dbg_param_close();

#endif   /* LOG_H   */
