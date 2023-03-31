#include "Different_Size_Cube_Collider.h"

Different_Size_Cube_Collider::Different_Size_Cube_Collider(float _size,float _sizeX, float _sizeY, float _sizeZ, glm::vec3 _position)
{
	size = _size;
	sizeX = _sizeX;
	sizeY = _sizeY;
	sizeZ = _sizeZ;
}



void Different_Size_Cube_Collider::Draw()
{
}



for (int i = 0, i <= 8; i++)  // 8 nr total de obiecte
{
	for (int j = 0; j <= 8; j++)
	{
		//daca tiggerul nu este actiavat
		// - Popicele stiu doar de Lane dar nu intre ele
		if (i == j)
		{

		}
		else
		{
			if (TRIGGER == false)
			{

				// Bila
				if (gameObect[i] == Bowling_Ball)
				{
					if (gameObject[j] == Popice)
					{
						Pass
					}
				}
				//Lane
				if (gameObect[i] == Bowling_Lane)
				{
					if (gameObject[j] == Gutter)
					{
						Pass
					}
				}

				//Gutter
				if (gameObect[i] == Gutter)
				{
					if (gameObject[j] == Popice || gameObject[j] == Gutter || gameObject[j] == Bowling_Lane)
					{
						Pass
					}

				}
				//Popice
				if (gameObect[i] == Popice)
				{
					if (gameObject[j] == Popice || gameObject[j] == Gutter || gameObject[j] == Bowling_Ball)
					{
						Pass
					}
				}
				Pass_Collider(objects[i], objects[j]);
			}
			else
			{
				if (gameObect[i] == Bowling_Lane)
				{
					if (gameObject[j] == Gutter)
					{
						Pass
					}
				}
				if (gameObect[i] == Gutter)
				{
					if (gameObject[j] == Gutter)
					{
						Pass
					}
				}

				Pass_Collider(objects[i], objects[j]);


			}

			if (i == AABB && j = AABB)
			{
				Collision_Calculatin.AABB_AABB();
			}
			if (i == Sphere && j = Sphere)
			{
				Collision_Calculatin.Sphere_Sphere();
			}
			if (i == Sphere && j = AABB)
			{
				Collision_Calculatin.Sphere_AABB();
			}
			if (i == AABB && j = Sphere)
			{
				Collision_Calculatin.AABB_Sphere();
			}
		}

			




		//daca triggerul este activat
		// -Toate obiectele stiu unele de altele
	}
}


Pass_Collider()
{

	for (int i = 0, i <= 8; i++)
	{
		if ((static_cast<Popice*>(objects[i]))
		{
			AABB Collider
		}
		else if ((static_cast<Bila*>(objects[i]))
		{
			Sphere Collider
		}
		else if ((static_cast<Bowling_Lane*>(objects[i]))
		{
			AABB Collider
		}
		else if ((static_cast<Gutter*>(objects[i]))
		{
			AABB Collider
		}

	}
}