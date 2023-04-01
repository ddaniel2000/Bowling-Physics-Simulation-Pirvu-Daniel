#pragma once

#include "GameObject.h"
#include "Sphere_Collider.h"
#include "Collision_Forces.h"



//A basic sphere class derived from a game object
//It can move (basic position changing only at the moment!) via the arrow keys
class Sphere : public GameObject
{
public:
	// -- variables --
	float radius;
	float moveSpeed;
	float mass;
	glm::vec3 newPosition;
	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 newVelocity;
	float force;
	float drag;
	glm::vec3 gravity;

	Sphere_Collider* collider;

	glm::vec3 totalForce;
	glm::vec3 newTotalForce;

	// -- constructors/destructors --
	Sphere(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta - radius 1 - move speed - 1)
	Sphere(glm::vec3 pos, float _radius, float _moveSpeed);  //pass in a position, radius and movespeed
	Sphere(glm::vec3 pos, glm::vec3 col, float _radius, float _moveSpeed, float _mass); //pass in a position, colour, radius, move speed and mass
	~Sphere() {}; //default destructor

	Sphere_Collider* GetCollider();//getting variables for collision calculation class
	
	// -- functions -- 
	//Need to give definions to GameObject's pure virtual functions
	virtual void Draw();
	virtual void Update(float deltaTime);

	void Movement(float _deltaTime);
	void CalculateForces(float _deltaTime);
	void ResetForce();
};