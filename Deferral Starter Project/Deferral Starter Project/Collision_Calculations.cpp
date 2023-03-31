#include "Collision_Calculations.h"
#include <iostream>

Collision_Calculations::Collision_Calculations()
{

}

//AABB collision checking and response
void Collision_Calculations::AABB_AABB(GameObject* a, GameObject* b)
{
	//cube - cube

	//getting variables from gameobjects
	Collider* c = a->GetCollider();
	Collider* d = b->GetCollider();


	//c->position = a->position;
	//d->position = b->position;

	//restitusion for impulse calculation
	float restitution = 0.01f;

	//calculating normal
	glm::vec3 Normal = (c->position - d->position);
	glm::vec3 CollisionNormal = glm::normalize(Normal);

	//x axis colission
	bool collisionX = c->position.x + (c->sizeX /2 ) >= d->position.x - (d->sizeX /2) && d->position.x + (d->sizeX / 2) >= c->position.x - (c->sizeX /2);
	//y axis colission
	bool collisionY = c->position.y + (c->sizeY / 2) >= d->position.y - (d->sizeY / 2) && d->position.y + (d->sizeY / 2) >= c->position.y - (c->sizeY / 2);
	//z axis colission
	bool collisionZ = c->position.z + (c->sizeZ / 2) >= d->position.z - (d->sizeZ / 2) && d->position.z + (d->sizeZ / 2) >= c->position.z - (c->sizeZ / 2);




	//checking if all axis collide
	if (collisionX && collisionY && collisionZ)
	{
		b->colour = glm::vec3(1, 0, 0);

	}
	else
	{
		b->colour = glm::vec3(0, 1, 1);
		return;
	}
}

Collision_Calculations::~Collision_Calculations()
{

}

//Collision detection + response between sphere objects
void Collision_Calculations::Sphere_Sphere(GameObject* a, GameObject* b)
{
	//getting variables from gameobjects
	Collider* c = a->GetCollider();
	Collider* d = b->GetCollider();

	//restitusion for impulse calculation
	float restitution = 0.5f;

	//calculating normal
	glm::vec3 Normal = (d->position - c->position);
	glm::vec3 CollisionNormal = glm::normalize(Normal);

	//Checking if sphere distance between each other is smaller than both radii, if yes, collision detected
	if (pow(c->position.x - d->position.x, 2) + pow(c->position.y - d->position.y, 2) + pow(c->position.z - d->position.z, 2) <= pow(d->radius + d->radius, 2))
	{

		b->colour = glm::vec3(1, 0, 0);

	
	}
	else
	{
		b->colour = glm::vec3(0, 1, 1);
		return;
	}
}


void Collision_Calculations::Sphere_AABB(GameObject* a, GameObject* b)
{

	//getting variables from gameobjects
	Collider* c = a->GetCollider();
	Collider* d = b->GetCollider();


	float closest_x = std::fmax(d->position.x - (d->sizeX / 2), std::fmin(c->position.x, d->position.x + (d->sizeX / 2)));
	float closest_y = std::fmax(d->position.y - (d->sizeY / 2), std::fmin(c->position.y, d->position.y + (d->sizeY / 2)));
	float closest_z = std::fmax(d->position.z - (d->sizeZ / 2), std::fmin(c->position.z, d->position.z + (d->sizeZ / 2)));

	// Calculate the distance between the closest point and the center of the sphere
	float distance = std::sqrt(std::pow(closest_x - c->position.x, 2) + std::pow(closest_y - c->position.y, 2) + std::pow(closest_z - c->position.z, 2));

	// Check if the distance is less than or equal to the radius of the sphere
	if (distance <= c->radius)
	{
		a->colour = glm::vec3(1, 0, 0);
		if (static_cast<Sphere*>(a) && static_cast<Cube*>(b))
		{
			std::cout << " SPHERE - CUBE" << std::endl;
		}
		if (static_cast<Sphere*>(a) && static_cast<Bowling_Lane*>(b))
		{
			std::cout << " SPHERE - BOWLING_LANE" << std::endl;
		}
	}
	else
	{
		a->colour = glm::vec3(0, 1, 1);
		return;
	}

}

void Collision_Calculations::AABB_Sphere(GameObject* a, GameObject* b)
{

	//getting variables from gameobjects
	Collider* c = a->GetCollider();
	Collider* d = b->GetCollider();

	//restitusion for impulse calculation
	float restitution = 0.5f;

	//calculating normal
	glm::vec3 Normal = (d->position - c->position);
	glm::vec3 CollisionNormal = glm::normalize(Normal);


	float closest_x = std::fmax(c->position.x - (c->sizeX / 2), std::fmin(d->position.x, c->position.x + (c->sizeX / 2)));
	float closest_y = std::fmax(c->position.y - (c->sizeY / 2), std::fmin(d->position.y, c->position.y + (c->sizeY / 2)));
	float closest_z = std::fmax(c->position.z - (c->sizeZ / 2), std::fmin(d->position.z, c->position.z + (c->sizeZ / 2)));

	// Calculate the distance between the closest point and the center of the sphere
	float distance = std::sqrt(std::pow(closest_x - d->position.x, 2) + std::pow(closest_y - d->position.y, 2) + std::pow(closest_z - d->position.z, 2));

	// Check if the distance is less than or equal to the radius of the sphere
	if (distance <= d->radius)
	{
		b->colour = glm::vec3(1, 0, 0);
		if (static_cast<Cube*>(a) && static_cast<Sphere*>(b))
		{
			std::cout << " CUBE - SPHERE" << "  closest:" << c->sizeX << " " << c->sizeY << " " << c->sizeZ << std::endl;
			
		}
		if (static_cast<Bowling_Lane*>(a) && static_cast<Sphere*>(b))
		{
			std::cout << " BOWLING_LANE - SPHERE" << "  closest:" << c->sizeX << " " << c->sizeY << " " << c->sizeZ << std::endl;

		}
	}
	else
	{
		b->colour = glm::vec3(0, 1, 1);
		return;
	}

}


