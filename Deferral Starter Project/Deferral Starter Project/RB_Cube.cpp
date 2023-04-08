#include "RB_Cube.h"


RB_Cube::RB_Cube()
{
	size = 1;
	sizeX = 5;
	sizeY = 5;
	sizeZ = 5;
}


RB_Cube::RB_Cube(glm::vec3 _position, glm::vec3 _colour, float _size, float _mass)
{
	size = _size;
	sizeX = _size;
	sizeY = _size;
	sizeZ = _size;
}


RB_Cube::RB_Cube(glm::vec3 _position, glm::vec3 _colour, float _mass, float _size, float _sizeX, float _sizeY, float _sizeZ)
{
	size = _size;
	sizeX = _sizeX;
	sizeY = _sizeY;
	sizeZ = _sizeZ;
	
}

void RB_Cube::Draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(colour.r, colour.g, colour.b);
	glScalef(sizeX, sizeY, sizeZ);
	glutSolidCube(size);
	//glutWireCube(size) - if you'd rather see through it
	glPopMatrix();
}

void RB_Cube::Update(float deltaTime)
{
}
