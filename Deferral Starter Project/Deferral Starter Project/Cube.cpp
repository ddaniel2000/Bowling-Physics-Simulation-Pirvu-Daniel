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
		glutSolidCube(size);
	glPopMatrix();


}

void Cube::Update(float deltaTime)
{
	
	collider->position = position;
}