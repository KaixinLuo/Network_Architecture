/* ------------- WRAPPERS FOR THE DLC_LAYER CODE ---------- */
/* --- Please do not modify this file. --------- */
/* --- Any doubts, send email to shivkuma@cis.ohio-state.edu
   ----- */


extern Log pkt_log;

static caddr_t cn_reset(),cn_create(),cn_neighbor(),
               cn_uneighbor(),cn_route(),cn_hops(),cn_send();
static 
dlc_layer_receive();								      

#define dlc_other_event_handlers()                      \
{							\
  case EV_RESET:					\
  {							\
       cn->cn_iq_length = 0;				\
       cn->cn_iq_limit = 1;				\
       result=(caddr_t)cn;				\
       break;						\
  }							\
  case EV_CREATE:					\
       result = cn_create((char *)arg);			\
       break; 						\
  case EV_DEL:						\
       comp_delete((Component *)cn);			\
       result = (caddr_t)cn;				\
       break;						\
  case EV_NEIGHBOR:					\
       result = cn_neighbor(cn, (Component *)arg);	\
       break;						\
  case EV_UNEIGHBOR:					\
       result = cn_uneighbor(cn, (Component *)arg);	\
       break;						\
  case EV_LEGAL_NEXT_HOPS:				\
       result = cn_hops(cn);				\
       break;						\
  case EV_MAKE_ROUTE:					\
       result = cn_route(cn, (list *)arg);		\
       break;						\
  case EV_START:					\
     result = (caddr_t)(cn);				\
     break;						\
  case EV_UPDATE_ROUTE_ACTIVITY:			\
     update_routes(src,(Component *)cn);                \
        result=(caddr_t)cn;				\
       break;						\
							\
}

caddr_t dlc_layer_action(Component *src,
			 DLCConnectiont *cn,
			 int type,
			 PDU_TYPE *pdu,
			 caddr_t arg)
{
     caddr_t result = NULL;	      			      
     switch (type)  {
     case EV_RECEIVE:
       dlc_layer_receive(cn,src,pdu);				 
	  result = (caddr_t)cn;
	  break;			
	  dlc_other_event_handlers();	 
     default:
	  break;			  
     }					    
     return(result);			      
}

#define DatalinkFromApplication(src) ((src)->co_class == APP_CLASS)
#define DatalinkFromPhysical(src) ((src)->co_class == PHY_CLASS)

#define send_pdu_to_physical_layer(cn,pdu)					 \
{										 \
     Neighbor *n;								 \
										 \
     for (n=(Neighbor *)cn->cn_neighbors->l_head;n;n=n->n_next) {		 \
	  if (n->n_c->co_class == PHY_CLASS)					 \
	       break;								 \
     }										 \
     if (M.doX)                                                                  \
	route_activity((Component *)cn, n->n_c, 10, 2, 0);                       \
     ev_enqueue(EV_RECEIVE, (Component *)cn, n->n_c, ev_now()+10,		 \
		n->n_c->co_action, (PDU_TYPE *) pdu_to_physical, (caddr_t)NULL); \
}

#define send_pdu_to_application_layer(cn,pdu)				\
{									\
      Neighbor *n;							\
      for (n=(Neighbor *)cn->cn_neighbors->l_head;n;n=n->n_next) {	\
	  if (n->n_c->co_class == APP_CLASS)				\
	       break;							\
     }									\
									\
     if (M.doX) 				                        \
	 route_activity((Component *)cn, n->n_c, 10, 2, 0);             \
							                \
     ev_enqueue(EV_RECEIVE, (Component *)cn, n->n_c, ev_now()+10,	\
		n->n_c->co_action, (PDU_TYPE *) pdu_to_application,	\
		(caddr_t)NULL);						\
}

#define DLC_LAYER_ENTITY_TYPE DLCConnectiont
#define GENERIC_LAYER_ENTITY_TYPE Component

/****************************************/
static caddr_t
cn_create(name)
     register char *name;
{
    DLCConnectiont *newcn;

   /* Memory for the component structure. */
   newcn = (DLCConnectiont *)sim_malloc(sizeof(DLCConnectiont));

   /* First things first-- copy name into the new structure. */
   strncpy(newcn->cn_name, name, 40);

   /* have to create a neighbor list */
  newcn->cn_neighbors= l_create();
  newcn->cn_params = q_create();
  newcn->cn_type = DLC_LAYER_TYPE;
  newcn->cn_class = DLC_CLASS;
  newcn->cn_action = (PFP)dlc_layer_action;
  newcn->cn_menu_up = FALSE;
  newcn->cn_flash = 0;

 /* Initialize the parameters */
  newcn->cn_Name = param_init ((Component*)newcn, "Name",
             (PFD)NULL, (PFP)make_name_text, (PFP)make_short_name_text,
             param_input_name,
             0, DisplayMask | InputMask | CanHaveLogMask, 0.0);

   return((caddr_t)newcn);
}

/****************************************/
static caddr_t
cn_neighbor(cn,c)
     register DLCConnectiont *cn;
     register Component *c;
{
     register Neighbor *n;
    if (!(n=add_neighbor((Component*)cn,c,2,2,APP_CLASS,PHY_CLASS)))
        return ((caddr_t)NULL);
    return ((caddr_t)n);
}

/*****************************************/
static caddr_t
cn_uneighbor(cn,c)
   register DLCConnectiont *cn;
   register Component *c;
{
   return ((caddr_t)remove_neighbor((Component *)cn,c));
}

/******************************************/

static caddr_t
cn_hops(cn,l)
   register DLCConnectiont *cn;
   list *l;
{


    register list *nlist;
    register Neighbor *n;
    register Component *c;

/* what is legal for the next hop depends on the type of the previous
   hop. If the previous one is a link, then the next must be a connection.
   If the previous one is a connection, the next one may be either a link
   or a connection.
   (Allowing a connection with both ends at the same bte ) */

   /* The previous step in the route = tail of list is put in c */
   c = (Component *)(l->l_tail->le_data);

   /* Make an empty list */
   nlist = l_create();

   /* Put appropriate neighbors into list */
   for (n=(Neighbor *)cn->cn_neighbors->l_head;n;n=n->n_next)
       if (n->n_c!=c && ((c->co_class == APP_CLASS) ||
           (c->co_class == PHY_CLASS && n->n_c->co_class == APP_CLASS)))
            l_addt(nlist,(caddr_t)n->n_c);


    return ((caddr_t)nlist);


}

/*******************************************/
static caddr_t
cn_route(cn,route_list)
         register DLCConnectiont *cn;
         list *route_list;
{

#ifdef NOTDEF
         Param *p;
         Component *this_component;
         Component *other_component;
         Neighbor *n1;
         Neighbor *n2;
    

         p=param_init((Component *)cn,"Other End Connection :               ",
                      int_calc,make_int_text,make_short_int_text,
                      (PFI)NULL,0,DisplayMask | CanHaveLogMask,0.0);

        if ((((Component *)route_list->l_head->le_data)->co_name[3] !=
              cn->cn_name[3]) || 
             (((Component *)route_list->l_head->le_data)->co_name[2] !=
              cn->cn_name[2]) || 
              (((Component *)route_list->l_head->le_data)->co_name[1] !=
              cn->cn_name[1]) || 
              (((Component *)route_list->l_head->le_data)->co_name[0] !=
              cn->cn_name[0]) ) 
            strcat(p->p_name,((Component *)route_list->l_head->le_data)->
                              co_name);
        else strcat(p->p_name,((Component *)route_list->l_tail->le_data)->
                               co_name);
 
         cn->cn_vpi=vpi;

         this_component = (Component *)route_list->l_head->le_data;
         other_component = (Component *)route_list->l_tail->le_data ;      

         n1= (Neighbor *)this_component->co_neighbors->l_head;
         n2= (Neighbor *)other_component->co_neighbors->l_head;

         if (n1->n_c->co_name[3] == n2->n_c->co_name[3])
            cn->cn_simple_connection=1;
         

           return ((caddr_t)cn); /* return something non-null */
#endif
}
 
/********************************************************************/

