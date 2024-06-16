#include "EntityUI.h"
#include "game/game.h"

EntityUI::EntityUI(Vector2 pos, Vector2 size, const Material& mat, const std::string& name)
{
	this->position = pos;
	this->size = size;
	this->material = mat;
	this->name = name;
	mesh = new Mesh();
	mesh->createQuad(pos.x / 2, pos.y / 2, size.x, size.y, true);

	if (!this->material.shader) {
		this->material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	}
}

void EntityUI::render(Camera* camera2d)
{
	camera2d->enable();
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	material.shader->enable();
	material.shader->setUniform("u_model", model);
	material.shader->setUniform("u_viewprojection", camera2d->viewprojection_matrix);
	material.shader->setUniform("u_color", material.color);
	material.shader->setUniform("u_mesh", mesh);
	if (material.diffuse) {
		material.shader->setTexture("u_texture", material.diffuse, 0);
	}
	mesh->render(GL_TRIANGLES);
	material.shader->disable();

	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
}

void EntityUI::update(float delta_time)
{

	Entity::update(delta_time);
}