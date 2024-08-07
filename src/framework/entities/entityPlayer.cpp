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

	//Esfera pies peque�a
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

	if (is_grounded) {
		if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)) {
			velocity.y = 15.0;
		}
		if (Input::isKeyPressed(SDL_SCANCODE_W)) {
			move_dir += front;
		}
	}
	else {

		if (Input::isKeyPressed(SDL_SCANCODE_Q)) {
			points_hidden += 0.15;
		}
		if (Input::isKeyPressed(SDL_SCANCODE_W)) {
			move_dir += front;
		}
		if (Input::isKeyPressed(SDL_SCANCODE_E)) {
			points_hidden += 0.15;
		}
		if (Input::isKeyPressed(SDL_SCANCODE_A)) {
			points_hidden += 0.05;
		}
		if (Input::isKeyPressed(SDL_SCANCODE_D)) {
			points_hidden += 0.05;
		}
		velocity.y -= 9.8f * delta_time * 3;
	}

	float speed_mult = 1.5f;

	//move_dir.normalize();
	move_dir *= speed_mult;
	float pepitoo = World::get_instance()->pepito;
	pepitoo = (int)pepitoo % 5;
	std::cout << "model.getTranslation().y: " << model.getTranslation().y << std::endl;


	// METER EESTO EN UNA FUNCION DE PLAYER
	float max_ray_dist = 1.3f;
	Vector3 colPoint, colNormal;
	Vector3 center = model.getTranslation() + Vector3(0.f, 1.0f, 0.f);
	bool previously_grounded = is_grounded;

	for (auto e : World::get_instance()->root.children) {
		EntityMesh* em = dynamic_cast<EntityMesh*>(e);
		if (!em) {
			continue;
		}
		Mesh* mesh = em->mesh;
		if (mesh->testRayCollision(em->model, center, Vector3(0, -1, 0), colPoint, colNormal, max_ray_dist, false)) {
			is_grounded = true;
			if (model.getTranslation().y >= 10.0f && model.getTranslation().y < 300.0f) {
				if (previously_grounded == false && airborne_time > 1.0f) {
					HCHANNEL hellYea = Audio::Play("data/audio/hellYea.wav", 0.5f, false);
					points += points_hidden;
					points_hidden = 0;
					if (hellYea == 0) {
						std::cerr << "Failed to play audio: data/audio/hellYea.wav" << std::endl;
					}
					airborne_time = 0.f;
				}
			}

			if (pepitoo == -4 || pepitoo == -3 || pepitoo == -2 || pepitoo == 2 || pepitoo == 3 || pepitoo == 4) {
				points -= 100;
				HCHANNEL Pipe = Audio::Play("data/audio/Pipe.wav", 0.5f, false);
				if (Pipe == 0) {
					std::cerr << "Failed to play audio: data/audio/Pipe.wav" << std::endl;
				}
			}
			World::get_instance()->pepito = 0.f;
			break;
		}
		else {
			is_grounded = false;
		}
	}

	if (!is_grounded) {
		airborne_time += delta_time; 
	}
	else {
		airborne_time = 0.f; 
	}

	std::vector<sCollisionData> collisions;
	CheckPlayerCollision(model.getTranslation(), collisions, 0.2f);
	CheckPlayerCollision(model.getTranslation(), collisions, 0.6f);

	velocity += move_dir;

	for (const auto& collision : collisions) {
		Vector3 colPoint = collision.colPoint;
		Vector3 colNormal = collision.colNormal;

		colNormal.normalize();

		float velocityDotNormal = velocity.dot(colNormal);

		Vector3 velocityAlongNormal = velocityDotNormal * colNormal;

		bool isGroundCollision = std::abs(colNormal.y - 1.0f) < 0.01f;

		if (isGroundCollision) {
			float dampingFactor = 0.9f; 
			velocity.y *= dampingFactor;
			velocity -= velocityAlongNormal;

		}
		else {
			velocity -= velocityAlongNormal;

			float restitution = 0.8f; 
			Vector3 reflectedVelocity = -velocityDotNormal * colNormal * restitution;

			velocity += reflectedVelocity;

			if (velocity.dot(colNormal) < 0) {
				velocity -= velocity.dot(colNormal) * colNormal;
			}
		}
	}
	calculatepoints(collisions);
	position += velocity * delta_time;

	velocity.x *= 0.90f;
	velocity.z *= 0.90f;

	model.setTranslation(position);

	model.rotate(camera_yaw, Vector3(0, 1, 0));
	model.rotate(World::get_instance()->pepito, Vector3(-1, 0, 0));

	EntityMesh::update(delta_time);
}

bool EntityPlayer::CheckPlayerCollision(const Vector3& target_pos, std::vector<sCollisionData>& collisions, float radius)
{
	Vector3 character_center;
	if (radius == 0.6f) {
		character_center = target_pos + Vector3(0.f, 1.0f, 0.f);
	}
	else {
		character_center = target_pos + Vector3(0.0f, 0.2f, 0.0f);
	}

	Vector3 colPoint;
	Vector3 colNormal;

	for (auto e : World::get_instance()->root.children) {
		EntityMesh* em = dynamic_cast<EntityMesh*>(e);
		if (!em) {
			continue;
		}
		Mesh* mesh = em->mesh;
		if (mesh->testSphereCollision(e->model, character_center, radius, colPoint, colNormal)) {
			collisions.push_back({ colPoint,colNormal.normalize() });
		}
	}
	return !collisions.empty();
}

void EntityPlayer::calculatepoints(std::vector<sCollisionData>& collisions)
{

	Vector3 colPoint;
	Vector3 colNormal;

	for (auto e : World::get_instance()->root.children) {
		EntityMesh* em = dynamic_cast<EntityMesh*>(e);
		if (!em) {
			continue;
		}
		Mesh* mesh = em->mesh;
		if (mesh->testSphereCollision(e->model, model.getTranslation() + Vector3(0.f, 1.2f, 0.f), 1.f, colPoint, colNormal)) {
			if (velocity.x > 0.f) {
				points += 0.1;
			}
			std::cout << points << std::endl;
			collisions.push_back({ colPoint,colNormal.normalize() });
		}
	}
}