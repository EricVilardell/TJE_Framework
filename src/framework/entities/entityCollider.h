#pragma once
#include "entityMesh.h"


enum eCollisionFilter {
	NONE = 0,
	FLOOR = 1 << 0,
	WALL = 1 << 1,
	PLAYER = 1 << 2,
	ENEMY = 1 << 3,
	// Both WALL and FLOOR are considered SCENARIO
	// using OR operator
	SCENARIO = WALL | FLOOR,
	ALL = 0xFF
};


struct sCollisionData {
	Vector3 colPoint;
	Vector3 colNormal;
	bool collided;
	float distance;
};


class EntityCollider : public EntityMesh {

public:

	bool is_dynamic = false;

	int layer = NONE;

	// New methods
	//bool testCollision(...);
	bool checkPlayerCollisions(const Vector3& target_pos, std::vector<sCollisionData>& ground_collisions, std::vector<sCollisionData>& wall_collision);

};
