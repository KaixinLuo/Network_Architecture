
/*
  $Log: route_activity.h,v $
  Revision 4.0  1996/08/23 20:02:27  tlin
  bump to mickey mouse version

  Revision 1.4  1996/06/03 11:41:58  tlin
  refresh screen when expose; not debug yet

  Revision 1.3  1996/06/03 04:34:46  tlin
  working with copy gc

  Revision 1.2  1996/06/03 03:58:25  tlin
  syntax bugs gone

  Revision 1.1  1996/06/03 01:37:09  tlin
  Initial revision

  */

/* for CISE project -- developed by tlin@cis */

int init_route_activity();
int delete_route_activity();
int update_routes(Component *src, Component *dest);
int route_activity(Component *src, Component *dest, tick_t delay, 
		       int color, int error);
void refresh_route_activity(ClientData clientData, XEvent *eventPtr);
