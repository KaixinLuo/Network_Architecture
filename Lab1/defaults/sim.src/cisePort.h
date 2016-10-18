
/*
  $Log: cisePort.h,v $
  Revision 4.0  1996/08/23 20:02:27  tlin
  bump to mickey mouse version

  Revision 3.5  1996/07/25 15:37:14  tlin
  min/max

  Revision 3.4  1996/07/24 16:58:32  tlin
  foo

 * Revision 3.3  96/07/24  16:57:57  tlin
 * add Xutil.h
 * 
 * Revision 3.2  96/07/24  16:30:02  tlin
 * add tk.h
 * 
  */

#ifndef CISEPORT_H
#define CISEPORT_H
#define USE_NON_CONST

/* copied from tkPort.h in Tcl/Tk */

/* this should be removed before shipping */
#ifdef linux
#  define HAVE_LIMITS_H
#  define HAVE_UNISTD_H
#endif


#ifdef hppa
#  define HAVE_LIMITS_H
#  define HAVE_UNISTD_H
#endif


#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <strings.h>

#ifdef HAVE_LIMITS_H
#   include <limits.h>
#else
#   include "compat/limits.h"
#endif

#include <math.h>
#include <pwd.h>

#ifdef NO_STDLIB_H
#   include "compat/stdlib.h"
#else
#   include <stdlib.h>
#endif

#include <string.h>
#include <sys/types.h>
#include <sys/file.h>

#ifdef HAVE_SYS_SELECT_H
#   include <sys/select.h>
#endif

#include <sys/stat.h>
#include <sys/time.h>

#define USE_NON_CONST

#ifndef _TCL
#   include <tcl.h>
#endif
#ifndef _TK
#   include <tk.h>
#include <X11/Xutil.h>
#endif

#ifdef HAVE_UNISTD_H
#   include <unistd.h>
#else
#   include <sys/unistd.h>
#endif

#include <stdarg.h>

#ifndef min
#define min(a,b)  ((a)<(b)?(a):(b))
#define max(a,b)  ((a)<(b)?(b):(a))
#endif

#endif /* CISEPORT_H */
