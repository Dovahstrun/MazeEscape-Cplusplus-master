//Project Includes

#include "Level.h"
#include "Wall.h"
#include "Exit.h"
#include "Player.h"
#include "Baddy.h"
#include "score.h"
#include "Coin.h"
#include "Key.h"

Level::Level()
	: m_player(nullptr)
	, m_updateList()
	, m_drawSpriteList()
	, m_drawUIList()
	,m_collisionList()
{
	loadLevel(1);
}

void Level::Draw(sf::RenderTarget & _target)
{
	//Create and update camera
	sf::View camera = _target.getDefaultView();
	//TODO: Follow player with camera

	// Draw game world to the window
	_target.setView(camera);
	//Draw game objects
	for (int i = 0; i < m_drawSpriteList.size(); ++i)
	{
		if (m_drawSpriteList[i]->isActive())
		{
			m_drawSpriteList[i]->Draw(_target);
		}
	}



	// Draw UI to the window
	_target.setView(_target.getDefaultView());
	//Draw UI objects
	for (int i = 0; i < m_drawUIList.size(); ++i)
	{
		if (m_drawUIList[i]->isActive())
		{
			m_drawUIList[i]->Draw(_target);
		}
	}
}

void Level::Update(sf::Time _frameTime)
{
	//Update
	for (int i = 0; i < m_updateList.size(); ++i)
	{
		if (m_updateList[i]->isActive())
		{
			m_updateList[i]->Update(_frameTime);
		}
	}

	// -----------------------------------------------
	// Collision Section
	// -----------------------------------------------

	for (int i = 0; i < m_collisionList.size(); ++i)
	{
		GameObject* handler = m_collisionList[i].first;
		GameObject* collider = m_collisionList[i].second;


		if (handler->isActive() && collider->isActive())
		{
			if (handler->GetBounds().intersects(collider->GetBounds()))
			{
				handler->Collide(*collider);
			}
		}
	}
}

void Level::loadLevel(int _levelToLoad)
{

	///Cleanup the old level

	//Delete any data already in the level
	for (int i = 0; i < m_updateList.size(); ++i)
	{
		delete m_updateList[i];
	}

	//Clear out the lists
	m_updateList.clear();
	m_drawSpriteList.clear();
	m_drawUIList.clear();
	m_collisionList.clear();

	///Setup all the game objects

	Player* ourPlayer = new Player();
	ourPlayer->SetPosition(0.0f, 0.0f);
	m_updateList.push_back(ourPlayer);


	Coin* ourCoin = new Coin();
	ourCoin->SetPosition(300.0f, 300.0f);
	m_updateList.push_back(ourCoin);
	m_collisionList.push_back(std::make_pair(ourCoin, ourPlayer));


	Score* ourScore = new Score();
	ourScore->SetPlayer(ourPlayer);
	m_updateList.push_back(ourScore);
	m_drawUIList.push_back(ourScore);

	Key* ourKey = new Key();
	ourKey->SetPosition(750.0f, 500.0f);
	m_updateList.push_back(ourKey);
	m_collisionList.push_back(std::make_pair(ourKey, ourPlayer));


	Exit* ourExit = new Exit();
	ourExit->SetPosition(1000.0f, 150.0f);
	ourExit->SetPlayer(ourPlayer);
	m_updateList.push_back(ourExit);


	Wall* ourWall = new Wall();
	ourWall->SetPosition(700.0f, 800.0f);
	m_updateList.push_back(ourWall);
	m_collisionList.push_back(std::make_pair(ourPlayer, ourWall));


	//Add objects to draw lists
	m_drawSpriteList.push_back(ourCoin);
	m_drawSpriteList.push_back(ourKey);
	m_drawSpriteList.push_back(ourExit);
	m_drawSpriteList.push_back(ourWall);
	m_drawSpriteList.push_back(ourPlayer);
}
