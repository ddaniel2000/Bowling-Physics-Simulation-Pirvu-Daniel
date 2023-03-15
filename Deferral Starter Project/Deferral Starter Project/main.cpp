#include <GL/glew.h>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 

#include <iostream>
#include <vector>

#include "Cube.h"
#include "Sphere.h"
#include "Bowling_Lane.h"
#include "Gutter.h"


using namespace std;

float camX = 0.0f;
float camY = 0.0f;
float camZ = 5.0f;


/*
	MAKE SURE TO READ THE "HELPFUL DRAWING CODE.TXT" FILE AS PART OF THIS PROJECT TOO!
*/

// -- global variables --
vector<GameObject*> objects;
int oldTimeSinceStart;
int newTimeSinceStart;

// Initialization
void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//Create objects and place them in the objects vector
	//If they aren't in the objects vector, they will not be drawn / updated!

	//constructor - position and size only
	//GameObject* cube1 = new Cube(glm::vec3(5, 0, 0), 2); 
	//default constructor used
	//GameObject* cube2 = new Cube;
	//constructor - position, colour, size
	//GameObject* cube3 = new Cube(glm::vec3(2, 2, -2), glm::vec3(0, 1, 0), 0.5f); 	

	//Bowling Lane -- Constructor - position, color, size
	GameObject* bowling_lane = new Bowling_Lane(glm::vec3(0, -1, 0), glm::vec3(0, 1, 0), 0.2f);

	// Gutter -- Constructor - position, color, size
	GameObject* gutter1 = new Gutter(glm::vec3(1.3, -0.4, 0), glm::vec3(1, 1, 1), 1.0f);
	GameObject* gutter2 = new Gutter(glm::vec3(-1.3, -0.4, 0), glm::vec3(1, 1, 1), 1.0f);


	//constructor - position, colour, radius, moveSpeed
	GameObject* sphere1 = new Sphere(glm::vec3(-1, 0, -1), glm::vec3(0, 0, 1), 1.5f, 10.0f); 
	
	//Bowling Lane ---
	objects.push_back(bowling_lane);
	//Gutter --
	objects.push_back(gutter1);
	objects.push_back(gutter2);

	//objects.push_back(cube1);
	//objects.push_back(cube2);
	//objects.push_back(cube3);
	

	objects.push_back(sphere1);
}

//Drawing
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Position the objects for viewing
	gluLookAt(
		camX, camY, camZ, // - eye
		camX, camY, 0.0,  // - center
		0.0, 1.0, 0.0); // - up

	//Draw all our game objects
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Draw();
	}

	glutSwapBuffers();
}

//Called when nothing else is happening (such as rendering)
void idle()
{
	//Work out the delta time - the time between the last frame and this frame
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	float deltaTime = (newTimeSinceStart - oldTimeSinceStart) / 1000.0f;
	//cout << "Delta Time (seconds): " << deltaTime << endl; - if you want to check the delta time

	// Move Camera
	if (GameObject::keys['w'] == true)
	{
		camZ -= 0.1f;
	}
	if (GameObject::keys['a'] == true)
	{
		camX -= 0.1f;
	}
	if (GameObject::keys['s'] == true)
	{
		camZ += 0.1f;
	}
	if (GameObject::keys['d'] == true)
	{
		camX += 0.1f;
	}

	
	
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
	//If you want to see keys pressed printed to the console
	//std::cout << "Key pressed: " << key << std::endl;
	
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
	//If you want to see keys pressed printed to the console
	//std::cout << "Key lifted: " << key << std::endl;
}

void keySpecialDown(int key, int x, int y)
{
	GameObject::specialKeys[key] = true;
	//If you want to see keys pressed printed to the console
	//std::cout << "Special Key pressed: " << key << std::endl;
}

void keySpecialUp(int key, int x, int y)
{
	GameObject::specialKeys[key] = false;
	//If you want to see keys pressed printed to the console
	//std::cout << "Special Key lifted: " << key << std::endl;
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