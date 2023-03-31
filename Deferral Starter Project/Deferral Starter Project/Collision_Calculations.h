#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <map>
#include "glm/glm.hpp"

#include "GameObject.h"
#include "Cube.h"
#include "Sphere.h"
#include "Bowling_Lane.h"
#include "Collision_Forces.h"


class Collision_Calculations
{
public:

	Collision_Calculations();
	~Collision_Calculations();

	//functions for collision check + response

	void Sphere_Sphere(GameObject* a, GameObject* b);
	void AABB_AABB(GameObject* a, GameObject* b);
	void AABB_Sphere(GameObject* a, GameObject* b);
	void Sphere_AABB(GameObject* a, GameObject* b);


};


