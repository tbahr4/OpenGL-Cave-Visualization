//
// Engine.cpp
// 
// Used to create an OpenGL instance for rendering
//

#include "Engine.h"











// Constructors
//

Engine::Engine(const char* windowTitle, int screenWidth, int screenHeight, vec3 initialCamPos, float camYaw, float camPitch, float movementSpeed, float mouseSensitivity, float fov, vec3 backgroundColor, vec3 defaultVoxelColor, float voxelSizeMultiplier) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->backgroundColor = backgroundColor;
	this->defaultVoxelColor = defaultVoxelColor;
	this->voxelSizeMultiplier = voxelSizeMultiplier;
	
	// Setup camera
	camera = new Camera(initialCamPos, camYaw, camPitch, movementSpeed, mouseSensitivity, fov);

	// Setup world object to store world space positions of the voxels
	world = new World(defaultVoxelColor, voxelSizeMultiplier);

	// Setup shapes object
	shapes = new Shapes(voxelSizeMultiplier);

	// Last mouse movement position
	prevX = screenWidth / 2.0f;
	prevY = screenHeight / 2.0f;


	// Begin Initialization
	//

	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	window = glfwCreateWindow(screenWidth, screenHeight, windowTitle, NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window!" << endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);

	// Make this engine object the current instance of this window
	glfwSetWindowUserPointer(window, this);

	// Init callbacks
	glfwSetCursorPosCallback(window, mouse_callback);					// Direct mouse movement to function
	glfwSetScrollCallback(window, scroll_callback);						// Direct scroll wheel movement to function
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);		// Capture mouse cursor


	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD!" << endl;
		exit(1);
	}
	glViewport(0, 0, screenWidth, screenHeight);		// Set rendered view; can render outside this if desired
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);		// Setup function call for when screen is resized

	// Initialize shaders
	shader = new Shader("shader.vs", "shader.fs");


	// Configure vertex attributes
	VAO = unsigned int();
	VBO = unsigned int();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, shapes->cube().size() * sizeof(float), &shapes->cube()[0], GL_STATIC_DRAW);

	// POSITION attrib  
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// TEXTUREPOS attrib
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// NORMAL attrib
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Rendering
	shader->use();					// Enable shader
	glEnable(GL_DEPTH_TEST);		// Enable depth
}

// loop
//
// To be called every frame
// Returns false if window has been signaled to close
//
bool Engine::loop() {
	if (glfwWindowShouldClose(window)) {
		// Delete vertex resources
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		// Terminate
		glfwTerminate();
		
		return false;
	}

	// Begin main loop

	// Update timings
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	processKeyboardInput(window); // Get Keyboard input

	// Clear screen with background
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);	// Set clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);								// Now clear it

	// Generate rendering matrices to identity matrix
	mat4 model = mat4(1.0f);
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);

	// Update shader
	projection = perspective(radians(camera->fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	view = camera->GetViewMatrix();
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	// Display shapes
	int blockCount = world->getBlockCount();
	for (int i = 0; i < blockCount; i++) {
		// Calculate the model matrix for each object then pass to shader
		model = mat4(1.0f);
		model = translate(model, world->getPositionVector()[i]);
		shader->setMat4("model", model);

		shader->setVec3("voxelColor", world->getPropertyVector()[i].color);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// Output frame buffer
	glfwSwapBuffers(window);
	glfwPollEvents();

	// Frame complete
	return true;
}



// processKeyboardInput
//
// Processes keyboard inputs
//
void Engine::processKeyboardInput(GLFWwindow* window) {
	// Exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	//const float cameraSpeed = 5.0f * deltaTime;

	// Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
}





// framebuffer_size_callback
//
// Called whenever the screen is resized
//
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	Engine* e = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));

	e->screenWidth = width;
	e->screenHeight = height;
	glViewport(0, 0, e->screenWidth, e->screenHeight);
}



// mouse_callback
//
// Processes mouse inputs
//
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	Engine* e = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));

	// If first time focus
	if (e->firstMouseFocus) {
		e->prevX = (float)xpos;
		e->prevY = (float)ypos;
		e->firstMouseFocus = false;
	}

	float xoffset = (float)xpos - e->prevX;
	float yoffset = e->prevY - (float)ypos;
	e->prevX = (float)xpos;
	e->prevY = (float)ypos;

	e->camera->ProcessMouseMovement(xoffset, yoffset);
}

// scroll_callback
//
// Processes scroll wheel inputs
//
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Engine* e = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));

	e->camera->ProcessMouseScroll((float)yoffset);
}