#include "Sized_AABB_Collider.h"

Sized_AABB_Collider::Sized_AABB_Collider(float _size, float _sizeX, float _sizeY, float _sizeZ, glm::vec3 _position)
{

	sizeX = _sizeX * _size;
	sizeY = _sizeY * _size;
	sizeZ = _sizeZ * _size;
}


void Sized_AABB_Collider::Draw()
{

}