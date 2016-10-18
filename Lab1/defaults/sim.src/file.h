
/* 
   $Log: file.h,v $
   Revision 4.0  1996/08/23 20:02:27  tlin
   bump to mickey mouse version

   Revision 3.0  1996/05/30 14:40:54  tlin
   bump to 3.0; before Tk adition

   Revision 1.2  1996/05/29 17:21:55  tlin
   read_world()

   Revision 1.1  1996/05/29 16:50:32  tlin
   Initial revision


   */
/*   cise project -- tlin@cis                      */


int save_world(list *clist, char *filename, list *route_table);
int save_snapshot(list *clist, char *filename, list *route_table);
list *read_world(char *name);
