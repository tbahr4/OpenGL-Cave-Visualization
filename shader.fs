#version 330 core

in vec2 TextureCoord;
in vec3 Normal;
out vec4 FragmentColor;		// Color of each fragment

uniform vec3 voxelColor;

vec4 adjustBrightness(vec4 color, float multiplier);		// Returns the adjusted brightness of the given color



void main()
{
	// Outline
	float outlineSize = 0.02f;
	if (TextureCoord.x < outlineSize || TextureCoord.x > 1-outlineSize || TextureCoord.y < outlineSize || TextureCoord.y > 1-outlineSize) {
		FragmentColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	} else {
		FragmentColor = vec4(voxelColor, 1.0f);		// Set initial color

		// Shading
		if (Normal.x == 0 && Normal.y == 0 && Normal.z > 0) FragmentColor = adjustBrightness(FragmentColor, .8);		// Front
		else if (Normal.x == 0 && Normal.y == 0 && Normal.z < 0) FragmentColor = adjustBrightness(FragmentColor, .7);	// Back
		else if (Normal.x < 0 && Normal.y == 0 && Normal.z == 0) FragmentColor = adjustBrightness(FragmentColor, .6);	// Left
		else if (Normal.x > 0 && Normal.y == 0 && Normal.z == 0) FragmentColor = adjustBrightness(FragmentColor, .9);	// Right
		else if (Normal.x == 0 && Normal.y < 0 && Normal.z == 0) FragmentColor = adjustBrightness(FragmentColor, .4);	// Bottom
		else if (Normal.x == 0 && Normal.y > 0 && Normal.z == 0) FragmentColor = adjustBrightness(FragmentColor, 1);	// Top
	}	
}


// adjustBrightness
//
// Returns the adjusted brightness of the given color
//
vec4 adjustBrightness(vec4 color, float multiplier) {
	return vec4(color.x * multiplier, color.y * multiplier, color.z * multiplier, color.w);
}