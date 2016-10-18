
#
#
# space-time diagram
#
#     for CISE project at CIS, OSU
#     by  Ting-hsien Lin, tlin@cis.ohio-state.edu
#
 
# $Log: space-time.tcl,v $
# Revision 1.6  1996/09/25 17:27:23  tlin
# add dummy return in make_node_space_time{}. Otherwise
# core dump on 2nodes_error.config.
#
# Revision 1.5  1996/09/24 21:36:11  tlin
# use RaiseList
#
# Revision 1.4  1996/09/20 07:16:38  tlin
# foo
#
# Revision 1.3  1996/09/19 07:25:18  tlin
# mostly work for multiple ST diagram. may need further debug
#
# Revision 1.2  1996/09/19 06:22:16  tlin
# works for one ST diagram. Need modify to make it work for more than one
#
# Revision 1.1  1996/09/19 06:20:58  tlin
# Initial revision
#


proc make_node_space_time {node1 node2 geometry} {
    set s s${node1}To$node2
    global STx1 STx2 STx3 
    global STWidth STHeight STWHeight STTop STBottom
    global STScale STBaseTime STEndTime
    global STLastLabel STtick_dist STtick_density 

    set STScale($s)    5   
    #              1 in time = STScale points in graph
    set STWidth($s)    280
    set STHeight($s)   1000
    set STWHeight($s)  200
    set STTop($s)      20
    set STBottom($s)   20
    set STBaseTime($s) 0
    set STEndTime($s)  [expr ($STHeight($s)-$STBottom($s))/$STScale($s)+$STBaseTime($s)]
    set STLastLabel($s)    0
    set STtick_dist($s)    100
    set STtick_density($s) 0

    set w .st$node1-$node2
    set c $w.c
    toplevel $w
    wm geometry $w [expr $STWidth($s)+20]x$STWHeight($s)$geometry
    wm title $w "Space-time diag. $node1-$node2"

    frame $w.drawingarea
    scrollbar $w.vscroll -command "$c yview"
    pack $w.vscroll -in $w.drawingarea -side right -fill y
    # scrollbar $w.hscroll -command "$c xview" -orient horiz
    # pack $w.hscroll -in $w.drawingarea -side bottom -fill x

    canvas $c -relief sunken -borderwidth 2 \
	    -scrollregion "0 0 $STWidth($s) $STHeight($s)" \
	    -yscrollincrement 1 \
	    -background lightblue \
	    -yscrollcommand "$w.vscroll set"
	    # -xscrollcommand "$w.hscroll set"
    bind $c <2> "$c scan mark %x %y"
    bind $c <B2-Motion> "$c scan dragto %x %y"
    pack $c -expand yes -fill both -in $w.drawingarea
    set STx1($s) [expr $STWidth($s) / 4]
    set STx2($s) [expr $STWidth($s) / 4 * 2]
    set STx3($s) [expr $STWidth($s) / 4 * 3]
    $c create line $STx1($s) 10 $STx1($s) $STHeight($s) -fill black -tag fixed
    $c create line $STx3($s) 10 $STx3($s) $STHeight($s) -fill black -tag fixed

    set STtick_density($s) [expr $STtick_dist($s)/$STScale($s)]
    for {set y $STTop($s); set label $STBaseTime($s)} \
	    {$label < $STEndTime($s)} \
	    {set y [expr $y+$STtick_dist($s)]; \
	    set label [expr $label+$STtick_density($s)]} {
	$c create text $STx1($s) $y -text $label -anchor e -tag event_time
	$c create text $STx3($s) $y -text $label -anchor w -tag event_time
    }
    set STLastLabel($s) $label
    
    pack $w.drawingarea -fill both -expand 1

    global RaiseList
    lappend RaiseList $w

    return 
    # don't remove this dummy statement;
    # the global var RaiseList need this to keep correct value
    # don't know why yet. -- tlin@cis, 9/24/96
    # removing it causing failure of 2nodes_error.config -- 9/25/96
}


# dir=0: node1->node2; dir=1: node2->node1
proc st_event {node1 node2 dir t1 t2 label error} {
    set s s${node1}To$node2
    global STx1 STx2 STx3
    global STWidth STHeight STWHeight STTop STScale STBaseTime STEndTime

    set c .st$node1-$node2.c

    set x_from $STx1($s); set x_to $STx3($s); set from $node1
    if {$dir} { set x_from $STx3($s); set x_to $STx1($s); set from $node2}

    set y1 [expr ($t1 - $STBaseTime($s))*$STScale($s)+$STTop($s)]
    set y3 [expr ($t2 - $STBaseTime($s))*$STScale($s)+$STTop($s)]
    set y2 [expr ($y1+$y3)/2]
    $c create line $x_from $y1 $x_to $y3 -arrow last -fill white \
            -tag event_line
    $c create text $STx2($s) $y2 -text $label -anchor s \
            -tag event_tag

    # puts "error=$error"
    if {$error} {
	# puts "   a cross y2=$y2"
	$c create line [expr $STx2($s) - 5] [expr $y2 - 5] \
		[expr $STx2($s) + 5] [expr $y2 + 5] \
		-fill red -tag event_line -width 3
	$c create line [expr $STx2($s) - 5] [expr $y2 + 5] \
		[expr $STx2($s) + 5] [expr $y2 - 5] \
		-fill red -tag event_line -width 3
    }

    set frac [expr (($t2-$STBaseTime($s))*$STScale($s)-$STWHeight($s)+\
	    $STTop($s)+40)/$STHeight($s)]
    if {$frac>0} {$c yview moveto $frac}

    if {$t2>=$STEndTime($s)} {
	st_advanceTimeBy $s $c [expr $t2-$STEndTime($s)+10]
    }
}

proc st_advanceTimeBy {s c amount} {
    global STx1 STx2 STx3
    global STScale STBaseTime STWidth STEndTime
    global STTop
    global STLastLabel STtick_dist STtick_density 

    set ypix [expr $amount*$STScale($s)]

    $c addtag too_old enclosed 0 -1000 $STWidth($s) $ypix
    $c dtag fixed too_old
    $c delete too_old 
    
    $c move event_time 0 -$ypix
    $c move event_line 0 -$ypix
    $c move event_tag  0 -$ypix
    set STBaseTime($s) [expr $STBaseTime($s)+$amount]
    set STEndTime($s)  [expr $STEndTime($s) +$amount]

    set label $STLastLabel($s)
    if {$label < $STBaseTime($s)} {set label $STBaseTime($s)}

    set y [expr ($label-$STBaseTime($s))*$STScale($s)+$STTop($s)]
    for {set label $STLastLabel($s); \
	    set y [expr ($label-$STBaseTime($s))*$STScale($s)+$STTop($s)]} \
	    {$label < $STEndTime($s)} \
	    {set y [expr $y+$STtick_dist($s)]; \
	    set label [expr $label+$STtick_density($s)]} {
	$c create text $STx1($s) $y -text $label -anchor e -tag event_time
	$c create text $STx3($s) $y -text $label -anchor w -tag event_time
    }
    set STLastLabel($s) $label
}

