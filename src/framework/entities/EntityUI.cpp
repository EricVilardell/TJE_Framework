#include "EntityUI.h"


EntityUI::EntityUI(Vector2 pos, Vector2 size, const Material& mat, const std::string& name)
{
	this->position = pos;
	this->size = size;
	this->material = mat;
	this->name = name;
	quad = new Mesh();
	quad->createQuad(pos.x, pos.y, size.x, size.y, false);

	if (!this->material.shader) {
		this->material.shader = Shader::Get("data/shaders/basics.vs", "data/shaders/color.fs");
	}

}

void EntityUI::render(Camera* camera2d)
{
	if (!visible) {
		return;
	}

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	World* world = World::get_instance();
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
	Entity::render(camera2d);
}

void EntityUI::update(float delta_time)
{
	Vector2 mouse_pos = Input::mouse_position;
	if ((name == "play") && mouse_pos.x > (position.x - size.x * 0.5f) &&
		mouse_pos.x <(position.x + size.x * 0.5f) &&
		mouse_pos.y >(position.y - size.y * 0.5f) &&
		mouse_pos.y < (position.y + size.y * 0.5f)) {
		material.color = Vector4::RED;
		/*
		if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
		Game::instance->currentStage = Game::instance.playstage
		}*/
	}
	else {
		material.color = Vector4::WHITE;
	}

	if ((name == "exit") && mouse_pos.x > (position.x - size.x * 0.5f) &&
		mouse_pos.x <(position.x + size.x * 0.5f) &&
		mouse_pos.y >(position.y - size.y * 0.5f) &&
		mouse_pos.y < (position.y + size.y * 0.5f)) {
		material.color = Vector4::RED;
		/*
		if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
		Game::instance->currentStage = Game::instance.playstage
		}*/
	}
	else {
		material.color = Vector4::WHITE;
	}

	Entity::update(delta_time);
}