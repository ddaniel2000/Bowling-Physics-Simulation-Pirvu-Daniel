#pragma once

#include "GameObject.h"
#include "AABB_Collider.h"
#include "Collision_Forces.h"

//A basic cube class derived from a game object
class Pin : public GameObject
{
public:
	// -- variables --
	float mass;
	float size;
	float drag;
	float force;
	float sizeX;
	float sizeY;
	float sizeZ;

	glm::vec3 velocity;
	glm::vec3 newPosition;
	glm::vec3 newVelocity;
	glm::vec3 acceleration;

	glm::vec3 gravity;

	AABB_Collider* collider;

	glm::vec3 totalForce;
	glm::vec3 newTotalForce;

	float moveSpeed;

	// -- constructors/destructors --
	Pin(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta - size 1)
	Pin(glm::vec3 pos, float _size);  //pass in a position and size
	Pin(glm::vec3 pos, glm::vec3 col, float _size, float _sizeX, float _sizeY, float _sizeZ, float _moveSpeed, float _mass); //pass in a position, colour and size
	~Pin() {}; //default destructor

	AABB_Collider* GetCollider();

	// -- functions -- 
	//Need to give definions to GameObject's pure virtual functions
	virtual void Draw();
	virtual void Update(float deltaTime);

	void Movement(float _deltaTime);
	void CalculateForces(float _deltaTime);
	void ResetForce();
};