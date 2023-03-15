#include "Sphere.h"

//We can either hard code the values in GameObject (like in Sphere())
//or
//We can use the GameEngine constructors to fill the values ( like in Sphere(x, y, z, radius, speed))
Sphere::Sphere(): GameObject()
{
	radius = 1.0f;
	moveSpeed = 5.0f;
	force = 0.0f;
}

Sphere::Sphere(glm::vec3 pos, float _radius, float _moveSpeed)
	:GameObject(pos) //note the use of GameObject constructor
{
	radius = _radius;
	moveSpeed = _moveSpeed;
}

Sphere::Sphere(glm::vec3 pos, glm::vec3 col, float _radius, float _moveSpeed):
	GameObject(pos, col) //note the use of GameObject constructor
{
	radius = _radius;
	moveSpeed = _moveSpeed;
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
	//This uses only special keys at the moment - aka the arrow keys
	//You can use normal keys via
	//GameObject::keys['a'] for the a key for example
	if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		position.y += moveSpeed * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		position.y -= moveSpeed * deltaTime;
	 




}

