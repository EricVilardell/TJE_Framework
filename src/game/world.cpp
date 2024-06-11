#include "world.h"
#include "framework/input.h"
#include "game.h"

World* World::instance = nullptr;

World::World()
{
	int window_width = Game::instance->window_width;
	int window_height = Game::instance->window_height;

	//Material player_material;
	//player_material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/color.fs");
	player = new EntityPlayer();
	player->model.setTranslation(383.f, 330.f, 0.f);
	//player->model.setTranslation(383.f, 330.f, -265.f);	//second spawn wrong map collisions
	player->material.diffuse = new Texture();
	player->mesh = Mesh::Get("data/charmander/004 - Charmander.obj");

	/*Material player_material;
	player_material.diffuse = Texture::Get("data/meshes/muneco.png");
	player_material.shader = Shader::Get("data/shaders/skinning.vs", "data/shader/texture.fs");
	player->mesh = Mesh::Get("data/meshes/export.MESH");
	player->material = player_material;

	player->isAnimated = true;*/
	//player = new entityplayer(mesh::get("data/meshes/export.mesh"));
	//player->mesh = mesh::get("data/meshes/sphere.obj");
	player->material.diffuse = Texture::Get("data/charmander/004 - charmander.mtl");
	player->material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	//subir el player como mesh ahora, no como obj, y subir un shader que no se sube solo ahora.
	//nuevo boolean isAnimated en entity_mesh
	//classe animator meterla en update en un if del isAnimated, con deltaTime, en el entity_mesh

	zone_min = Vector3(-8.0f, 0.f, -22.0f); // Set your minimum corner here
	zone_max = Vector3(4.0f, 0.f, 25.0f);    // Set your maximum corner here
	end_game = false;


	Material landscape_cubemap;
	landscape_cubemap.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/cubemap.fs");
	landscape_cubemap.diffuse = new Texture();
	landscape_cubemap.diffuse->loadCubemap("landscape", {
		"data/textures/skybox2/px.png",
		"data/textures/skybox2/nx.png",
		"data/textures/skybox2/ny.png",
		"data/textures/skybox2/py.png",
		"data/textures/skybox2/pz.png",
		"data/textures/skybox2/nz.png"
		});
	skybox = new EntityMesh(Mesh::Get("data/meshes/cubemap.ASE"), landscape_cubemap, "landscape");
	parseScene("data/myscene.scene");
}

void World::render()
{
	glDisable(GL_DEPTH_TEST);
	skybox->render(current_camera);
	glEnable(GL_DEPTH_TEST);

	player->render(current_camera);
	drawGrid();

	root.render(current_camera);


}

void World::update(float seconds_elapsed)
{
	if (free_camera) {
		float speed = seconds_elapsed * mouse_speed; 

		// Example

		// Mouse input to rotate the cam
		if (Input::isMousePressed(SDL_BUTTON_LEFT)) //is left button pressed?
		{
			current_camera->rotate(Input::mouse_delta.x * 0.0005f, Vector3(0.0f, -1.0f, 0.0f));
			current_camera->rotate(Input::mouse_delta.y * 0.0005f, current_camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
		}

		// Async input to move the camera around
		if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 10; //move faster with left shift
		if (Input::isKeyPressed(SDL_SCANCODE_W)) current_camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_S)) current_camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_A)) current_camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_D)) current_camera->move(Vector3(-1.0f, 0.0f, 0.0f) * speed);
	}
	else {


		if (Input::isKeyPressed(SDL_SCANCODE_A)) {
			camera_yaw = camera_yaw - 2.f * seconds_elapsed;

		}

		if (Input::isKeyPressed(SDL_SCANCODE_D)) {
			camera_yaw = camera_yaw + 2.f * seconds_elapsed;

		}
		if (Input::isKeyPressed(SDL_SCANCODE_Q)) {
			pepito = pepito - 4.f * seconds_elapsed;

		}

		if (Input::isKeyPressed(SDL_SCANCODE_E)) {
			pepito = pepito + 4.f * seconds_elapsed;

		}

		camera_pitch = camera_pitch - Input::mouse_delta.y * seconds_elapsed;
		camera_pitch = clamp(camera_pitch, -M_PI * 0.4f, M_PI * 0.4f);

		Vector3 current_position = current_camera->eye; 

		Matrix44 mYaw;
		mYaw.setRotation(camera_yaw, Vector3(0, 1, 0));

		Matrix44 mPitch;
		mPitch.setRotation(camera_pitch, Vector3(-1, 0, 0));

		Matrix44 finalrotation = (mPitch * mYaw);
		Vector3 front = finalrotation.frontVector().normalize();
		Vector3 eye;
		Vector3 center;

		float orbit_dist = 5.f;
		eye = player->model.getTranslation() - front * orbit_dist;
		center = player->model.getTranslation() + Vector3(0.f, 0.1f, 0.0f);

		Vector3 dir = eye - center;

		Vector3 collision;
		Vector3 normal;
		float max_ray_dist = dir.length();

		// Check for collision
		bool collided = false;
		for (auto e : World::get_instance()->root.children) {
			EntityMesh* em = dynamic_cast<EntityMesh*>(e);
			if (!em) {
				continue;
			}
			Mesh* mesh = em->mesh;
			if (mesh->testRayCollision(em->model, center, dir.normalize(), collision, normal, max_ray_dist, false)) {
				collided = true;
				break;
			}
		}

		if (collided) {
			eye = collision + normal * 0.1f;
		}

		player->update(seconds_elapsed);
		current_camera->lookAt(eye, center, Vector3(0, 1, 0));
		skybox->model = player->model;

	}
	Vector3 player_position = player->model.getTranslation();
	if (!end_game && player_position.x >= zone_min.x && player_position.x <= zone_max.x && player_position.z >= zone_min.z && player_position.z <= zone_max.z) { // Only checking x and z coordinates
		std::cout << "Player entered the target zone! Game over." << std::endl;
		end_game = true;
		// Change game state to end game
		Game::instance->currentStage = Game::instance->intro_stage;
		player->model.setTranslation(383.f, 335.f, 0.f);
	}

	if (player->model.getTranslation().y < -10.0f) {
		Game::instance->currentStage = Game::instance->intro_stage;
		player->model.setTranslation(383.f, 335.f, 0.f);
	}

	root.update(seconds_elapsed);
}

void World::addEntity(Entity* entity)
{
	root.addChild(entity);
}

void World::removeEntity(Entity* entity)
{
	entities_to_destroy.push_back(entity);
}

void World::get_collisions(const Vector3& position, std::vector<sCollisionData>& ground_collisions, std::vector<sCollisionData>& wall_collisions)
{
	for (auto e : root.children)
	{
		EntityCollider* ec = dynamic_cast<EntityCollider*>(e);
		if (ec == nullptr) {
			continue;
		}
		ec->checkPlayerCollisions(position, ground_collisions, wall_collisions);
	}
}

sCollisionData World::raycast(const Vector3& origin, const Vector3& direction, int layer, float max_ray_dist)
{
	sCollisionData data;

	for (auto e : root.children)
	{
		EntityCollider* ec = dynamic_cast<EntityCollider*>(e);
		if (ec == nullptr/* || !(ec->getLayer() & layer)*/) {
			continue;
		}

		Vector3 col_point;
		Vector3 col_normal;

		if (!ec->mesh->testRayCollision(ec->model, origin, direction, col_point, col_normal, max_ray_dist)) {
			continue;
		}

		data.collided = true;

		float new_distance = (col_point - origin).length();
		if (new_distance < data.distance) {
			data.colPoint = col_point;
			data.colNormal = col_normal;
			data.distance = new_distance;
			data.collided = ec;
		}
	}
	return data;
}

bool World::parseScene(const char* filename)
{
	std::cout << " + Scene loading: " << filename << "..." << std::endl;

	std::ifstream file(filename);

	if (!file.good()) {
		std::cerr << "Scene [ERROR]" << " File not found!" << std::endl;
		return false;
	}

	std::map<std::string, sRenderData> meshes_to_load;

	std::string scene_info, mesh_name, model_data;
	file >> scene_info; file >> scene_info;
	int mesh_count = 0;

	// Read file line by line and store mesh path and model info in separated variables
	while (file >> mesh_name >> model_data)
	{
		if (mesh_name[0] == '#')
			continue;

		// Get all 16 matrix floats
		std::vector<std::string> tokens = tokenize(model_data, ",");

		// Fill matrix converting chars to floats
		Matrix44 model;
		for (int t = 0; t < tokens.size(); ++t) {
			model.m[t] = (float)atof(tokens[t].c_str());
		}

		// Add model to mesh list (might be instanced!)
		sRenderData& render_data = meshes_to_load[mesh_name];
		render_data.models.push_back(model);
		mesh_count++;
	}

	// Iterate through meshes loaded and create corresponding entities
	for (auto data : meshes_to_load) {

		mesh_name = "data/" + data.first;
		sRenderData& render_data = data.second;

		// No transforms, nothing to do here
		if (render_data.models.empty())
			continue;


		Material mat = render_data.material;
		EntityMesh* new_entity = nullptr;

		size_t tag = data.first.find("@tag");

		if (tag != std::string::npos) {
			Mesh* mesh = Mesh::Get("...");
			// Create a different type of entity
			// new_entity = new ...
		}
		else {
			Mesh* mesh = Mesh::Get(mesh_name.c_str());
			new_entity = new EntityMesh();
			new_entity->mesh = mesh;
			new_entity->material = mat;
		}

		if (!new_entity) {
			continue;
		}

		new_entity->name = data.first;

		// Create instanced entity
		if (render_data.models.size() > 1) {
			new_entity->isInstanced = true;
			new_entity->models = render_data.models; // Add all instances
		}
		// Create normal entity
		else {
			new_entity->model = render_data.models[0];
		}

		// Add entity to scene root
		root.addChild(new_entity);
	}

	std::cout << "Scene [OK]" << " Meshes added: " << mesh_count << std::endl;
	return true;
}