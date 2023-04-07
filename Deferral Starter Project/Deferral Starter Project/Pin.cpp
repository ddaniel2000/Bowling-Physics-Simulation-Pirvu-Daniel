#include "Pin.h"
#include <iostream>

Pin::Pin(glm::vec3 pos, glm::vec3 col, float _size, float _sizeX, float _sizeY, float _sizeZ, float _moveSpeed, float _mass) :
	GameObject(pos, col) //note the use of GameObject constructor
{
	position = pos;
	size = _size;
	sizeX = _sizeX;
	sizeY = _sizeY;
	sizeZ = _sizeZ;

	mass = _mass;
	position = pos;
	velocity = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	totalForce = glm::vec3(0, 0, 0);
	drag = 0.01f;
	gravity = glm::vec3(0, 0.02f, 0);

	moveSpeed = _moveSpeed;
	//getting variables into collider 
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

AABB_Collider* Pin::GetCollider()
{
	return collider;
}

void Pin::Update(float deltaTime)
{
	//std::cout << position.y << std::endl;
	CalculateForces(deltaTime);

	//Cubes are static at the moment so nothing changes for them
	collider->position = position;
}
void Pin::CalculateForces(float _deltaTime)
{
	
	//eulers to calculate velocity and new position
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