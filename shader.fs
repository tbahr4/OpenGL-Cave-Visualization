#version 330 core

in vec2 TextureCoord;
out vec4 FragmentColor;		// Color of each fragment

uniform vec3 voxelColor;

void main()
{
	float outlineSize = 0.02f;
	if (TextureCoord.x < outlineSize || TextureCoord.x > 1-outlineSize || TextureCoord.y < outlineSize || TextureCoord.y > 1-outlineSize) 
		FragmentColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	else
		FragmentColor = vec4(voxelColor, 1.0f);
}