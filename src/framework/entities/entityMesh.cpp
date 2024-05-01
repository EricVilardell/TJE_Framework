#include "entityMesh.h"

void EntityMesh::render(Camera* camera) {

	if (!material.shader) {
		material.shader = Shader::Get(isInstanced ? "data/shaders/instanced.vs" : "data/shaders/basic.vs", "data/shaders/texture.fs");
	}

	// Enable shader and pass uniforms 
	material.shader->enable();

	if (!isInstanced) {
		material.shader->setUniform("u_model", model);
	}
	
	material.shader->setUniform("u_viewproj", camera->viewprojection_matrix);
	material.shader->setTexture("u_texture", material.diffuse, 0);

	// Render the mesh using the shader
	mesh->render(GL_TRIANGLES);

	// Disable shader after finishing rendering
	material.shader->disable();

	Entity::render(camera);
}

void EntityMesh::update(float delta_time)
{
	Entity::update(delta_time);
}
