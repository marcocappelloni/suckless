/* See LICENSE file for copyright and license details. */

/* includes */
#include "movestack.c"
#include "themes/nimona.h"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=10" };
static const char dmenufont[]       = "FiraCode Nerd Font:size=10"; //"monospace:size=10";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { norm_fg, norm_bg, norm_bor },
	[SchemeSel]  = { sel_fg, sel_bg,  sel_bor  },
	[SchemeStatus]  = { stat_fg, stat_bg,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { tag_sel_fg, tag_sel_bg,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { tag_norm_fg, tag_norm_bg,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { info_sel_fg, info_sel_bg,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { info_norm_fg, info_norm_bg,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",         NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",      NULL,       NULL,       1 << 8,       0,           -1 },
	{ "pavucontrol",  NULL,       NULL,       0,            1,           -1 },
	{ "pomatez",      NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[]",      monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static char linenumberdmenu[] = "15";
/*static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };*/
static const char *dmenucmd[]     = { "dmenu_run", "-i", "-m", dmenumon, "-fn", dmenufont, "-l", linenumberdmenu, NULL };
//static const char *termcmd[]      = { "kitty", NULL };
static const char *termcmd[]      = { "kitty", NULL };
static const char *termcmd2[]      = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd2 } },
	//{ MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
	//{ MODKEY,                       XK_F1,     spawn,          {.v = browsercmd } },
	//{ MODKEY|ShiftMask,             XK_0,      spawn,          {.v = powermenucmd } },
	//{ MODKEY,                       XK_p,      spawn,          {.v = passmenucmd } },
	//{ MODKEY,                       XK_c,      spawn,          {.v = simplecalcmd } },
	{ MODKEY,                       XK_F7,     togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	//{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	//{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	//{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	//{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  //{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	/*{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },*/
	{ MODKEY,                       XK_Left,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Right, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask|ControlMask, XK_e,      quit,           {0} },
	//{ 0,				XF86XK_AudioLowerVolume,spawn,{.v = decvol} },	
	//{ 0,				XF86XK_AudioRaiseVolume,spawn,{.v = incvol} },
	//{ 0,				XF86XK_AudioMute,spawn,{.v = mutevol} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
