// Project Includes
#include "Pickup.h"
#include "Player.h"

Pickup::Pickup()
	: SpriteObject()
{

}

void Pickup::Collide(GameObject & _collider)
{
	//Only do something if thing touched was player

	//We take the generic refernce to a game object passed in
	//We get the address for the game objet
	//We attempt to treat that address as if it is for a player
	//If successful, it IS a player and address s stored in castPlayer
	//If not successful, it is NOT a player and nullptr is stored in castPlayer
	Player* castPlayer = dynamic_cast<Player*>(&_collider);

	//Only do the thing if player is not null
	if (castPlayer != nullptr)
	{
		//Do something based on type of pickup
		OnPickup(*castPlayer);

		//Disappear
		m_active = false;
	}


	//Do something based on type of pickup
	//Disappear
}

void Pickup::OnPickup(Player & _player)
{
	//Do nothing
}
