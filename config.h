/* See LICENSE file for copyright and license details. */
/*
 * TODO 1: Make a man page for all these when done.
 * TODO 2: Add all settings in xresources.
 * Total Lines of Code: 3829 total. (with comments, man pages, readme, etc...)
 * ... still could be less...
 */

/* appearance */
static unsigned int borderpx  = 1;  /* border pixel of windows */
static unsigned int snap      = 32; /* snap pixel              */
static int showbar            = 1;  /* 0 means no bar          */
static int topbar             = 1;  /* 0 means bottom bar      */
static const int gappx              = 15; /* gaps between windows */
static const int swallowfloating    = 0;  /* 1 = swallow floating windows by default */
static const int user_bh            = 0;  /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "FantasqueSansMono Nerd Font Mono:size=10", "Noto Color Emoji:pixelsize=10:antialias=true:autohint=true"};
static const char dmenufont[]       =   "FantasqueSansMono Nerd Font Mono:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* Cool Autostart */
static const char *const autostart[] = {
	"wallp",     NULL,    /* load a random wallp. */
	"remaps",    NULL,    /* key remaps           */
	"dunst",     NULL,    /* notifications server */
	"unclutter", NULL,    /* Hide mouse when idle */
	"dwmblocks", NULL,    /* dwmblocks statusbar  */
	"xcompmgr",  NULL,    /* Transparency Effects */
	NULL                  /* terminate            */
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm",   "-g", "120x34", "-e", "ranger", NULL };
const char *spcmd3[] = {"st", "-n", "spcalc", "-g", "50x20",  "-e", "bc", "-lq", NULL };
const char *spcmd4[] = {"keepassxc", NULL };
const char *spcmd5[] = {"st", "-n", "spvol",  "-g", "80x20",  "-e", "pulsemixer", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"spcalc",      spcmd3},
	{"keepassxc",   spcmd4},
	{"spvol",       spcmd5},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
/* window rules */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance      title           tags mask   isfloating  isterminal  noswallow  monitor */
	/* { "Brave",   NULL,	   NULL,	   1 << 8,     0,	   0,          -1,        -1 }, */
	{ "Gimp",    NULL,	   NULL,	   0,	       1,	   0,           0,        -1 },
	{ "St",      NULL,         NULL,           0,          0,          1,           0,        -1 },
	{ NULL,      "spterm",	   NULL,	   SPTAG(0),   1,	   1,           0,        -1 },
	{ NULL,	     "spfm",	   NULL,	   SPTAG(1),   1,	   1,           0,        -1 },
	{ NULL,      "spcalc",     NULL,       	   SPTAG(2),   1,          1,           1,        -1 },
	{ NULL,      "keepassxc",  NULL,	   SPTAG(3),   1,	   0,           1,        -1 },
	{ NULL,      "spvol",      NULL,	   SPTAG(4),   1,	   1,           1,        -1 },
	{ NULL,      NULL,         "Event Tester", 0,          0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
#include "fibonacci.c"
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* * Xresources preferences to load at startup * */
ResourcePref resources[] = {
	{ "normbgcolor",        STRING,  &normbgcolor },
	{ "normbordercolor",    STRING,  &normbordercolor },
	{ "normfgcolor",        STRING,  &normfgcolor },
	{ "selbgcolor",         STRING,  &selbgcolor },
	{ "selbordercolor",     STRING,  &selbordercolor },
	{ "selfgcolor",         STRING,  &selfgcolor },
	{ "borderpx",          	INTEGER, &borderpx },
	{ "snap",          	INTEGER, &snap },
	{ "showbar",          	INTEGER, &showbar },
	{ "topbar",          	INTEGER, &topbar },
	{ "nmaster",          	INTEGER, &nmaster },
	{ "resizehints",       	INTEGER, &resizehints },
	{ "mfact",       	FLOAT,   &mfact },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BTN */
static char *statuscmds[] = { "notify-send \"Mouse $BTN\"" };
static char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

/* Add somewhere in your constants definition section.     */
#include <X11/XF86keysym.h> /* used for the Thinkpad keys. */
static Key keys[] = {
	TAGKEYS( XK_1, 0 )
	TAGKEYS( XK_2, 1 )
	TAGKEYS( XK_3, 2 )
	TAGKEYS( XK_4, 3 )
	TAGKEYS( XK_5, 4 )
	TAGKEYS( XK_6, 5 )
	TAGKEYS( XK_7, 6 )
	TAGKEYS( XK_8, 7 )
	TAGKEYS( XK_9, 8 )

	/* modifier           key        function        argument */
	{ MODKEY,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             XK_Return, spawn,          {.v = termcmd  } },
	{ MODKEY|ShiftMask,   XK_Return, togglescratch,  {.ui = 0 } },
	{ MODKEY,             XK_a,      spawn,          SHCMD("$TERMINAL -e abook -C \"$XDG_CONFIG_HOME\"/abook/abookrc --datafile \"$XDG_DATA_HOME\"/abook/addressbook") },
	{ MODKEY,             XK_b,      spawn,          SHCMD("dmenubookmarks") },
	{ MODKEY|ShiftMask,   XK_b,      togglebar,      {0} },
	{ MODKEY|ControlMask, XK_b,      spawn,          SHCMD("killall dwmblocks && setsid dwmblocks") },
	{ MODKEY,             XK_c,      togglescratch,  {.ui = 2 } },
	{ MODKEY,             XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,             XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,             XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,   XK_q,      killclient,     {0} },
	{ MODKEY,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,   XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,   XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,             XK_y,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,   XK_y,      setlayout,      {.v = &layouts[4]} },
   	{ MODKEY,             XK_u,      setlayout,      {.v = &layouts[5]} },
 	{ MODKEY|ShiftMask,   XK_u,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,             XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,   XK_space,  togglefloating, {0} },
	{ MODKEY,             XK_m,      spawn,          SHCMD("pulsemixer --toggle-mute && pkill -RTMIN+4 dwmblocks") },
	{ MODKEY,             XK_s,      togglesticky,   {0} },
	{ MODKEY,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,             XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,   XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,             XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,             XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,             XK_e,      spawn,          SHCMD("$TERMINAL -e neomutt ; pkill -RTMIN+9 dwmblocks") },
	{ MODKEY|ShiftMask,   XK_e,      spawn,          SHCMD("$TERMINAL -e nmtui") },
	{ MODKEY,             XK_w,      spawn,          SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,   XK_w,      spawn,          SHCMD("$BROWSER --incognito") },
	{ MODKEY,             XK_x,      spawn,          SHCMD("dmenusxivdirpick") },
	{ MODKEY|ShiftMask,   XK_x,      spawn,          SHCMD("sxiv ~/media/pix/screenshots") },
	{ MODKEY|ControlMask, XK_x,      spawn,          SHCMD("sxiv -r ~/media/pix") },
	{ MODKEY,             XK_v,      togglescratch,  {.ui = 4 } },
	{ MODKEY|ShiftMask,   XK_v,      spawn,          SHCMD("$TERMINAL -e nvim -c VimwikiIndex") },
	{ MODKEY,             XK_minus,  spawn,          SHCMD("pulsemixer --change-volume -15 && pkill -RTMIN+4 dwmblocks") },
	{ MODKEY|ShiftMask,   XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY|ControlMask, XK_minus,  incnmaster,     {.i = -1 } },
	{ MODKEY,             XK_equal,  spawn,          SHCMD("pulsemixer --change-volume +15 && pkill -RTMIN+4 dwmblocks") },
	{ MODKEY|ShiftMask,   XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ControlMask, XK_equal,  incnmaster,     {.i = +1 } },
	{ MODKEY,             XK_g,      setgaps,        {.i = gappx } },
	{ MODKEY|ShiftMask,   XK_g,      setgaps,        {.i = 0 } },
	{ MODKEY,             XK_p,      spawn,          SHCMD("dmenupass") },
	{ MODKEY|ShiftMask,   XK_p,      togglescratch,  {.ui = 3 } },
	{ MODKEY,             XK_r,      togglescratch,  {.ui = 1 } },
	{ 0,                  XK_Print,  spawn,          SHCMD("maim ~/media/pix/screenshots/pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,          XK_Print,  spawn,          SHCMD("maimpick") },
	{ MODKEY,             XK_Print,  spawn,          SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,   XK_Print,  spawn,          SHCMD("dmenurecord kill") },
	{ 0,                  XK_Insert, spawn,          SHCMD("dmenusnippets") },
	{ MODKEY,             XK_F1,     spawn,          SHCMD("displayselect") },
	{ MODKEY,             XK_F2,     spawn,          SHCMD("autosyncmail") },
	{ MODKEY,             XK_F3,     spawn,          SHCMD("dmenumount") },
	{ MODKEY,             XK_F4,     spawn,          SHCMD("dmenuumount") },
	{ MODKEY,	      XK_grave,  spawn,          SHCMD("dmenuunicode") },

	/* Manage Volume */
	{ ALTKEY,	      XK_0,      spawn,          SHCMD("pulsemixer --set-volume-all 100:100 && pkill -RTMIN+4 dwmblocks") },
	{ ALTKEY|ShiftMask,   XK_0,      spawn,          SHCMD("pulsemixer --set-volume-all 0:0 && pkill -RTMIN+4 dwmblocks") },
	{ ALTKEY,	      XK_1,      spawn,          SHCMD("pulsemixer --set-volume-all 10:10 && pkill -RTMIN+4 dwmblocks") },
	{ ALTKEY,	      XK_2,      spawn,          SHCMD("pulsemixer --set-volume-all 20:20 && pkill -RTMIN+4 dwmblocks") },
	{ ALTKEY,	      XK_3,      spawn,          SHCMD("pulsemixer --set-volume-all 30:30 && pkill -RTMIN+4 dwmblocks") },
	{ ALTKEY,	      XK_4,      spawn,          SHCMD("pulsemixer --set-volume-all 40:40 && pkill -RTMIN+4 dwmblocks") },
	{ ALTKEY,	      XK_5,      spawn,          SHCMD("pulsemixer --set-volume-all 50:50 && pkill -RTMIN+4 dwmblocks") },
	{ ALTKEY,	      XK_6,      spawn,          SHCMD("pulsemixer --set-volume-all 60:60 && pkill -RTMIN+4 dwmblocks") },
	{ ALTKEY,	      XK_7,      spawn,          SHCMD("pulsemixer --set-volume-all 70:70 && pkill -RTMIN+4 dwmblocks") },
	{ ALTKEY,	      XK_8,      spawn,          SHCMD("pulsemixer --set-volume-all 80:80 && pkill -RTMIN+4 dwmblocks") },
	{ ALTKEY,	      XK_9,      spawn,          SHCMD("pulsemixer --set-volume-all 90:90 && pkill -RTMIN+4 dwmblocks") },

	{ ALTKEY,             XK_space,  spawn,          SHCMD("kbselect") },
	{ MODKEY,             XK_Escape, quit,           {1} },
	{ MODKEY|ShiftMask,   XK_Escape, spawn,          SHCMD("kill -9 -1") },

	/* Thinkpad Keys */
	{ 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("pulsemixer --change-volume +5 && pkill -RTMIN+4 dwmblocks") },
	{ 0, XF86XK_AudioLowerVolume, spawn, SHCMD("pulsemixer --change-volume -5 && pkill -RTMIN+4 dwmblocks") },
	{ 0, XF86XK_AudioMute,        spawn, SHCMD("pulsemixer --toggle-mute && pkill -RTMIN+4 dwmblocks") },
	{ 0, XF86XK_AudioMicMute,     spawn, SHCMD("$TERMINAL -e pulsemixer ; pkill -RTMIN+4 dwmblocks") },
	{ 0, XF86XK_Launch1,          spawn, SHCMD("sysact") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	/* { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} }, */
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
