
/*
   $Log: cise.h,v $
   Revision 4.3  1996/09/24 20:20:15  tlin
   foo

   Revision 4.2  1996/09/24 19:38:04  tlin
   add make_node_graph() and make_space_time()

   Revision 4.1  1996/09/20 06:06:05  tlin
   Cise_ClrImg()

   Revision 4.0  1996/08/23 20:02:27  tlin
   bump to mickey mouse version

   Revision 1.11  1996/07/25 17:41:12  tlin
   send graph works, preliminary

 * Revision 1.10  96/07/14  05:52:56  tlin
 * add Cise_Send()
 * 

   */

/* Tk inclusion for CISE -- tlin@cis  */



int Cise_Init(Tcl_Interp *interp);
int Cise_Init2(ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);

int Cise_RunCmd     (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_StepCmd    (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_PauseCmd   (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_ResumeCmd  (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_StopTimeCmd(ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_Delay      (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);


int Cise_Load   (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_Save   (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_Time   (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_Srandom(ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);

int Cise_Send   (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_SendBulk(ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_GetImg (ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);
int Cise_ClrImg(ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]);

void nothing2do(ClientData clientData);

int initBulkData();

