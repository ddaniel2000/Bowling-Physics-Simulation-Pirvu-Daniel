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
	position = pos;
	velocity = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	totalForce = glm::vec3(0, 0, 0);
	drag = 0.01f;

	moveSpeed = _moveSpeed;
	collider = new Sphere_Collider(radius, position);
}

glm::vec3 gravity = glm::vec3(0, 0.02f, 0);

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
	//glutWireSphere(radius, 10, 10);
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
	if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		totalForce.y += moveSpeed * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		totalForce.y -= moveSpeed * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		totalForce.x -= moveSpeed * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		totalForce.x += moveSpeed * deltaTime;

	//Go Forward with big foce
	if (GameObject::keys['f'] == true)
		totalForce.z -= 50;


	//Jump & land with gravity 
	/*if (GameObject::keys[32] == true)
		*/
	collider->position = position;
	//std::cout <<"x=" << newVelocity.x << " " << "y="<< newVelocity.y << " " << "z=" << newVelocity.z << std::endl;
}

void Sphere::CalculateForces(float _deltaTime)
{
	//totalForce = glm::vec3(0, 0, 0) * mass; //no gravity force
	//totalForce = glm::vec3(0, -0.1f, 0) * mass;   // adding gravity to the object +gravity -9.8f

		//eulers to calculate velocity and new position
	acceleration = totalForce / mass;

	newVelocity = velocity + (acceleration) * _deltaTime - velocity * drag/* - gravity*/;
	newPosition = position + (velocity) * _deltaTime;

	newTotalForce = totalForce - totalForce * drag;
	totalForce = newTotalForce;

	velocity = newVelocity;
	position = newPosition;

	//std::cout << "sphere x =" << position.x<<std::endl;
	
	//std::cout << totalForce.x << " " << totalForce.y << " " << totalForce.z  << " acceleration: " << acceleration.x << " " << acceleration.y << " " << acceleration.z << std::endl;
	ResetForce();
	
}

void  Sphere::ResetForce()
{
	totalForce = glm::vec3(0, 0, 0);
	
}