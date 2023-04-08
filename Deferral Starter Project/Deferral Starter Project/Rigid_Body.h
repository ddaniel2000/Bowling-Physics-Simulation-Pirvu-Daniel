#pragma once
#include "GameObject.h"
#include "Collider.h"

class Rigid_Body : public GameObject
{
public:
	
	float mass;
	Collider* collider;


	/* -- Rotational motion -- */
	glm::vec3 orientation;
	glm::vec3 Angulat_Velocity;
	glm::vec3 Angular_Acceleration;
	glm::vec3 torque;
	glm::mat3 Matrix = glm::mat3(1.0f);


	/* -- Linear motion -- */
	glm::vec3 linearVelocity;
	glm::vec3 linearAcceleration;
	glm::vec3 forceValue;
	glm::vec3 forcePosition;

	Rigid_Body();
	Rigid_Body(glm::vec3 _position, glm::vec3 _colour, float _mass);


	virtual void Update(float deltaTime);
	virtual void Draw() = 0;

};

