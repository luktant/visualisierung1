#version 330 core
in vec2 uv;
in vec3 pos;

out vec4 color; 

//rendering description:
//0=Maximum intensity projection
//1=First Hit
//2=Gradient
uniform int rendering;
uniform int width;
uniform int height;
uniform int depth;
uniform float samplingStepSize;

uniform mat3 filterKernelX;
uniform mat3 filterKernelY;

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
		vec3 step = normalize(direction)*samplingStepSize;
		
		float maximum = 0;
		float val;
		bool firstHit = false;
		
		if(rendering<2){
			for(step; start.z<end.z && !firstHit; start+=step){
				vec3 c =  texture(volumeTexture, start/textureSize).xyz;
				val = max(max(c.x, c.y), c.z);
				if(maximum<val){
					maximum = val;
					if(rendering==1) firstHit = true;
				}			
			}
		}else{
			mat3 neighbourhood;
			for(step; start.z<end.z && !firstHit; start+=step){
				float i000 = texture(volumeTexture, vec3(start.x-1, start.y-1, start.z)/textureSize).x;
				float i001 = texture(volumeTexture, vec3(start.x-1, start.y, start.z)/textureSize).x;
				float i010 = texture(volumeTexture, vec3(start.x-1, start.y+1, start.z)/textureSize).x;
				float i011 = texture(volumeTexture, vec3(start.x, start.y-1, start.z)/textureSize).x;
				float i100 = texture(volumeTexture, vec3(start.x, start.y, start.z)/textureSize).x;
				float i101 = texture(volumeTexture, vec3(start.x, start.y+1, start.z)/textureSize).x;
				float i110 = texture(volumeTexture, vec3(start.x+1, start.y-1, start.z)/textureSize).x;
				float i111 = texture(volumeTexture, vec3(start.x+1, start.y, start.z)/textureSize).x;
				float i1000 = texture(volumeTexture, vec3(start.x+1, start.y+1, start.z)/textureSize).x;
				
				neighbourhood = mat3(i000, i001, i010,
									 i011, i100, i101,
									 i110, i111, i1000);

			    mat3 Gx = filterKernelX*neighbourhood;
				mat3 Gy = filterKernelY*neighbourhood;

				float sGx = Gx[0][0]+Gx[0][1]+Gx[0][2]+Gx[1][0]+Gx[1][1]+Gx[1][2]+Gx[2][0]+Gx[2][1]+Gx[2][2];
				float sGy = Gy[0][0]+Gy[0][1]+Gy[0][2]+Gy[1][0]+Gy[1][1]+Gy[1][2]+Gy[2][0]+Gy[2][1]+Gy[2][2];
				val =  atan(sqrt(pow(sGx, 2) + pow(sGy, 2)));
				maximum = max(val, maximum);
			}		
		}
		color = vec4(maximum, maximum, maximum, start);		
	}	
	else{
		color = vec4(0,0,0,0);
	}	
}