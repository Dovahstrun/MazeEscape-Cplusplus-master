// Project Includes
#include "Key.h"
#include "AssetManager.h"

Key::Key()
	: Pickup()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Key.png"));
	//TEMP: Position Key
	m_sprite.setPosition(750.0f, 900.0f);
}

void Key::OnPickup(Player & _player)
{

	_player.ChangeKey(true);
}
