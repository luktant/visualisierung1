#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_MainWindow.h"
#include "Volume.h"
#include "VectorField.h"
#include "MultiSet.h"
#include <vector>
#include <QFileDialog>
#include <QPainter>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QStatusBar>
#include <QVariant>


class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:

		MainWindow(QWidget *parent = 0);
		~MainWindow();

	
	protected slots :
		void								 openFileAction();
		void								 closeAction();

	public slots:
		void								 interpolationChanged();
		void								 renderingChanged();
		void								 rotationChanged();
		void								 setRotationSpeed(double s);
		void								 moveUp();
		void								 moveDown();
		void								 moveLeft();
		void								 moveRight();
		void								 zoom(double value);							 
		void								 useGPU(bool);
		void								 changeSamplingStepsize(double);
	private:

		// USER INTERFACE ELEMENTS

		Ui_MainWindow						*m_Ui;


		// DATA 

		enum DataType
		{
			VOLUME					= 0,
			VECTORFIELD				= 1,
			MULTIVARIATE			= 2
		};

		struct FileType
		{
			QString			filename;
			DataType		type;
		}									 m_FileType;

		Volume								*m_Volume;						// for Volume-Rendering
		VectorField							*m_VectorField;					// for Flow-Visualisation
		MultiSet							*m_MultiSet;					// for Multivariate Data

};

#endif
