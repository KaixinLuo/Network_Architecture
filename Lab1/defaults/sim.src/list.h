/*
 *
 * $Log: list.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:29  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:25  goyal
 * Lab1
 * 
 * Revision 1.0  96/04/24  15:01:45  shivkuma
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


#ifndef LIST_H
#define LIST_H
/* list.h,v 1.0 1993/10/21 19:11:49 NIST */
/* SHIV : cleaned up for CISE */

/* Doubly-linked list/queue routines.
   Hacked from PC/IP queue routines.  */

typedef	struct	l_elt	{	/* list element */
	struct	l_elt	*le_next, *le_prev;  /* Links */
	caddr_t le_data;
} l_elt;

typedef	struct	list	{		/* list header */
	l_elt	*l_head;		/* first element in list */
	l_elt	*l_tail;		/* last element in list */
	int	l_len;			/* number of elements in queue */
	int	l_max;			/* maximum length */
	int	l_min;			/* minimum length */
} list;

extern caddr_t l_remh(), l_remt();
extern l_elt *l_addt(), *l_addh(), *l_adda(), *l_find(),
		*le_remh(), *le_remt();
extern list *l_create();
void l_obliterate(), lq_delete();

/* The following macros implement most of the common list operations */

/* Add an element to the head of the list */

#define le_addh(l, elt)  { \
	if ((l)->l_head == 0) \
	  (l)->l_tail = (l_elt *)(elt); \
	else \
	  (l)->l_head->le_prev = (l_elt *)(elt); \
	((l_elt *)(elt))->le_next = (l)->l_head; \
	((l_elt *)(elt))->le_prev = 0; \
	(l)->l_head = (l_elt *)(elt); \
	if (++((l)->l_len) > (l)->l_max) \
	  (l)->l_max = (l)->l_len; \
}
			   
/* Add an element to the tail of a list */

#define le_addt(l, elt)  { \
	if ((l)->l_tail == 0) \
	  (l)->l_head = (l_elt *)(elt); \
	else \
	  (l)->l_tail->le_next = (l_elt *)(elt); \
	((l_elt *)(elt))->le_prev = (l)->l_tail; \
	((l_elt *)(elt))->le_next = 0; \
	(l)->l_tail = (l_elt *)(elt); \
	if (++((l)->l_len) > (l)->l_max) \
	  (l)->l_max = (l)->l_len; \
}

/* Add an element after a specified element in the list.  If prev == */
/* &l->l_head, can be used to add an element to the head of the queue */

#define le_adda(l, prev, new)  { \
	if ((l)->l_head == 0)  {		            /*** Empty */ \
	  ((l_elt *)(new))->le_prev = ((l_elt *)(new))->le_next = 0; \
	  (l)->l_tail = (l_elt *)(new); \
	} else if ((l)->l_tail == (l_elt *)(prev))  {         /*** At end */ \
	  ((l_elt *)(new))->le_prev = (l_elt *)(prev); \
	  (l)->l_tail = (l_elt *)(new); \
	} else if ((l_elt *)(&l->l_head) == (l_elt *)(prev))  { /*** At front */ \
	  ((l_elt *)(new))->le_prev = 0; \
	  (l)->l_head->le_prev = (l_elt *)(new); \
	} else  {					    /*** Middle */ \
	  ((l_elt *)(new))->le_prev = (l_elt *)(prev); \
	  ((l_elt *)(prev))->le_next->le_prev = (l_elt *)(new); \
	} \
	((l_elt *)(new))->le_next = ((l_elt *)(prev))->le_next; \
	((l_elt *)(prev))->le_next = (l_elt *)(new); \
	if (++((l)->l_len) > (l)->l_max) \
	  (l)->l_max = (l)->l_len; \
}


/* Delete a given element. */

#define le_del(l, elt)  { \
	if (((l_elt *)(elt))->le_next) \
	  ((l_elt *)(elt))->le_next->le_prev = ((l_elt *)(elt))->le_prev; \
	else \
	  (l)->l_tail = ((l_elt *)(elt))->le_prev; \
	if (((l_elt *)(elt))->le_prev) \
	  ((l_elt *)(elt))->le_prev->le_next = ((l_elt *)(elt))->le_next; \
	else \
	  (l)->l_head = ((l_elt *)(elt))->le_next; \
	if (--(l)->l_len < (l)->l_min) \
	  (l)->l_min = (l)->l_len; \
}
#endif   /* LIST_H   */
