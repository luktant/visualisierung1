#include "OGLWidget.h"

OGLWidget::OGLWidget(QWidget *parent) :
		QGLWidget(QGLFormat(), parent)
{
	fileLoaded = false;
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	useGPU = true;
	width = 640;
	heigth = 480;
	rotationSpeed = 0.f;
	pixel[640 * 480];
	timer->start(1);
}

OGLWidget::~OGLWidget()
{
	delete pixel;
	__glewDeleteBuffers(1, &volumeBuffer);	
	glDeleteVertexArrays(1, &VAO);
}

void OGLWidget::initializeGL()
{
	if (!glfwInit())
	{
		std::cout << "Failed to init glfw, using only CPU" << std::endl;
		useGPU = false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew, using only CPU" << std::endl;
		useGPU = false;
	}
	//Bugfixes..
	__glewGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glfwGetProcAddress("glGenVertexArrays");
	__glewBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
	__glewDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glfwGetProcAddress("glDeleteVertexArrays");
	__glewGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glfwGetProcAddress("glGenerateMipmap");
	__glewGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)glfwGetProcAddress("glGenFramebuffers");
	__glewBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)glfwGetProcAddress("glBindFramebuffer");
	__glewCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)glfwGetProcAddress("glCheckFramebufferStatus");
	__glewFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)glfwGetProcAddress("glFramebufferTexture");

	qglClearColor(QColor(Qt::black));
	raycastingShader.addShaderFromSourceFile(QGLShader::Vertex, "shader/simple.vert");
	raycastingShader.addShaderFromSourceFile(QGLShader::Fragment, "shader/simple.frag");	
	raycastingShader.link();	
}

void OGLWidget::paintGL()
{	
	if (fileLoaded){
		if (useGPU){
			if (!raycastingShader.bind()){
				qWarning() << "Couldnt bind shader program, using only CPU";
				useGPU = false;
				return;
			}
			//DRAW..
			raycastingShader.release();
		}
		else{
			double t = glfwGetTime();
			volume->rotate(rotationSpeed);
			data = volume->rayCast();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			float* pixel = &data[0];
			glDrawPixels(width, heigth, GL_LUMINANCE, GL_FLOAT, pixel);
			double t1 = glfwGetTime();
			std::cout << 1.0f/(t1 - t)<<" FPS" << std::endl;
		}
	}
}

void OGLWidget::initializeBuffers()
{
	//load data to buffer
	__glewGenBuffers(1, &volumeBuffer);
	__glewBindBuffer(GL_ARRAY_BUFFER, volumeBuffer);	
	__glewBufferData(GL_ARRAY_BUFFER, volume->m_Size * sizeof(float), pixel, GL_LUMINANCE);	
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//LOAD volume data in vao
	
	glBindVertexArray(0);
}

void OGLWidget::gpuRayCast()
{

}

void OGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLint)w, (GLint)h);
	qglClearColor(QColor(Qt::black));
	pixel[w*h];
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