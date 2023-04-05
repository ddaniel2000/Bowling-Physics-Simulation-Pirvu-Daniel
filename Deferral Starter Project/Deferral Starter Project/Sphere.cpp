#include "Sphere.h"
#include <iostream>


Sphere::Sphere(glm::vec3 pos, glm::vec3 col, float _radius, float _moveSpeed, float _mass):
	GameObject(pos, col) //note the use of GameObject constructor
{
	radius = _radius;
	mass = _mass;
	position = pos;
	velocity = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	totalForce = glm::vec3(0, 0, 0);
	drag = 0.01f;
	gravity = glm::vec3(0, 0.02f, 0);

	moveSpeed = _moveSpeed;
	collider = new Sphere_Collider(radius, position);
}



Sphere_Collider* Sphere::GetCollider()
{
	return collider;
}


void Sphere::Draw()
{
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glColor3f(colour.r, colour.g, colour.b);
		glutSolidSphere(radius, 10, 10); //if you'd rather it shows solid

	glPopMatrix();

	// Lines rendered from origin to all axis
	glPushMatrix();
	glBegin(GL_LINES);

	glColor3f(1, 0, 0);
	glVertex3f(position.x, position.y, position.z); //uses the game objects position values
	glVertex3f(position.x + 1, position.y, position.z); //positive x axis

	glColor3f(0, 1, 0); //note the colour change per line
	glVertex3f(position.x, position.y, position.z);
	glVertex3f(position.x, position.y + 1, position.z); //positive y axis

	glColor3f(1, 0, 1);
	glVertex3f(position.x, position.y, position.z);
	glVertex3f(position.x, position.y, position.z + 1); //positive z axis
	glEnd();
	glPopMatrix();
}

void Sphere::Update(float deltaTime)
{
	Movement(deltaTime);
	CalculateForces(deltaTime);

	collider->position = position;
	
	////impulse calculation
}

void Sphere::Movement(float deltaTime)
{

	//moving bullet by increasing velocity to the corresponding axis
	//if (GameObject::specialKeys[GLUT_KEY_UP] == true)
	//	totalForce.z -= moveSpeed * deltaTime;
	//if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
	//	totalForce.z += moveSpeed * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		totalForce.x -= moveSpeed * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		totalForce.x += moveSpeed * deltaTime;

	//Go Forward with big foce
	if (GameObject::keys['f'] == true)
	{
		
		totalForce.z -= 50;
	}
		

	collider->position = position;
	
}

void Sphere::CalculateForces(float _deltaTime)
{

	//eulers to calculate velocity and new position
	acceleration = totalForce / mass;

	newVelocity = velocity + (acceleration) * _deltaTime - velocity * drag - gravity;
	newPosition = position + (velocity) * _deltaTime;

	newTotalForce = totalForce - totalForce * drag;
	totalForce = newTotalForce;

	velocity = newVelocity;
	position = newPosition;


	ResetForce();
	//std::cout << Force().x << Force().z;
}

void  Sphere::ResetForce()
{
	totalForce = glm::vec3(0, 0, 0);
	
}

glm::vec3 Sphere::Force()
{
	return mass * acceleration;
}