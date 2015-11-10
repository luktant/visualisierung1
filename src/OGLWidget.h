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

class OGLWidget : public QGLWidget
{

public:
	OGLWidget(QWidget *parent = 0);
	~OGLWidget();
	
	QSize sizeHint() const;
	bool fileLoaded;

	void paintGL();

protected:
	void initializeGL();
	void resizeGL(int w, int h);

private:
	QMatrix4x4 pMatrix;
	QGLShaderProgram shaderProgram;
	QVector<QVector3D> vertices;
};
#endif