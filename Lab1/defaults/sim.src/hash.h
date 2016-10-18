/*
 *
 * $Log: hash.h,v $
 * Revision 4.0  1996/08/23 20:02:27  tlin
 * bump to mickey mouse version
 *
 * Revision 3.1  1996/06/03 01:53:36  tlin
 * prototyping
 *
 * Revision 3.0  1996/05/30 14:40:54  tlin
 * bump to 3.0; before Tk adition
 *
 * Revision 2.1  1996/05/28 05:57:31  tlin
 * bump to v 2.1; before tcl/tk conversion
 *
 * Revision 0.1  1996/05/27 22:51:23  tlin
 * test
 *
 * Revision 0.0  96/04/26  15:34:22  goyal
 * Lab1
 * 
 * Revision 1.0  96/04/24  15:01:39  shivkuma
 * Lab 1
 * 
 * Revision 1.1  96/04/21  23:59:58  shivkuma
 * Version Before Putting in User-Friendly names
 * 
 * Revision 0.0  96/02/21  00:43:58  goyal
 * Initial Revision
 * 
 *
 *
 */

#ifndef HASH_H
#define HASH_H
/* SHIV : cleaned up for CISE */

#include "q.h"

/* hash.h,v 1.3.2.21 1993/05/21 19:11:31 ath Rel2_2 */

/*  Header file for a hash table.  */

/* This will actually also contain the key and record, but they are variable
   length & are not shown here.  */
typedef struct _Hash_elem  {
  struct _Hash_elem *he_next;	/* Pointer for use by queue */
  char he_key[1];		/* Start of the key here */
} Hash_elem;

typedef queue Hash_bucket;

typedef struct _Htable {
  int ht_size, ht_key_size, ht_rec_size;
  Hash_bucket *ht_table;
  /* Next two vars used by ht_iter */
  int ht_iter_current_bucket;
  Hash_elem *ht_iter_next_item;
} *Htable;

Htable ht_create(int size, int key_size, int rec_size);
int    ht_insert(Htable ht, char *key, char *rec);
int    ht_delete(Htable ht, char *key);
char  *ht_find(Htable ht, char *key);
int    ht_obliterate(Htable ht);
int    ht_iter_setup(Htable ht);
char  *ht_iter(Htable ht);

#endif   /* HASH_H   */
