#pragma once

#include "Collider.h"

class Sphere_Collider : public Collider
{
public:

	Sphere_Collider(float _radius, glm::vec3 _position); //constructor for getting sphere radius and position
	~Sphere_Collider();

	void Draw();

};

