/** Header file for a heap. */
/* SHIV : cleaned up for CISE */
/*
 *
 * $Log: heap.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.4  1996/05/30 13:30:13  tlin
 * foo
 *
 * Revision 2.3  1996/05/30 11:06:56  tlin
 * prototyping
 *
 * Revision 2.2  1996/05/29 21:31:56  tlin
 * foo
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:25  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:22  goyal
 * Lab1
 * 
 * Revision 1.0  96/04/24  15:01:41  shivkuma
 * Lab 1
 * 
 * Revision 1.1  96/04/21  23:59:58  shivkuma
 * Version Before Putting in User-Friendly names
 * 
 * Revision 0.0  96/02/21  00:43:59  goyal
 * Initial Revision
 * 
 *
 *
 */


/* heap.h,v 1.0 1993/10/21 19:11:36 NIST */

#ifndef HEAP_H
#define HEAP_H


/* Change these two lines to redefine the key used in the heap. */
typedef unsigned Key_type;
#define KEY_LESS_THAN(k1, k2) ((k1) < (k2))

typedef struct _heap_elt {
	Key_type key;
	caddr_t elt;
} Heap_elt;

#define HEAP_DEFAULT_SIZE 32 
typedef struct _heap {
	int size;		/* Number of elements in the heap */
	int max_size;		/* Max number that can be stored
				   before the array must be resized. */
	Heap_elt *elts;
	int iter;		/* Index to iterate over heap elements. */
} Heap;

#define HEAP_PARENT(elt_index) (((elt_index) - 1) / 2)
#define HEAP_LEFT(elt_index)   ((elt_index) * 2 + 1)
#define HEAP_RIGHT(elt_index)  (((elt_index) + 1) * 2)

/* Swap elts[i] with elts[j] */
#define HEAP_SWAP(h, i, j) \
	{ \
	  Heap_elt he; \
	  he = h->elts[(i)]; \
	  h->elts[(i)] = h->elts[(j)]; \
	  h->elts[(j)] = he; \
	}

Heap *heap_create();
void heap_destroy(Heap *h);
void heap_insert(Heap *h, Key_type key, caddr_t elt);
caddr_t heap_min(Heap *h);
caddr_t heap_extract_min(Heap *h);



#endif  /* HEAP_H */








