#version 330 core

in vec3 viewPlane;

out vec2 uv;
out vec3 pos;

void main(){
	vec3 p = (viewPlane*2)-1;
	gl_Position = vec4(p, 1);
	uv = vec2(0.5, 0.5)+(0.5*p).xy;
	pos = p;
}