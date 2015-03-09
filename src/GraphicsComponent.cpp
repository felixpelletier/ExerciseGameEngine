#include "GraphicsComponent.h"
#include "ModelInstance.h"

namespace Soul{

GraphicsComponent::GraphicsComponent(int id, int model){

	this->id = id;
	this->model_id = model;

}

void GraphicsComponent::draw(ModelManager& modelManager, const Shader& shader){
	
	glUniformMatrix4fv(shader.s_modelMat, 1, GL_FALSE, &modelMat[0][0]);

	Model* model = modelManager.getModel(model_id);
	std::vector<Mesh>* meshes = &model->meshes;

	for (auto &mesh : *meshes){
		Texture* texture = &model->textures[mesh.materialId];
		texture->bind(shader.DiffuseTexID, shader.NormalTexID);	
		mesh.bind(shader.s_vertexPosition, shader.s_vertexUV, shader.s_vertexNormal);	
	
		// Draw the triangles !
		glDrawElements(
		    GL_TRIANGLES,      // mode
		    mesh.indices,    // count
		    GL_UNSIGNED_INT,   // type
		    nullptr           // element array buffer offset
		);

	}
}

}
