/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static int centered = 1;                    /* -c option; centers dmenu on screen */
static int min_width = 500;                    /* minimum width when centered */
static const float menu_height_ratio = 4.0f;  /* This is the ratio used in the original calculation */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"monospace:size=10"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
/* Dracula colors */
//static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
//  [SchemeNorm] = { "#f8f8f2", "#282a36" },
//	[SchemeSel] = { "#f8f8f2", "#6272a4" },
//	[SchemeOut] = { "#000000", "#00ffff" },
//};
/* Catppuccin mocha colors */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
  [SchemeNorm] = { "#cdd6f4", "#1e1e2e" },
	[SchemeSel] = { "#1e1e2e", "#89b4fa" },
	[SchemeOut] = { "#000000", "#89dceb" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

/* Size of the window border */
static unsigned int border_width = 2;
