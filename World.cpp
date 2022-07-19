//
// World.h
// 
// Handles the position vector for each voxel, and
// supports voxel creation and property edits
//

#include "World.h"




// Constructors
//
World::World(vec3 defaultVoxelColor, float voxelSizeMultiplier) {
	this->defaultVoxelColor = defaultVoxelColor;
	this->voxelSizeMultiplier = voxelSizeMultiplier;
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

// getPropertyVector
//
// Returns the block property vector
//
vector<blockProperty>& World::getPropertyVector() {
	return blockProperties;
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
void World::addBlock(float x, float y, float z) {
	blockPositions.push_back(vec3(x, y, z) * voxelSizeMultiplier);
	blockProperties.push_back(blockProperty(defaultVoxelColor));			// Default color
}
void World::addBlock(vec3 coords) {
	blockPositions.push_back(coords * voxelSizeMultiplier);
	blockProperties.push_back(blockProperty(defaultVoxelColor));			// Default color
}
void World::addBlock(vec3 coords, vec3 color) {					// Specifies color
	blockPositions.push_back(coords * voxelSizeMultiplier);
	blockProperties.push_back(blockProperty(color));
}
void World::addBlock(float x, float y, float z, vec3 color) {			// Specifies color
	blockPositions.push_back(vec3(x, y, z) * voxelSizeMultiplier);
	blockProperties.push_back(blockProperty(color));
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
			blockProperties.erase(blockProperties.begin() + i);
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
	blockProperties.erase(blockProperties.begin() + index);
}


// clear
//
// Remove all blocks
//
void World::clear() {
	blockPositions.clear();
	blockProperties.clear();
}


// setVector
//
// Replaces the previous vector with a premade new one
//
void World::setVector(vector<vec3> newVector) {
	clear();		// Clear previous vector

	// Adjust vector to match size
	for (auto v : newVector) {
		v *= voxelSizeMultiplier;
		blockProperties.push_back(blockProperty(defaultVoxelColor));
	}

	blockPositions = newVector;
}
void World::setVector(vector<vec3> newVector, vector<blockProperty>& properties) {		// Allows color specification
	setVector(newVector);

	if (properties.size() != newVector.size()) throw invalid_argument("ERROR::WORLD::setVector\nInvalid properties size");
	blockProperties = properties;
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
			blockPositions.push_back(vec3(x, y, z) * voxelSizeMultiplier);
		else if (c == '0')
			;// Do nothing
		else if (c == ' ')
			continue;
		else
			throw out_of_range("ERROR::ENGINE::WORLD::SETVECTOR\nInvalid string");

		// Iterate
		x += voxelSizeMultiplier;
		i++;
		if (i == blockLength) {
			// Reset x
			x = 0;
			i = 0;

			y += voxelSizeMultiplier;
			j++;
			if (j == blockLength) {
				// Reset y
				y = 0;
				j = 0;

				z += voxelSizeMultiplier;
			}
		}

		// Add default color
		blockProperties.push_back(blockProperty(defaultVoxelColor));
	}
}
void World::setVector(vec3 startPosition, string blockList, int blockLength, vector <blockProperty>& properties) {		// Allows color specification
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
			blockPositions.push_back(vec3(x, y, z) * voxelSizeMultiplier);
		else if (c == '0')
			;// Do nothing
		else if (c == ' ')
			continue;
		else
			throw out_of_range("ERROR::ENGINE::WORLD::setVector\nInvalid string");

		// Iterate
		x += voxelSizeMultiplier;
		i++;
		if (i == blockLength) {
			// Reset x
			x = 0;
			i = 0;

			y += voxelSizeMultiplier;
			j++;
			if (j == blockLength) {
				// Reset y
				y = 0;
				j = 0;

				z += voxelSizeMultiplier;
			}
		}
	}

	// Copy properties
	if (properties.size() != blockPositions.size()) throw invalid_argument("ERROR::WORLD::setVector\nInvalid properties size");
	blockProperties = properties;
}





// World modification
//



// addBox
//
// Adds multiple blocks to generate a box in default color
//
void World::addBox(vec3 startPosition, vec3 dimensions) {
	float maxX = startPosition.x + dimensions.x;
	float maxY = startPosition.y + dimensions.y;
	float maxZ = startPosition.z + dimensions.z;

	for (float z = startPosition.z; z < maxZ; z++) {
		for (float y = startPosition.y; y < maxY; y++) {
			for (float x = startPosition.x; x < maxX; x++) {
				addBlock(x, y, z);
				blockProperties.push_back(blockProperty(defaultVoxelColor));
			}
		}
	}
}
void World::addBox(vec3 startPosition, vec3 dimensions, vector<blockProperty>& properties) {	// Allows color specification; property order->XYZ
	if (properties.size() != (dimensions.x * dimensions.y * dimensions.z)) throw invalid_argument("ERROR::WORLD::addBox\nInvalid properties size");

	float maxX = startPosition.x + dimensions.x;
	float maxY = startPosition.y + dimensions.y;
	float maxZ = startPosition.z + dimensions.z;

	int i = 0;
	for (float z = startPosition.z; z < maxZ; z++) {
		for (float y = startPosition.y; y < maxY; y++) {
			for (float x = startPosition.x; x < maxX; x++) {
				addBlock(x, y, z, properties[i++].color);
			}
		}
	}
}





