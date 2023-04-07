#include <GL/glew.h>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 

#include <iostream>
#include <vector>

#include "Cube.h"
#include "Sphere.h"
#include "Bowling_Lane.h"
#include "Gutter.h"
#include "Pin.h"

#include "Collider.h"
#include "Sphere_Collider.h"
#include "AABB_Collider.h"
#include "Collision_Calculations.h"

using namespace std;

float camX = 0.0f;
float camY = 0.0f;
float camZ = 5.0f;
float camZTest= 0.0f;

int mouseX;
int mouseY;

// -- global variables --
vector<GameObject*> objects;
vector<glm::vec3> startPos;
int oldTimeSinceStart;
int newTimeSinceStart;

// Initialization
void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//Create objects and place them in the objects vector
	//If they aren't in the objects vector, they will not be drawn / updated!

	GameObject* sphere1 = new Sphere(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1), 0.5f, 250.0f, 5.0f);
	GameObject* cube1 = new Cube(glm::vec3(-1, -0.6, -10), glm::vec3(1, 0, 0), 0.3f);
	GameObject* cube2 = new Cube(glm::vec3(0, -0.6, -15), glm::vec3(1, 0, 0), 0.3f);
	GameObject* cube3 = new Cube(glm::vec3(1, -0.6, -20), glm::vec3(1, 0, 0), 0.3f);
	GameObject* cube4 = new Cube(glm::vec3(-1, -0.6, -25), glm::vec3(1, 0, 0), 0.3f);
	GameObject* cube5 = new Cube(glm::vec3(-1, -0.4, -30), glm::vec3(1, 0, 0), 0.8f);
	GameObject* cube6 = new Cube(glm::vec3(0, -0.7, -35), glm::vec3(1, 0, 0), 0.3f);
	GameObject* cube7 = new Cube(glm::vec3(1, -0.4, -40), glm::vec3(1, 0, 0), 0.8f);
	GameObject* cube8 = new Cube(glm::vec3(-1, -0.4, -45), glm::vec3(1, 0, 0), 0.8f);

	GameObject* pin1 = new Pin(glm::vec3(0, -0.5, -50), glm::vec3(1, 0, 1), 0.5f, 0.7f, 1.5f, 0.7f, 10.0f, 2.0f);
	GameObject* pin2 = new Pin(glm::vec3(0.3, -0.5, -51), glm::vec3(1, 0, 1), 0.5f, 0.7f, 1.5f, 0.7f, 10.0f, 2.0f);
	GameObject* pin3 = new Pin(glm::vec3(-0.3, -0.5, -51), glm::vec3(1, 0, 1), 0.5f, 0.7f, 1.5f, 0.7f, 10.0f, 2.0f);
	GameObject* pin4 = new Pin(glm::vec3(-0.6, -0.5, -52), glm::vec3(1, 0, 1), 0.5f, 0.7f, 1.5f, 0.7f, 10.0f, 2.0f);
	GameObject* pin5 = new Pin(glm::vec3(0.6, -0.5, -52), glm::vec3(1, 0, 1), 0.5f, 0.7f, 1.5f, 0.7f, 10.0f, 2.0f);

	//Bowling Lane -- Constructor - position, color, size
	GameObject* bowling_lane = new Bowling_Lane(glm::vec3(0, -1, -40), glm::vec3(0, 1, 0), 0.2f, 30.0f, 1.0f, 500.0f);

	// Gutter -- Constructor - position, color, size
	GameObject* gutter1 = new Gutter(glm::vec3(1.3, 0.0, -40), glm::vec3(1, 1, 1), 1.0f, 0.2, 1.5, 100.0f);
	GameObject* gutter2 = new Gutter(glm::vec3(-1.3, 0.0, -40), glm::vec3(1, 1, 1), 1.0f, 0.2, 1.5, 100.0f);

	
	//constructor - position, colour, radius, moveSpeed
	objects.push_back(sphere1);

	objects.push_back(cube1);
	objects.push_back(cube2);
	objects.push_back(cube3);
	objects.push_back(cube4);
	objects.push_back(cube5);
	objects.push_back(cube6);
	objects.push_back(cube7);
	objects.push_back(cube8);
	
	//Bowling Lane ---
	objects.push_back(bowling_lane);
	objects.push_back(pin1);
	objects.push_back(pin2);
	objects.push_back(pin3);
	objects.push_back(pin4);
	objects.push_back(pin5);
	//Gutter --
	objects.push_back(gutter1);
	objects.push_back(gutter2);


	for (int i = 0; i < objects.size(); ++i)
	{
		if (dynamic_cast<Pin*>(objects[i]))
		{
			startPos.push_back(dynamic_cast<Pin*>(objects[i])->position);
			//std::cout << dynamic_cast<Pin*>(objects[i])->position.x << " " << dynamic_cast<Pin*>(objects[i])->position.y << " " << dynamic_cast<Pin*>(objects[i])->position.z << std::endl;
		}
	}
}

//Drawing aaaaaaaa
void drawScene()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();



	// Position the objects for viewing
	gluLookAt(
		0, 2, camZ, // - eye
		0, 0, camZTest,  // - center
		0.0, 1.0, 0.0); // - up

	//Draw all our game objects
	for (int i = 0; i < objects.size(); ++i)
	{

		objects[i]->Draw();
	}

	glutSwapBuffers();
}

void CameraMovement()
{
	camZ = objects[0]->position.z + 3;
	camZTest = camZ -3;
	// Move Camera
	//if (GameObject::keys['w'] == true)
	//{
	//	camZ -= 0.1f;
	//	camZTest -= 0.1f;
	//}
	//if (GameObject::keys['a'] == true)
	//{
	//	camX -= 0.1f;
	//}
	//if (GameObject::keys['s'] == true)
	//{
	//	camZ += 0.1f;
	//	camZTest += 0.1f;
	//}
	//if (GameObject::keys['d'] == true)
	//{
	//	camX += 0.1f;
	//}
	//if (GameObject::keys['q'] == true)
	//{
	//	camY += 0.1f;
	//}
	//if (GameObject::keys['e'] == true)
	//{
	//	camY -= 0.1f;
	//}
}


glm::vec3 vec0(0, 0, 0);
void ResetGame()
{
	if (GameObject::keys['r'] == true)
	{
		int j = -1;
		for (int i = 0; i < objects.size(); ++i)
		{
			
			if (dynamic_cast<Pin*>(objects[i]))
			{
				j++;
				dynamic_cast<Pin*>(objects[i])->position = startPos[j];
				dynamic_cast<Pin*>(objects[i])->velocity = vec0;
				//std::cout << j << std::endl;
			}
			if (dynamic_cast<Sphere*>(objects[i]))
			{
				dynamic_cast<Sphere*>(objects[i])->position = vec0;
				dynamic_cast<Sphere*>(objects[i])->velocity = vec0;
			}
		}

	}
}


void Objects_Passed_To_CollideCheck()
{
	Collision_Calculations Collision;
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects.size(); j++)
		{
			//if (objects[i] == dynamic_cast<Sphere*>(objects[i]))
			//{
			//	Collision.Sphere_AABB(objects[i], objects[j]);
			//	if (objects[i] == dynamic_cast<Sphere*>(objects[i]) && (objects[j] == dynamic_cast<Bowling_Lane*>(objects[j])))
			//	{
			//		std::cout << "Sphere-BowlingLane" << std::endl;
			//	}
			//	if (objects[i] == dynamic_cast<Sphere*>(objects[i]) && (objects[j] == dynamic_cast<Gutter*>(objects[j])))
			//	{
			//		std::cout << "Sphere-Gutter" << std::endl;
			//	}
			//	if (objects[i] == dynamic_cast<Sphere*>(objects[i]) && (objects[j] == dynamic_cast<Pin*>(objects[j])))
			//	{
			//		std::cout << "Sphere-Pin" << std::endl;
			//	}
			//}
			//else if (objects[i] == dynamic_cast<Sphere*>(objects[i]))
			//{
			//	Collision.AABB_AABB(objects[i], objects[j]);
			//	if (objects[i] == dynamic_cast<Pin*>(objects[i]) && (objects[j] == dynamic_cast<Bowling_Lane*>(objects[j])))
			//	{
			//		std::cout<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<std::endl;
			//	}

			//}
			if (i == j)
			{
				
			}
			else
			{
				if (dynamic_cast<Sphere*>(objects[i]) && dynamic_cast<Bowling_Lane*>(objects[j]))
				{
					Collision.Sphere_AABB(objects[i], objects[j]);
					
				}
				if (dynamic_cast<Sphere*>(objects[i]) && dynamic_cast<Cube*>(objects[j]))
				{
					Collision.Sphere_AABB(objects[i], objects[j]);
					
				}
				if (dynamic_cast<Sphere*>(objects[i]) && dynamic_cast<Gutter*>(objects[j]))
				{
					Collision.Sphere_AABB(objects[i], objects[j]);
					
				}
				if (dynamic_cast<Pin*>(objects[i]) && dynamic_cast<Bowling_Lane*>(objects[j]))
				{
					Collision.AABB_AABB(objects[i], objects[j]);
				
				}
				if (dynamic_cast<Sphere*>(objects[0])->position.z < -40)
				{
					if (dynamic_cast<Pin*>(objects[i]) && dynamic_cast<Gutter*>(objects[j]))
					{
						Collision.AABB_AABB(objects[i], objects[j]);
						
					}
					if (dynamic_cast<Sphere*>(objects[i]) && dynamic_cast<Pin*>(objects[j]))
					{
						Collision.Sphere_AABB(objects[i], objects[j]);
						
					}
					if (dynamic_cast<Pin*>(objects[i]) && dynamic_cast<Pin*>(objects[j]))
					{
						Collision.AABB_AABB(objects[i], objects[j]);
						
					}
				}
			}			
		}
	}

	
}

//Called when nothing else is happening (such as rendering)
void idle()
{
	//Work out the delta time - the time between the last frame and this frame
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	float deltaTime = (newTimeSinceStart - oldTimeSinceStart) / 1000.0f;

	Objects_Passed_To_CollideCheck();

	CameraMovement();
	ResetGame();

	//Update all our game objects
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Update(deltaTime);
	}
	glutPostRedisplay();
}


//Delete any memory gotten from the new keyword
//Is only called when the ESC key is used to leave the game
void CleanUp()
{
	for (int i = objects.size() - 1; i >= 0; --i)
	{
		delete objects[i];
	}
	objects.clear();
}



// Keyboard input processing functions 
void keyInputDown(unsigned char key, int x, int y)
{
	GameObject::keys[key] = true;

	switch (key)
	{
	case 27: // Esc key
		CleanUp();
		exit(0);
		break;
	default:
		break;
	}
}

void keyInputUp(unsigned char key, int x, int y)
{
	GameObject::keys[key] = false;

}

void keySpecialDown(int key, int x, int y)
{
	GameObject::specialKeys[key] = true;

}

void keySpecialUp(int key, int x, int y)
{
	GameObject::specialKeys[key] = false;

}


//OpenGL window reshape
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

//Entry point into the program
int main(int argc, char** argv)
{
	//Setup for legacy OpenGL usage
	glutInit(&argc, argv);
	glutInitContextVersion(2, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	//Window settings
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Basic Deferral Project");

	//Callbacks
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInputDown);
	glutKeyboardUpFunc(keyInputUp);
	glutSpecialFunc(keySpecialDown);
	glutSpecialUpFunc(keySpecialUp);
	glutIdleFunc(idle);


	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}