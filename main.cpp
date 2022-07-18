
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
#define VOXEL_COLOR vec3(0.0f, 0.2f, 0.3f)
#define VOXEL_SIZE_MULTIPLIER 1.0f




Engine engine(SCREEN_TITLE, INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT, INITIAL_POSITION, CAM_DEFAULT_YAW, CAM_DEFAULT_PITCH, MOVEMENT_SPEED, MOUSE_SENSITIVITY, FOV, BACKGROUND_COLOR, VOXEL_COLOR, VOXEL_SIZE_MULTIPLIER);



int main() {
	// Generate world
	//
	engine.world->setVector(vec3(0, 0, 0), "111111111111111111111111111", 3);

	

	// Improve World.h voxel vector indexing; Allow storage of properties in each voxel

	// Color selection

	// Begin engine loop
	while (engine.loop());		// Loop until window has been closed
}


