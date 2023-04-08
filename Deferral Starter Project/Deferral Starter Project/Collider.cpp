#include "Collider.h"

Collider::Collider()
{
}

// Cube construcot
Collider::Collider(float _size, glm::vec3 _position)
{
	size = _size;
}

//AABB constuctor
Collider::Collider(float _size,float _sizeX, float _sizeY, float _sizeZ, glm::vec3 _position)
{
	size = _size;   //Size
	sizeZ = _sizeZ; //Lenght
	sizeX = _sizeX; //Width
	sizeY = _sizeY; //Height
}

 // Deconstructor
Collider::~Collider()
{

}