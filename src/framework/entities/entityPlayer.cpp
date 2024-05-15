#include "entityPlayer.h"
#include "game/world.h"
#include "framework/input.h"

EntityPlayer::EntityPlayer()
{
}

void EntityPlayer::render(Camera* camera)
{
	EntityMesh::render(camera);

	Shader* shader = Shader::Get("data/shaders/basic.vs", "data/shaders/flat.fs");
	Mesh* sphere_wall = Mesh::Get("data/meshes/sphere.obj");
	Mesh* sphere_feet = Mesh::Get("data/meshes/sphere.obj");
	Matrix44 m = model;
	Matrix44 m1 = model;

	shader->enable();
	// esfera cuerpo gorda
	m.translate(0.0f, 1.f, 0.0f);
	m.scale(0.6f, 0.6f, 0.6f);

	shader->setUniform("u_color", Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	shader->setUniform("u_model", m);

	sphere_wall->render(GL_LINES);

	//Esfera pies pequeña
	m1.translate(0.0f, 0.2f, 0.0f);
	m1.scale(0.2f, 0.2f, 0.2f);

	shader->setUniform("u_color", Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	shader->setUniform("u_model", m1);

	sphere_feet->render(GL_LINES);


	shader->disable();
	
}

void EntityPlayer::update(float delta_time)
{
	float camera_yaw = World::get_instance()->camera_yaw;
	Matrix44 mYaw;
	mYaw.setRotation(camera_yaw, Vector3(0, 1, 0));

	Vector3 front = mYaw.frontVector();
	Vector3 right = mYaw.rightVector();

	Vector3 position = model.getTranslation();

	Vector3 move_dir;
	bool is_grounded = true;

	if (Input::isKeyPressed(SDL_SCANCODE_W)) {
		move_dir += front;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_S)) {
		move_dir -= front;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_A)) {
		move_dir += right;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_D)) {
		move_dir -= right;
	}

	if (!is_grounded) {
		velocity.y -= 9.8f * delta_time;
	}
	else if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)){
		velocity.y = 2.0f;
	}

	float speed_mult = 1.5f;

	move_dir.normalize();
	move_dir *= speed_mult;
	velocity += move_dir;

	position += velocity * delta_time;

	velocity.x *= 0.90f;
	velocity.z *= 0.90f;

	model.setTranslation(position);
	model.rotate(camera_yaw, Vector3(0, 1, 0));

	EntityMesh::update(delta_time);
}