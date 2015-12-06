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
	delete pixel,
	glDeleteTextures(1, &texid);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void OGLWidget::initializeGL()
{	
	//Init GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to init glfw, using only CPU" << std::endl;
		useGPU = false;
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
		double t = glfwGetTime();
		if (useGPU){
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
			gpuRayCast();
		}
		else{			
			volume->rotate(rotationSpeed);
			data = volume->rayCast();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			float* pixel = &data[0];
			glDrawPixels(width, height, GL_LUMINANCE, GL_FLOAT, pixel);			
		}
		double t1 = glfwGetTime();
		if ((int)t1>(int)t) std::cout << 1.0f / (t1 - t) << " FPS" << std::endl;
	}	
}

void OGLWidget::initializeShaderAndBuffer(){
	raycastingShader = new Shader("shader/simple.vert", "shader/simple.frag");
	
	
	float positions[12] = {
		-1, -1, 0,
		-1, 1, 0,
		1, 1, 0,
		1, -1, 0 };
	
	unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };

	int vertexCount = 4;
	int indexCount = 6;

	GLuint shaderHandle = raycastingShader->programHandle;

	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount* sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//3D texture is used to store the volumetric data for the shader
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_3D, texid);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//--- Not sure if this works, couldnt access volume Data so far but to use a 3D texture for the voxel data should be the best solution
	glTexImage3D(GL_TEXTURE_3D,      // 3D texture
		0,                  // level 0 (for mipmapping)
		GL_LUMINANCE,       // pixel format of texture
		volume->width(), volume->height(), volume->depth(), // texture size
		0,                  // border size 0
		GL_LUMINANCE,       // pixel format of data supplied
		GL_FLOAT,			// pixel storage type of data supplied
		volume->voxels());// pointer to data chunk
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
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
}

void OGLWidget::gpuRayCast()
{
	glUseProgram(raycastingShader->programHandle);
	glBindVertexArray(VAO);
	//set the uniforms
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_3D);

	// bind volume data
	glBindTexture(GL_TEXTURE_3D, texid);
	auto tex_location = glGetUniformLocation(raycastingShader->programHandle, "volumeData");
	glUniform1i(tex_location, 0);
		
	glBindVertexArray(this->VAO);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_3D, 0);
	glDisable(GL_TEXTURE_3D);
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
		break;
	case Direction::DOWN:
		volume->translate(1);
		break;
	case Direction::LEFT:
		volume->translate(2);
		break;
	case Direction::RIGHT:
		volume->translate(3);
		break;
	}
}

void OGLWidget::zoom(int value)
{
	if (value>0){
		//ZOOM IN
		std::cout << "Zoom in not implementet yet.." << std::endl;
	}
	else if(value<0){
		//ZOOM OUT
		std::cout << "Zoom out not implementet yet.." << std::endl;
	}
}

void OGLWidget::setVolume(Volume* v)
{
	this->volume = v;
}

void OGLWidget::changeRotationAxis(RotationAxis r)
{
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