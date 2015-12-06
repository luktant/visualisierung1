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
#include <QOpenGLTexture>
#include <QTimer>
#include <vector>
#include "Volume.h"
#include "Shader.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

enum RotationAxis{ X, Y, Z };
enum Interpolation{NEAREST, TRILINEAR};
enum Rendering{ MIP, FIRSTHIT };
enum Direction{UP, DOWN, LEFT, RIGHT};

class OGLWidget : public QGLWidget
{

public:
	OGLWidget(QWidget *parent = 0);
	~OGLWidget();
	
	int width, height;
	float rotationSpeed;
	RotationAxis actualAxis = RotationAxis::Y;

	bool fileLoaded;
	bool ready;
	bool useGPU = false;
	Volume* volume;

	std::vector<float> data;
	float* pixel;

	void setVolume(Volume* v);
	void changeRotationAxis(RotationAxis r);
	void changeInterpolation(Interpolation i);
	void changeRendering(Rendering r);
	void gpuRayCast();
	void move(Direction d);
	void zoom(int value);
	void initializeShaderAndBuffer();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	GLuint positionBuffer;
	GLuint indexBuffer;
	GLuint VAO;
	GLuint texid;

	Shader* raycastingShader;
};