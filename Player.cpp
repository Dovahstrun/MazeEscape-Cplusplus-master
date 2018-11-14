// Project Includes
#include "Player.h"
#include "AssetManager.h"
#include "Wall.h"


//Constants
#define SPEED 500.0f

Player::Player()
	: MovingObject() // Initialise base class
	, m_score(0)
	, m_key(false)
	, m_animationSystem()
	, m_level(nullptr)
	//, m_deathSound()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/PlayerWalkDown1.png"));

	//Set up the animation
	m_animationSystem.SetSprite(m_sprite);

	//Create individual animations
	Animation& standDown = m_animationSystem.CreateAnimation("standDown");
	standDown.AddFrame(AssetManager::GetTexture("graphics/PlayerWalkDown1.png"));

	Animation& runDown = m_animationSystem.CreateAnimation("runDown");
	runDown.AddFrame(AssetManager::GetTexture("graphics/PlayerWalkDown2.png"));
	runDown.AddFrame(AssetManager::GetTexture("graphics/PlayerWalkDown3.png"));
	runDown.SetPlayBackSpeed(8);
	runDown.SetLoop(true);

	m_animationSystem.Play("runDown");

	//Set up sounds
	//m_deathSound.setBuffer(AssetManager::GetSoundBuffer("audio/death.wav"));


}

void Player::Update(sf::Time _frameTime)
{
	//First assume no keys are pressed
	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;

	//Use the keyboard function to check which keys are currently held down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_velocity.y = -SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_velocity.x = -SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_velocity.y = SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_velocity.x = SPEED;
	}


	//Call the update function manually on the player class. This will actually move the character
	MovingObject::Update(_frameTime);

	//Process animations
	m_animationSystem.Update(_frameTime);

}

void Player::Collide(GameObject & _collider)
{
	//Only do something if thing touched was player

	//Dynamic cast the gameObject reference into a wall pointer
	//If it succeeds, it was a wall
	Wall* wallCollider = dynamic_cast<Wall*>(&_collider);

	//If it was a wall we need to move ourselves outside the walls bounds, AKA back where we were
	if (wallCollider != nullptr)
	{
		//the player did hit a wall

		//Go back to the position that the player was in before
		m_sprite.setPosition(m_oldPosition);

		//Clumsy, results in sticky walls but good enough for this game
	}
}

int Player::GetScore()
{
	return m_score;
}

void Player::ChangeScore(int _changeBy)
{
	m_score += _changeBy;
}

bool Player::GetKey()
{
	return m_key;
}

void Player::ChangeKey(bool _keyChange)
{
	m_key = _keyChange;
}

void Player::Kill()
{
	//Reload current level
	if (m_level != nullptr)
	{
		m_level->ReloadLevel();
		//m_deathSound.play();
	}
}

void Player::setLevel(Level * _newLevel)
{
	m_level = _newLevel;
}

void Player::advanceLevel()
{
	if (m_level != nullptr)
	{
		m_level->loadLevel(m_level->GetCurrentLevel()+1);
	}
	
}
