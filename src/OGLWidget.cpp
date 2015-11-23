#include "OGLWidget.h"

OGLWidget::OGLWidget(QWidget *parent) :
		QGLWidget(QGLFormat(), parent)
{
	fileLoaded = false;	
}

OGLWidget::~OGLWidget()
{

}

void OGLWidget::initializeGL()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
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
	if (fileLoaded){/*

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		QMatrix4x4 mMatrix;
		QMatrix4x4 vMatrix;

		shaderProgram.bind();
		shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);
		shaderProgram.setUniformValue("color", QVector4D(0.5, 0, 0, 1));
		shaderProgram.setAttributeArray("vertex", vertices.constData());
		shaderProgram.enableAttributeArray("vertex");
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		shaderProgram.disableAttributeArray("vertex");
		shaderProgram.release();

	}else{*/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float* pixel = &data[0];
		glDrawPixels(640, 480, GL_LUMINANCE, GL_FLOAT, pixel);
		shaderProgram.release();
	}
}

QSize OGLWidget::sizeHint() const
{
	return QSize(640, 480);
}

void OGLWidget::resizeGL(int w, int h)
{
	if (h == 0){
		h = 1;
	}
	pMatrix.setToIdentity();
	pMatrix.perspective(60.f, (float) w / (float) h, .2f, 10.f);
	glViewport(0, 0, w, h);
}