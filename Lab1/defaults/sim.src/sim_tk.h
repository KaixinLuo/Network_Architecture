

/*
   $Log: sim_tk.h,v $
   Revision 4.0  1996/08/23 20:02:27  tlin
   bump to mickey mouse version

   Revision 1.6  1996/06/03 00:45:48  tlin
   neighbor relationship is shown on canvas

   Revision 1.5  1996/06/02 17:51:04  tlin
   workaable, phase 1

   Revision 1.4  1996/06/01 05:48:36  tlin
   add char *name to icon_xxx()

   Revision 1.3  1996/06/01 02:23:22  tlin
   function without body is ready

   Revision 1.2  1996/06/01 01:53:24  tlin
   foo

   Revision 1.1  1996/06/01 01:46:25  tlin
   Initial revision

   
   */

/* Tk inclusion for CISE -- tlin@cis  */

#ifndef SIM_TK_H
#define SIM_TK_H

typedef struct {
    Component *scomponent;
    int x, y, w, h;
} XComponent;


XComponent* icon_app (Component *co, int x, int y);
XComponent* icon_dlc (Component *co, int x, int y);
XComponent* icon_phy (Component *co, int x, int y);
XComponent* icon_link(Component *co, int x, int y);


int show_neighbor_relation(Component *c1, Component *c2);


#endif
