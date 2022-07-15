//
// World.h
// 
// Handles the position vector for each voxel, and
// supports voxel creation and property edits
//

#include "World.h"




// Constructors
//
World::World() {
	// Do nothing
}

// Helper functions
//

// getPositionVector
// 
// Returns the position vector for use
//
vector<vec3>& World::getPositionVector() {
	return blockPositions;
}


// getBlockCount
//
// Returns blockCount
//
int World::getBlockCount() const {
	return (int)blockPositions.size();
}


// Voxel modification
//

// addBlock
//
// Adds a block to the world
//
void World::addBlock(int x, int y, int z) {
	blockPositions.push_back(vec3(x, y, z));
}
void World::addBlock(vec3 coords) {
	blockPositions.push_back(coords);
}


// removeBlock
//
// Removes a block from the world
// Returns true if found
//
bool World::removeBlock(int x, int y, int z) {
	for (int i = 0; i < getBlockCount(); i++) {
		if (blockPositions[i].x == x && blockPositions[i].y == y && blockPositions[i].z == z) {
			blockPositions.erase(blockPositions.begin() + i);		// Erase at index
			return true;
		}
	}
	
	// None found
	return false;
}


// removeBlockAt
//
// Removes the block at given index
//
void World::removeBlockAt(int index) {
	blockPositions.erase(blockPositions.begin() + index);
}


// clear
//
// Remove all blocks
//
void World::clear() {
	blockPositions.clear();
}


// setVector
//
// Replaces the previous vector with a premade new one
//
void World::setVector(vector<vec3> newVector) {
	clear();		// Clear previous vector
	blockPositions = newVector;
}


// setVector
//
// Replaces the previous vector with the given binary string
// Begins a new line every blockLength blocks
// Begins at given startPosition
// For each 1/0 character, iteration continues toward +x, +y, then +z
//
void World::setVector(vec3 startPosition, string blockList, int blockLength) {
	// Reset the vector
	clear();

	// Error check
	if (blockLength <= 0) return;


	float x = startPosition.x;
	float y = startPosition.y;
	float z = startPosition.z;

	int i = 0;
	int j = 0;
	for (char c : blockList) {
		if (c == '1')
			blockPositions.push_back(vec3(x, y, z));
		else if (c == '0')
			;// Do nothing
		else
			throw out_of_range("ERROR::ENGINE::WORLD::SETVECTOR\nInvalid string");

		// Iterate
		x++;
		i++;
		if (i == blockLength) {
			// Reset x
			x = 0;
			i = 0;

			y++;
			j++;
			if (j == blockLength) {
				// Reset y
				y = 0;
				j = 0;

				z++;
			}
		}
	}
}