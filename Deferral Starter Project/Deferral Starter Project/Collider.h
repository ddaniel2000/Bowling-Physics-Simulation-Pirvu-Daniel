#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <map>
#include "glm/glm.hpp"

#include "Collision_Forces.h"

/// This is the brief description of this class
/// 
/// This is the detailed description of this class. More staff here
class Collider
{
public:

	//variables to pass in for the collision check
	glm::vec3 position;

	float size;
	float radius;
	float sizeX;
	float sizeY;
	float sizeZ;

	float width;
	float height;
	float lenght;

	Collider();

	//Cube
	Collider(float _size, glm::vec3 _position);
	//Sphere
	//Collider(float _radius, glm::vec3 _position);
	//AABB
	Collider(float _size, float _sizeX, float _sizeY, float _sizeZ, glm::vec3 _position);

	~Collider();

};