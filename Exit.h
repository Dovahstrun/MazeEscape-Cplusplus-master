#pragma once

// Project Includes
#include "StaticObject.h"
#include "Player.h"

class Exit : public StaticObject
{
public:
	Exit();

	//Overriding Methods
	void Update(sf::Time _frameTime);
	void Collide(GameObject& _collider);

	//Public Score Methods
	void SetPlayer(Player* _player);

private:

	Player* m_player;
};