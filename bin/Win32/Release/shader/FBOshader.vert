#version 330 core

in vec3 position;
uniform mat4 mvp;
out vec3 col;

void main()
{  
	vec4 pos = mvp*vec4(position, 1);
    gl_Position = pos;
	col = position.xyz;
}