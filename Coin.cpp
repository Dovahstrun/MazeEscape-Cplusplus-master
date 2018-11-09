// Project Includes
#include "Coin.h"
#include "AssetManager.h"

Coin::Coin()
	: Pickup()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Coin.png"));
	//TEMP: Position coin
	m_pickupSound.setBuffer(AssetManager::GetSoundBuffer("audio/pickup.wav"));
}

void Coin::OnPickup(Player & _player)
{
	_player.ChangeScore(1);
	m_pickupSound.play();
}
