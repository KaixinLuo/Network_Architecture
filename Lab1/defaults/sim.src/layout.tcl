

# $Log: layout.tcl,v $
# Revision 4.13  1996/09/25 19:33:48  tlin
# remove unused menu items
#
# Revision 4.12  1996/09/24 21:35:59  tlin
# use RaiseList
#
# Revision 4.11  1996/09/24 20:28:52  tlin
# the display of node-graph and space-time diagram
# is control by world file
#
# Revision 4.10  1996/09/20 18:34:00  tlin
# foo
#
# Revision 4.9  1996/09/20 18:31:52  tlin
# foo
#
# Revision 4.8  1996/09/20 07:21:03  tlin
# unify short cut in run
#
# Revision 4.7  1996/09/20 07:01:52  tlin
# add debugLevel
#
# Revision 4.6  1996/09/20 06:30:06  tlin
# clear_image{}: clear transmitted image
#
# Revision 4.5  1996/09/19 08:26:59  tlin
# foo
#
# Revision 4.4  1996/09/19 08:00:07  tlin
# send msg/graph triggers run if not already running
#
# Revision 4.3  1996/09/19 07:28:50  tlin
# key binding: ctrl-D to delay
#
# Revision 4.2  1996/09/19 06:18:25  tlin
# split space-time.tcl for space-time diagram
#
# Revision 4.1  1996/09/19 03:27:39  tlin
# remove h-scroll bar in space-time diagram.
#
# Revision 4.0  1996/08/23 20:02:27  tlin
# bump to mickey mouse version
#
# Revision 1.30  1996/08/01 15:51:41  tlin
# geometry change
#
# Revision 1.29  96/07/31  16:52:12  tlin
# foo
# 
# 
#

#
#
# layout script for cise project -- tlin@cis, 6/2/96
#
#

# container frames
    frame  .mbar        -relief raised -bd 2
    frame  .middle
    frame  .cmd         -relief raised -bd 2
    frame  .status_line -relief raised -bd 2

# command buttons
    button .cmd.c1 -bitmap hourglass -command {nop hourglass}
    button .cmd.c2 -bitmap questhead -command {nop questhead}
#    pack   .cmd.c1 .cmd.c2

# status line
    label  .filename    -text "Filename: (None)"  
    label  .label1      -text "Simulation Time: "
    label  .time        -text "0 usec"
    label  .stopTime    -text "Stop Time: 0 usec" 
    label  .delayTime   -text "Delay: 0 usec"     
    label  .debugLevel  -text "DebugLevel: $MdebugLevel"
    label  .msg         -text ""

# drawing area (canvas)
    set Mbg_name SteelBlue
    canvas .c -width $width -height $height -background $Mbg_name

# pack them up
    pack   .mbar        -side top -fill x
    pack   .middle      -side top -fill both -expand yes
    pack   .status_line -side top -fill x
    pack   .cmd  -in .middle -side left  -fill both
    pack   .c    -in .middle -side left  -fill both -expand yes
    pack   .filename .stopTime .delayTime .debugLevel .msg\
                             -in .status_line -side left  -fill both -ipadx 3m
    pack   .time .label1     -in .status_line -side right -fill both

# menu items
menubutton .mbar.file -text File -underline 0 -menu .mbar.file.menu
menubutton .mbar.edit -text Edit -underline 0 -menu .mbar.edit.menu
menubutton .mbar.run  -text Run  -underline 0 -menu .mbar.run.menu
menubutton .mbar.help -text Help -underline 0 -menu .mbar.help.menu
pack .mbar.file .mbar.edit .mbar.run -side left
pack .mbar.help -side right

menu .mbar.file.menu
.mbar.file.menu add command -label "Load" -underline 0 -accelerator "Ctrl+L" -command {menu_load ""}
.mbar.file.menu add separator
.mbar.file.menu add command -label "Exit" -underline 1 -accelerator "Ctrl-Q" -command exit

menu .mbar.edit.menu
.mbar.edit.menu add command -label "Raise"  -underline 0                       -command {raise_all}

menu .mbar.run.menu
.mbar.run.menu add command -label "Run"         -underline 0 -accelerator "Ctrl+R" -command {menu_run}
.mbar.run.menu add separator
.mbar.run.menu add command -label "Single step" -underline 0                       -command {menu_step}
.mbar.run.menu add command -label "Pause"       -underline 0                       -command {menu_pause}
.mbar.run.menu add command -label "Resume"      -underline 3                       -command {menu_resume}
.mbar.run.menu add command -label "Delay"       -underline 4 -accelerator "Ctrl+D" -command {menu_delay}
.mbar.run.menu add separator
.mbar.run.menu add command -label "Stop Time"   -underline 5                       -command {menu_stopTime}
.mbar.run.menu add separator
.mbar.run.menu add command -label "Inc Debug Level" -underline 0                       -command {menu_debugLevel 1}
.mbar.run.menu add command -label "Dec Debug Level" -underline 0                       -command {menu_debugLevel -1}

menu .mbar.help.menu
.mbar.help.menu add command -label "About CSE" -underline 0 -command about
.mbar.help.menu add command -label "How to use" -underline 0 -command how_to_use


# global binding
proc global_binding {} {
    bind . <Control-n> {nop New}
    bind . <Control-l> {menu_load ""}
    bind . <Control-s> {nop Save}
    bind . <Control-x> {nop Delete}
    bind . <Control-z> {nop Undo}
    bind . <Control-r> menu_run
    bind . <Control-d> menu_delay
    bind . <Control-q> exit
}

global_binding
bind . <Expose> global_binding


# add a dialog box for node 1

proc make_node_dialog {node geometry} {
    set c .node$node
    toplevel $c
    wm geometry $c $geometry

    frame $c.butts
    button $c.b1 -text "Send msg"     -command "get_txt_and_send $c.text $node"
    button $c.b2 -text "Send graph"   -command "get_img_and_send $c.c $node"
    button $c.b3 -text "Clear msg"    -command "$c.text delete 1.0 end"
    button $c.b4 -text "Clear graph"  -command "clear_image $c.c $node"
    button $c.b5 -text "Load  graph"  -command "load_image $c.c $node"
    pack $c.b1 $c.b2 $c.b3 $c.b4 $c.b5 -in $c.butts -side top -fill x

    frame $c.text_frame 
    text $c.text -relief raised -bd 2 \
	    -yscrollcommand "$c.t_vscroll set" \
	    -xscrollcommand "$c.t_hscroll set" \
	    -background lightseagreen \
	    -width 20 -height 12
    scrollbar $c.t_vscroll -command "$c.text yview"
    scrollbar $c.t_hscroll -command "$c.text xview" -orient horiz
    pack $c.t_vscroll -in $c.text_frame -side right  -fill y
    pack $c.t_hscroll -in $c.text_frame -side bottom -fill x
    pack $c.text      -in $c.text_frame -side left   -fill both -expand 1
    focus $c.text
    # bind .text <Configure> {puts "config %w %h"}

    canvas $c.c  -width 150 -height 190 -background lightblue
    pack $c.butts $c.text_frame $c.c -side left; raise $c

    global ImageLoaded RaiseList
    set ImageLoaded(n$node) 0
    lappend RaiseList $c
}

# bind .c <Expose> {after 500 {raise .node1; raise .node2; raise .node3}}


proc show_msg {node msg} {
    set c .node$node
    #$c.text insert end "$node $msg\n"
    $c.text insert end "$msg\n"
    $c.text yview end
}

proc get_txt_and_send {text node} {
    #puts            [$text get {insert linestart} {insert lineend}]
    cise_send $node [$text get {insert linestart} {insert lineend}]
    $text mark set insert {insert + 1 lines}
}

proc load_image {c node} {
    global tk_library ImageLoaded
    
    image create photo image2 -file $tk_library/demos/images/earth.gif
    set h [image height image2]
    set w [image width  image2]
    $c create image 0 0 -image image2 -anchor nw -tag img
    set ImageLoaded(n$node) 1
    info globals
}

proc clear_image {c node} {
    global tk_library ImageLoaded
    $c delete img
    cise_clrImg $node $c
    set ImageLoaded(n$node) 0
}

proc get_img_and_send {c node} {
    global ImageLoaded

    if {$ImageLoaded(n$node)!=1} {load_image $c $node; update}
    cise_getImg $node $c 150 190
    cise_sendBulk  $node
}



proc raise_all {} {
    global RaiseList
    foreach c $RaiseList {
	raise $c
    }
}
