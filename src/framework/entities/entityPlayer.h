#pragma once
#include "entityMesh.h"
#include "entityCollider.h"

class EntityPlayer : public EntityMesh {

public:
	bool is_grounded = false;
	EntityPlayer();
	Vector3 velocity = (0.0f, 0.0f, 0.0f);
	void render(Camera* camera);
	void update(float delta_time);

};