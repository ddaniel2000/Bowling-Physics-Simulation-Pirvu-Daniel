#pragma once

#include "GameObject.h"

//A basic cube class derived from a game object
class Bowling_Lane : public GameObject
{
public:
	// -- variables --
	float size;


	// -- constructors/destructors --
	Bowling_Lane(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta - size 1)
	Bowling_Lane(glm::vec3 pos, float _size);  //pass in a position and size
	Bowling_Lane(glm::vec3 pos, glm::vec3 col, float _size); //pass in a position, colour and size
	~Bowling_Lane() {}; //default destructor

	// -- functions -- 
	//Need to give definions to GameObject's pure virtual functions
	virtual void Draw();
	virtual void Update(float deltaTime);
};