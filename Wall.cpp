
// Project Includes
#include "Wall.h"
#include "AssetManager.h"

Wall::Wall()
	: SpriteObject() // Initialise parent class
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/BrickWall2.png"));
	//TODO: TEMP POSITION
	m_sprite.setPosition(600.0f, 500.0f);
}