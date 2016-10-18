#ifndef PDU_H
#define PDU_H

#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>

#define INTSIZE   sizeof(int)
#define DATASIZE  128               /* maximum length          */
#define MAXNODES  20

/* The following are the types of messages communicated between 
 * physical layer & datalink layer, and client & server 
 */
enum boolean { NO, YES };

/* ---------- D_PDU Definition (Used in Go Back N Labs) ----- */
#define D_INFO	0
#define D_RR	1
#define D_REJ	2

/* data unit between app. layer and datalink layer */
typedef struct {
	char data[DATASIZE];           /* message */
} A_PDU_TYPE;
#define A_PDU_SIZE sizeof(A_PDU_TYPE)

/* data unit between datalink layer and physical layer */
typedef struct {
     int              address;	//The address of the receiver

     /* ----------- Begin: New fields (Used in Go Back N Labs)  -------- */
     int              type;		// One of D_INFO, D_RR, D_REJ
     int              number;	// Sequence number, ack number, or nak number
     enum boolean	  p_bit;	// P bit, 0 or 1
     /* ----------- End: New fields (Used in Go Back N Labs) -------- */

     A_PDU_TYPE		a_pdu;		// The application data.
     enum boolean	error;		// YES if the packet is corrupted, otherwise NO.
	 
	 /* ----------- Used in phyisical layer ------------- */
	 int sender;	// the sender's address
} D_PDU_TYPE;
#define D_PDU_SIZE sizeof(D_PDU_TYPE)

/* data unit between physical layers */
typedef struct {
     D_PDU_TYPE        d_pdu;	// dlc data.
} PH_PDU_TYPE;
#define PH_PDU_SIZE sizeof(PH_PDU_TYPE)

/* ------ Values for the type field in PDU_TYPE ---- */
#define TYPE_IS_A_PDU 0
#define TYPE_IS_D_PDU 1
#define TYPE_IS_PH_PDU 2

typedef struct {
	union {
		A_PDU_TYPE a_pdu;
		D_PDU_TYPE d_pdu;
		PH_PDU_TYPE ph_pdu;
	} u; 

     int type;    //One of TYPE_IS_A_PDU, TYPE_IS_D_PDU, TYPE_IS_PH_PDU
} PDU_TYPE;
#define PDU_SIZE sizeof(PDU_TYPE)

// Initialize the pool of packets. Returns 0 for failure.
int pdu_init();
// Allocates a packet and returns a pointer thereto.  The packet is guaranteed to contain garbage.
PDU_TYPE *pdu_alloc();
//Passed a packet pointer, frees it.
void pdu_free(PDU_TYPE *pdu);

#endif   /* PDU_H   */
