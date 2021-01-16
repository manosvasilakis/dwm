# dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements
------------
In order to build dwm you need the Xlib header files.


## Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


## Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

## Features Added
1. FullScreen any program with Super+f
2. Custom bar height
3. Show number of windows in every tag
4. Autostart required app from within dwm
5. Window Gaps in all layouts
6. Extra Layouts:
	1. Fibonacci Layout
	2. Bottonstack Layout
7. Application Scratchpads (like i3wm)
8. Make a window sticky (follows u arround) Super+s
9. Swallow useless windows
10. Xresources color settings

TODO:
1. Statusbar Transparency
2. Statusbar Padding
3. Statusbar Click Support
4. Systray Support
