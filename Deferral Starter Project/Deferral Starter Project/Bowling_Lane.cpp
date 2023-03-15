#include "Bowling_Lane.h"

//We can either hard code the values in GameObject (like in Cube())
//or
//We can use the GameEngine constructors to fill the values ( like in Cube(x, y, z, size))
Bowling_Lane::Bowling_Lane() : GameObject()
{
	size = 1.0f;

}

Bowling_Lane::Bowling_Lane(glm::vec3 pos, float _size)
	:GameObject(pos) //note the use of GameObject constructor
{
	size = _size;
}

Bowling_Lane::Bowling_Lane(glm::vec3 pos, glm::vec3 col, float _size) :
	GameObject(pos, col) //note the use of GameObject constructor
{
	size = _size;
}



//Position and colour a cube in the scene
void Bowling_Lane::Draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(colour.r, colour.g, colour.b);
	//glRotatef(45, 1.0f, 2, 0);
	glScalef(20, 1, 100);
	glutSolidCube(size);
	//glutWireCube(size); //- if you'd rather see through it
	glPopMatrix();
}

void Bowling_Lane::Update(float deltaTime)
{
	//Cubes are static at the moment so nothing changes for them

}
