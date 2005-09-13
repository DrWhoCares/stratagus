//       _________ __                 __
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/
//  ______________________                           ______________________
//                        T H E   W A R   B E G I N S
//      Stratagus - A free fantasy real time strategy game engine
//
/**@name menus.h - The menu headerfile. */
//
//      (c) Copyright 1999-2005 by Andreas Arens and Jimmy Salmon
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; only version 2 of the License.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//      02111-1307, USA.
//
//      $Id$

#ifndef __MENUS_H__
#define __MENUS_H__

//@{

/*----------------------------------------------------------------------------
--  Includes
----------------------------------------------------------------------------*/

#include "ui.h"
#include "util.h"
#include "script.h"

/*----------------------------------------------------------------------------
--  Defines/Declarations
----------------------------------------------------------------------------*/

#define MI_FLAGS_NONE       0  /// no flags
#define MI_FLAGS_ACTIVE     1  /// cursor on item
#define MI_FLAGS_CLICKED    2  /// mouse button pressed down on item
#define MI_FLAGS_SELECTED   4  /// selected item
#define MI_FLAGS_DISABLED   8  /// grayed out item
#define MI_FLAGS_INVISIBLE 16  /// invisible item

/**
**  Menu button referencing
**  Each button is 300 x 144  => 50 buttons (53 for Expansion GFX)
**  For multi-version buttons: button - 1 == disabled, + 1 == depressed
**  For gems: -1 == disabled, +1 == depressed, +2 checked,
**  +3 checked+depressed
*/
typedef int MenuButtonId;

/// @todo FILL IN THIS TABLE!!!!

#define MBUTTON_UP_ARROW    29
#define MBUTTON_DOWN_ARROW  32
#define MBUTTON_LEFT_ARROW  35
#define MBUTTON_RIGHT_ARROW 38
#define MBUTTON_S_KNOB      40
#define MBUTTON_S_VCONT     42
#define MBUTTON_S_HCONT     44
#define MBUTTON_PULLDOWN    46
#define MBUTTON_VTHIN       48

#define MBUTTON_SC_GEM_ROUND                 7
#define MBUTTON_SC_GEM_SQUARE               12
#define MBUTTON_SC_UP_ARROW                 17
#define MBUTTON_SC_DOWN_ARROW               20
#define MBUTTON_SC_LEFT_ARROW               23
#define MBUTTON_SC_RIGHT_ARROW              26
#define MBUTTON_SC_S_KNOB                   28
#define MBUTTON_SC_S_VCONT                  30
#define MBUTTON_SC_S_HCONT                  33
#define MBUTTON_SC_PULLDOWN_DOWN_ARROW      50
#define MBUTTON_SC_PULLDOWN_DISABLED        54
#define MBUTTON_SC_PULLDOWN                 57
#define MBUTTON_SC_PULLDOWN_TOP             60
#define MBUTTON_SC_PULLDOWN_MIDDLE          63
#define MBUTTON_SC_PULLDOWN_BOTTOM          66
#define MBUTTON_SC_PULLDOWN_BOTTOM_SELECTED 69
#define MBUTTON_SC_PULLDOWN_TOP_SELECTED    72
#define MBUTTON_SC_INPUT                    81
#define MBUTTON_SC_BUTTON_LEFT              107
#define MBUTTON_SC_BUTTON                   116
#define MBUTTON_SC_BUTTON_RIGHT             125

	/// Offsets into NetMultiSetupMenuItems
#define SERVER_PLAYER_STATE 5
#define SERVER_PLAYER_READY 32
#define SERVER_PLAYER_LAG   46
#define SERVER_PLAYER_TEXT  60

	/// Offsets into NetMultiClientMenuItems
#define CLIENT_PLAYER_STATE  5
#define CLIENT_RACE         21
#define CLIENT_RESOURCE     23
#define CLIENT_UNITS        25
#define CLIENT_FOG_OF_WAR   27
#define CLIENT_TILESET      29
#define CLIENT_GAMETYPE     31
#define CLIENT_PLAYER_READY 32
#define CLIENT_PLAYER_TEXT  46

// For the game speed slider in the speed settings screen.
#define MIN_GAME_SPEED 50
#define MAX_GAME_SPEED 250

struct _button_style_;
struct _map_info_;
struct _world_map_;
class Graphic;
struct _menuitem_;

/*----------------------------------------------------------------------------
--  Menus
----------------------------------------------------------------------------*/

typedef void (*MenuitemTextActionType)(struct _menuitem_*);
typedef void (*MenuitemButtonHandlerType)(void);
typedef void (*MenuitemPulldownActionType)(struct _menuitem_*, int);
typedef void (*MenuitemListboxActionType)(struct _menuitem_*, int);
typedef void* (*MenuitemListboxRetrieveType)(struct _menuitem_*, int);
typedef void (*MenuitemListboxHandlerType)(void);
typedef void (*MenuitemVSliderActionType)(struct _menuitem_*);
typedef void (*MenuitemVSliderHandlerType)(void);
typedef void (*MenuitemHSliderActionType)(struct _menuitem_*);
typedef void (*MenuitemHSliderHandlerType)(void);
typedef void (*MenuitemDrawfuncDrawType)(struct _menuitem_*);
typedef void (*MenuitemInputActionType)(struct _menuitem_*, int);
typedef void (*MenuitemCheckboxActionType)(struct _menuitem_*);

/**
**  Menuitem definition.
**  @todo docu.
*/
typedef struct _menuitem_text_ {
	StringDesc* text;
	TextAlignment Align;
	char* normalcolor;
	char* reversecolor;
	MenuitemTextActionType action;
} MenuitemText;
typedef struct _menuitem_button_ {
	char* Text;
	struct _button_style_* Style;
	MenuitemButtonHandlerType Handler;
	unsigned HotKey;
} MenuitemButton;
typedef struct _menuitem_pulldown_ {
	char** options;
	int xsize;
	int ysize;
	MenuButtonId button;
	MenuitemPulldownActionType action;
	int noptions;
	int defopt;
	int curopt;
	int cursel;  /* used in popup state */
} MenuitemPulldown;
typedef struct _menuitem_listbox_ {
	void* options;
	int xsize;
	int ysize;
	MenuButtonId button;
	MenuitemListboxActionType action;
	int noptions;
	int defopt;
	int curopt;
	int cursel;  /* used in mouse-over state */
	int nlines;
	int startline;
	int dohandler;
	MenuitemListboxRetrieveType retrieveopt;
	MenuitemListboxHandlerType handler;  /* for return key */
} MenuitemListbox;
typedef struct _menuitem_vslider_ {
	unsigned cflags;
	int xsize;  /// x-size of slider, not including buttons
	int ysize;  /// y-size of slider, not including buttons
	MenuitemVSliderActionType action;
	int defper;
	int percent;  /// percent of the way to bottom (0 to 100)
	int cursel;   /// used in mouse-over state
	int style;
	MenuitemVSliderHandlerType handler; /// for return key
} MenuitemVslider;
typedef struct _menuitem_hslider_ {
	unsigned cflags;
	int xsize;  /// x-size of slider, not including buttons
	int ysize;  /// y-size of slider, not including buttons
	MenuitemHSliderActionType action;
	int defper;
	int percent;  /// percent of the way to right (0 to 100)
	int curper;   /// used in mouse-move state
	int cursel;   /// used in mouse-over state
	int style;
	MenuitemHSliderHandlerType handler; /// for return key
} MenuitemHslider;
typedef struct _menuitem_drawfunc_ {
	MenuitemDrawfuncDrawType draw;
} MenuitemDrawfunc;
typedef struct _menuitem_input_ {
	char *buffer;
	unsigned int iflags;
	int xsize;
	int ysize;
	MenuButtonId button;
	MenuitemInputActionType action;  /// for key
	int nch;
	int maxch;
	char* normalcolor;
	char* reversecolor;
} MenuitemInput;
typedef struct _menuitem_checkbox_ {
	char* Text;
	unsigned int Checked : 1;
	struct _checkbox_style_* Style;
	MenuitemCheckboxActionType Action;
} MenuitemCheckbox;

struct _menu_;
typedef enum {
	MiTypeText, MiTypeButton, MiTypePulldown, MiTypeListbox,
	MiTypeVslider, MiTypeHslider, MiTypeDrawfunc, MiTypeInput,
	MiTypeCheckbox
} MiTypeType;

typedef struct _menuitem_ {
	MiTypeType MiType;
	int XOfs;
	int YOfs;
	unsigned Flags;
	unsigned char *Id;
	int Font;
	unsigned int LuaHandle;
	struct _menu_* Menu;  /// backpointer for speedups
	union {
		MenuitemText Text;
		MenuitemButton Button;
		MenuitemPulldown Pulldown;
		MenuitemListbox Listbox;
		MenuitemVslider VSlider;
		MenuitemHslider HSlider;
		MenuitemDrawfunc DrawFunc;
		MenuitemInput Input;
		MenuitemCheckbox Checkbox;
		// ... add here ...
	} D;
} Menuitem;

	/// for MI_TYPE_xSLIDER
#define MI_CFLAGS_UP    1
#define MI_CFLAGS_DOWN  2
#define MI_CFLAGS_LEFT  1
#define MI_CFLAGS_RIGHT 2
#define MI_CFLAGS_KNOB  4
#define MI_CFLAGS_CONT  8

#define MI_IFLAGS_PASSWORD 1 /// Input is a password

#define MI_STYLE_SC_VSLIDER 1
#define MI_STYLE_SC_HSLIDER 2

typedef void (*InitFuncType)(struct _menu_*);
typedef void (*ExitFuncType)(struct _menu_*);
typedef void (*NetActionType)(void);

/**
**  Menu definition.
*/
typedef struct _menu_ {
	/// @todo char* Name; /// menu name
	int       X;          /// menu area x pos
	int       Y;          /// menu area y pos
	int       Width;      /// menu area width
	int       Height;     /// menu area height
	char*     Panel;      /// optional background panel
	Graphic*  BackgroundG;/// optional background image behind the menu panel
	int       DefSel;     /// initial selected item number (or -1)
	int       NumItems;   /// number of items to follow
	Menuitem* Items;      /// buttons, etc
	InitFuncType InitFunc;  /// constructor
	ExitFuncType ExitFunc;  /// destructor
	NetActionType NetAction;/// network action callback
} Menu;

/*----------------------------------------------------------------------------
--  Variables
----------------------------------------------------------------------------*/

extern int GuiGameStarted;                    /// Game Started?
extern Menu* CurrentMenu;                     /// Current menu
extern Graphic *MenuButtonGraphics[];/// Menu button graphics
extern Graphic *MenuButtonG;         /// Current menu button graphics

extern char MenuMapFullPath[1024];  /// Full path to currently selected map

extern int nKeyStrokeHelps;    /// Number of loaded keystroke helps
extern char** KeyStrokeHelps;  /// Keystroke help pairs

#define MENUS_MAXMENU 128  /// @todo wrong place, docu
#define MENUS_MAXFUNC 128  /// @todo wrong place, docu

#ifdef DOXYGEN  // no real code, only for document

#else

	/// Hash table of all the menus
typedef hashtable(Menu*, MENUS_MAXMENU) _MenuHash;
extern _MenuHash MenuHash;
	/// Hash table of all the menu functions
typedef hashtable(void*, MENUS_MAXFUNC) _MenuFuncHash;
extern _MenuFuncHash MenuFuncHash;

#endif

/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

	/// Initialize the hash tables for the menus
extern void InitMenuFuncHash(void);

	/// Set-up menus for a specific race
extern void InitMenus(int race);
	/// Update menu item state. (disabled, ...)
extern void UpdateMenuItemButton(Menuitem* items);
	/// Draw menu
extern void DrawMenu(Menu* menu);
	/// Draw menu button
extern void DrawMenuButton(struct _button_style_* style, unsigned flags,
	int x, int y, const char* text);
	/// Set menu backgound and draw it
extern void MenusSetBackground(void);
	/// Draw and process a menu
extern void ProcessMenu(const char* menu_id, int loop);
	/// End the current menu
extern void EndMenu(void);
	/// Find a menu by id
extern Menu* FindMenu(const char* menu_id);

	/// The scenario path received from server, Update the client menu
extern int NetClientSelectScenario(void);
	/// State info received from server, Update the client menu.
extern void NetClientUpdateState(void);
	/// Notify menu display code to update info
extern void NetConnectForceDisplayUpdate(void);
	/// Compare Local State <-> Server's state, force Update when changes
extern void NetClientCheckLocalState(void);

	/// Sound options menu
extern void SoundOptionsMenu(void);
	/// Speed options menu
extern void SpeedOptionsMenu(void);
	/// Preferences menu
extern void PreferencesMenu(void);
	/// Diplomacy menu
extern void DiplomacyMenu(void);

	/// Save game menu
extern void SaveGameMenu(void);
	/// Load game menu
extern void LoadGameMenu(void);

	/// Restart confirm menu
extern void RestartConfirmMenu(void);
	/// Quit to menu confirm menu
extern void QuitToMenuConfirmMenu(void);
	/// Exit confirm menu
extern void ExitConfirmMenu(void);

	/// Initialize the (ccl-loaded) menus data
extern void InitMenuData(void);

	/// Edit resource properties
extern void EditorEditResource(void);
	/// Edit ai properties
extern void EditorEditAiProperties(void);

	/// Save map from the editor
extern int EditorSaveMenu(void);
	/// Load map from the editor
extern void EditorLoadMenu(void);
	/// Setup Editor Paths
extern void SetupEditor(void);

	/// Error menu
extern void ErrorMenu(char*);

	/// Menu Loop
extern void MenuLoop(const char* filename, struct _world_map_* map);

	/// Pre menu setup
extern void PreMenuSetup(void);

	/// Exit Menus
extern void ExitMenus();

//@}

#endif // !__MENUS_H__
