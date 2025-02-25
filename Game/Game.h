#pragma once

// Copyright (C) 2023 p1skates (@havokgamers)
// #includes changes WorldOne.h
//
// Copyright (C) 2019 Pharap (@Pharap)
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

#include <Arduboy2.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "GameEngine
/TileImages.h"
#include "GameEngine
/TileType.h"
#include "GameEngine
/WorldOne.h"
#include "GameEngine
/Entity.h"
#include "GameEngine
/Camera.h"

class Game
{
private:
	static constexpr int16_t movementSpeed = 2;
	static constexpr int16_t gravitySpeed = 1;

	static constexpr int16_t centreScreenX = (WIDTH / 2);
	static constexpr int16_t centreScreenY = (HEIGHT / 2);

	static constexpr int16_t halfTileWidth = (tileWidth / 2);
	static constexpr int16_t halfTileHeight = (tileHeight / 2);

private:
	Arduboy2 arduboy;
	Map map;
	Camera camera;
	Entity playerEntity { centreScreenX, centreScreenY, 0, 0 };

public:
	void setup()
	{
		this->arduboy.begin();

		// Load map
		this->loadMapFromProgmem(map0);
	}

	void loop()
	{
		if(!this->arduboy.nextFrame())
			return;

		this->arduboy.pollButtons();

		this->arduboy.clear();

		// Update and render
		this->updateGameplay();
		this->renderGameplay();

		this->arduboy.display();
	}

	void updateGameplay()
	{
		// Handle xVelocity
		int16_t xVelocity = 0;

		if(this->arduboy.pressed(LEFT_BUTTON))
		{
			xVelocity -= movementSpeed;
		}

		if(this->arduboy.pressed(RIGHT_BUTTON))
		{
			xVelocity += movementSpeed;
		}

		this->playerEntity.xVelocity = xVelocity;

		// Handle jumping (yVelocity)
		if(this->arduboy.justPressed(A_BUTTON))
		{
			if(this->playerEntity.yVelocity > 0)
				this->playerEntity.yVelocity = -8;
		}

		// If player is jumping
		if(this->playerEntity.yVelocity < 0)
		{
			// Slowly reduce negative velocity with gravity
			this->playerEntity.yVelocity += gravitySpeed;
		}
		else
		{
			// Else apply normal gravity
			this->playerEntity.yVelocity = gravitySpeed;
		}

		// Update the player's position
		this->updatePlayerPosition();

		// Figure out the new map position based on the player's current position
		const int16_t newMapX = (this->playerEntity.x - centreScreenX);
		const int16_t newMapY = (this->playerEntity.y - centreScreenY);

		this->camera.x = ((newMapX < 0) ? 0 : newMapX);
		this->camera.y = ((newMapY < 0) ? 0 : newMapY);
	}

	void drawPlayer()
	{
		const int16_t x = ((this->playerEntity.x - halfTileWidth) - this->camera.x);
		const int16_t y = ((this->playerEntity.y - halfTileHeight) - this->camera.y);

		this->arduboy.fillRect(x, y, tileWidth, tileHeight, BLACK);
	}

	void updatePlayerPosition()
	{
		// Figure out the point that the player should be moving to
		int16_t newX = (this->playerEntity.x + this->playerEntity.xVelocity);
		int16_t newY = (this->playerEntity.y + this->playerEntity.yVelocity);

		// Figure out the tile coordinate that the player should be moving to
		const int16_t tileX = (newX / tileWidth);
		const int16_t tileY = (newY / tileHeight);

		// Find the x coordinate of the player's new right side
		const int16_t rightX = (newX + halfTileWidth);

		// Find which tile the player's new right side is in
		const int16_t rightTileX = (rightX / tileWidth);

		// Find the tile the player is trying to move into
		const TileType rightTile = map.getTile(rightTileX, tileY);

		// If the tile is solid
		if(isSolid(rightTile))
		{
			// Adjust the player's position to prevent collision
			newX = ((rightTileX * tileWidth) - halfTileWidth);
		}
		
		// Find the x coordinate of the player's new left side
		const int16_t leftX = ((newX - halfTileWidth) - 1);
		
		// Find which tile the player's new left side is in
		const int16_t leftTileX = (leftX / tileWidth);

		// Find the tile the player is trying to move into
		const TileType leftTile = map.getTile(leftTileX, tileY);

		// If the tile is solid
		if(isSolid(leftTile))
		{
			// Adjust the player's position to prevent collision
			newX = (((leftTileX + 1) * tileWidth) + halfTileWidth);
		}

		// Find the x coordinate of the player's new bottom side
		const int16_t bottomY = (newY + halfTileHeight);

		// Find which tile the player's new bottom side is in
		const int16_t bottomTileY = (bottomY / tileHeight);

		// Find the tile the player is trying to move into
		const TileType bottomTile = map.getTile(tileX, bottomTileY);

		if(isSolid(bottomTile))
		{
			// Adjust the player's position to prevent collision
			newY = ((bottomTileY * tileHeight) - halfTileHeight);
		}

		// Find the x coordinate of the player's new top side
		const int16_t topY = ((newY - halfTileHeight) - 1);

		// Find which tile the player's new top side is in
		const int16_t topTileY = (topY / tileHeight);

		// Find the tile the player is trying to move into
		const TileType topTile = map.getTile(tileX, topTileY);

		// If the tile is solid
		if(isSolid(topTile))
		{
			// Adjust the player's position to prevent collision
			newY = (((topTileY + 1) * tileHeight) + halfTileHeight);
		}

		// Assign the player's new position
		// Whilst preventing the position from going out of bounds
		this->playerEntity.x = ((newX > halfTileHeight) ? newX : halfTileWidth);
		this->playerEntity.y = ((newY > halfTileHeight) ? newY : halfTileHeight);
	}

	void renderGameplay()
	{
		// Draw map
		this->drawMap(this->camera.x, this->camera.y, this->map);

		// Draw player
		this->drawPlayer();

		// Print camera position
		this->arduboy.print(this->camera.x);
		this->arduboy.print(F(", "));
		this->arduboy.println(this->camera.y);

		// Printer player entity position
		this->arduboy.print(this->playerEntity.x);
		this->arduboy.print(F(", "));
		this->arduboy.println(this->playerEntity.y);
	}

	void loadMapFromProgmem(const Map & progmemMap)
	{
		// Copy map from progmem into map
		memcpy_P(&this->map, &progmemMap, sizeof(Map));
	}

	void drawMap(int16_t mapX, int16_t mapY, Map map)
	{
		constexpr size_t screenTileWidth = ((WIDTH / tileWidth) + 1);
		constexpr size_t screenTileHeight = ((HEIGHT / tileHeight) + 1);

		for(uint8_t y = 0; y < screenTileHeight; ++y)
		{
			const int16_t mapTileY = (mapY / tileHeight);
			const int16_t tileY = (mapTileY + y);
	
			// If tile is out of bounds, continue next iteration
			if(tileY < 0 || tileY >= map.getHeight())
				continue;
	
			const int16_t mapRemainderY = (mapY % tileHeight);
			const int16_t drawY = ((y * tileHeight) - mapRemainderY);
	
			for(uint8_t x = 0; x < screenTileWidth; ++x)
			{
				const int16_t mapTileX = (mapX / tileWidth);
				const int16_t tileX = (mapTileX + x);
	
				// If tile is out of bounds, continue next iteration
				if(tileX < 0 || tileX >= map.getWidth())
					continue;
	
				const int16_t mapRemainderX = (mapX % tileWidth); 
				const int16_t drawX = ((x * tileWidth) - mapRemainderX);

				// Get tile type from map
				TileType tileType = map.getTile(tileX, tileY);

				// Draw tile
				Sprites::drawOverwrite(drawX, drawY, tileImages, getTileIndex(tileType));
			}
		}
	}
};
