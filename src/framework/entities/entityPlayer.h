#pragma once
#include "entityMesh.h"
#include "entityCollider.h"

class EntityPlayer : public EntityMesh {

public:
	bool is_grounded = false;
	EntityPlayer();
	Vector3 velocity = (0.0f, 0.0f, 0.0f);
	float points = 0.f;
	bool isAnimated = false;
	void render(Camera* camera);
	void update(float delta_time);
	bool CheckPlayerCollision(const Vector3& target_pos, std::vector<sCollisionData>& collisions, float radius);
	void calculatepoints(std::vector<sCollisionData>& collisions);
};