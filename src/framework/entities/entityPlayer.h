#pragma once
#include "entityMesh.h"
#include "entityCollider.h"
#include "framework/audio.h"

class EntityPlayer : public EntityMesh {

public:
	bool is_grounded = false;
	bool was_grounded = true;
	EntityPlayer();
	Vector3 velocity = (0.0f, 0.0f, 0.0f);
	float points = 0.f;
	float points_hidden = 0.f;
	bool isAnimated = false;
	float airborne_time;
	void render(Camera* camera);
	void update(float delta_time);
	bool CheckPlayerCollision(const Vector3& target_pos, std::vector<sCollisionData>& collisions, float radius);
	void calculatepoints(std::vector<sCollisionData>& collisions);
};