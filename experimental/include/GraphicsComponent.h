#pragma once

#include "ModelInstance.h"

namespace Soul{

class GraphicsComponent{
	public : enum GraphicComponentType {Simple, Instanced}; 
	
	protected:
		static const GraphicComponentType type = Simple;
	public:
		virtual GraphicComponentType getType() { return type; };
		GraphicsComponent() {};
		GraphicsComponent(ModelInstance model);
		ModelInstance model;


};

}
