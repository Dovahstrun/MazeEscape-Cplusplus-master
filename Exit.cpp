
// Project Includes
#include "Exit.h"
#include "AssetManager.h"

Exit::Exit()
	: StaticObject() // Initialise parent class
	, m_player(nullptr)
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorClosed.png"));
	m_sprite.setPosition(1000.0f, 150.0f);
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

void Exit::SetPlayer(Player * _player)
{
	m_player = _player;
}
