#pragma once
#include "framework/entities/entityMesh.h"
#include "game.h"

class World {
public:
	static World* instance;

	Camera* camera;

	World() {}; 			// Constructor
	virtual ~World() {};

	void render();

	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);

};