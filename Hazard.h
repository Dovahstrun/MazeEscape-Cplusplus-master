#pragma once

//Project Includes
#include "SpriteObject.h"

class Hazard : public SpriteObject
{

public:

	Hazard(); //Constructor

	//Overriding Methods
	void Collide(GameObject& _collider);

};
