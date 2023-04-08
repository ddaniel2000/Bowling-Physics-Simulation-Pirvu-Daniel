#pragma once
#include "Rigid_Body.h"

class RB_Cube : public Rigid_Body
{
public:
	
	float size;		
	float sizeX;	
	float sizeY;
	float sizeZ;
	RB_Cube();  //Constuctor for cube
	RB_Cube(glm::vec3 _position, glm::vec3 _colour, float _size, float _mass );  //Constuctor for cube
	RB_Cube(glm::vec3 _position, glm::vec3 _colour, float _mass, float _size, float _sizeX, float _sizeY, float _sizeZ); // Constructor or sized cube
	~RB_Cube() {}; //default destructor

	virtual void Draw();
	virtual void Update(float deltaTime);
};

