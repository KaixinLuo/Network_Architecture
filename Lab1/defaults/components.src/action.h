/* 
   $Log: action.h,v $
   Revision 4.0  1996/08/23 20:06:37  tlin
   bump to mickey mouse version

   Revision 3.0  1996/05/30 14:42:17  tlin
   bump to 3.0; before Tk adition

   Revision 1.4  1996/05/30 13:57:28  tlin
   foo

   Revision 1.3  1996/05/30 10:48:22  tlin
   LINKConnectiont was defined in link.h

   Revision 1.2  1996/05/30 10:30:06  tlin
   foo

   Revision 1.1  1996/05/30 10:28:41  tlin
   Initial revision

   */

/*   cise project -- tlin@cis                      */



caddr_t application_layer_action();
caddr_t dlc_layer_action        ();
caddr_t physical_layer_action   ();
caddr_t link_action             ();

