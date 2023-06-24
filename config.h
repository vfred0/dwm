/* See LICENSE file for copyright and license details. */

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = {"Iosevka:style:bold:size=10", "JetBrainsMono Nerd Font:style:bold:size=8" };

#include "themes/catppuccin.h"
static const char *colors[][3]      = {
    /*                     fg       bg      border */
    [SchemeNorm]       = { gray3,   black,  gray2 },
    [SchemeSel]        = { gray4,   blue,   blue  },
    [SchemeTitle]      = { white,   black,  black }, 
    [TabSel]           = { blue,    gray2,  black },
    [TabNorm]          = { gray3,   black,  black },
    [SchemeTag]        = { gray3,   black,  black },
    [SchemeTag1]       = { blue,    black,  black },
    [SchemeTag2]       = { red,     black,  black },
    [SchemeTag3]       = { orange,  black,  black },
    [SchemeTag4]       = { green,   black,  black },
    [SchemeTag5]       = { pink,    black,  black },
    [SchemeLayout]     = { green,   black,  black },
    [SchemeBtnPrev]    = { green,   black,  black },
    [SchemeBtnNext]    = { yellow,  black,  black },
    [SchemeBtnClose]   = { red,     black,  black },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-c", "spterm", "-g", "160x34", NULL };
const char *spcmd2[] = {"st", "-c", "spmusic", "-g", "160x34", "-e", "cmus", NULL };
const char *spcmd3[] = {"st", "-c", "spcalc", "-g", "56x8", "-f", "monospace:size=12", "-e", "bc", "-lq", NULL};
static Sp scratchpads[] = {
	/* name         cmd  */
	{"spterm",      spcmd1},
	{"spmusic",     spcmd2},
    {"spcalc",      spcmd3},
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance   title           tags mask  isfloating  monitor */
	{ "St",	           NULL,      NULL,           1 << 0,    0,          -1 },
	{ "firefox",       NULL,      NULL,           1 << 1,    0,          -1 },
	{ "Soffice",       NULL,      NULL,           1 << 2,    0,          -1 },
	{ NULL,	           NULL,      "LibreOffice",  1 << 2,    0,          -1 },
	{ "Gimp",          NULL,      NULL,           1 << 2,    0,          -1 },
	{ "Inkscape",      NULL,      NULL,           1 << 2,    0,          -1 },
	{ "mpv",           NULL,      NULL,           0,         1,          -1 },
	{ "Nsxiv",         NULL,      NULL,           0,         1,          -1 },
	{ "st-floating",   NULL,      NULL,           0,         1,          -1 },
	{ "spterm",        NULL,      NULL,           SPTAG(0),  1,          -1 },
	{ "spmusic",       NULL,      NULL,           SPTAG(1),  1,          -1 },
	{ "spcalc",        NULL,      NULL,           SPTAG(2),  1,          -1 },
	{ NULL,            NULL,      "Event Tester", 0,         0,          -1 }, /* xev */
	{ "Tk",            NULL,      NULL,           0,         1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "TTT",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu-run-i", NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	{ MODKEY,                           XK_c,       spawn,          SHCMD("rofi -show drun") },
    { MODKEY,                           XK_Return,  spawn,          SHCMD("alacritty")},
    {MODKEY | ControlMask,              XK_0,       spawn,          SHCMD("volume mute")},
    {MODKEY | ControlMask,              XK_minus,   spawn,          SHCMD("volume down")},
    {MODKEY | ControlMask,              XK_plus,    spawn,          SHCMD("volume up")},
    {NULL,                              XK_Print,   spawn,          SHCMD("flameshot gui")},
	{ MODKEY|ShiftMask,                 XK_m,       spawn,          SHCMD("microphone toggle")},

    // toggle stuff
    { MODKEY,                           XK_b,       togglebar,      {0} },
    { MODKEY|ControlMask,               XK_t,       togglegaps,     {0} },
    { MODKEY|ShiftMask,                 XK_space,   togglefloating, {0} },
    { MODKEY,                           XK_f,       togglefullscr,  {0} },

    { MODKEY|ControlMask,               XK_w,       tabmode,        { -1 } },
    { MODKEY,                           XK_j,       focusstack,     {.i = +1 } },
    { MODKEY,                           XK_k,       focusstack,     {.i = -1 } },
    { MODKEY,                           XK_i,       incnmaster,     {.i = +1 } },
    { MODKEY,                           XK_d,       incnmaster,     {.i = -1 } },


    // { MODKEY,                           XK_h,       setmfact,       {.f = -0.05} },
    // { MODKEY,                           XK_l,       setmfact,       {.f = +0.05} },
    // { MODKEY|ShiftMask,                 XK_h,       setcfact,       {.f = +0.25} },
    // { MODKEY|ShiftMask,                 XK_l,       setcfact,       {.f = -0.25} },
    // { MODKEY|ShiftMask,                 XK_o,       setcfact,       {.f =  0.00} },


    { MODKEY|ShiftMask,                 XK_j,       movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,                 XK_k,       movestack,      {.i = -1 } },
    { MODKEY|ShiftMask,                 XK_Return,  zoom,           {0} },
    { MODKEY,                           XK_Tab,     view,           {0} },
    { MODKEY,                           XK_space,   setlayout,      {0} },
    { MODKEY|ControlMask,               XK_comma,   cyclelayout,    {.i = -1 } },
    { MODKEY|ControlMask,               XK_period,  cyclelayout,    {.i = +1 } },
    { MODKEY,                           XK_0,       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,                 XK_0,       tag,            {.ui = ~0 } },
    { MODKEY,                           XK_comma,   focusmon,       {.i = -1 } },
    { MODKEY,                           XK_period,  focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,                 XK_comma,   tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,                 XK_period,  tagmon,         {.i = +1 } },


    { MODKEY,                           XK_q,       killclient,     {0} },

    { MODKEY|ShiftMask,                 XK_r,       restart,        {1} },
	{ MODKEY|ShiftMask,             	XK_q,    	quit,           {0} },
    { MODKEY,                           XK_e,       hidewin,        {0} },
    { MODKEY|ShiftMask,                 XK_e,       restorewin,     {0} },

    TAGKEYS(                            XK_1,                       0)
    TAGKEYS(                            XK_2,                       1)
    TAGKEYS(                            XK_3,                       2)
    TAGKEYS(                            XK_4,                       3)
    TAGKEYS(                            XK_5,                       4)    
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = dmenucmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
	{ "font",               STRING,  &font },
	{ "color0",		STRING,  &normbgcolor },
	{ "color8",		STRING,  &normbordercolor },
	{ "foreground",		STRING,  &normfgcolor },
	{ "color8",             STRING,  &selbgcolor },
	{ "color7",		STRING,  &selbordercolor },
	{ "foreground",         STRING,  &selfgcolor },
};
