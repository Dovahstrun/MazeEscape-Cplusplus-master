#pragma once

#include "GameObject.h"
#include "Player.h"

class Level
{

public:

	Level();

	virtual void Draw(sf::RenderTarget& _target);
	virtual void Update(sf::Time _frameTime);

	void loadLevel(int _levelToLoad);

private:

	Player* m_player;
	std::vector<GameObject*> m_updateList;
	std::vector<GameObject*> m_drawSpriteList;
	std::vector<GameObject*> m_drawUIList;
	std::vector<std::pair<GameObject*, GameObject*> > m_collisionList;
};
