#include "Bowling_Lane.h"

Bowling_Lane::Bowling_Lane(glm::vec3 pos, glm::vec3 col, float _size, float _sizeX, float _sizeY, float _sizeZ,float _mass) :
	GameObject(pos, col) //note the use of GameObject constructor
{

	position = pos;
	size = _size;
	sizeX = _sizeX;
	sizeY = _sizeY;
	sizeZ = _sizeZ;
	mass = _mass;

	// Sending size, sizeX, sizeY, sizeZ & position
	collider = new AABB_Collider(size, sizeX, sizeY, sizeZ, position);

	// sizeX, sizeY, sizeZ are used to calculate the collider's boundaries

}



//Position and colour a cube in the scene
void Bowling_Lane::Draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(colour.r, colour.g, colour.b);
	//glRotatef(45, 1.0f, 2, 0);
	glScalef(sizeX, sizeY, sizeZ);
	glutSolidCube(size);

	glPopMatrix();

}

AABB_Collider* Bowling_Lane::GetCollider()
{

	return collider;

}

/* -- Update --*/
void Bowling_Lane::Update(float deltaTime)
{

	//Cubes are static at the moment so nothing changes for them
	collider->position = position;

}
