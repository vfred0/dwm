static const unsigned int snap = 32;
static const unsigned int borderpx = 0;
static const unsigned int gappih = 10;
static const unsigned int gappiv = 10;
static const unsigned int gappoh = 10;
static const unsigned int gappov = 10;
static int smartgaps = 0;
static const int showbar = 1;
static const int topbar = 1;
static const int colorfultag = 1;
static const char *fonts[] = {"Iosevka:style:bold:size=10", "JetBrainsMono Nerd Font:style:bold:size=8"};
static const unsigned int tag_underline_padding = 5;
static const unsigned int tag_underline_height = 2;
static const unsigned int tag_underline_above = 0;
static const int is_tag_underline_for_active = 0;
static const int bar_pdading_horizontal = 5;
static const int bar_pdading_vertical = 11;

#include "themes/catppuccin.h"
static const char *colors[][3] = {
    /*                     fg       bg      border */
    [SchemeNorm] = {gray3, black, gray2},
    [SchemeSel] = {gray4, blue, blue},
    [SchemeTitle] = {white, black, black},
    [TabSel] = {blue, gray2, black},
    [TabNorm] = {gray3, black, black},
    [SchemeTag] = {gray3, black, black},
    [SchemeTag1] = {blue, black, black},
    [SchemeTag2] = {red, black, black},
    [SchemeTag3] = {orange, black, black},
    [SchemeTag4] = {green, black, black},
    [SchemeTag5] = {pink, black, black},
    [SchemeLayout] = {green, black, black},
    [SchemeBtnPrev] = {green, black, black},
    [SchemeBtnNext] = {yellow, black, black},
    [SchemeBtnClose] = {red, black, black},
};

static const int tagschemes[] = {
    SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5};

// typedef struct {
// 	const char *name;
// 	const void *cmd;
// } Sp;
// const char *spcmd1[] = {"alacritty"};
// const char *spcmd2[] = {"pcmanfm"};
// static Sp scratchpads[] = {
// 	/* name         cmd  */
// 	{"alacritty",      spcmd1},
// 	{"pcmanfm",     spcmd2},
// };

/* tagging */
static const char *tags[] = {"I", "II", "III", "IV", "V"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Brave-browser", NULL, NULL, 1 << 0, 0, -1},
};

#include "layouts_gaps.c"
/* layout(s) */
static const float mfact = 0.5;      /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;        /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    {"TTT", bstack},
    {"><>", NULL},
};

#include "keymaps.c"