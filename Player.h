#pragma once

// Project Includes
#include "MovingObject.h"
#include "AnimationSystem.h"
#include "Level.h"

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
	void Kill();
	void setLevel(Level* _newLevel);
	void advanceLevel();

private:

	int m_score;
	bool m_key;
	AnimationSystem m_animationSystem;
	Level* m_level;
//
//protected:
//
//	sf::Sound m_deathSound;

};