#include "GameObject.h"

std::map<char, bool> GameObject::keys;
std::map<int, bool> GameObject::specialKeys;

GameObject::GameObject()
{
	position = glm::vec3(0, 0, 0);

	colour = glm::vec3(1, 0, 1);
}

GameObject::GameObject(glm::vec3 pos)
{
	position = pos;
	colour = glm::vec3(1, 1, 1);
}

GameObject::GameObject(glm::vec3 pos, glm::vec3 col)
{
	position = pos;
	colour = col;
}

GameObject::~GameObject()
{
}
