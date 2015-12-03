#pragma once
#ifndef OGLWIDGET_H
#define OGLWIDGET_H

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

	Volume* volume;

	std::vector<float> data;
	float* pixel;

	void setVolume(Volume* v);
	void changeRotationAxis(RotationAxis r);
	void changeInterpolation(Interpolation i);
	void changeRendering(Rendering r);

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	QMatrix4x4 pMatrix;
	QGLShaderProgram shaderProgram;
	QVector<QVector3D> vertices;
};
#endif