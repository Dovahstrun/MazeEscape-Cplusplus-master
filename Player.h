#pragma once

// Project Includes
#include "MovingObject.h"

class Player : public MovingObject
{

public:

	Player();

	//Overriding Methods
	void Update(sf::Time _frameTime);
	virtual void Collide(GameObject& _collider);

	//Public player methods
	int GetScore();
	void ChangeScore(int _changeBy);
	bool GetKey();
	void ChangeKey(bool _keyChange);

private:

	int m_score;
	bool m_key;

};