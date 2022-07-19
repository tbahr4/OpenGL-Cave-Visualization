
#include <iostream>
#include "Engine.h"

#define SCREEN_TITLE "OpenGL Visualization"
#define INITIAL_SCREEN_WIDTH 800
#define INITIAL_SCREEN_HEIGHT 600
#define INITIAL_POSITION vec3(1.0f, 1.0f, 7.0f)
#define CAM_DEFAULT_YAW -90.0f
#define CAM_DEFAULT_PITCH 0.0f
#define MOVEMENT_SPEED 5.0f
#define MOUSE_SENSITIVITY 0.1f
#define FOV 45.0f
#define BACKGROUND_COLOR vec3(0.2f, 0.3f, 0.3f)
#define DEFAULT_VOXEL_COLOR vec3(0.0f, 0.2f, 0.3f)
#define VOXEL_SIZE_MULTIPLIER 1.0f




Engine engine(SCREEN_TITLE, INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT, INITIAL_POSITION, CAM_DEFAULT_YAW, CAM_DEFAULT_PITCH, MOVEMENT_SPEED, MOUSE_SENSITIVITY, FOV, BACKGROUND_COLOR, DEFAULT_VOXEL_COLOR, VOXEL_SIZE_MULTIPLIER);



int main() {
	// Generate world
	//
	/*vector<blockProperty> properties = {
		blockProperty(vec3(0.9f, 0.9f, 0.9f)),
		blockProperty(vec3(0.8f, 0.8f, 0.8f)),
		blockProperty(vec3(0.25f, 0.25f, 0.25f)),
		blockProperty(vec3(0.0f, 0.0f, 0.0f)),
		blockProperty(vec3(1.0f, 0.9f, 0.1f)),
		blockProperty(vec3(1.0f, 0.5f, 0.1f)),
		blockProperty(vec3(0.8f, 0.15f, 0.1f)),
		blockProperty(vec3(0.5f, 0.25f, 0.2f)),
		blockProperty(vec3(0.5f, 0.7f, 0.1f)),
		blockProperty(vec3(0.3f, 0.4f, 0.1f)),
		blockProperty(vec3(0.15f, 0.55f, 0.8f)),
		blockProperty(vec3(0.1f, 0.45f, 0.45f)),
		blockProperty(vec3(0.25f, 0.25f, 0.6f)),
		blockProperty(vec3(0.95f, 0.6f, 0.75f)),
		blockProperty(vec3(0.8f, 0.25f, 0.78f)),
	};*/
	

	//engine.world->addBox(vec3(0, 0, 0), vec3(5, 5, 5));
	
	//engine.world->addBox(vec3(0, 0, 0), vec3(16, 1, 1), properties);	

	//engine.world->setVector(vec3(0, 0, 0), "00001 00010 00100 01000 10000   00010 00100 01000 10000 00000   00100 01000 10000 00000 00000   01000 10000 00000 00000 00000   10000 00000 00000 00000 00000   00000 00000 00000 00000 00000", 5, properties);


	//engine.world->addBox(vec3(0, 0, 0), vec3(16, 16, 16));

	engine.world->addBlock(0, 0, 0);
	



	// Begin engine loop
	while (engine.loop());		// Loop until window has been closed
}


