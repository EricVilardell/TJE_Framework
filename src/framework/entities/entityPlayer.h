#pragma once
#include "entityMesh.h"

class EntityPlayer : public EntityMesh {

public:

	EntityPlayer();
	Vector3 velocity = (0.0f, 0.0f, 0.0f);
	void render(Camera* camera);
	void update(float delta_time);

};