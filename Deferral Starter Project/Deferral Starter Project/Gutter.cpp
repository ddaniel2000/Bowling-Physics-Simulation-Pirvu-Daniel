#include "Gutter.h"
#include <iostream>
using namespace std;

Gutter::Gutter(glm::vec3 pos, glm::vec3 col, float _size, float _sizeX, float _sizeY, float _sizeZ) :
	GameObject(pos, col) //note the use of GameObject constructor
{
	position = pos;
	size = _size;
	sizeX = _sizeX;
	sizeY = _sizeY;
	sizeZ = _sizeZ;
	
	collider = new AABB_Collider(size, sizeX, sizeY, sizeZ, position);
}

void Gutter::Draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(colour.r, colour.g, colour.b);
	glScalef(sizeX, sizeY, sizeZ);
	glutSolidCube(size);
	glPopMatrix();
}

AABB_Collider* Gutter::GetCollider()
{
	return collider;
}

void Gutter::Update(float deltaTime)
{
	//std::cout << "aaaaaaaaaaaaaaa";
	collider->position = position;
	// Move UP the gutters by pressing C
	if (GameObject::keys['c'] == true )
	{
		if (position.y < -0.3)
		{

			position.y = 0.0;
		}


	}

	// Move DOWN the gutters by pressing X
	if (GameObject::keys['x'] == true )
	{
		if (position.y >= -0.1)
		{

			position.y = -5.0;
		}


	}
	
}

