#pragma once

#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QWidget>
#include <gl/GLU.h>
#include <gl/GL.h>
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

class OGLWidget : public QGLWidget
{
public:
	OGLWidget(QWidget *parent = 0);
	~OGLWidget();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};
#endif