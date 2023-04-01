#pragma once

#include "GameObject.h"
#include "AABB_Collider.h"
#include "Collision_Forces.h"

//A basic cube class derived from a game object
class Gutter : public GameObject
{
public:
	// -- variables --
	float size;
	float sizeX;
	float sizeY;
	float sizeZ;


	AABB_Collider* collider;
	// -- constructors/destructors --
	//Gutter(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta - size 1)
	//Gutter(glm::vec3 pos, float _size);  //pass in a position and size
	Gutter(glm::vec3 pos, glm::vec3 col, float _size, float _sizeX, float _sizeY, float _sizeZ); //pass in a position, colour and size
	~Gutter() {}; //default destructor
	AABB_Collider* GetCollider();
	// -- functions -- 
	//Need to give definions to GameObject's pure virtual functions
	virtual void Draw();
	virtual void Update(float deltaTime);
};