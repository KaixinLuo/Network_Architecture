/* ----- DO NOT REMOVE OR MODIFY ----- */
#include "cisePort.h"
#include "sim.h"
#include "component.h"
#include "comptypes.h"
#include "list.h"
#include "eventdefs.h"
#include "main.h"
#include "route_activity.h"
#include "sim_tk.h"
#include "dlc_layer.h"

/****************************************************/

static dlc_layer_receive(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity,
                        GENERIC_LAYER_ENTITY_TYPE *generic_layer_entity,
                        PDU_TYPE *pdu)
{
    if (DatalinkFromApplication(generic_layer_entity)) {
        FromApplicationToDatalink(dlc_layer_entity, pdu);
    } else if (DatalinkFromPhysical(generic_layer_entity)) {
        FromPhysicalToDatalink(dlc_layer_entity, pdu);   
    }
   return 0;
}

/* ----- START HERE AND COMPLETE THE FOLLOWING TWO FUNCTIONS ----- */


FromApplicationToDatalink(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity,
                   PDU_TYPE *pdu_from_application)
{
   PDU_TYPE *pdu_to_physical; /* use this with pdu_alloc() */ 

   // Just a sanity check
   if(pdu_from_application->type!=TYPE_IS_A_PDU) cse_panic("Empty a_pdu\n");

   // Create d_pdu using pdu_alloc()
   pdu_to_physical = pdu_alloc();
   pdu_to_physical->type = TYPE_IS_D_PDU;
   
   // update address field, a_pdu field and error field;   
	pdu_to_physical->u.d_pdu.a_pdu = pdu_from_application->u.a_pdu;
	pdu_to_physical->u.d_pdu.address = GetReceiverID(dlc_layer_entity);
	pdu_to_physical->u.d_pdu.error = NO;
	
	cse_debug(1,"\nd_pdu generated");
	cse_debug(1,"\naddress: %d", pdu_to_physical->u.d_pdu.address);
	cse_debug(1,"\nPDU_TYPE: %d", pdu_to_physical->type);
	
   /* Send to physical layer; 
      Use something like this:

   send_pdu_to_physical_layer(dlc_layer_entity,pdu_to_physical);
   */
   
   //cse_debug(0,"\nsending d_pdu to physcial layer");
   printf("\nsending d_pdu to physical_layer");
   send_pdu_to_physical_layer(dlc_layer_entity, &pdu_to_physical);
 
   /* Free a_pdu;
      Use something like this:

   pdu_free(pdu_from_application);
   */
   cse_debug(1, "\nFreeing application pdu");
   pdu_free(pdu_from_application);

   return 0;
}


FromPhysicalToDatalink(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity,
                      PDU_TYPE *pdu_from_physical)
{
	
	cse_debug(1,"\nd_pdu recieved from pysical layer");
    PDU_TYPE * pdu_to_application;

   /* just a sanity check */ 
    if (pdu_from_physical->type != TYPE_IS_D_PDU) cse_panic("Empty d_pdu\n");
	
   /* 
      1. Check error and the address fields. 
      2. Send a_pdu to the application layer only if the d_pdu is error-free.
   */
   int curr_address = GetNodeID(dlc_layer_entity);
   int dpdu_address = pdu_from_physical->u.d_pdu.address;
   int dpdu_error = pdu_from_physical->u.d_pdu.error;
   
   if((curr_address == dpdu_address) && (dpdu_error != YES)){
	   pdu_to_application = pdu_alloc();
	   pdu_to_application->type = TYPE_IS_A_PDU;
	   
	   
	   pdu_to_application->u.a_pdu = pdu_from_physical->u.d_pdu.a_pdu;
	   send_pdu_to_application_layer(dlc_layer_entity, pdu_to_application);
	   
	   cse_debug(1,"\nMessage Sent successfully  \n\n\n");
   }else{
	   cse_debug(1,"\nd_pdu was currupted. Packet Dropped.");
   }

   // Free d_pdu;
   
   pdu_free(pdu_from_physical);
   
    return 0;
}

