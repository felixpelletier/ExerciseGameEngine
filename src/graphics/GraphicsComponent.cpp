#include "graphics/GraphicsComponent.h"
#include "graphics/ModelInstance.h"

namespace Soul{

GraphicsComponent::GraphicsComponent(){

	this->id = 0;
	this->model_id = 0;
	this->enabled = false;

}

GraphicsComponent::GraphicsComponent(int id, int model){

	this->id = id;
	this->model_id = model;
	this->enabled = true;

}

}
