#pragma once

#include "GameObject.h"

//A basic cube class derived from a game object
class Gutter : public GameObject
{
public:
	// -- variables --
	float size;


	// -- constructors/destructors --
	Gutter(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta - size 1)
	Gutter(glm::vec3 pos, float _size);  //pass in a position and size
	Gutter(glm::vec3 pos, glm::vec3 col, float _size); //pass in a position, colour and size
	~Gutter() {}; //default destructor

	// -- functions -- 
	//Need to give definions to GameObject's pure virtual functions
	virtual void Draw();
	virtual void Update(float deltaTime);
};