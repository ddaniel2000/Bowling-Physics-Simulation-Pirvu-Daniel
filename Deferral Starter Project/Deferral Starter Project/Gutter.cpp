#include "Gutter.h"
#include <iostream>
using namespace std;


//Gutter::Gutter() : GameObject()
//{
//	size = 1.0f;
//
//}
//
//Gutter::Gutter(glm::vec3 pos, float _size)
//	:GameObject(pos) //note the use of GameObject constructor
//{
//	size = _size;
//}

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

//0.2, 0.5, 40.0
//Position and colour a gutter in the scene
void Gutter::Draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(colour.r, colour.g, colour.b);
	//glRotatef(45, 1.0f, 2, 0);
	glScalef(sizeX, sizeY, sizeZ);
	glutSolidCube(size);
	//glutWireCube(size); //- if you'd rather see through it
	glPopMatrix();
}

AABB_Collider* Gutter::GetCollider()
{
	return collider;
}

void Gutter::Update(float deltaTime)
{
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

