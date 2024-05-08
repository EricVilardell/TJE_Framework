/*#pragma once
#include "framework/entities/entityMesh.h"
#include "game.h"
#include <iostream>
#include <fstream>

class World {
public:
	static World* instance;

	Camera* camera;

	World() {}; 			// Constructor
	virtual ~World() {};

	void render();
	void update(float seconds_elapsed);

	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);

}; */

#pragma once
#include "framework/entities/entityMesh.h"
#include "game.h"
#include "graphics/material.h"
#include <iostream>
#include <fstream>

class World {
	static World* instance;

public:
	static World* get_instance() {
		if (instance != nullptr)return instance;
		instance = new World();
		return instance;
	}
	EntityMesh* skybox;
	EntityMesh* player = nullptr;
	Entity root;
	float camera_yaw = 0.f;
	float camera_pitch = 0.f;
	float camera_speed = 2.0f;
	float mouse_speed = 0.5f;
	bool free_camera = true;
	World(); 			// Constructor

	void render();
	void update(float seconds_elapsed);
	std::map<std::string, sRenderData> meshes_to_load;
	std::vector<Entity*> entities_to_destroy;
	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
	bool parseScene(const char* filename);

};