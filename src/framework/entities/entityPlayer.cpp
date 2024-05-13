#include "entityPlayer.h"
#include "game/world.h"
#include "framework/input.h"

EntityPlayer::EntityPlayer()
{
}

void EntityPlayer::render(Camera* camera)
{

	EntityMesh::render(camera);
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