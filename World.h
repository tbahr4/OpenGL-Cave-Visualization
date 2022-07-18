//
// World.h
// 
// Handles the position vector for each voxel, and
// supports voxel creation and property edits
//
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <stdexcept>
#include <iostream>


using namespace std;
using namespace glm;

struct blockProperty {
	vec3 color;

	blockProperty(vec3 color) {
		this->color = color;
	}
};




class World
{
private:
	vector<vec3> blockPositions;
	vector<blockProperty> blockProperties;

	vec3 defaultVoxelColor;
	float voxelSizeMultiplier;

public:
	// Constructors
	//
	World(vec3 defaultVoxelColor, float voxelSizeMultiplier);

	// Helper functions
	vector<vec3>& getPositionVector();				// Returns the position vector for use
	vector<blockProperty>& getPropertyVector();		// Returns the block property vector
	int getBlockCount() const;						// Returns blockCount

	// Voxel modification
	void addBlock(float x, float y, float z);	// Adds a block to the world
	void addBlock(vec3 coords);					// 
	void addBlock(vec3 coords, vec3 color);					// Allows color specification
	void addBlock(float x, float y, float z, vec3 color);	//
	
	bool removeBlock(int x, int y, int z);	// Removes a block from the world; Returns true if found
	void removeBlockAt(int index);			// Removes the block at given index
	void clear();							// Remove all blocks

	void setVector(vector<vec3> newVector);		// Replaces the previous vector with a premade new one
	void setVector(vector<vec3> newVector, vector<blockProperty>& properties);	// Allows color specification

	void setVector(vec3 startPosition, string blockList, int blockLength);		// Replaces the previous vector with the given binary string; Begins a new line every blockLength blocks
	void setVector(vec3 startPosition, string blockList, int blockLength, vector<blockProperty>& properties);	// Allows color specification
	
	// World modification
	void addBox(vec3 startPosition, vec3 dimensions);		// Adds multiple blocks to generate a box in default color
	void addBox(vec3 startPosition, vec3 dimensions, vector<blockProperty>& properties);	// Allows color specification; property order->XYZ
};



