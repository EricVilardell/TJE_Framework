#pragma once
#include "framework/entities/entityMesh.h"
#include "game.h"
#include "framework/entities/entityMesh.h"
#include "framework/entities/entityPlayer.h"
#include "game.h"
#include "graphics/material.h"
#include "framework/entities/entityCollider.h"
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
	EntityPlayer* player;
	EntityMesh* snowboard;
	Entity root;
	Camera* camera2d;
	Camera* current_camera = Game::instance->camera;
	float camera_yaw = 0.f;
	float camera_pitch = 0.f;
	float pepito = 0;
	float camera_speed = 2.0f;
	float mouse_speed = 100.f;
	bool free_camera = false;
	Vector3 zone_min;
	Vector3 zone_max;
	bool end_game;
	World(); 			// Constructor

	void render();
	void update(float seconds_elapsed);
	std::map<std::string, sRenderData> meshes_to_load;
	std::vector<Entity*> entities_to_destroy;
	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
	sCollisionData raycast(const Vector3& origin, const Vector3& direction, int layer, float max_ray_dist);
	void get_collisions(const Vector3& position, std::vector<sCollisionData>& collision_ground, std::vector<sCollisionData>& collision_wall);
	void addWayPointFromScreenPos(const Vector2& coord);
	bool parseScene(const char* filename);
	bool CheckPlayerCollision(const Vector3& target_pos, std::vector<sCollisionData>& collisions, float radius);
};