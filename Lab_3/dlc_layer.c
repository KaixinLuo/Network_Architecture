/* ----------- PROGRAMMING ASSIGNMENT 3  ----------------- 
 * Name: Jake Hill
 * Class: CSE 3461
 * Instructor: Gojko Babic
 * ---------------------------------------------------- */
/* --- DO NOT REMOVE OR MODIFY  #include STATEMENTS BELOW --- */

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

static int
window_open(DLC_Conn_Info_TYPE *dci)
{
   /* Based on a number of a_pdu's in the transmission buffer 
      and values for snd_nxt, snd_una and window_size    
      determine if there is a new a_pdu ready to be sent */

  int result;
  int data_available = DataInPDUBuffer(dci);
  int occupied_window;

  occupied_window = ((dci->snd_nxt >= dci->snd_una) ?
      (dci->snd_nxt - dci->snd_una) :
      (dci->snd_nxt + dci->window_size + 1 - dci->snd_una));
  result = ((occupied_window < data_available) &&
                   (occupied_window < dci->window_size));
  
  return result; // result = 1, there is an a_pdu ready
                 // result = 0, there is not
}

/**************************************************************/
/* --- DO NOT REMOVE OR MODIFY THIS FUNCTION --- */
static 
dlc_layer_receive(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity,
		  GENERIC_LAYER_ENTITY_TYPE *generic_layer_entity,
		  PDU_TYPE *pdu)
{
	/* Gets the appropriate  DLC_Conn_Info_TYPE structure */
	DLC_Conn_Info_TYPE *dci;
	dci = Datalink_Get_Conn_Info(dlc_layer_entity,pdu);
      
	if (DatalinkFromApplication(generic_layer_entity)) {
	    FromApplicationToDatalink(dlc_layer_entity, pdu, dci);
	} else if (DatalinkFromPhysical(generic_layer_entity)) {
	    FromPhysicalToDatalink(dlc_layer_entity, pdu, dci);
	}
	return 0;
}



static
FromApplicationToDatalink(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity, PDU_TYPE *pdu_from_application,
				   DLC_Conn_Info_TYPE *dci)
{
  /* Insert the pdu from the applicaiton layer to the 
     transmission buffer. Use:
     InsertPDUIntoBuffer(dlc_layer_entity, pdu, dci); */
    InsertPDUIntoBuffer(dlc_layer_entity, pdu_from_application, dci);
  
  
  /* If possible send info frame. You may use: 
     SendInfo(dlc_layer_entity, dci); */
     
    if(window_open(dci)){
      SendInfo(dlc_layer_entity, dci);
    }
}

static
FromPhysicalToDatalink(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity,
					  PDU_TYPE *pdu_from_physical,
					  DLC_Conn_Info_TYPE *dci)
{

	/* Check and discard the pdu when error is detected */
  if(pdu_from_physical->u.d_pdu.error){
    return 0;
  }
	
	/* If not discarded, check d_pdu.type and call an 
        appropriate function: 
	   if RR you may use and call DataLinkProcessRR()
	   if REJ you may use and call DataLinkProcessREJ()
	   if INFO you may use and call DataLinkProcessINFO() */
  switch(pdu_from_physical->u.d_pdu.type){
    case D_INFO :
      DatalinkProcessInfo(dlc_layer_entity, pdu_from_physical, dci);
      break;
    case D_RR :
      DatalinkProcessRR(dlc_layer_entity, pdu_from_physical, dci);
      break;
    case D_REJ :
      DatalinkProcessREJ(dlc_layer_entity, pdu_from_physical, dci);
      break;
  }
}

static
DatalinkProcessRR(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity,
				  PDU_TYPE *pdu,
				  DLC_Conn_Info_TYPE *dci)
{

  /* Ignore and discard all other RRs */
  
  //Check for valid address
  if(pdu->u.d_pdu.address != GetNodeID(dlc_layer_entity) && 
      pdu->u.d_pdu.address != GetReceiverID(dlc_layer_entity)){
    pdu_free(pdu);
    return 0;
  }
  
  //Update window and send all info pdu's allowed by window
  UpdatePDUBuffer(dlc_layer_entity,pdu,dci);
  dci->snd_una = pdu->u.d_pdu.number;
  while(window_open(dci)){
    SendInfo(dlc_layer_entity, dci);
  }
  
  if(pdu->u.d_pdu.p_bit){
  
    if(pdu->u.d_pdu.address == GetNodeID(dlc_layer_entity)) {
        /* If this is a command RR with P/F_bit=1:
            *Free up space in the retransmission buffer.
            *Clear rej_already_sent 
            *Update snd_una
            *Send as many info pdu's as allowed by window. 
            *Create and send to physical layer a response RR with P/F_=1
        */
        
        dci->rej_already_sent = 0;
        //Set p_bit based on command RR's fields
        SendRR(dlc_layer_entity, pdu, dci);
        
    }else if(dci->rr_pbit_sent){
        /* If this is response RR with P/F_bit=1 and rr_pbit=1:
            *Free up space in the retransmission buffer.
            *Clear rr_pbit_sent 
            *Update snd_una and snd_nxt
            *Send as many info pdu's as allowed by window.
        */
        dci->rr_pbit_sent = 0;
    }
  }
 
  /* Free pdu */
  pdu_free(pdu);
  return 0;
}


static
DatalinkProcessREJ(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity,
				   PDU_TYPE *pdu, DLC_Conn_Info_TYPE *dci)
{
   /* Check the address and if not correct discard frame and
       return 0;
      Otherwise, free up space in the retransmission buffer */
  if(pdu->u.d_pdu.address != GetReceiverID(dlc_layer_entity) ||
      pdu->u.d_pdu.p_bit){
    pdu_free(pdu);
    return 0;
  }
  UpdatePDUBuffer(dlc_layer_entity, pdu, dci);  
     /* update snd_una and snd_nxt */
  dci->snd_una = pdu->u.d_pdu.number;
  dci->snd_nxt = dci->snd_una;
     /* Send as many pdu's as allowed by window */
  while(window_open(dci)){
    SendInfo(dlc_layer_entity, dci);
  }
	/* Free pdu */
  pdu_free(pdu);
    return 0;
}

static
DatalinkProcessInfo(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity,
					PDU_TYPE *pdu,
					DLC_Conn_Info_TYPE *dci)
{
	PDU_TYPE *pdu_to_application;
     
 /* Check the address and P/F_bit and if not correct discard frame */
  if(pdu->u.d_pdu.address != GetNodeID(dlc_layer_entity) ||
      pdu->u.d_pdu.p_bit){
    return 0;
  }
 /* Check if the pdu has the expected sequence number
    When out of sequence, then send REJ, discard pdu and 
    return 0 */
	if(pdu->u.d_pdu.number != dci->rcv_nxt){
	  SendREJ(dlc_layer_entity, pdu, dci);
	  return 0;
	}
	
/* If expected PDU, then increment rcv_nxt,
      clear rej_already_sent and RR is sent
   You may use SendRR() to send RR to physical */
	dci->rcv_nxt = (dci->rcv_nxt + 1) % MODULO;
	dci->rej_already_sent = 0;
	SendRR(dlc_layer_entity, pdu, dci);
  
  /* --- Send pdu to application */
	pdu_to_application = pdu_alloc();
	pdu_to_application->type = TYPE_IS_A_PDU;
	pdu_to_application->u.a_pdu = pdu->u.d_pdu.a_pdu;
	send_pdu_to_application_layer( dlc_layer_entity, pdu_to_application);
	
	/* Free pdu */
	pdu_free(pdu);
	return 0;
}

/**************************************************************/
/* --- DO NOT CHNAGE NAME OF THIS FUNCTION --- */
/* The function is automatically called when the timer expires*/
static
DatalinkTimerExpired(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity,
					 DLC_Conn_Info_TYPE *dci)
{
  /* Only if there are a_pdu in the buffer, allocate a new d_pdu 
    and fill in the needed fields for a command RR with P_Fbit=1 
    Set rr_pbit_sent=1
    Send d_pdu to physical layer 
  */
  dci->snd_nxt = dci->snd_una;
  /*--- Explicitly allocate a command RR ---*/
  if(window_open(dci)){
	  PDU_TYPE *comm_RR = pdu_alloc();
	  comm_RR->type = TYPE_IS_D_PDU;
	  comm_RR->u.d_pdu.type = D_RR;
    comm_RR->u.d_pdu.p_bit = 1;
    comm_RR->u.d_pdu.number = dci->rcv_nxt; 
    comm_RR->u.d_pdu.address = GetReceiverID(dlc_layer_entity);
	  comm_RR->u.d_pdu.error = NO;
	
	  dci->rr_pbit_sent = 1;
    SendRR(dlc_layer_entity, comm_RR, dci);
  }
  
  return 0;
}

static
SendInfo(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity,
			  DLC_Conn_Info_TYPE *dci)
{
     /* get a_pdu to send */
	PDU_TYPE *pdu_to_send;
	pdu_to_send = GetPDUFromBuffer(dci);
  
	/* Copy it to a new d_pdu and fill the remaining fields */
	PDU_TYPE *d_pdu = pdu_alloc();
	d_pdu->type = TYPE_IS_D_PDU;
	d_pdu->u.d_pdu.a_pdu = pdu_to_send->u.a_pdu;
	d_pdu->u.d_pdu.type = D_INFO;
		d_pdu->u.d_pdu.p_bit = NO;
	d_pdu->u.d_pdu.number = dci->snd_nxt;
	d_pdu->u.d_pdu.address = GetReceiverID(dlc_layer_entity);
	d_pdu->u.d_pdu.error = NO;
	/* increment snd_nxt */
	dci->snd_nxt = (dci->snd_nxt + 1) % MODULO;
     /* Set timer. Use:
	   SetTimer(dlc_layer_entity,dci);    */
  SetTimer(dlc_layer_entity, dci);
	/* --- Send d_pdu to physical layer: Same as Lab1 --- */
	
	send_pdu_to_physical_layer(dlc_layer_entity, d_pdu);
  return 0;
}

static
SendRR(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity, PDU_TYPE *pdu,
	   DLC_Conn_Info_TYPE *dci)
{
	/* Allocate a new d_pdu and fill in the needed fields */
	PDU_TYPE *d_pdu = pdu_alloc();
	d_pdu->type = TYPE_IS_D_PDU;
	//d_pdu->u.d_pdu.a_pdu = pdu->u.a_pdu;
	d_pdu->u.d_pdu.type = D_RR;
  d_pdu->u.d_pdu.p_bit = pdu->u.d_pdu.p_bit; //set to one if pdu is RR
  d_pdu->u.d_pdu.number = dci->rcv_nxt; 
  d_pdu->u.d_pdu.address = pdu->u.d_pdu.address; //set to reciever if command RR
	d_pdu->u.d_pdu.error = NO;
	SetTimer(dlc_layer_entity, dci);
	/* Send to d_pdu to physical layer */
  send_pdu_to_physical_layer(dlc_layer_entity, d_pdu);
  
	return 0;
}

static
SendREJ(DLC_LAYER_ENTITY_TYPE *dlc_layer_entity, PDU_TYPE *pdu,
		DLC_Conn_Info_TYPE *dci)
{
  if(dci->rej_already_sent){
    return 0;
  }
	/* Allocate a new d_pdu and fill in the needed fields */
	PDU_TYPE *d_pdu = pdu_alloc();
	d_pdu->type = TYPE_IS_D_PDU;
	d_pdu->u.d_pdu.a_pdu = pdu->u.a_pdu;
	d_pdu->u.d_pdu.type = D_REJ;
		d_pdu->u.d_pdu.p_bit = NO;
	d_pdu->u.d_pdu.number = dci->rcv_nxt;
	d_pdu->u.d_pdu.address = GetNodeID(dlc_layer_entity);
	d_pdu->u.d_pdu.error = NO;
	/* Send to d_pdu to physical layer */
  send_pdu_to_physical_layer(dlc_layer_entity, d_pdu);
	/* rej_already_sent set to 1 */
  dci->rej_already_sent = 1;
	return 0;
}

