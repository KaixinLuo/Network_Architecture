/*
 *
 * $Log: mempool.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.2  1996/05/29 22:23:09  tlin
 * remove inline
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:34  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:27  goyal
 * Lab1
 * 
 * Revision 1.0  96/04/24  15:01:51  shivkuma
 * Lab 1
 * 
 * Revision 1.1  96/04/22  00:00:01  shivkuma
 * Version Before Putting in User-Friendly names
 * 
 * Revision 0.0  96/02/21  00:44:01  goyal
 * Initial Revision
 * 
 *
 *
 */

#ifndef MEMPOOL_H
#define MEMPOOL_H
/* mempool.h,v 1.0 1993/10/21 19:12:03 NIST */
/* SHIV : cleaned up for CISE */

#include "sim.h"
#include "q.h"

/* Header file for the memory pool */

typedef struct _Mempool {
  queue *mp_free;		/* List of free envelopes */
  queue *mp_mem_chunks;		/* List of big chunks of memory allocated */
  unsigned mp_data_size, mp_how_many;
  unsigned mp_envs_per_rec;
} Mempool;

typedef struct _MemEnvelope {
  struct _MemEnvelope *me_next, *me_prev;
} MemEnvelope;


caddr_t  mp_alloc(register Mempool *mp);
void     mp_free(register Mempool *mp, register char *p);
Mempool *mp_init(int how_many, int data_size);
void     mp_destroy(Mempool *mp);
int      mp_more_mem(Mempool *mp);
void     mp_free_all(Mempool *mp);


#endif   /* MEMPOOL_H   */
