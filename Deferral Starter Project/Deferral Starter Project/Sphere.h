#pragma once

#include "GameObject.h"


//A basic sphere class derived from a game object
//It can move (basic position changing only at the moment!) via the arrow keys
class Sphere : public GameObject
{
public:
	// -- variables --
	float radius;
	float moveSpeed;
	float force;

	// -- constructors/destructors --
	Sphere(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta - radius 1 - move speed - 1)
	Sphere(glm::vec3 pos, float _radius, float _moveSpeed);  //pass in a position, radius and movespeed
	Sphere(glm::vec3 pos, glm::vec3 col, float _radius, float _moveSpeed); //pass in a position, colour, radius and move speed
	~Sphere() {}; //default destructor

	// -- functions -- 
	//Need to give definions to GameObject's pure virtual functions
	virtual void Draw();
	virtual void Update(float deltaTime);
};