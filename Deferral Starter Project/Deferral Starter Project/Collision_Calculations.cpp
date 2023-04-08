#include "Collision_Calculations.h"
#include <iostream>

Collision_Calculations::Collision_Calculations()
{

}

Collision_Calculations::~Collision_Calculations()
{

}

/* -- Collision Check for AABB - AABB --*/

/// <summary>
/// 
/// The AABB-AABB check collision
/// 
/// </summary>
/// <param name="AABB"></param>
/// <param name="AABB"></param>
void Collision_Calculations::AABB_AABB(GameObject* a, GameObject* b)
{

	// Adding variables from gameobjects
	Collider* d = a->GetCollider();
	Collider* c = b->GetCollider();

	// X axis colission
	bool collisionX = c->position.x + (c->sizeX / 2) >= d->position.x - (d->sizeX / 2) && d->position.x + (d->sizeX / 2) >= c->position.x - (c->sizeX / 2);
	// Y axis colission
	bool collisionY = c->position.y + (c->sizeY / 2) >= d->position.y - (d->sizeY / 2) && d->position.y + (d->sizeY / 2) >= c->position.y - (c->sizeY / 2);
	// Z axis colission
	bool collisionZ = c->position.z + (c->sizeZ / 2) >= d->position.z - (d->sizeZ / 2) && d->position.z + (d->sizeZ / 2) >= c->position.z - (c->sizeZ / 2);

	// Calculating Normal between the objects
	glm::vec3 Normal = (d->position - c->position);
	glm::vec3 CollisionNormal = glm::normalize(Normal);

	// Restitusion for impulse calculation
	// "Bouncyness" between collisions
	float restitution = 0.2f;

	// Calculate distance between objects
	float distance = glm::dot(d->position, c->position);

	// Checking if all axis collide
	if (collisionX && collisionY && collisionZ)
	{

		if (dynamic_cast<Pin*>(a) && dynamic_cast<Bowling_Lane*>(b))
		{

			dynamic_cast<Pin*>(a)->velocity.y = !dynamic_cast<Pin*>(a)->gravity.y;

		}

		/// <summary>
		/// The PINS will bounce of the GUTTERS by using an impulse and mass on velocity.x
		/// </summary>
		/// <Pin="a"></param>
		/// <Gutter="b"></param>
		if (dynamic_cast<Pin*>(a) && dynamic_cast<Gutter*>(b))
		{
			float impulse = 0.8;
			if (dynamic_cast<Gutter*>(b) && b->position.x > 1)
			{

				dynamic_cast<Pin*>(a)->velocity.x -= impulse * dynamic_cast<Pin*>(a)->mass;
				
			}
			if (dynamic_cast<Gutter*>(b) && b->position.x < 1)
			{

				dynamic_cast<Pin*>(a)->velocity.x += impulse * dynamic_cast<Pin*>(a)->mass;
				
			}

		}

		/// <summary>
		/// 
		/// The Pins will interact with each other by using a relative Velocity (substracting velocityies) & Impulse
		/// The restitutuin is the coeficient of bouncyness
		/// 
		/// </summary>
		/// <param name="Pin"></param>
		/// <param name="Pin"></param>
		if (dynamic_cast<Pin*>(a) && dynamic_cast<Pin*>(b))
		{

			glm::vec3 relativeVelocity = dynamic_cast<Pin*>(a)->velocity - dynamic_cast<Pin*>(b)->velocity;
			float impulseScalar = -(1 + restitution) * glm::dot(relativeVelocity, CollisionNormal) / ((1 / dynamic_cast<Pin*>(a)->mass) + (1 / dynamic_cast<Pin*>(b)->mass));


			dynamic_cast<Pin*>(b)->velocity = relativeVelocity - impulseScalar / 2 / dynamic_cast<Pin*>(a)->mass * CollisionNormal;
		}
	}
	else
	{

		return;
	}
}

/* -- Collision Check for SPHERE - AABB --*/

/// <summary>
/// 
/// </summary>
/// <param name="Sphere"></param>
/// <param name="AABB"></param>
void Collision_Calculations::Sphere_AABB(GameObject* a, GameObject* b)
{

	//getting variables from gameobjects
	Collider* c = a->GetCollider();
	Collider* d = b->GetCollider();


	float closest_x = std::fmax(d->position.x - (d->sizeX / 2), std::fmin(c->position.x, d->position.x + (d->sizeX / 2)));
	float closest_y = std::fmax(d->position.y - (d->sizeY / 2), std::fmin(c->position.y, d->position.y + (d->sizeY / 2)));
	float closest_z = std::fmax(d->position.z - (d->sizeZ / 2), std::fmin(c->position.z, d->position.z + (d->sizeZ / 2)));

	glm::vec3 closestPoint(closest_x, closest_y, closest_z);

	// Calculate the distance between the closest point and the center of the sphere
	float distance = std::sqrt(std::pow(closest_x - c->position.x, 2) + std::pow(closest_y - c->position.y, 2) + std::pow(closest_z - c->position.z, 2));

	glm::vec3 Normal = (closestPoint - c->position);
	glm::vec3 CollisionNormal = glm::normalize(Normal);

	//restitusion for impulse calculation
	float restitution = 0.3f;

	// Check if the distance is less than or equal to the radius of the sphere
	if (distance <= c->radius)
	{
		// If Sphere & Cube collide
		if (dynamic_cast<Sphere*>(a) && dynamic_cast<Cube*>(b))
		{

			/// <summary>
			/// 
			/// The SPHERE collide with any of the CUBES
			/// The SPHERE position is set to 0, 0, 0
			/// The SPHERE velocity on z axis is 0
			/// 
			/// </summary>
			/// <Sphere->position="a"></param>
			/// <Sphere->velocity="b"></param>
			a->position = glm::vec3(0, 0, 0);
			dynamic_cast<Sphere*>(a)->velocity.z = 0;
			
		}

		/// <summary>
		/// 
		/// The SPHERE will stay on the BOWLING LANE by reversing the velocity
		/// 
		/// The SPHERE can JUMP by pressing "Space" using an impulse that modify the velocity on y axis
		/// 
		/// </summary>
		/// <SPhere ="a"></param>
		/// <Bowling_Ball ="b"></param>
		if (dynamic_cast<Sphere*>(a) && dynamic_cast<Bowling_Lane*>(b))
		{
			float impulse = 0.5;
			// Press Space
			if (GameObject::keys[32] == true)
			{
				// Jump by adding to Velocity on Y axis
				dynamic_cast<Sphere*>(a)->velocity.y += impulse * dynamic_cast<Sphere*>(a)->mass;

			}
			else
			{

				// Push the Sphere back up 
				dynamic_cast<Sphere*>(a)->velocity.y -= dynamic_cast<Sphere*>(a)->velocity.y;

			}

		}

		/// <summary>
		/// 
		///	Bouce the Sphere of the Gutters
		/// 
		/// </summary>
		/// <Sphere="a"></param>
		/// <Gatter="b"></param>
		if (dynamic_cast<Sphere*>(a) && dynamic_cast<Gutter*>(b))
		{

			//// RelativeVelocity between objects
			glm::vec3 relativeVelocity = dynamic_cast<Gutter*>(b)->velocity - dynamic_cast<Sphere*>(a)->velocity ;

			// Scaling Impulse
			float impulseScalar = glm::dot(relativeVelocity, CollisionNormal) + ((1 / dynamic_cast<Sphere*>(a)->mass) + (1 / dynamic_cast<Gutter*>(b)->mass));

			// Push the sphere back from where it comes
			dynamic_cast<Sphere*>(a)->velocity.x += relativeVelocity.x - impulseScalar / dynamic_cast<Sphere*>(a)->mass * -dynamic_cast<Sphere*>(a)->velocity.x;
			
			if (dynamic_cast<Gutter*>(b)->position.x > 1)
			{

				dynamic_cast<Sphere*>(a)->velocity.x = -dynamic_cast<Sphere*>(a)->velocity.x - 1;

			}
			else
			{

				dynamic_cast<Sphere*>(a)->velocity.x = -dynamic_cast<Sphere*>(a)->velocity.x + 1;

			}
		}

		if (dynamic_cast<Sphere*>(a) && dynamic_cast<Pin*>(b))
		{
			// RelativeVelocity between objects
			glm::vec3 relativeVelocity = dynamic_cast<Sphere*>(a)->velocity - dynamic_cast<Pin*>(b)->velocity;

			// Impulse Scalar
			float impulseScalar = -(1 + restitution) * glm::dot(relativeVelocity, CollisionNormal) / ((1 / dynamic_cast<Sphere*>(a)->mass) + (1 / dynamic_cast<Pin*>(b)->mass));

			// Push the Pin from the Sphere
			dynamic_cast<Pin*>(b)->velocity = relativeVelocity - impulseScalar / dynamic_cast<Sphere*>(a)->mass * CollisionNormal;

			// Push the Sphere from the Pin
			//dynamic_cast<Sphere*>(a)->velocity = relativeVelocity - impulseScalar / dynamic_cast<Pin*>(b)->mass * CollisionNormal;

		}

	}
	else
	{

		return;

	}

}

/* -- Collision Check for AABB - SPHERE --*/

/// <summary>
/// 
/// The AABB-Sphere collision check
/// 
/// </summary>
/// <param name="AABB"></param>
/// <param name="Sphere"></param>
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
	
		return;
		
	}

}

/* -- Collision Check for SPHERE - SPHERE --*/

/// <summary>
/// 
/// The Sphere-Sphere collision check
/// 
/// </summary>
/// <param name="Sphere"></param>
/// <param name="Sphere"></param>
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

