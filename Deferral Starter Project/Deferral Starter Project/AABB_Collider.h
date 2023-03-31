#pragma once
#include "Collider.h"



class AABB_Collider : public Collider
{

public:

	AABB_Collider(float _size,float _sizeX, float _sizeY, float _sizeZ, glm::vec3 _position);	//constructor for getting cube size and position
	AABB_Collider(float _size, glm::vec3 _position);	//constructor for getting cube size and position
	~AABB_Collider() {};		//default destructor


	void Draw();
};

