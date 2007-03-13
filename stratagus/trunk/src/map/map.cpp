//       _________ __                 __
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/
//  ______________________                           ______________________
//                        T H E   W A R   B E G I N S
//         Stratagus - A free fantasy real time strategy game engine
//
/**@name map.cpp - The map. */
//
//      (c) Copyright 1998-2007 by Lutz Sammer, Vladi Shabanski and
//                                 Francois Beerten
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

//@{

/*----------------------------------------------------------------------------
--  Includes
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stratagus.h"
#include "unittype.h"
#include "map.h"
#include "tileset.h"
#include "minimap.h"
#include "player.h"
#include "unit.h"
#include "pathfinder.h"
#include "ui.h"
#include "editor.h"
#include "script.h"

/*----------------------------------------------------------------------------
--  Variables
----------------------------------------------------------------------------*/

CMap Map;                        /// The current map
int FlagRevealMap;               /// Flag must reveal the map
int ReplayRevealMap;             /// Reveal Map is replay
char CurrentMapPath[1024];       /// Path of the current map

/*----------------------------------------------------------------------------
--  Visible and explored handling
----------------------------------------------------------------------------*/

/**
**  Marks seen tile -- used mainly for the Fog Of War
**
**  @param x  Map X tile-position.
**  @param y  Map Y tile-position.
*/
void CMap::MarkSeenTile(int x, int y)
{
	int tile;
	int seentile;
	CMapField *mf;

	mf = this->Fields + x + y * this->Info.MapWidth;
	//
	//  Nothing changed? Seeing already the correct tile.
	//
	if ((tile = mf->Tile) == (seentile = mf->SeenTile)) {
		return;
	}
	mf->SeenTile = tile;

	UI.Minimap.UpdateXY(x, y);
}

/**
**  Reveal the entire map.
*/
void CMap::Reveal(void)
{
	int x;
	int y;
	int p;  // iterator on player.

	//
	//  Mark every explored tile as visible. 1 turns into 2.
	//
	for (x = 0; x < this->Info.MapWidth; ++x) {
		for (y = 0; y < this->Info.MapHeight; ++y) {
			for (p = 0; p < PlayerMax; ++p) {
				if (!this->Fields[x + y * this->Info.MapWidth].Visible[p]) {
					this->Fields[x + y * this->Info.MapWidth].Visible[p] = 1;
				}
			}
			MarkSeenTile(x, y);
		}
	}
	//
	//  Global seen recount. Simple and effective.
	//
	for (x = 0; x < NumUnits; ++x) {
		//
		//  Reveal neutral buildings. Gold mines:)
		//
		if (Units[x]->Player->Type == PlayerNeutral) {
			for (p = 0; p < PlayerMax; ++p) {
				if (Players[p].Type != PlayerNobody &&
						(!(Units[x]->Seen.ByPlayer & (1 << p)))) {
					UnitGoesOutOfFog(Units[x], Players + p);
					UnitGoesUnderFog(Units[x], Players + p);
				}
			}
		}
		UnitCountSeen(Units[x]);
	}
}

/*----------------------------------------------------------------------------
--  Map queries
----------------------------------------------------------------------------*/

/**
**  Water on map tile.
**
**  @param tx  X map tile position.
**  @param ty  Y map tile position.
**
**  @return    True if water, false otherwise.
*/
bool CMap::WaterOnMap(int tx, int ty) const
{
	Assert(tx >= 0 && ty >= 0 && tx < Info.MapWidth && ty < Info.MapHeight);
	return (Fields[tx + ty * Info.MapWidth].Flags & MapFieldWaterAllowed) != 0;
}

/**
**  Coast on map tile.
**
**  @param tx  X map tile position.
**  @param ty  Y map tile position.
**
**  @return    True if coast, false otherwise.
*/
bool CMap::CoastOnMap(int tx, int ty) const
{
	Assert(tx >= 0 && ty >= 0 && tx < Info.MapWidth && ty < Info.MapHeight);
	return (Fields[tx + ty * Info.MapWidth].Flags & MapFieldCoastAllowed) != 0;

}

/**
**  Can move to this point, applying mask.
**
**  @param x     X map tile position.
**  @param y     Y map tile position.
**  @param mask  Mask for movement to apply.
**
**  @return      True if could be entered, false otherwise.
*/
int CheckedCanMoveToMask(int x, int y, int mask)
{
	if (x < 0 || y < 0 || x >= Map.Info.MapWidth || y >= Map.Info.MapHeight) {
		return 0;
	}

	return !(Map.Fields[x + y * Map.Info.MapWidth].Flags & mask);
}

/**
**  Can an unit of unit-type be placed at this point.
**
**  @param type  unit-type to be checked.
**  @param x     X map tile position.
**  @param y     Y map tile position.
**
**  @return      True if could be entered, false otherwise.
*/
int UnitTypeCanBeAt(const CUnitType *type, int x, int y)
{
	int addx;  // iterator
	int addy;  // iterator
	int mask;  // movement mask of the unit.

	Assert(type);
	mask = type->MovementMask;
	for (addx = 0; addx < type->TileWidth; addx++) {
		for (addy = 0; addy < type->TileHeight; addy++) {
			if (!CheckedCanMoveToMask(x + addx, y + addy, mask)) {
				return 0;
			}
		}
	}
	return 1;
}

/**
**  Can an unit be placed to this point.
**
**  @param unit  unit to be checked.
**  @param x     X map tile position.
**  @param y     Y map tile position.
**
**  @return      True if could be placeded, false otherwise.
*/
int UnitCanBeAt(const CUnit *unit, int x, int y)
{
	Assert(unit);
	return UnitTypeCanBeAt(unit->Type, x, y);
}

/**
**  Fixes initially the wood and seen tiles.
*/
void PreprocessMap(void)
{
	int ix;
	int iy;
	CMapField *mf;

	for (ix = 0; ix < Map.Info.MapWidth; ++ix) {
		for (iy = 0; iy < Map.Info.MapHeight; ++iy) {
			mf = Map.Fields + ix + iy * Map.Info.MapWidth;
			mf->SeenTile = mf->Tile;
		}
	}
}

/**
**  Release info about a map.
**
**  @param info  CMapInfo pointer.
*/
void FreeMapInfo(CMapInfo *info)
{
	if (info) {
		info->Description.clear();
		info->Filename.clear();
		info->MapWidth = info->MapHeight = 0;
		memset(info->PlayerSide, 0, sizeof(info->PlayerSide));
		memset(info->PlayerType, 0, sizeof(info->PlayerType));
		info->MapUID = 0;
	}
}

/**
**  Alocate and initialise map table
*/
void CMap::Create()
{
	Assert(!this->Fields);

	this->Fields = new CMapField[this->Info.MapWidth * this->Info.MapHeight];
	this->Visible[0] = new unsigned[this->Info.MapWidth * this->Info.MapHeight / 2];
	memset(this->Visible[0], 0, this->Info.MapWidth * this->Info.MapHeight / 2 * sizeof(unsigned));
	InitUnitCache();
}

/**
**  Cleanup the map module.
*/
void CMap::Clean(void)
{
	delete[] this->Fields;
	delete[] this->Visible[0];

	// Tileset freed by Tileset?

	FreeMapInfo(&this->Info);
	this->Fields = NULL;
	memset(this->Visible, 0, sizeof(this->Visible));
	this->NoFogOfWar = false;
	this->Tileset.Clear();
	memset(this->TileModelsFileName, 0, sizeof(this->TileModelsFileName));
	this->TileGraphic = NULL;

	FlagRevealMap = 0;
	ReplayRevealMap = 0;

	UI.Minimap.Destroy();
}


/*----------------------------------------------------------------------------
-- Load Map Functions
----------------------------------------------------------------------------*/

/**
**  Load the map presentation
**
**  @param mapname  map filename
*/
void LoadStratagusMapInfo(const std::string &mapname) 
{
	// Set the default map setup by replacing .smp with .sms
	std::string::size_type loc = mapname.find(".smp");
	if (loc != std::string::npos) {
		Map.Info.Filename = mapname;
		Map.Info.Filename.replace(loc, 4, ".sms");
	}
	
	LuaLoadFile(mapname);
}

//@}