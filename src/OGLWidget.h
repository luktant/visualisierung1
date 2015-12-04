#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <QtOpenGL/QGLWidget>
#include <QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>
#include <QtOpenGL>
#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <vector>
#include "Volume.h"

enum RotationAxis{ X, Y, Z };
enum Interpolation{NEAREST, TRILINEAR};
enum Rendering{ MIP, FIRSTHIT };

class OGLWidget : public QGLWidget
{

public:
	OGLWidget(QWidget *parent = 0);
	~OGLWidget();
	
	int width, heigth;
	float rotationSpeed;
	RotationAxis actualAxis = RotationAxis::Y;

	bool fileLoaded;
	bool ready;
	bool useGPU;

	Volume* volume;

	std::vector<float> data;
	float* pixel;

	void setVolume(Volume* v);
	void changeRotationAxis(RotationAxis r);
	void changeInterpolation(Interpolation i);
	void changeRendering(Rendering r);
	void gpuRayCast();
	void initializeBuffers();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	GLuint volumeBuffer;
	GLuint VAO;

	QMatrix4x4 pMatrix;
	QGLShaderProgram raycastingShader;
	QVector<QVector3D> vertices;
};