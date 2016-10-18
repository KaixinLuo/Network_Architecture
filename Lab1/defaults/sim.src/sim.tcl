

# $Log: sim.tcl,v $
# Revision 4.5  1996/09/25 19:50:15  tlin
# about{}
#
# Revision 4.4  1996/09/25 17:16:56  tlin
# debugLevel: 0-3
#
# Revision 4.3  1996/09/20 07:02:14  tlin
# foo
#
# Revision 4.2  1996/09/20 06:58:43  tlin
# add $MdebugLevel
#
# Revision 4.1  1996/09/19 06:19:17  tlin
# split space-time.tcl for space-time diagram
#
# Revision 4.0  1996/08/23 20:02:27  tlin
# bump to mickey mouse version
#
# Revision 3.39  1996/07/31 17:03:37  tlin
# foo
#
#


#
#
# driving script for cise project -- tlin@cis, 5/26/96
#
#

# include some useful subroutines
source $cise_library/subr.tcl
source $cise_library/space-time.tcl


# ------------------------------------------------------
#
#      general outlook of the window
#
# ------------------------------------------------------

wm geometry . +50+30
wm title . "CSE 3461/5461 Computer Network Simulator"

set width  1000
set height 750


source $cise_library/layout.tcl


# ------------------------------------------------------
#
#      menu commands 
#
# ------------------------------------------------------


proc nop {name} {
    .msg configure -text "Command $name: this function is not ready yet"
}

proc menu_load {filename} {
    global Mfilename
    if {$filename == ""} {
	set Mfilename [input .d "Wait for input" "Please input filename:" $Mfilename]
    } else {
	set Mfilename $filename
    }
    .filename configure -text "Filename: $Mfilename"
    .msg      configure -text "[cise_load]"
}

proc menu_run {} {
    bind . <space> {menu_step1}
    .msg configure -text "[cise_run]; <space> for single step"
}

proc menu_step {} {
    bind . <space> {menu_step1}
    menu_step1
}

proc menu_step1 {} {
    .msg configure -text "[cise_step]; use \"Resume\" to resume; <space> for more";
}

proc menu_pause {} {
    .msg configure -text [cise_pause]
}

proc menu_resume {} {
    bind . <space> {}
    .msg configure -text [cise_resume]
}

proc menu_delay {} {
    set t [cise_delay]
    set t [input .d "Wait for input" "Please input amount of delay (msec)" $t]
    change_delayTime $t
}

proc menu_stopTime {} {
    set t [expr [cise_stopTime]/1000]
    set t [input .d "Wait for input" "Please input Stop Time (usec)" $t]
    change_stopTime $t
}

proc about {} {
    dialog .about {About CSE} \
	    {
CSE 3461/5461 Network Simulator ver2.0,
The Ohio State Univ, 2012.
PI:		Gojko Babic
Developer:	Kazuya Sakai

-- 
CISE project was developed at CIS,		
The Ohio State Univ, 1995-1996.

Principle Investigator:  Steve Lai
		       Raj Jain
Developers:   Ting-hsien Lin
	       Kalyanaraman Shivkumar
	       Rohit Goyal} \
	    info -1 OK
}

proc how_to_use {} {
    global cise_library
    xnotify .d "Help: How to use" "$cise_library/how-to-use.txt" -1 "OK"
}


# ------------------------------------------------------
#
#      draw graph for objects
#
# ------------------------------------------------------


set icon_color(app)  tan
set icon_color(dlc)  orange
set icon_color(phy)  yellow
set icon_color(link) green
set icon_color(bomb) red
proc make_icon {name type x y} {
    global icon_color
    .c create rectangle [expr $x-15] [expr $y-15] [expr $x+15] [expr $y+15] \
	    -fill $icon_color($type) -tag $name
    .c create text $x $y -text $name -tag $name
}

proc show_neighbor_relation {x1 y1 x2 y2 name1 name2} {
    .c create line $x1 $y1 $x2 $y2 -fill white -tag $name1$name2
    .c lower $name1$name2
}


# ------------------------------------------------------
#
#      status line
#
# ------------------------------------------------------

proc update_time {} {
    .time configure -text "[cise_time] usec"
}

proc change_stopTime {t} {
    cise_stopTime [expr $t*1000]
    set a [cise_stopTime]
    .stopTime configure -text "Stop Time: [expr $a/1000] usec"
}
change_stopTime 100000

proc change_delayTime {t} {
    cise_delay $t
    .delayTime configure -text "Delay: [cise_delay] msec"
}
change_delayTime 50

proc menu_debugLevel {inc} {
    global MdebugLevel
    incr MdebugLevel $inc
    if {$MdebugLevel<0} {set MdebugLevel 0}
    if {$MdebugLevel>3} {set MdebugLevel 3}
    .debugLevel configure -text "DebugLevel: $MdebugLevel"
}


# ------------------------------------------------------
#
#      main program
#
# ------------------------------------------------------


# show all windows so menu_load{} has a canvas to draw on
update

# some variables (eg. canvas .c) are not created yet when 
# Cise_Init() is invoked. cise_init2 takes care of these.
cise_init2

set Mfilename ""
if {$argc>=1} {
    menu_load [lindex $argv 0]
}
