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
#include "Rigid_Body.h"
#include "RB_Cube.h"

using namespace std;

// -- Camera variables --
float camX = 0.0f;
float camY = 0.0f;
float camZ = 5.0f;
float camZTest= 0.0f;

// -- global variables --
vector<GameObject*> objects;
vector<glm::vec3> startPos;
int oldTimeSinceStart;
int newTimeSinceStart;

// Initialization
void setup(void)
{

	std::cout << "START BY PRESSING R " <<std::endl 
		<< "----------------------" << std::endl
		<<"MOVE RIGHT - -> (Right Arrow)" << std::endl 
		<< "MOVE LEFT - <-(Left Arrow)" << std::endl 
		<< "PUSH 1 TIME WITH FORCE - G"<< std::endl 
		<< "PUSH FORWARD - F" << std::endl 
		<< "JUMP - Space" << std::endl 
		<< "RESET - R " << std::endl 
		<< "GUTTER ON - C " << std::endl 
		<< "GUTTER OFF - X "<<std::endl 
		<< std::endl 
		<< "Good luck to hit the pins at the end of the lane";


	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* Create the objects needed */

	// Sphere objects -- Constructor - position, color, radius, moveSpeed, mass
	GameObject* sphere1 = new Sphere(glm::vec3(0, 10, 0), glm::vec3(0, 1, 1), 0.5f, 100.0f, 2.0f);

	// Cube objects-- Constructor - position, color, size, mass
	GameObject* cube1 = new Cube(glm::vec3(-1, -0.6, -10), glm::vec3(1, 0, 0), 0.3f, 1.0f);
	GameObject* cube2 = new Cube(glm::vec3(0, -0.6, -15), glm::vec3(1, 0, 0), 0.3f, 1.0f);
	GameObject* cube3 = new Cube(glm::vec3(1, -0.6, -20), glm::vec3(1, 0, 0), 0.3f, 1.0f);
	GameObject* cube4 = new Cube(glm::vec3(-1, -0.6, -25), glm::vec3(1, 0, 0), 0.3f, 1.0f);
	GameObject* cube5 = new Cube(glm::vec3(-1, -0.4, -30), glm::vec3(1, 0, 0), 0.8f, 1.0f);
	GameObject* cube6 = new Cube(glm::vec3(0, -0.7, -35), glm::vec3(1, 0, 0), 0.3f, 1.0f);
	GameObject* cube7 = new Cube(glm::vec3(1, -0.4, -40), glm::vec3(1, 0, 0), 0.8f, 1.0f);
	GameObject* cube8 = new Cube(glm::vec3(-1, -0.4, -45), glm::vec3(1, 0, 0), 0.8f, 1.0f);

	// Pin objects -- Constructor - position, color, size, sizeX, sizeY, sizeZ, moveSpeed, mass
	GameObject* pin1 = new Pin(glm::vec3(0, -0.5, -50), glm::vec3(1, 0, 1), 0.5f, 0.7f, 1.5f, 0.7f, 10.0f, 2.2f);
	GameObject* pin2 = new Pin(glm::vec3(0.3, -0.5, -51), glm::vec3(1, 0, 1), 0.5f, 0.7f, 1.5f, 0.7f, 10.0f, 2.2f);
	GameObject* pin3 = new Pin(glm::vec3(-0.3, -0.5, -51), glm::vec3(1, 0, 1), 0.5f, 0.7f, 1.5f, 0.7f, 10.0f, 2.2f);
	GameObject* pin4 = new Pin(glm::vec3(-0.6, -0.5, -52), glm::vec3(1, 0, 1), 0.5f, 0.7f, 1.5f, 0.7f, 10.0f, 2.2f);
	GameObject* pin5 = new Pin(glm::vec3(0.6, -0.5, -52), glm::vec3(1, 0, 1), 0.5f, 0.7f, 1.5f, 0.7f, 10.0f, 2.2f);

	//Bowling Lane -- Constructor - position, color, size
	GameObject* bowling_lane = new Bowling_Lane(glm::vec3(0, -1, -40), glm::vec3(0, 1, 0), 0.2f, 30.0f, 1.0f, 500.0f, 50.0f);

	// Gutter -- Constructor - position, color, size, sizeX, sizeY, sizeZ, mass
	GameObject* gutter1 = new Gutter(glm::vec3(1.3, 0.0, -40), glm::vec3(1, 1, 1), 1.0f, 0.2, 1.5, 100.0f, 100.1f);
	GameObject* gutter2 = new Gutter(glm::vec3(-1.3, 0.0, -40), glm::vec3(1, 1, 1), 1.0f, 0.2, 1.5, 100.0f, 100.1f);


	/* Add the objects to the vector*/

	//Sphere --
	objects.push_back(sphere1);

	//Cube --
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

	//Pins --
	objects.push_back(pin1);
	objects.push_back(pin2);
	objects.push_back(pin3);
	objects.push_back(pin4);
	objects.push_back(pin5);

	//Gutter --
	objects.push_back(gutter1);
	objects.push_back(gutter2);


	/* Add the first positions of the Pins to be used for Reset */

	//Loop the from first to last object
	for (int i = 0; i < objects.size(); ++i)
	{

		// If the object is Pin 
		if (dynamic_cast<Pin*>(objects[i]))
		{

			// Tahe his position and add it to the Vector
			startPos.push_back(dynamic_cast<Pin*>(objects[i])->position);
			
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

	/* Camera used to follow the player on Z axis*/
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

/* -- Camera movement --*/

/// <summary>
/// The camera is following the Z axis of the Sphere with a little offset
/// </summary>
void CameraMovement()
{
	camZ = objects[0]->position.z + 3;
	camZTest = camZ -3;

}

/// <summary>
/// Vector3.Zero
/// </summary>
glm::vec3 vec0(0, 0, 0);


/* -- Restart the game --*/

/// <summary>
/// By pressing R key, the position & velocity of the PINS and SPHERE is reseted
/// </summary>
void ResetGame()
{

	// If R key is pressed
	if (GameObject::keys['r'] == true)
	{
		// restart J
		int j = -1;

		// Loop the objects
		for (int i = 0; i < objects.size(); ++i)
		{
			
			// If the object is Pin
			if (dynamic_cast<Pin*>(objects[i]))
			{
				//Reset his position and velocity
				j++;
				dynamic_cast<Pin*>(objects[i])->position = startPos[j];
				dynamic_cast<Pin*>(objects[i])->velocity = vec0;
				
			}

			// If the object is Sphere
			if (dynamic_cast<Sphere*>(objects[i]))
			{

				// Reset his position and velocity
				dynamic_cast<Sphere*>(objects[i])->position = vec0;
				dynamic_cast<Sphere*>(objects[i])->velocity = vec0;

			}

		}

	}

}

/* -- Objects are sent to Collide Check--*/

/// <summary>
/// Objects are choosen and sent to their specific Collide Check 
/// </summary>
void Objects_Passed_To_CollideCheck()
{
	// Instantiate the class Collision_calculations
	Collision_Calculations Collision;

	/* -- Every object will "try" to check the collision with every other object --*/ 

	// Loop the objects 
	for (int i = 0; i < objects.size(); i++)
	{
		// Check the i object with the rest of the objects
		for (int j = 0; j < objects.size(); j++)
		{
			// the object will not check with itself
			if (i != j)
			{
				//Check if the 1st object is Sphere and 2nd object is Bowling Lane
				if (dynamic_cast<Sphere*>(objects[i]) && dynamic_cast<Bowling_Lane*>(objects[j]))
				{
					// Add them to Sphere_AABB Check Collision
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

				/* -- Interactions of Pin-Gutter & Pin-Sphere --*/

				// They will activate one the Sphere will reach a certain point on the Z axis
				// This is made not to check all the time all the objects 
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

	/* -- Custon Funtions --*/

	Objects_Passed_To_CollideCheck();
	CameraMovement();
	ResetGame();

	/* ------------------- */

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
	glutInitWindowPosition(500, 100);
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