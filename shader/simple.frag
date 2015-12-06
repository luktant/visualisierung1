#version 330 core

in vec3 pos;

out vec4 fragColor;

uniform sampler3D volumeData;

// RAYCASTING PER FRAGMENT
void main()
{   
	fragColor = vec4(pos, 1);
}