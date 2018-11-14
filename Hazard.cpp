//Project includes
#include "Hazard.h"
#include "AssetManager.h"
#include "Player.h"

Hazard::Hazard()
	: SpriteObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Obstacle.png"));
}

void Hazard::Collide(GameObject & _collider)
{
	//Only do something if thing touched was player
	Player* castPlayer = dynamic_cast<Player*>(&_collider);

	//Only do the thing if player is not null
	if (castPlayer != nullptr)
	{
		//We were touched by the player, therefore KILL THEM
		castPlayer->Kill();
	}


	//Do something based on type of pickup
	//Disappear
}
