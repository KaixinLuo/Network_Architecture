
# $Log: subr.tcl,v $
# Revision 4.3  1996/09/25 19:43:15  tlin
# foo
#
# Revision 4.2  1996/09/24 20:41:56  tlin
# foo
#
# Revision 4.1  1996/09/19 07:32:08  tlin
# better look in input dialog
#
# Revision 4.0  1996/08/23 20:02:27  tlin
# bump to mickey mouse version
#
# Revision 1.5  1996/06/04 17:13:39  tlin
# add xnotify{}
#
# Revision 1.4  1996/06/04 14:35:56  tlin
# in input{}, focus $w.entry
#
# Revision 1.3  1996/06/04 14:19:52  tlin
# pause, resume, single step works more consistently
#
# Revision 1.2  1996/06/03 11:07:23  tlin
# add input{}
#
# Revision 1.1  1996/06/03 00:54:13  tlin
# Initial revision
#

#
#
# supporting script for cise project -- tlin@cis, 5/26/96
#
#


# ------------------------------------------------------
#
#      graphical support
#
# ------------------------------------------------------

# copied from the TK book
proc dialog {w title text bitmap default args} {
    global button


    toplevel $w -class Dialog
    wm title $w $title
    wm iconname $w Dialog
    wm geometry $w +300+300
    frame $w.top -relief raised -bd 1
    pack  $w.top -side top -fill both
    frame $w.bot -relief raised -bd 1
    pack  $w.bot -side bottom -fill both
    
    message $w.top.msg -width 4i -text $text \
	    -font -Adobe-Times-Medium-R-Normal-*-180-*
    pack $w.top.msg -side right -expand 1 -fill both \
	    -padx 3m -pady 3m
    if {$bitmap != ""} {
	label $w.top.bitmap -bitmap $bitmap
	pack $w.top.bitmap -side left -padx 3m -pady 3m
    }

    set i 0
    foreach but $args {
	button $w.bot.button$i -text $but -command "set button $i"
	if {$i == $default} {
	    frame $w.bot.default -relief sunken -bd 1
	    raise $w.bot.button$i
	    pack $w.bot.default -side left -expand 1 -padx 3m -pady 2m
	    pack $w.bot.button$i -in $w.bot.default \
		    -side left -padx 2m -pady 2m -ipadx 2m -ipady 1m
	} else {
	    pack $w.bot.button$i -side left -expand 1 \
		    -side left -padx 3m -pady 3m -ipadx 2m -ipady 1m
	}
	incr i
    }

    if {$default >= 0} {
	bind $w <Return> "$w.bot.button$default flash; set button $default"
    }
    set oldFocus [focus]
    grab set $w
    focus $w

    tkwait variable button
    destroy $w
    focus $oldFocus
    return $button
}




# modified from dialog{}
proc input {w title prompt value} {
    global  input_result input_var
    set input_var $value

    toplevel $w -class Dialog
    wm title $w $title
    wm iconname $w Input
    wm geometry $w +50+360
    label $w.prompt -text $prompt
    entry $w.entry  -width 20 -relief sunken -textvariable input_var
    pack  $w.prompt -side top -fill both -padx 2m
    pack  $w.entry            -fill both -padx 2m -pady 2m

    set oldFocus [focus]
    grab set $w
    focus $w.entry

    bind $w.entry <Return> {set input_result $input_var}

    tkwait variable input_result
    destroy $w
    focus $oldFocus
    return $input_result
}


# inspired by xnotify in Unix
# modified from dialog in Tcl/Tk book
proc xnotify {w title filename default args} {
    global button

    toplevel $w -class Dialog
    wm title $w $title
    wm iconname $w Dialog
    wm geometry $w +220+70
    frame $w.top -relief raised -bd 1
    pack  $w.top -side top -fill both
    frame $w.bot -relief raised -bd 1
    pack  $w.bot -side bottom -fill both
    
    text $w.top.text -yscrollcommand "$w.top.scroll set"
    scrollbar $w.top.scroll -command "$w.top.text yview"
    pack $w.top.scroll -side right -fill y
    pack $w.top.text   -side left -expand 1 -fill both -padx 3m -pady 3m
    loadFile $w.top.text $filename
    

    set i 0
    foreach but $args {
	button $w.bot.button$i -text $but -command "set button $i"
	if {$i == $default} {
	    frame $w.bot.default -relief sunken -bd 1
	    raise $w.bot.button$i
	    pack $w.bot.default -side left -expand 1 -padx 3m -pady 2m
	    pack $w.bot.button$i -in $w.bot.default \
		    -side left -padx 2m -pady 2m -ipadx 2m -ipady 1m
	} else {
	    pack $w.bot.button$i -side left -expand 1 \
		    -side left -padx 3m -pady 3m -ipadx 2m -ipady 1m
	}
	incr i
    }

    if {$default >= 0} {
	bind $w <Return> "$w.bot.button$default flash; set button $default"
    }
    set oldFocus [focus]
    grab set $w
    focus $w

    tkwait variable button
    destroy $w
    focus $oldFocus
    return $button
}


proc loadFile {text_widget file} {
    $text_widget delete 1.0 end
    set f [open $file]
    while {![eof $f]} {
	$text_widget insert end [read $f 1000]
    }
    close $f
}
