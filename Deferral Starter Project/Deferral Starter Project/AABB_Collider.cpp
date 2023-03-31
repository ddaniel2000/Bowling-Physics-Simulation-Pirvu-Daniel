#include "AABB_Collider.h"

AABB_Collider::AABB_Collider(float _size,float _sizeX, float _sizeY, float _sizeZ, glm::vec3 _position)
{

	sizeX = _size * _sizeX;
	sizeY = _size * _sizeY;
	sizeZ = _size * _sizeZ;
}

AABB_Collider::AABB_Collider(float _size, glm::vec3 _position)
{

	sizeX = _size;
	sizeY = _size;
	sizeZ = _size;
}

void AABB_Collider::Draw()
{
}