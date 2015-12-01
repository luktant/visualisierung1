#include "OGLWidget.h"

OGLWidget::OGLWidget(QWidget *parent) :
		QGLWidget(QGLFormat(), parent)
{
	fileLoaded = false;
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	width = 640;
	heigth = 480;
	rotationSpeed = 0.f;
	pixel[640 * 480];
	timer->start(1);
}

OGLWidget::~OGLWidget()
{

}

void OGLWidget::initializeGL()
{
	qglClearColor(QColor(Qt::black));
	shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, "shader/simple.vert");
	shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, "shader/simple.frag");
	
	shaderProgram.link();
	if (!shaderProgram.bind()){
		qWarning() << "Couldnt bind shader program";
		return;
	}
	vertices<<QVector3D(1, 0, -2) <<QVector3D(0, 1, -2) <<QVector3D(-1, 0, -2);
}

void OGLWidget::paintGL()
{	
	if (fileLoaded){
		volume->rotate(rotationSpeed);
		data = volume->rayCast();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float* pixel = &data[0];
		glDrawPixels(width, heigth, GL_LUMINANCE, GL_FLOAT, pixel);
		shaderProgram.release();
	}
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
	if (i == Interpolation::NEAREST){ volume->trilinear = false; std::cout << "NEAREST" << std::endl; }
	else{ volume->trilinear = true; std::cout << "TRILINEAR" << std::endl; }
}