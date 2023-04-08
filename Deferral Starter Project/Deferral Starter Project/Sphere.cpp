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
	airFriction = 0.001f; //it is used when the sphere is falling/jumping
	gravity = glm::vec3(0, -9.81f, 0);

	

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

	AngularVelodity(deltaTime);
}

void Sphere::AngularVelodity(float _deltaTime)
{
	
	//std::cout << "Sphere at (" << position.x << ", " << position.y << ", " << position.z << ") with radius " << radius << std::endl;
	

	// calculate the angle of rotation based on the angular velocity and time step
	double angle = sqrt(ax * ax + ay * ay + az * az) * _deltaTime;

	// if the angle is zero, no rotation is needed
	if (angle == 0) return;

	// normalize the angular velocity vector
	double len = sqrt(ax * ax + ay * ay + az * az);
	ax /= len;
	ay /= len;
	az /= len;

	// calculate the rotation matrix
	double c = cos(angle);
	double s = sin(angle);
	double ux = ax;
	double uy = ay;
	double uz = az;
	double rotation[3][3] = {
		{c + ux * ux * (1 - c),   ux * uy * (1 - c) - uz * s, ux * uz * (1 - c) + uy * s},
		{uy * ux * (1 - c) + uz * s, c + uy * uy * (1 - c),   uy * uz * (1 - c) - ux * s},
		{uz * ux * (1 - c) - uy * s, uz * uy * (1 - c) + ux * s, c + uz * uz * (1 - c)}
	};

	double x_new = rotation[0][0] * x + rotation[0][1] * y + rotation[0][2] * z;
	double y_new = rotation[1][0] * x + rotation[1][1] * y + rotation[1][2] * z;
	double z_new = rotation[2][0] * x + rotation[2][1] * y + rotation[2][2] * z;
	x = x_new;
	y = y_new;
	z = z_new;

}
void Sphere::Movement(float deltaTime)
{

	//moving bullet by increasing velocity to the corresponding axis

	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		totalForce.x -= moveSpeed * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		totalForce.x += moveSpeed * deltaTime;


	//Go Forward with big foce
	if (GameObject::keys['f'] == true)
	{
		
		totalForce.z -= 2;
	}
		

	collider->position = position;
	
}

void Sphere::CalculateForces(float _deltaTime)
{

	//eulers to calculate velocity and new position
	acceleration = totalForce / mass;

	newVelocity = velocity + (acceleration) * _deltaTime - velocity * drag + gravity * drag;
	newPosition = position + (velocity) * _deltaTime;

	newTotalForce = totalForce - totalForce * drag;
	totalForce = newTotalForce;

	velocity = newVelocity;
	position = newPosition;

	impulse = velocity * mass;

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