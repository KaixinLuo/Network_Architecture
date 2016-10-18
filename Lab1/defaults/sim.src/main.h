

/* 
   $Log: main.h,v $
   Revision 4.2  1996/09/20 06:44:20  tlin
   dprintf()

   Revision 4.1  1996/09/20 06:31:58  tlin
   M.debugLevel

   Revision 4.0  1996/08/23 20:02:27  tlin
   bump to mickey mouse version

   Revision 3.19  1996/06/30 01:01:45  tlin
   add back get_argv() and -x option

                                                   */
/*   cise project -- tlin@cis                      */

#include <tk.h>

#ifdef MAIN
#    define extern 
#endif

typedef struct {
    char   *libDir;       /* path to library; for help and .tcl files */
    char   *pr_name;      /* program name                         */
    char   *filename;     /* World file name                      */
    list   *comps;        /* the components for simulator to run  */
    char   snapname[32];  /* for snap file                        */
    tick_t stoptime;      /* for simulation to stop               */
    int    delay;         /* delay between events, in usec        */
    short  delta;         /* ??                                   */
    int    running;       /* Is the simulator running             */
    int    paused;        /* Is the simulator running             */
    int    single_step;   /* Single stepping or not?              */
    int    seed;          /* seed for random                      */
    int    debugLevel;    /* for dprintf()                        */
    int    doX;           /* if FALSE, don't open any X windows   */

    /* X window related */
    int        reverse_video;
    int        depth;       /* depth of screen                    */
    Tcl_Interp *interp;
    Tk_Window  tk_canvas;
    Window     canvas;
    Display    *display;
    GC         gc;          /* default GC                         */
    char       *bg_name;    /* background color of canvas         */
    XColor     *bg_color;   /* background color of canvas         */
    GC         gcxor[10];   /* GC with XOR function               */
    GC         gccopy[10];  /* GC with Copy function              */
    ulong      colors[10];  /* colors xor'ed with background      */
} ENVIRONMENT;


extern ENVIRONMENT M;     /* the finite state machine             */


int  start_tk(int argc, char **argv);
void init_cise();
int  init_simulator();
int  get_argv(int *argc, char **argv);
int  usage(char *argv[]);
int  sim_reset(list *comps);
int  sim_start(list *comps);


void cse_debug( int level, char *format, ...);


#ifdef MAIN
#    undef extern 
#endif
