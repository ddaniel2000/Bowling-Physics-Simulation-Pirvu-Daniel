#include "Pin.h"
#include <iostream>

Pin::Pin(glm::vec3 pos, glm::vec3 col, float _size, float _sizeX, float _sizeY, float _sizeZ, float _moveSpeed, float _mass) :
	GameObject(pos, col) //note the use of GameObject constructor
{
	
	size = _size;
	mass = _mass;
	position = pos;
	sizeX = _sizeX;
	sizeY = _sizeY;
	sizeZ = _sizeZ;
	moveSpeed = _moveSpeed;

	velocity = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	totalForce = glm::vec3(0, 0, 0);
	gravity = glm::vec3(0, 0.02f, 0);

	// Drag force that stops the objects aka "Friction Force"
	drag = 0.01f;

	// Adding size, sizeX, sizeY, sizeZ and position into collider
	collider = new AABB_Collider(size, sizeX, sizeY, sizeZ, position);

}

//Position and colour a cube in the scene
void Pin::Draw()
{

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(colour.r, colour.g, colour.b);
	//glRotatef(45, 1.0f, 2, 0);
	glScalef(sizeX, sizeY, sizeZ);
	glutSolidCube(size);

	glPopMatrix();

}

// Getting the collider
AABB_Collider* Pin::GetCollider()
{

	return collider;

}

void Pin::Update(float deltaTime)
{
	
	CalculateForces(deltaTime);

	// Set the position into Collider every frame
	// The position is used for collidingCheck
	collider->position = position;

}

/* -- Eulers to calculate velocityand new position -- */
void Pin::CalculateForces(float _deltaTime)
{
	
	acceleration = totalForce / mass;

	newVelocity = velocity + (acceleration)*_deltaTime - velocity * drag - gravity;
	newPosition = position + (velocity)*_deltaTime;

	newTotalForce = totalForce - totalForce * drag;
	totalForce = newTotalForce;

	velocity = newVelocity;
	position = newPosition;

	ResetForce();

}

void  Pin::ResetForce()
{

	totalForce = glm::vec3(0, 0, 0);

}