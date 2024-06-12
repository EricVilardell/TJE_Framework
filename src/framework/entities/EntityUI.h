#pragma once

#include "entity.h"
#include "graphics/mesh.h"
#include "graphics/material.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "framework/camera.h"
#include "game/world.h"
#include "framework/input.h"

class EntityUI : public Entity {

public:
	Vector2 position;
	Vector2 size;
	Mesh* quad;
	std::string name;
	EntityUI(Vector2 pos, Vector2 size, const Material& mat, const std::string& name);
	Mesh* mesh = nullptr;
	Material material;
	bool visible;
	void render(Camera* camera2d);
	void update(float delta_time);

};