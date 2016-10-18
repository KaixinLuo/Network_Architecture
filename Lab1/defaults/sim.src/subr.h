/* 
   $Log: subr.h,v $
   Revision 4.0  1996/08/23 20:02:27  tlin
   bump to mickey mouse version

   Revision 3.1  1996/05/30 21:50:40  tlin
   add usleep() for non-BSD

   Revision 3.0  1996/05/30 14:40:54  tlin
   bump to 3.0; before Tk adition

   Revision 1.6  1996/05/30 11:40:19  tlin
   find_neighbor()

   Revision 1.5  1996/05/30 10:44:28  tlin
   more prototping, make_text() ...

   Revision 1.4  1996/05/30 10:26:30  tlin
   more prototyping, stdarg.h

   Revision 1.3  1996/05/30 09:55:50  tlin
   foo

   Revision 1.2  1996/05/29 23:16:34  tlin
   prototyping

   Revision 1.1  1996/05/29 23:14:44  tlin
   Initial revision

   */

/*   cise project -- tlin@cis                      */



char *make_text(Component *c, Param *p);
char *make_name_text(Component *c, Param *p);
char *make_short_name_text(Component *c, Param *p);
int  param_input_name(Param *p, char *s, Component *c);
char *make_int_text(Component *c, Param *p);
char *make_short_int_text(Component *c, Param *p);
double int_calc(Component *c, Param *p);
char *make_double_text(Component *c, Param *p);
char *make_short_double_text(Component *c, Param *p);
double double_calc(Component *c, Param *p);
char *make_bool_text(Component *c, Param *p);
char *make_short_bool_text(Component *c, Param *p);
char *make_string_text(Component *c, Param *p);
char *make_short_string_text(Component *c, Param *p);
double bool_calc(Component *c, Param *p);
double color_calc(Component *c, Param *p);
double pktq_calc(Component *c, Param *p);
char * pktq_text(Component *c, Param *p);
char * pktq_short_text(Component *c, Param *p);
double q_calc(Component *c, Param *p);
char *q_text(Component *c, Param *p);
char *q_short_text(Component *c, Param *p);
int param_input_int(Param *p, char *s, Component *c);
int param_input_double(Param *p, char *s, Component *c);
int param_input_bool(Param *p, char *s, Component *c);
int param_input_string(Param *p, char *s, Component *c);


char *sim_malloc(unsigned size);
char *sim_calloc(unsigned nelem, unsigned elsize);
char *sim_realloc(char *ptr, unsigned size);

void cse_panic(char *s);

Neighbor *find_neighbor(list *l, Component *c);
Neighbor *add_neighbor(register Component *c, register Component *neighc,
		       int max_num_neighbors, int num_classes, ...);
int remove_neighbor(register Component *c, register Component *neighc);


Param *param_init(Component *c, char *name, PFD calc_val, 
		  PFP make_text, PFP make_short_text, PFI input,
		  int display_type, int flags, double scale);


int  ucase(register char *s);
#ifndef BSD
    //void usleep(unsigned long usec);
#endif
