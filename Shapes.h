//
// Shapes.h
// 
// Generates vertex arrays used to render shapes
//
#pragma once

#include <vector>
#include <stdexcept>

using namespace std;


#define CUBE_VERTEX_COUNT 180






class Shapes 
{
public:
	// Constructors
	Shapes(float sizeMultiplier);		// Generates each vertex array from given size multiplier

	// Accessor functions
	vector<float>& cube();

private:
	// Vertices to generate a cube
	//
	vector<float> cubeVertices = {
		// Vertex positions		// Texture coords		// Normal	
		//						// (Unused currently)   //
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,				0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,				0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,				0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,				0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,				0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,				0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,				0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,				0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,				0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,				0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,				0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,				0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,				-1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,				-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,				-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,				-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,				-1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,				-1.0f, 0.0f, 0.0f,
											 		
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,				1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,				1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,				1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,				1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,				1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,				1.0f, 0.0f, 0.0f,
											 				
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,				0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,				0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,				0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,				0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,				0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,				0.0f, -1.0f, 0.0f,
											 	
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,				0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,				0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,				0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,				0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,				0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 			0.0f, 1.0f, 0.0f
	};
};