#include "Cube.h"
#include <iostream>

//We can either hard code the values in GameObject (like in Cube())
//or
//We can use the GameEngine constructors to fill the values ( like in Cube(x, y, z, size))
//Cube::Cube() : GameObject()
//{
//	size = 1.0f;
//
//}
//
//Cube::Cube(glm::vec3 pos, float _size)
//	:GameObject(pos) //note the use of GameObject constructor
//{
//	size = _size;
//}

Cube::Cube(glm::vec3 pos, glm::vec3 col, float _size):
	GameObject(pos, col) //note the use of GameObject constructor
{
	size = _size; 
	sizeX = _size;
	sizeY = _size;
	sizeZ = _size;
	position = pos;
	
	collider = new AABB_Collider(size,position);
}

AABB_Collider* Cube::GetCollider()
{
	return collider;
}
//Position and colour a cube in the scene
void Cube::Draw()
{
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glColor3f(colour.r, colour.g, colour.b);
		//glRotatef(45, 1.0f, 2, 0);
		//glScalef(1, 2.5, 1);
		glutSolidCube(size);
		//glutWireCube(size); //- if you'd rather see through it
	glPopMatrix();



}

void Cube::Update(float deltaTime)
{
	//Cubes are static at the moment so nothing changes for them
	collider->position = position;

	

	if (GameObject::keys['i'] == true)
	{
		position.y += 0.1f;
	}
	if (GameObject::keys['k'] == true)
	{
		position.y -= 0.1f;
	}
	if (GameObject::keys['j'] == true)
	{
		position.x -= 0.1f;
	}
	if (GameObject::keys['l'] == true)
	{
		position.x += 0.1f;
	}
}