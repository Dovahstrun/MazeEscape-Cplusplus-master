#pragma once

// Project Includes
#include "StaticObject.h"
#include "Player.h"

class Exit : public StaticObject
{
public:
	Exit();

	//Overriding Methods
	virtual void Update(sf::Time _frameTime);

	//Public Score Methods
	void SetPlayer(Player* _player);

private:

	Player* m_player;
};