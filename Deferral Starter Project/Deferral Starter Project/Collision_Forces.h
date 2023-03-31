#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <map>
#include "glm/glm.hpp"

class Collision_Forces
{
	float mass;
	glm::vec3 position;
	glm::vec3 Velocity;

	Collision_Forces();
	~Collision_Forces();

};