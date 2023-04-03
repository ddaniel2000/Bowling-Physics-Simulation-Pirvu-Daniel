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

	//x axis colission
	bool collisionX = c->position.x + (c->sizeX /2 ) >= d->position.x - (d->sizeX /2) && d->position.x + (d->sizeX / 2) >= c->position.x - (c->sizeX /2);
	//y axis colission
	bool collisionY = c->position.y + (c->sizeY / 2) >= d->position.y - (d->sizeY / 2) && d->position.y + (d->sizeY / 2) >= c->position.y - (c->sizeY / 2);
	//z axis colission
	bool collisionZ = c->position.z + (c->sizeZ / 2) >= d->position.z - (d->sizeZ / 2) && d->position.z + (d->sizeZ / 2) >= c->position.z - (c->sizeZ / 2);


	//checking if all axis collide
	if (collisionX && collisionY && collisionZ)
	{
		
		if (dynamic_cast<Pin*>(a) && dynamic_cast<Bowling_Lane*>(b))
		{
			dynamic_cast<Pin*>(a)->velocity.y -= dynamic_cast<Pin*>(a)->velocity.y - dynamic_cast<Pin*>(a)->gravity.y;
		}

		if (dynamic_cast<Pin*>(a) && dynamic_cast<Gutter*>(b))
		{
			if (dynamic_cast<Gutter*>(b) && b->position.x > 1)
			{
				dynamic_cast<Pin*>(a)->velocity.x -= (dynamic_cast<Pin*>(a)->velocity.x) + 1;
				std::cout << " Pin - Gutter-Dreapta" << std::endl;
			}
			if (dynamic_cast<Gutter*>(b) && b->position.x < 1)
			{
				dynamic_cast<Pin*>(a)->velocity.x += (dynamic_cast<Pin*>(a)->velocity.x) + 1;
				std::cout << " Pin - Gutter-Stanga" << std::endl;
			}
		}
	}
	else
	{
		
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


	glm::vec3 Normal = (d->position - c->position);
	glm::vec3 CollisionNormal = glm::normalize(Normal);

	//restitusion for impulse calculation
	float restitution = 0.5f;
	// Check if the distance is less than or equal to the radius of the sphere
	if (distance <= c->radius)
	{
		
		if (dynamic_cast<Sphere*>(a) && dynamic_cast<Cube*>(b))
		{
			
			//if the sphere collide with any of the cubes
			//The sphere position is set to 0,0,0
			//The velocity on z axis is 0
			a->position = glm::vec3(0, 0, 0);
			dynamic_cast<Sphere*>(a)->velocity.z = 0;
			//std::cout << " SPHERE - Cube" << std::endl;
		}
		if (dynamic_cast<Sphere*>(a) && dynamic_cast<Bowling_Lane*>(b))
		{
			
			//std::cout << " SPHERE - BOWLING_LANE" << std::endl;
			if (GameObject::keys[32] == true)
			{
				dynamic_cast<Sphere*>(a)->totalForce.y += 500;
			}
			//push the sphere back up 
			dynamic_cast<Sphere*>(a)->velocity.y -= dynamic_cast<Sphere*>(a)->velocity.y - dynamic_cast<Sphere*>(a)->gravity.y;
		}
		if (dynamic_cast<Sphere*>(a) && dynamic_cast<Gutter*>(b))
		{
			
			//std::cout << " SPHERE - GUTTER" << std::endl;

			//push the sphere back up 
			if (dynamic_cast<Gutter*>(b) && b->position.x > 1)
			{
				dynamic_cast<Sphere*>(a)->velocity.x -= (dynamic_cast<Sphere*>(a)->velocity.x) + 2;
				std::cout << " SPHERE - Gutter-Dreapta" << std::endl;
			}
			if (dynamic_cast<Gutter*>(b) && b->position.x < 1)
			{
				dynamic_cast<Sphere*>(a)->velocity.x += (dynamic_cast<Sphere*>(a)->velocity.x) + 2;
				std::cout << " SPHERE - Gutter-Stanga" << std::endl;
			}
		}
		if (dynamic_cast<Sphere*>(a) && dynamic_cast<Pin*>(b))
		{
			
			//When the ball z coordinate is < than -40, then it will start the calculations for this response
			if (dynamic_cast<Sphere*>(a)->position.z < -40)
			{
				glm::vec3 relativeVelocity = dynamic_cast<Sphere*>(a)->velocity - dynamic_cast<Pin*>(b)->velocity;
				float impulseScalar = -(1 + restitution) * glm::dot(relativeVelocity, CollisionNormal) / ((1 / dynamic_cast<Sphere*>(a)->mass) + (1 / dynamic_cast<Pin*>(b)->mass));
				std::cout << " Pin - Sphere" << std::endl;


				dynamic_cast<Pin*>(b)->velocity = relativeVelocity - impulseScalar / dynamic_cast<Pin*>(b)->mass * CollisionNormal;

			}
		}
		//b->colour = glm::vec3(1, 0, 0);

	}
	else
	{

		return;
	}

}

void Collision_Calculations::AABB_Sphere(GameObject* a, GameObject* b)
{

	//getting variables from gameobjects
	Collider* c = a->GetCollider();
	Collider* d = b->GetCollider();

	float closest_x = std::fmax(c->position.x - (c->sizeX / 2), std::fmin(d->position.x, c->position.x + (c->sizeX / 2)));
	float closest_y = std::fmax(c->position.y - (c->sizeY / 2), std::fmin(d->position.y, c->position.y + (c->sizeY / 2)));
	float closest_z = std::fmax(c->position.z - (c->sizeZ / 2), std::fmin(d->position.z, c->position.z + (c->sizeZ / 2)));

	// Calculate the distance between the closest point and the center of the sphere
	float distance = std::sqrt(std::pow(closest_x - d->position.x, 2) + std::pow(closest_y - d->position.y, 2) + std::pow(closest_z - d->position.z, 2));

	// Check if the distance is less than or equal to the radius of the sphere
	if (distance <= d->radius)
	{

	}
	else
	{
		//b->colour = glm::vec3(0, 1, 1);
		return;
	}

}


