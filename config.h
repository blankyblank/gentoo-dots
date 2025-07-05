/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int enablegaps                = 0;  /* 1 means gaps are enabled */
static const int smartgaps                 = 1;  /* 1 means no outer gap when there is only one window */
static const int monoclegaps               = 0;  /* 1 means outer gaps in monocle layout */
static const unsigned int borderpx         = 2;  /* border pixel of windows */
static const unsigned int gappih           = 2; /* horiz inner gap between windows */
static const unsigned int gappiv           = 2; /* vert inner gap between windows */
static const unsigned int gappoh           = 2; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov           = 2; /* vert outer gap between windows and screen edge */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const char *fonts[]                 = {"JetBrainsMono Nerd Font:size=15"};
static int enableautoswallow               = 1; /* enables autoswallowing newly spawned clients */
static float swallowborder                 = 1.0f; /* add this multiplied by borderpx to border when a client is swallowed */
static const float rootcolor[]             = COLOR(0x282C34ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1f, 0.1f, 0.1f, 1.0f}; /* You can also use glsl colors */
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0xC678DDff, 0x282C34ff, 0x282C34F4 },
	[SchemeSel]  = { 0x282C34ff, 0xC678DDff, 0xC678DDff },
	[SchemeUrg]  = { 0,          0,          0xE06C75ff },
};

/* tagging - TAGCOUNT must be no greater than 31 */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = WLR_ERROR;

/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {
	/* app_id             title   tags mask  isfloating   isterm noswallow monitor scratchkey*/
	/* examples: */
	{ "Gimp_EXAMPLE",     NULL,       0,         1,       0,       0,   -1,      0  },
	{ NULL,               "footpg",   0,         1,       1,       0,   -1,      0  },
	{ "footpg",           NULL,       0,         1,       1,       0,   -1,      0  },
	{ "firefox_EXAMPLE",  NULL,       1 << 8,    0,       0,       0,   -1,      0  },
	{ "foot",             NULL,       0,         0,       1,       1,   -1,      0  },
	{ NULL,               "alsaterm", 0,         1,       0,       0,   -1,     'a' },
	{ NULL,               "iwterm",   0,         1,       0,       0,   -1,     'i' },
	{ NULL,               "topterm",  0,         1,       0,       0,   -1,     'b' },
	{ "vesktop",          NULL,       0,         1,       0,       0,   -1,     'v' },
	{ NULL,               "Fractal",  0,         1,       0,       0,   -1,     'e' },
};

/* layout(s) */
static const Layout layouts[] = {
//	{ "><>",      NULL },
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "[M]",      monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	.options = "caps:swapescape",
};

static const int repeat_rate = 55;
static const int repeat_delay = 300;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 0;
static const int drag_lock = 0;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER;
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.2;
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

#define MODKEY WLR_MODIFIER_LOGO
#define MODKEY1 WLR_MODIFIER_ALT
#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_ALT,   KEY,            toggletag,       {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]         = { "foot", NULL };
static const char *menucmd2[]        = { "tofi-dwl", NULL };
static const char *menucmd[]         = { "fuzzel", NULL };
static const char *statcmd[]         = { "foot", "-e", "top", NULL };
static const char *term2cmd[]        = { "kitty", NULL };
static const char *ffplaycmd[]       = { "foot", "-e", "fzffplay", NULL };
static const char *yazvidcmd[]       = { "foot", "-e", "yazi", "/home/blank/.local/media/video-drive1/", NULL };
static const char *clipcmd[]         = { "clipmenu", NULL };
static const char *passcmd[]         = { "passmenu", NULL };
static const char *qtbrowsercmd[]    = { "qutebrowser", NULL };
static const char *browsercmd[]      = { "zen-bubblejail", NULL };
static const char *mullvadcmd[]      = { "bubblejail", "run", "mullvad", NULL };
static const char *ytbrowsercmd[]    = { "zen-youtube-flatpak", NULL };
static const char *bravecmd[]        = { "brave-flatpak", NULL }; 
static const char *filecmd[]         = { "foot", "-e", "yazi", NULL };
static const char *lockcmd[]         = { "basedlock", NULL };
static const char *volupcmd[]        = { "amixer","-c","1","sset", "Master", "5%+", NULL };
static const char *voldowncmd[]      = { "amixer","-c","1","sset", "Master", "5%-", NULL };
static const char *briteupcmd[]      = { "backlight.sh", "-u", NULL };
static const char *britedowncmd[]    = { "backlight.sh", "-d", NULL };
static const char *scrnscmd[]        = { "screenshot", "-s", NULL };
static const char *fscrncmd[]        = { "screenshot", "-f", NULL };
static const char *rebootcmd[]       = { "loginctl", "reboot", NULL };
static const char *logoutcmd[]       = { "logout.sh", NULL };

/* named scratchpads - First arg only serves to match against key in rules*/
static const char *scratchpadcmd1[] = { "a", "foot", "--title", "alsaterm", "-W", "120x34", "-e", "alsamixer", NULL };
static const char *scratchpadcmd2[] = { "i", "foot", "--title", "iwterm", "-W", "120x34", "-e", "iwctl", NULL };
static const char *scratchpadcmd3[] = { "b", "foot", "--title", "topterm", "-W", "130x38", "-e", "btop", NULL };
static const char *scratchpadcmd4[] = { "v", "discord-flatpak", NULL };
static const char *scratchpadcmd5[] = { "e", "flatpak", "run", "org.gnome.Fractal", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ MODKEY,                       XKB_KEY_d,           spawn,            {.v = menucmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_D,           spawn,            {.v = menucmd2} },
	{ MODKEY,                       XKB_KEY_Return,      spawn,            {.v = termcmd } },
	{ MODKEY,                       XKB_KEY_s,           spawn,            {.v = term2cmd } },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_U,           spawn,            {.v = ffplaycmd } },
	{ MODKEY,                       XKB_KEY_u,           spawn,            {.v = yazvidcmd} },
	{ MODKEY,                       XKB_KEY_p,           spawn,            {.v = clipcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_P,           spawn,            {.v = passcmd} },
	{ MODKEY,                       XKB_KEY_w,           spawn,            {.v = qtbrowsercmd } },
	{ MODKEY,                       XKB_KEY_z,           spawn,            {.v = browsercmd } },
	{ MODKEY,                       XKB_KEY_c,           spawn,            {.v = mullvadcmd} },
	{ MODKEY,                       XKB_KEY_y,           spawn,            {.v = ytbrowsercmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_W,           spawn,            {.v = bravecmd } },
	{ MODKEY,                       XKB_KEY_n,           spawn,            {.v = filecmd } },
  { 0,                            XKB_KEY_XF86Display, spawn,            {.v = lockcmd } },
	{ 0,                            XKB_KEY_Print,       spawn,            {.v = scrnscmd} },
	{ MODKEY,                       XKB_KEY_Print,       spawn,            {.v = fscrncmd} },
	{ 0,         XKB_KEY_XF86AudioRaiseVolume,           spawn,            {.v = volupcmd } },
	{ 0,         XKB_KEY_XF86AudioLowerVolume,           spawn,            {.v = voldowncmd } },
	{ 0,          XKB_KEY_XF86MonBrightnessUp,           spawn,            {.v = briteupcmd} },
	{ 0,        XKB_KEY_XF86MonBrightnessDown,           spawn,            {.v = britedowncmd} },
	{ MODKEY,                       XKB_KEY_b,           togglebar,        {0} },
	{ MODKEY,                       XKB_KEY_a,           togglescratch,    {.v = scratchpadcmd1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_N,           togglescratch,    {.v = scratchpadcmd2 } },
	{ MODKEY,                       XKB_KEY_r,           togglescratch,    {.v = scratchpadcmd3 } },
	{ MODKEY,                       XKB_KEY_v,           togglescratch,    {.v = scratchpadcmd4 } },
	{ MODKEY,                       XKB_KEY_e,           togglescratch,    {.v = scratchpadcmd5 } },
	{ MODKEY,                       XKB_KEY_j,           focusstack,       {.i = +1} },
	{ MODKEY,                       XKB_KEY_k,           focusstack,       {.i = -1} },
	{ MODKEY,                       XKB_KEY_i,           incnmaster,       {.i = +1} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_I,           incnmaster,       {.i = -1} },
	{ MODKEY,                       XKB_KEY_h,           setmfact,         {.f = -0.05f} },
	{ MODKEY,                       XKB_KEY_l,           setmfact,         {.f = +0.05f} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_l,           togglegaps,       {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_Return,      zoom,             {0} },
	{ MODKEY,                       XKB_KEY_Tab,         view,             {0} },
	{ MODKEY,                       XKB_KEY_q,           killclient,       {0} },
	{ MODKEY,                       XKB_KEY_t,           setlayout,        {.v = &layouts[0]} },
	{ MODKEY,                       XKB_KEY_m,           setlayout,        {.v = &layouts[1]} },
	//{ MODKEY,                       XKB_KEY_f,           setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XKB_KEY_space,       setlayout,        {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_space,       togglefloating,   {0} },
	{ MODKEY,                       XKB_KEY_f,           togglefullscreen, {0} },
	{ MODKEY,                       XKB_KEY_comma,       toggleswallow,    {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_S,           toggleautoswallow,{0} },
	{ MODKEY,                       XKB_KEY_0,           view,             {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_parenright,  tag,              {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_less,        tagmon,           {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_greater,     tagmon,           {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1,    XKB_KEY_exclam,                        0),
	TAGKEYS(          XKB_KEY_2,    XKB_KEY_at,                            1),
	TAGKEYS(          XKB_KEY_3,    XKB_KEY_numbersign,                    2),
	TAGKEYS(          XKB_KEY_4,    XKB_KEY_dollar,                        3),
	TAGKEYS(          XKB_KEY_5,    XKB_KEY_percent,                       4),
	TAGKEYS(          XKB_KEY_6,    XKB_KEY_asciicircum,                   5),
	TAGKEYS(          XKB_KEY_7,    XKB_KEY_ampersand,                     6),
	TAGKEYS(          XKB_KEY_8,    XKB_KEY_asterisk,                      7),
	TAGKEYS(          XKB_KEY_9,    XKB_KEY_parenleft,                     8),
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_C,          quit,              {0} },
  { MODKEY1|WLR_MODIFIER_CTRL,    XKB_KEY_Delete,     spawn,             {.v = rebootcmd} },
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit,   {0} },

#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = statcmd} },
	{ ClkStatus,   0,      BTN_RIGHT,  spawn,          {.v = logoutcmd} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};
