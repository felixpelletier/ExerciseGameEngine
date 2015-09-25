#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "misc.h"
#include "graphics/Light.h"
#include "entities/Entity.h"
#include "entities/EntityManager.h"
#include "graphics/GraphicsComponent.h"
#include "graphics/GraphicSystem.h"
#include "collisions/CollisionSystem.h"
#include "position/PositionSystem.h"
#include "scripting/ScriptingSystem.h"
#include <random>

using namespace Soul;

void makeGrid(std::vector<glm::vec3>* list, int size,float tileHalfSize);

int main()
{
	GraphicSystem* graphics = new GraphicSystem();
	CollisionSystem* collisions = new CollisionSystem();
	PositionSystem* mover = new PositionSystem();
	mover->addListener(graphics);
	mover->addListener(collisions);
	EntityManager entityGod = EntityManager(collisions, graphics);
	ScriptingSystem* scripting = new ScriptingSystem(&entityGod, mover);
	scripting->addListener(graphics);
	collisions->addListener(scripting);

	std::vector<Handle> entities;

	Handle h_player = entityGod.createEntity("Snowmobile.obj");

	entities.push_back(h_player);
	
	/*for (int o = 0; o < 100; o++){
		Handle h_oildrum = entityGod.createEntity("oildrum.obj");
		glm::vec3 ranPos;
		const float low = -100.0f;
		const float high = 100.0f;
		ranPos.x = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low))); 
		ranPos.z = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low))); 
		float ranOrient = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(glm::pi<float>())));
		mover->translate(h_oildrum, ranPos);
		mover->rotate(h_oildrum, ranOrient, glm::vec3(0.0f, 1.0f, 0.0f));
		entities.push_back(h_oildrum);
	}*/
	
	std::vector<glm::vec3> tiles;

	int floor_model = graphics->getModelManager()->loadModel("ice.obj");
	Model* floor_model_p = graphics->getModelManager()->getModel(floor_model);

	//Generating the floor tiles
	BoundingBox floorBox = BoundingBox(floor_model_p);
	makeGrid(&tiles, 15, floorBox.max.x - floorBox.min.x);

	for (auto &tile_pos : tiles){
		Handle h_tile = entityGod.createStaticEntity("ice.obj");
		mover->setToTranslation(h_tile, tile_pos);
	}

	double lastTime = glfwGetTime();
	
	glm::vec3 position;
	float orientation = 0.0f;
	float speed = 0.0f;

	do{
		double currentTime = glfwGetTime();
		float dt = float(currentTime - lastTime);
		lastTime = currentTime;
		
		if (1/dt < 999999) std::cout << 1/dt << " FPS\n"; //If FPS<55, notify

		float speedBoost = 6.0f;
		float orientationDampen = 0.2f;
		// Move forward
		if (glfwGetKey(graphics->window, GLFW_KEY_UP ) == GLFW_PRESS){
		    speed += speedBoost * dt;
		}
	
		//Move backward
		if (glfwGetKey(graphics->window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		    speed -= speedBoost * dt;
		}

		//Turn left
		if (glfwGetKey(graphics->window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		   orientation  += glm::pow(glm::abs(speed), 0.5f) * orientationDampen * dt;
		}
		
		//Turn right
		if (glfwGetKey(graphics->window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		   orientation -= glm::pow(glm::abs(speed), 0.5f) * orientationDampen * dt;
		}
		
		//Speed damping
		if (glm::abs(speed) < 3.0f){
			speed = speed * glm::pow(0.2f, dt);
		}
		else{
			speed = speed * glm::pow(0.7f, dt);
		}
		position[0] += speed * dt * glm::sin(orientation);
		position[2] += speed * dt * glm::cos(orientation);

		mover->setToTranslation(h_player, position);
		mover->rotate(h_player, orientation, glm::vec3(0.0f, 1.0f, 0.0f));

		collisions->update(dt);

		scripting->update(dt);

		graphics->cameraPos = glm::vec3(position);
		graphics->cameraPos.y = 3.0f;
		graphics->cameraPos.x -= 6.0f * glm::sin(orientation);
		graphics->cameraPos.z -= 6.0f * glm::cos(orientation);

		graphics->viewMat = glm::lookAt(
		    graphics->cameraPos, // Camera is at (4,3,3), in World Space
		    position, // and looks at the origin
		    glm::vec3(0.0f,1.0f,0.0f)  // Head is up (set to 0,-1,0 to look upside-down)
		);


		graphics->update(dt);

	 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(graphics->window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	glfwWindowShouldClose(graphics->window) == 0 );

	return 0;
}



void makeGrid(std::vector<glm::vec3>* list, int size,float tileSize){
	float offset = tileSize * (size/4.0f);
	for(int x = 0; x < size;x++){
		for(int y = 0; y < size;y++){
			list->push_back(glm::vec3(x*tileSize - offset,0.0f,y*tileSize - offset));
		}
	}
}

