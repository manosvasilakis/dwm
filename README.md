# dwm - dynamic window manager
------------
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
-------------
1. FullScreen any program with Super+f
2. Custom bar height
3. Show number of windows in every tag
4. Show Indicator for sticky window
5. Autostart required app from within dwm
6. Window Gaps in all layouts
7. Extra Layouts:
	1. Fibonacci Layout
	2. Bottonstack Layout
8. Application Scratchpads (like i3wm)
9. Make a window sticky (follows u arround) Super+s
10. Swallow useless windows
11. Xresources color settings
12. Systray Support
13. fsignals
14. Per tag settings (layout, mwfact, barpos and nmaster)

## Patches Applied
-------------
1. dwm-actualfullscreen-20191112-cb3f58a.diff
2. dwm-alpha-6.1.diff
3. dwm-bar-height-6.2.diff
4. dwm-clientindicatorshidevacant-6.2.diff
5. dwm-cool-autostart-6.2.diff
6. dwm-fsignal-6.2.diff
7. dwm-layoutmenu-6.2.diff
8. dwm-ru_gaps-6.2.diff
9. dwm-ru_bottomstack-6.2.diff
10. dwm-ru_fibonacci-6.2.diff
11. dwm-scratchpads-20200414-728d397b.diff
12. dwm-statuscmd-signal-6.2.diff
13. dwm-sticky-6.1.diff
14. dwm-stickyindicator-6.2.diff
15. dwm-swallow-20201211-61bb8b2.diff
16. dwm-systray-20200914-61bb8b2.diff
17. dwm-xresources-6.2.diff
18. dwm-pertag-20200914-61bb8b2.diff

TODO:
1. Statusbar Transparency
2. Statusbar Padding
	1. Make barpadding to work nicelly with the systray
4. Statusbar Click Support
5. ~~Statusbar Systray Support~~
