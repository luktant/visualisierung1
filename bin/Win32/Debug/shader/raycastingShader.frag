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
//x=0, y=1, z=2
uniform int rotationAxis;
uniform float samplingStepSize;
uniform float firstHitThreshold;

uniform mat3 filterKernelX;
uniform mat3 filterKernelY;

uniform sampler2D entryPoint;
uniform sampler2D exitPoint;
uniform sampler3D volumeTexture;


vec3 getKernelResult(vec3 start){
	//vars
	float i000, i001, i010, i011, i100, i101, i110, i111, i1000, sGx, sGy;
	mat3 neighbourhood, Gx, Gy;
	vec3 textureSize = vec3(width, height, depth);
	//result
	vec3 result = vec3(0,0,0);

	i000 = texture(volumeTexture, vec3(start.x-1, start.y-1, start.z)/textureSize).x;
	i001 = texture(volumeTexture, vec3(start.x-1, start.y, start.z)/textureSize).x;
	i010 = texture(volumeTexture, vec3(start.x-1, start.y+1, start.z)/textureSize).x;
	i011 = texture(volumeTexture, vec3(start.x, start.y-1, start.z)/textureSize).x;
	i100 = texture(volumeTexture, vec3(start.x, start.y, start.z)/textureSize).x;
	i101 = texture(volumeTexture, vec3(start.x, start.y+1, start.z)/textureSize).x;
	i110 = texture(volumeTexture, vec3(start.x+1, start.y-1, start.z)/textureSize).x;
	i111 = texture(volumeTexture, vec3(start.x+1, start.y, start.z)/textureSize).x;
	i1000 = texture(volumeTexture, vec3(start.x+1, start.y+1, start.z)/textureSize).x;
	neighbourhood = mat3(i000, i001, i010,
						 i011, i100, i101,
						 i110, i111, i1000);
	Gx = filterKernelX*neighbourhood;
	Gy = filterKernelY*neighbourhood;
	sGx = Gx[0][0]+Gx[0][1]+Gx[0][2]+Gx[1][0]+Gx[1][1]+Gx[1][2]+Gx[2][0]+Gx[2][1]+Gx[2][2];
	sGy = Gy[0][0]+Gy[0][1]+Gy[0][2]+Gy[1][0]+Gy[1][1]+Gy[1][2]+Gy[2][0]+Gy[2][1]+Gy[2][2];
	result.x = atan(sqrt(pow(sGx, 2) + pow(sGy, 2)));

	i000 = texture(volumeTexture, vec3(start.x, start.y-1, start.z-1)/textureSize).x;
	i001 = texture(volumeTexture, vec3(start.x, start.y-1, start.z)/textureSize).x;
	i010 = texture(volumeTexture, vec3(start.x, start.y-1, start.z+1)/textureSize).x;
	i011 = texture(volumeTexture, vec3(start.x, start.y, start.z-1)/textureSize).x;
	i100 = texture(volumeTexture, vec3(start.x, start.y, start.z)/textureSize).x;
	i101 = texture(volumeTexture, vec3(start.x, start.y, start.z+1)/textureSize).x;
	i110 = texture(volumeTexture, vec3(start.x, start.y+1, start.z-1)/textureSize).x;
	i111 = texture(volumeTexture, vec3(start.x, start.y+1, start.z)/textureSize).x;
	i1000 = texture(volumeTexture, vec3(start.x, start.y+1, start.z+1)/textureSize).x;
	neighbourhood = mat3(i000, i001, i010,
						 i011, i100, i101,
						 i110, i111, i1000);
	Gx = filterKernelX*neighbourhood;
	Gy = filterKernelY*neighbourhood;
	sGx = Gx[0][0]+Gx[0][1]+Gx[0][2]+Gx[1][0]+Gx[1][1]+Gx[1][2]+Gx[2][0]+Gx[2][1]+Gx[2][2];
	sGy = Gy[0][0]+Gy[0][1]+Gy[0][2]+Gy[1][0]+Gy[1][1]+Gy[1][2]+Gy[2][0]+Gy[2][1]+Gy[2][2];
	result.y = atan(sqrt(pow(sGx, 2) + pow(sGy, 2)));

	i000 = texture(volumeTexture, vec3(start.x-1, start.y, start.z-1)/textureSize).x;
	i001 = texture(volumeTexture, vec3(start.x, start.y, start.z-1)/textureSize).x;
	i010 = texture(volumeTexture, vec3(start.x+1, start.y, start.z-1)/textureSize).x;
	i011 = texture(volumeTexture, vec3(start.x-1, start.y, start.z)/textureSize).x;
	i100 = texture(volumeTexture, vec3(start.x, start.y, start.z)/textureSize).x;
	i101 = texture(volumeTexture, vec3(start.x+1, start.y, start.z)/textureSize).x;
	i110 = texture(volumeTexture, vec3(start.x-1, start.y, start.z+1)/textureSize).x;
	i111 = texture(volumeTexture, vec3(start.x, start.y, start.z+1)/textureSize).x;
	i1000 = texture(volumeTexture, vec3(start.x+1, start.y, start.z+1)/textureSize).x;
	neighbourhood = mat3(i000, i001, i010,
						 i011, i100, i101,
						 i110, i111, i1000);
	Gx = filterKernelX*neighbourhood;
	Gy = filterKernelY*neighbourhood;
	sGx = Gx[0][0]+Gx[0][1]+Gx[0][2]+Gx[1][0]+Gx[1][1]+Gx[1][2]+Gx[2][0]+Gx[2][1]+Gx[2][2];
	sGy = Gy[0][0]+Gy[0][1]+Gy[0][2]+Gy[1][0]+Gy[1][1]+Gy[1][2]+Gy[2][0]+Gy[2][1]+Gy[2][2];
	result.z = atan(sqrt(pow(sGx, 2) + pow(sGy, 2)));
	return result;
}


void main(){
	
	vec3 textureSize = vec3(width, height, depth);
	vec3 start = (texture(entryPoint, uv).xyz)*textureSize;	
	vec3 end = (texture(exitPoint, uv).xyz)*textureSize;	
	
	if(start!=end){		
		vec3 temp;	
		//Switch		
		if(distance(pos, start)>distance(pos,end)){
			temp = end;
			end = start;
			start = temp;		
		}
		if(rotationAxis==0 && start.x>end.x){
			temp = end;
			end = start;
			start = temp;
		}
		if(rotationAxis==1 && start.y>end.y){
			temp = end;
			end = start;
			start = temp;
		}
		if(rotationAxis==2 && start.z>end.z){
			temp = end;
			end = start;
			start = temp;
		}
		vec3 direction = (end-start);
		vec3 step = normalize(direction)*samplingStepSize;

		float maximum = 0;
		float val;		
		bool firstHit = false;
		
		//Different rendering types:
		if(rendering == 0 || rendering == 1){//MIP or FirstHit
			for(step; !firstHit && (rotationAxis==0 && end.x>start.x)||(rotationAxis==1 && end.y>start.y)||(rotationAxis==2 && end.z>start.z); start+=step){
				vec3 c =  texture(volumeTexture, start/textureSize).xyz;
				val = max(max(c.x, c.y), c.z);
				if(maximum<val){
					maximum = val;
					if(rendering==1 && val >= firstHitThreshold){
						firstHit=true;
						break;
					}
				}			
			}
			color = vec4(maximum, maximum, maximum, start);
		}else if(rendering == 2){ //Alpha Compositing
			vec4 alphaCompRGBA_a = vec4(0, 0, 0, 0);
			for(step; (rotationAxis==0 && end.x>start.x)||(rotationAxis==1 && end.y>start.y)||(rotationAxis==2 && end.z>start.z); start+=step){
				val = texture(volumeTexture, start/textureSize).x;
				vec4 alphaCompRGBA_b = vec4(0, val, 0, val);
				float alpha_c = alphaCompRGBA_a.w + (1 - alphaCompRGBA_a.w)*alphaCompRGBA_b.w;
				vec4 alphaCompRGBA_c = vec4(0, 0, 0, alpha_c);
				alphaCompRGBA_c = (1 / alpha_c) * (alphaCompRGBA_a.w * alphaCompRGBA_a + (1 - alphaCompRGBA_a.w)*alphaCompRGBA_b.w * alphaCompRGBA_b);
				alphaCompRGBA_a = alphaCompRGBA_c;
				if (alphaCompRGBA_a.w == 1)break;
			}
			color = alphaCompRGBA_a; //vec4(alphaCompRGBA_a.y, alphaCompRGBA_a.x, alphaCompRGBA_a.z, alphaCompRGBA_a.w);
		}else{//gradient
			vec3 grad;
			vec3 actual;
			for(step; (rotationAxis==0 && end.x>start.x)||(rotationAxis==1 && end.y>start.y)||(rotationAxis==2 && end.z>start.z); start+=step){		
				actual = getKernelResult(start);
				if(length(grad)<length(actual))grad = actual;
				maximum = max(val, maximum);
			}		
			color = vec4(grad, 1);
		}
	}	
	else{
		color = vec4(0,0,0,0);
	}	
}

