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
	double samplingStepSize = 1.0;
	float pi = 3.141592653589793238462643;
	RotationAxis actualAxis = RotationAxis::Y;

	bool fileLoaded;
	bool ready;
	bool useGPU = false;
	Volume* volume;
	std::vector<float> data;
	float* pixel;
	glm::mat4 Proj, View, Model, mvp;
	glm::vec3 cameraPosition = glm::vec3(-4, 2, 2);

	void setVolume(Volume* v);
	void changeRotationAxis(RotationAxis r);
	void changeInterpolation(Interpolation i);
	void changeRendering(Rendering r);
	void gpuRayCast();
	void move(Direction d);
	void zoom(double value);
	void initializeShaderAndBuffer();
	void changeGPUandCPU(bool use);

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	// only for fps calculation
	double lastTime;
	double lastFrameCalc = 0.f;
	int frameCount = 0;
	int fps = 0;
	float deltaT;

	GLuint viewPlaneBuffer;
	GLuint viewIndexBuffer;
	GLuint positionBuffer;
	GLuint indexBuffer;
	GLuint VAO;
	GLuint VAOview;
	GLuint FBOentry;
	GLuint FBOexit;
	GLuint volumeTexture; //volume data for shader (3D texture)
	GLuint entryPoint;    //ray entry point (2D texture)
	GLuint exitPoint;     //ray exit point (2D texture)
	GLuint db; //depth buffer

	Shader* raycastingShader;
	Shader* framebufferShader;
	Shader* viewPlaneShader;
	void renderToTexture();
	void countFPS();
};