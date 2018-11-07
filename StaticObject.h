#pragma once

// Project Includes
#include "SpriteObject.h"

class StaticObject : public SpriteObject
{

public:

	StaticObject();

	// Overriding Methods
	void Update(sf::Time _frameTime);

protected:

};