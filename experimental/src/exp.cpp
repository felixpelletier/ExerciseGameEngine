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
#include <misc.h>
#include <entity.h>
#include <systems/graphics.h>
#include <systems/collisions.h>
#include <random>

//#include <ScriptEngine.h>

using namespace Soul;

void makeGrid(std::vector<glm::vec3>* list, int size,float tileHalfSize);

int main()
{
	EntityManager entityGod;
	GraphicSystem graphics = GraphicSystem(&entityGod);
	CollisionSystem collisions = CollisionSystem(&entityGod);

	std::vector<Handle> entities;

	Handle h_floor = entityGod.createEntity(Entity::Standard, "ice.obj");
	Handle h_player = entityGod.createEntity(Entity::Player, "Snowmobile.obj");

	entities.push_back(h_floor);
	entities.push_back(h_player);

	
	for (int o = 0; o < 50; o++){
		Handle h_oildrum = entityGod.createEntity(Entity::Collectible, "oildrum.obj");
		Entity* oildrum = entityGod.getEntity(h_oildrum);
		glm::vec3 ranPos;
		const float low = -100.0f;
		const float high = 100.0f;
		ranPos.x = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low))); 
		ranPos.z = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low))); 
		float ranOrient = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(glm::pi<float>())));
		std::cout << "X: " << ranPos.x << " Z: " << ranPos.z << "\n";
		oildrum->graphics.model.modelMat = glm::rotate(oildrum->graphics.model.modelMat, ranOrient, glm::vec3(0.0f, 1.0f, 0.0f));
		oildrum->graphics.model.modelMat = glm::translate(oildrum->graphics.model.modelMat, ranPos);
		entities.push_back(h_oildrum);
	}
	
	std::vector<glm::vec3> tiles;

	//makeGrid(&tiles, 180, floor.boundingBox.max.x - floor.boundingBox.min.x);

	//floor.graphics = InstancedGraphicsComponent(0, "ice.obj",tiles);//this is ugly as fuck, but temporary

	double lastTime = glfwGetTime();
	
	glm::vec3 position;
	float orientation = 0.0f;
	float speed = 0.0f;

	do{
		Entity* player = entityGod.getEntity(h_player);
		double currentTime = glfwGetTime();
		float dt = float(currentTime - lastTime);
		lastTime = currentTime;
		
		if (1/dt < 55) std::cout << 1/dt << " FPS\n"; //If FPS<55, notify

		float speedBoost = 6.0f;
		float orientationDampen = 0.2f;
		// Move forward
		if (glfwGetKey(graphics.window, GLFW_KEY_UP ) == GLFW_PRESS){
		    speed += speedBoost * dt;
		}
		
		if (glfwGetKey(graphics.window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		    speed -= speedBoost * dt;
		}

		if (glfwGetKey(graphics.window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		   orientation  += glm::pow(glm::abs(speed), 0.5f) * orientationDampen * dt;
		}
		
		if (glfwGetKey(graphics.window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		   orientation -= glm::pow(glm::abs(speed), 0.5f) * orientationDampen * dt;
		}
		
		if (glm::abs(speed) < 3.0f){
			speed = speed * glm::pow(0.2f, dt);
		}
		else{
			speed = speed * glm::pow(0.7f, dt);
		}
		position[0] += speed * dt * glm::sin(orientation);
		position[2] += speed * dt * glm::cos(orientation);

		glm::mat4 playerMat;
		playerMat = glm::translate(playerMat, position);
		playerMat = glm::rotate(playerMat, orientation, glm::vec3(0.0f, 1.0f, 0.0f));

		player->graphics.model.modelMat = playerMat;

		collisions.update(dt, entities);

		graphics.cameraPos = glm::vec3(position);
		graphics.cameraPos.y = 3.0f;
		graphics.cameraPos.x -= 6.0f * glm::sin(orientation);
		graphics.cameraPos.z -= 6.0f * glm::cos(orientation);

		graphics.viewMat = glm::lookAt(
		    graphics.cameraPos, // Camera is at (4,3,3), in World Space
		    position, // and looks at the origin
		    glm::vec3(0.0f,1.0f,0.0f)  // Head is up (set to 0,-1,0 to look upside-down)
		);


		graphics.update(dt, entities);

	 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(graphics.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	glfwWindowShouldClose(graphics.window) == 0 );

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

//Entity createEntity("

