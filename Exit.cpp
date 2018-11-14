
// Project Includes
#include "Exit.h"
#include "AssetManager.h"

Exit::Exit()
	: StaticObject() // Initialise parent class
	, m_player(nullptr)
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorClosed.png"));
}

void Exit::Update(sf::Time _frameTime)
{
	if (m_player != nullptr)
	{
		bool key = m_player->GetKey();
		if (key)
		{
			m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorOpen.png"));
		}
	}
}

void Exit::Collide(GameObject & _collider)
{
	//Only do something if thing touched was player
	Player* castPlayer = dynamic_cast<Player*>(&_collider);

	//Only do the thing if player is not null
	if (castPlayer != nullptr)
	{
		//TODO: Load next level

		if (castPlayer->GetKey())
		{
			castPlayer->advanceLevel();
		}
	}


	//Do something based on type of pickup
	//Disappear
}

void Exit::SetPlayer(Player * _player)
{
	m_player = _player;
}
