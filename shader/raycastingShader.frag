#version 330 core
in vec2 uv;
in vec3 pos;

out vec4 color; 

//rendering description:
//0=Maximum intensity projection
//1=First Hit
uniform int rendering;
uniform int width;
uniform int height;
uniform int depth;

uniform sampler2D entryPoint;
uniform sampler2D exitPoint;
uniform sampler3D volumeTexture;

void main(){
	
	vec3 textureSize = vec3(width, height, depth);
	vec3 start = (texture(entryPoint, uv).xyz)*textureSize;	
	vec3 end = (texture(exitPoint, uv).xyz)*textureSize;	

	if(start!=end){		
		vec3 temp;	
		if(distance(pos, start)>distance(pos,end)){
			temp = end;
			end = start;
			start = temp;
		}
		if(start.z>end.z){
			temp = end;
			end = start;
			start = temp;
		}
		
		vec3 direction = (end-start);
		vec3 step = normalize(direction);
		
		float maximum = 0;
		float val;
		bool firstHit = false;
		
		for(step; start.z<end.z && !firstHit; start+=step){
			vec3 c =  texture(volumeTexture, start/textureSize).xyz;
			val = max(max(c.x, c.y), c.z);
			if(maximum<val){
				maximum = val;
				if(rendering==1) firstHit = true;
			}			
		}
		color = vec4(maximum, maximum, maximum, start);		
	}	
	else{
		color = vec4(0,0,0,0);
	}	
}