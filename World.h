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

using namespace std;
using namespace glm;



class World
{
private:
	vector<vec3> blockPositions;
	float voxelSizeMultiplier;

public:
	// Constructors
	//
	World(float voxelSizeMultiplier);

	// Helper functions
	vector<vec3>& getPositionVector();		// Returns the position vector for use
	int getBlockCount() const;				// Returns blockCount

	// Voxel modification
	void addBlock(int x, int y, int z);		// Adds a block to the world
	void addBlock(vec3 coords);				// 
	
	bool removeBlock(int x, int y, int z);	// Removes a block from the world; Returns true if found
	void removeBlockAt(int index);			// Removes the block at given index
	void clear();							// Remove all blocks

	void setVector(vector<vec3> newVector);		// Replaces the previous vector with a premade new one
	void setVector(vec3 startPosition, string blockList, int blockLength);		// Replaces the previous vector with the given binary string; Begins a new line every blockLength blocks
};

