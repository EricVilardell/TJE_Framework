#pragma once
#include "entity.h"
#include "graphics/mesh.h"
#include "framework/animation.h"
#include "graphics/material.h"
#include "graphics/shader.h"
#include "framework/camera.h"

class EntityMesh : public Entity {

public:
	EntityMesh() {};
	EntityMesh(Mesh* mesh, const Material& material, const std::string& name = "");
	~EntityMesh();

	Mesh* mesh = nullptr;

	Material material;

	bool isInstanced = false;
	std::vector<Matrix44> models;
	void addInstance(const Matrix44& model);

	void render(Camera* camera) override;
	void update(float delta_time) override;
};
