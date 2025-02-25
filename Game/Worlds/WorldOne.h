#pragma once

//
// Copyright (C) 2023 p1skates (@havokgamers)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <stdint.h>

#include "TileType.h"
#include "Map.h"

constexpr uint8_t map0Width = 14;
constexpr uint8_t map0Height = 10;

const TileType map0Data[map0Height][map0Width] PROGMEM =
{   {
		TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None,TileType::None, TileType::None, TileType::None, TileType::None, TileType::None
	},
  {
		TileType::None, TileType::Dirt, TileType::Dirt, TileType::Dirt, TileType::Dirt, TileType::None, TileType::Dirt, TileType::Dirt, TileType::Dirt,TileType::Dirt, TileType::Dirt, TileType::Dirt, TileType::Dirt, TileType::None
	},
   {
		TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None,TileType::None, TileType::None, TileType::None, TileType::None, TileType::None
	},
  {
		TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None,TileType::None, TileType::None, TileType::None, TileType::None, TileType::None
	},
  {
		TileType::Grass, TileType::Grass, TileType::None, TileType::Grass, TileType::None, TileType::Grass, TileType::Grass, TileType::Grass, TileType::Grass,TileType::None, TileType::Grass, TileType::Grass, TileType::Grass, TileType::Grass
	},
  {
		TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None,TileType::None, TileType::None, TileType::None, TileType::None, TileType::None
	},
	{
		TileType::Grass, TileType::Grass, TileType::Grass, TileType::Grass, TileType::Grass, TileType::None, TileType::None, TileType::Grass, TileType::Grass,TileType::Grass, TileType::Dirt, TileType::None, TileType::None, TileType::None
	},
	{
		TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::None,TileType::None, TileType::None, TileType::None, TileType::None, TileType::None
	},
	{
		TileType::None, TileType::None, TileType::None, TileType::None, TileType::None, TileType::Dirt, TileType::None, TileType::None, TileType::Grass,TileType::None, TileType::None, TileType::None, TileType::None, TileType::Dirt
	},
	{
		TileType::Grass, TileType::Grass, TileType::Grass, TileType::Grass, TileType::Dirt, TileType::Dirt, TileType::Grass, TileType::Grass, TileType::Dirt, TileType::Grass, TileType::Grass, TileType::Grass, TileType::Dirt, TileType::Dirt
	}
};


const Map map0 PROGMEM = Map(map0Data);
