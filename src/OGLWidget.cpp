#include "OGLWidget.h"

OGLWidget::OGLWidget(QWidget *parent) :
QGLWidget(QGLFormat(), parent)
{
	fileLoaded = false;
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	width = 640;
	height = 480;
	rotationSpeed = 0.f;
	pixel[640 * 480];
	timer->start(1);
}

OGLWidget::~OGLWidget()
{
	delete pixel;
	glDeleteTextures(1, &entryPoint);
	glDeleteTextures(1, &exitPoint);
	glDeleteTextures(1, &volumeTexture);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VAOview);
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &viewPlaneBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &viewIndexBuffer);
	glDeleteBuffers(1, &FBOentry);
	glDeleteBuffers(1, &FBOexit);
}

void OGLWidget::initializeGL()
{
	//Init GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to init glfw, using only CPU" << std::endl;
		useGPU = true;
	}
	//Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew, using only CPU" << std::endl;
		useGPU = false;
	}
	qglClearColor(QColor(Qt::black));
}

void OGLWidget::paintGL()
{
	if (fileLoaded){
		countFPS();
		if (useGPU){			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
			gpuRayCast();
			
		}
		else{			
			volume->rotate(rotationSpeed);
			volume->samplingStepSize = samplingStepSize;
			data = volume->rayCast();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			float* pixel = &data[0];
			glDrawPixels(width, height, GL_LUMINANCE, GL_FLOAT, pixel);
		}		
	}
}

void OGLWidget::initializeShaderAndBuffer(){
	framebufferShader = new Shader("shader/FBOshader.vert", "shader/FBOshader.frag");
	raycastingShader = new Shader("shader/raycastingShader.vert", "shader/raycastingShader.frag");
	float viewPlane[12] = {
		-1, -1, 0,
		-1, 1, 0,
		1, 1, 0,
		1, -1, 0 };
	unsigned int viewIndices[6] = { 0, 1, 2, 0, 2, 3 };

	float boundingBox[72] = {
		//Back
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,
		1, 0, 0,

		//Front
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,

		//Top
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,
		0, 1, 1,

		//Bottom
		1, 0, 1,
		0, 0, 1,
		0, 0, 0,
		1, 0, 0,

		//Right
		1, 1, 1,
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,

		// Left
		0, 1, 1,
		0, 1, 0,
		0, 0, 0,
		0, 0, 1 };


	const unsigned int indices[36] = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23 };

	//Setting values for raycasting Shader
	GLuint shaderHandle = framebufferShader->programHandle;
		
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), boundingBox, GL_STATIC_DRAW); //24=vertexcount
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), indices, GL_STATIC_DRAW); //36=indexcount
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	GLint positionIndex = glGetAttribLocation(shaderHandle, "position");
	glEnableVertexAttribArray(positionIndex);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_3D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Setting values for raycasting Shader
	GLuint sH = raycastingShader->programHandle;

	glGenBuffers(1, &viewPlaneBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, viewPlaneBuffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), viewPlane, GL_STATIC_DRAW); //4=vertexcount
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &viewIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, viewIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), viewIndices, GL_STATIC_DRAW); //6=indexcount
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//3D texture is used to store the volumetric data for the shader
	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &volumeTexture);
	glBindTexture(GL_TEXTURE_3D, volumeTexture);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3D(GL_TEXTURE_3D,      // 3D texture
		0,                  // level 0 mipmapping
		GL_RGB,       // pixel format of texture
		volume->width(), volume->height(), volume->depth(), // texture size
		0,                  // border size 0
		GL_LUMINANCE,       // pixel format of data supplied
		GL_FLOAT,			// pixel storage type of data supplied
		volume->voxels());// pointer to data chunk
	glDisable(GL_TEXTURE_3D);

	glGenVertexArrays(1, &VAOview);
	glBindVertexArray(VAOview);

	glBindBuffer(GL_ARRAY_BUFFER, viewPlaneBuffer);
	GLint vIndex = glGetAttribLocation(sH, "viewPlane");
	glEnableVertexAttribArray(vIndex);
	glVertexAttribPointer(vIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, viewIndexBuffer);

	glBindVertexArray(0);	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	//generate textures and framebuffer objects for ray entry and exit point
	//FBO for entry point + texture for entry point
	glGenTextures(1, &entryPoint);
	glBindTexture(GL_TEXTURE_2D, entryPoint);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glGenerateMipmap(GL_TEXTURE_2D);
	glGenFramebuffers(1, &FBOentry);
	glBindFramebuffer(GL_FRAMEBUFFER, FBOentry);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, entryPoint, 0);
	glGenRenderbuffers(1, &db);
	glBindRenderbuffer(GL_RENDERBUFFER, db);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, db);
	GLenum status;
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "FB error, status: " << status << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//FBO for exit point + texture for exit point
	glGenTextures(1, &exitPoint);
	glBindTexture(GL_TEXTURE_2D, exitPoint);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glGenerateMipmap(GL_TEXTURE_2D);
	glGenFramebuffers(1, &FBOexit);
	glBindFramebuffer(GL_FRAMEBUFFER, FBOexit);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, exitPoint, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, db);
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "FB error, status: " << status << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 10.0f);
	//Proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 6.0f, -1.0f);
	//Proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.1f, 100.0f);
	View = glm::lookAt(
		cameraPosition, //Camera is at
		glm::vec3(0.5, 0.5, 0.5), //looks at
		glm::vec3(0, 1, 0));  //upvector
	
	Model = glm::mat4(1.0f);
	mvp = (Proj * View * Model);
}

void OGLWidget::gpuRayCast()
{
	//first pass, render ray entry and exit point to texture
	renderToTexture();	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//second pass, render view plane, raycasting is performed in the raycasting shader

	glUseProgram(raycastingShader->programHandle);

	//Set the 2D textures (entry- and exitpoint of ray)
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entryPoint);
	auto tex_location = glGetUniformLocation(raycastingShader->programHandle, "entryPoint");
	glUniform1i(tex_location, 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, exitPoint);
	tex_location = glGetUniformLocation(raycastingShader->programHandle, "exitPoint");
	glUniform1i(tex_location, 1);

	//Set the 3D texture (volume Data);
	glEnable(GL_TEXTURE_3D),
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_3D, volumeTexture);
	tex_location = glGetUniformLocation(raycastingShader->programHandle, "volumeTexture");
	glUniform1i(tex_location, 2);
	glDisable(GL_TEXTURE_3D);

	//width, height, depth, renderingtype (enum) and stepsize as uniforms
	auto loc = glGetUniformLocation(raycastingShader->programHandle, "width");
	glUniform1i(loc, volume->width());

	loc = glGetUniformLocation(raycastingShader->programHandle, "height");
	glUniform1i(loc, volume->height());
	
	loc = glGetUniformLocation(raycastingShader->programHandle, "depth");
	glUniform1i(loc, volume->depth());

	loc = glGetUniformLocation(raycastingShader->programHandle, "rendering");
	glUniform1i(loc, volume->rendering);
	
	loc = glGetUniformLocation(raycastingShader->programHandle, "samplingStepSize");
	glUniform1f(loc, (float)samplingStepSize);

	glBindVertexArray(VAOview);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
	glUseProgram(0);
}

void OGLWidget::renderToTexture()
{
	//First update the ModelViewProjection Matrix in case of rotations etc.
	Model = glm::translate(Model, glm::vec3(0.5f, 0.5f, 0.5f));
	Model = glm::rotate(Model, (pi/8*rotationSpeed)/(float)glfwGetTime(), (actualAxis == RotationAxis::X ? glm::vec3(1, 0, 0) : (actualAxis == RotationAxis::Y ? glm::vec3(0, 1, 0) : glm::vec3(0, 0, 1))));
	Model = glm::translate(Model, glm::vec3(-0.5f, -0.5f, -0.5f));
	
	mvp = (Proj * View * Model);

	//Render in texture ENTRY POINT
	glBindFramebuffer(GL_FRAMEBUFFER, FBOentry);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0); //Use this line to display the texture entryPoint
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);	

	glUseProgram(framebufferShader->programHandle);

	auto mvp_loc = glGetUniformLocation(framebufferShader->programHandle, "mvp");
	glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	//Render in texture EXIT POINT
	glBindFramebuffer(GL_FRAMEBUFFER, FBOexit);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);//Use this line to display the texture exitPoint
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

	glUseProgram(framebufferShader->programHandle);

	mvp_loc = glGetUniformLocation(framebufferShader->programHandle, "mvp");
	glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void OGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLint)w, (GLint)h);
	qglClearColor(QColor(Qt::black));
	pixel[w*h];
}

void OGLWidget::move(Direction d){
	switch (d){
	case Direction::UP:
		volume->translate(0);
		View = glm::translate(View, glm::vec3(0, .1f, 0));
		break;
	case Direction::DOWN:
		volume->translate(1);
		View = glm::translate(View, glm::vec3(0, -.1f, 0));
		break;
	case Direction::LEFT:
		volume->translate(2);
		View = glm::translate(View, glm::vec3(-.1f, 0, -.25f));
		break;
	case Direction::RIGHT:
		volume->translate(3);
		View = glm::translate(View, glm::vec3(.1f, 0, .25f));
		break;
	}	
}

void OGLWidget::zoom(double value)
{
	std::cout << value << std::endl;
	Proj = glm::perspective(glm::radians(45.0f) - glm::radians((float)value), (float)width / (float)height, 0.1f, 10.0f);	
}

void OGLWidget::setVolume(Volume* v)
{
	this->volume = v;
}

void OGLWidget::changeRotationAxis(RotationAxis r)
{
	actualAxis = r;
	if (r == RotationAxis::X) volume->rAxis = Volume::Axis::X;
	else if (r == RotationAxis::Y) volume->rAxis = Volume::Axis::Y;
	else volume->rAxis = Volume::Axis::Z;
}

void OGLWidget::changeInterpolation(Interpolation i)
{
	if (i == Interpolation::NEAREST) volume->trilinear = false;
	else volume->trilinear = true;
}

void OGLWidget::changeRendering(Rendering r)
{
	if (r == Rendering::MIP) volume->rendering = Volume::Rendering::MIP;
	else volume->rendering = Volume::Rendering::FIRSTHIT;
}

void OGLWidget::countFPS(){	
	frameCount++;	
	double time;
	time = glfwGetTime();
	if (lastFrameCalc == 0.0f || (time - lastFrameCalc) >= 1.0f) {
		fps = frameCount;
		frameCount = 0;
		lastFrameCalc = time;
		std::cout <<fps <<" FPS"<< std::endl;
	}
	deltaT = time - lastTime;
	lastTime = time;	
}

void OGLWidget::changeGPUandCPU(bool use){
	useGPU = use;
}