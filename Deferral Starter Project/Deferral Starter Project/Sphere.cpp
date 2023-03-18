#include "Sphere.h"
#include <iostream>

//We can either hard code the values in GameObject (like in Sphere())
//or
//We can use the GameEngine constructors to fill the values ( like in Sphere(x, y, z, radius, speed))
//Sphere::Sphere(): GameObject()
//{
//	radius = 1.0f;
//	moveSpeed = 5.0f;
//	mass = 1.0f;
//	//force = 0.0f;
//}
//
//Sphere::Sphere(glm::vec3 pos, float _radius, float _moveSpeed)
//	:GameObject(pos) //note the use of GameObject constructor
//{
//	radius = _radius;
//	moveSpeed = _moveSpeed;
//	mass = 1.0f;
//}

Sphere::Sphere(glm::vec3 pos, glm::vec3 col, float _radius, float _moveSpeed, float _mass):
	GameObject(pos, col) //note the use of GameObject constructor
{
	radius = _radius;
	mass = _mass;
	velocity = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	totalForce = glm::vec3(0, 0, 0);
	drag = 0.01f;

	moveSpeed = _moveSpeed;

	/*
	//getting variables into collider 
	collider = new SphrCollide(radius, position);
	collider->mass = mass;
	collider->radius = radius;
	*/
}

void Sphere::Draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(colour.r, colour.g, colour.b);
	glutSolidSphere(radius, 10, 10); //if you'd rather it shows solid
		//glutWireSphere(radius, 10, 10);
	glPopMatrix();
}

void Sphere::Update(float deltaTime)
{
	CalculateForces();

	//eulers to calculate velocity and new position
	acceleration = totalForce / mass;

	newVelocity = velocity + (acceleration)*deltaTime - velocity * drag;
	newPosition = position + (velocity)*deltaTime;

	newTotalForce = totalForce - totalForce * drag /*- glm::vec3(0, 0.1f, 0)*/;
	totalForce = newTotalForce;

	velocity = newVelocity;
	position = newPosition;

	//moving bullet by increasing velocity to the corresponding axis
	if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		totalForce.z -= moveSpeed * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		totalForce.z += moveSpeed * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		totalForce.x -= moveSpeed * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		totalForce.x += moveSpeed * deltaTime;

	if (GameObject::keys['f'] == true)
		totalForce.y += moveSpeed * deltaTime * 2.0f;

}

void Sphere::CalculateForces()
{
	//totalForce = glm::vec3(0, 0, 0) * mass; //no gravity force
	//totalForce = glm::vec3(0, -0.1f, 0) * mass;   // adding gravity to the object +gravity -9.8f
}