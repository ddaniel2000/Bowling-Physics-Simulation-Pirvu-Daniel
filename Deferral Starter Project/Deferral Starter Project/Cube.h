#pragma once

#include "GameObject.h"
#include "AABB_Collider.h"
#include "Collision_Forces.h"

//A basic cube class derived from a game object
class Cube: public GameObject
{
public:
	// -- variables --
	float size;
	float sizeX;
	float sizeY;
	float sizeZ;
	// -- constructors/destructors --
	Cube(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta - size 1)
	Cube(glm::vec3 pos, float _size);  //pass in a position and size
	Cube(glm::vec3 pos, glm::vec3 col, float _size); //pass in a position, colour and size
	Cube(glm::vec3 pos, glm::vec3 col, float _size, float _moveSpeed, float _mass); //pass in a position, colour, radius, move speed and mass

	AABB_Collider* collider;

	~Cube() {}; //default destructor

	AABB_Collider* GetCollider();//getting variables for collision calculation class
	// -- functions -- 
	//Need to give definions to GameObject's pure virtual functions
	virtual void Draw();
	virtual void Update(float deltaTime);

};