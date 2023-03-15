#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <map>
#include "glm/glm.hpp"

//A basic abstract class that all game objects in the scene are based off
// abstract = We never will make a direct instance of GameObject but will make classes inherit from it
class GameObject
{
public:
	// -- variables --
	glm::vec3 position;
	glm::vec3 colour;

	static std::map<char, bool> keys; //save key presses and let game objects access them
	static std::map<int, bool> specialKeys; //static = one instance of these variables for the whole class (top of .cpp)

	// -- constructors/destructors --
	GameObject(); //default constructor - aka no values passed in (position at 0,0,0 - colour magenta)
	GameObject(glm::vec3 pos); //pass in a position (no colour passed in so defaults to white)
	GameObject(glm::vec3 pos, glm::vec3 col); //pass in a position, colour
	~GameObject(); //default destructor

	// -- functions -- 
	//pure virtual so all classes that derive from this one need to include a definion for these
	virtual void Draw() = 0; 
	virtual void Update(float deltaTime) = 0;
};