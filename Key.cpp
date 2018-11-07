// Project Includes
#include "Key.h"
#include "AssetManager.h"

Key::Key()
	: Pickup()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Key.png"));
	//TEMP: Position Key
}

void Key::OnPickup(Player & _player)
{

	_player.ChangeKey(true);
}
