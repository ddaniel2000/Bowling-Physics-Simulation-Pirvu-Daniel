#pragma once
#include "Collider.h"



class Sized_AABB_Collider : public Collider
{

public:
	float size;
	float sizeX;
	float sizeY;
	float sizeZ;
	Sized_AABB_Collider( float _size, float _sizeX, float _sizeY, float _sizeZ, glm::vec3 _position);	//constructor for getting cube size and position

	~Sized_AABB_Collider() {};		//default destructor


	void Draw();
};

