#include "Rigid_Body.h"

Rigid_Body::Rigid_Body()
{
	mass = 1;
}


Rigid_Body::Rigid_Body(glm::vec3 _position, glm::vec3 _colour, float _mass)
{
	mass = _mass;
}

void Rigid_Body::Update(float deltaTime)
{

	glm::vec3((position.x - forcePosition.x), (position.y - forcePosition.y), (position.z - forcePosition.z));

	/* --Linear Motion-- */
	linearAcceleration = forceValue / mass;
	linearVelocity = linearVelocity + linearAcceleration * deltaTime;
	position = position + linearVelocity * deltaTime;

	/* --Rotation Motion-- */
	Angular_Acceleration = glm::inverse(Matrix) * torque;
	Angulat_Velocity = Angulat_Velocity + Angular_Acceleration * deltaTime;
	orientation = orientation + Angulat_Velocity * deltaTime;

}


