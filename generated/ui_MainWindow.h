/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>
#include "OGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QWidget *centralwidget;
    QLabel *labelTop;
    QProgressBar *progressBar;
    QFrame *line;
    OGLWidget *openGLWidget;
    QGroupBox *interpolationBox;
    QRadioButton *nearestRadio;
    QRadioButton *trilinearRadio;
    QGroupBox *transformationBox;
    QGroupBox *groupBox;
    QRadioButton *zaxis;
    QRadioButton *xaxis;
    QRadioButton *yaxis;
    QLabel *label_2;
    QLabel *label;
    QDoubleSpinBox *rotationSpeed;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QPushButton *downButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *upButton;
    QGroupBox *groupBox_3;
    QLabel *label_4;
    QDoubleSpinBox *zoomFaktor;
    QCheckBox *gradientCheckBox;
    QGroupBox *renderingBox;
    QRadioButton *MIPRadio;
    QRadioButton *firstHitRadio;
    QCheckBox *gpuBox;
    QGroupBox *groupBox_4;
    QLabel *label_5;
    QDoubleSpinBox *sampling;
    QMenuBar *menubar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(985, 564);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelTop = new QLabel(centralwidget);
        labelTop->setObjectName(QStringLiteral("labelTop"));
        labelTop->setGeometry(QRect(20, 20, 1001, 16));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(false);
        progressBar->setGeometry(QRect(610, 20, 201, 23));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 50, 1011, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        openGLWidget = new OGLWidget(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 60, 640, 480));
        interpolationBox = new QGroupBox(centralwidget);
        interpolationBox->setObjectName(QStringLiteral("interpolationBox"));
        interpolationBox->setGeometry(QRect(650, 200, 161, 81));
        nearestRadio = new QRadioButton(interpolationBox);
        nearestRadio->setObjectName(QStringLiteral("nearestRadio"));
        nearestRadio->setGeometry(QRect(20, 20, 131, 17));
        nearestRadio->setCheckable(false);
        nearestRadio->setChecked(false);
        trilinearRadio = new QRadioButton(interpolationBox);
        trilinearRadio->setObjectName(QStringLiteral("trilinearRadio"));
        trilinearRadio->setGeometry(QRect(20, 50, 111, 17));
        trilinearRadio->setCheckable(false);
        trilinearRadio->setChecked(false);
        transformationBox = new QGroupBox(centralwidget);
        transformationBox->setObjectName(QStringLiteral("transformationBox"));
        transformationBox->setGeometry(QRect(650, 330, 331, 201));
        groupBox = new QGroupBox(transformationBox);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 141, 71));
        zaxis = new QRadioButton(groupBox);
        zaxis->setObjectName(QStringLiteral("zaxis"));
        zaxis->setGeometry(QRect(110, 20, 31, 17));
        zaxis->setCheckable(false);
        xaxis = new QRadioButton(groupBox);
        xaxis->setObjectName(QStringLiteral("xaxis"));
        xaxis->setGeometry(QRect(50, 20, 31, 17));
        xaxis->setCheckable(false);
        yaxis = new QRadioButton(groupBox);
        yaxis->setObjectName(QStringLiteral("yaxis"));
        yaxis->setGeometry(QRect(80, 20, 31, 17));
        yaxis->setCheckable(false);
        yaxis->setChecked(false);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 20, 31, 16));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 41, 20));
        rotationSpeed = new QDoubleSpinBox(groupBox);
        rotationSpeed->setObjectName(QStringLiteral("rotationSpeed"));
        rotationSpeed->setGeometry(QRect(60, 40, 62, 22));
        rotationSpeed->setSingleStep(0.1);
        groupBox_2 = new QGroupBox(transformationBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 100, 181, 91));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 40, 41, 21));
        downButton = new QPushButton(groupBox_2);
        downButton->setObjectName(QStringLiteral("downButton"));
        downButton->setGeometry(QRect(64, 63, 54, 23));
        leftButton = new QPushButton(groupBox_2);
        leftButton->setObjectName(QStringLiteral("leftButton"));
        leftButton->setGeometry(QRect(10, 40, 54, 23));
        rightButton = new QPushButton(groupBox_2);
        rightButton->setObjectName(QStringLiteral("rightButton"));
        rightButton->setGeometry(QRect(118, 40, 54, 23));
        upButton = new QPushButton(groupBox_2);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(64, 17, 54, 23));
        groupBox_3 = new QGroupBox(transformationBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(170, 20, 151, 71));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 20, 91, 21));
        zoomFaktor = new QDoubleSpinBox(groupBox_3);
        zoomFaktor->setObjectName(QStringLiteral("zoomFaktor"));
        zoomFaktor->setGeometry(QRect(80, 40, 62, 22));
        zoomFaktor->setMinimum(-30);
        zoomFaktor->setMaximum(30);
        zoomFaktor->setValue(0);
        gradientCheckBox = new QCheckBox(transformationBox);
        gradientCheckBox->setObjectName(QStringLiteral("gradientCheckBox"));
        gradientCheckBox->setGeometry(QRect(210, 110, 111, 17));
		gradientCheckBox->setCheckable(false);
        renderingBox = new QGroupBox(centralwidget);
        renderingBox->setObjectName(QStringLiteral("renderingBox"));
        renderingBox->setGeometry(QRect(820, 200, 161, 81));
        MIPRadio = new QRadioButton(renderingBox);
        MIPRadio->setObjectName(QStringLiteral("MIPRadio"));
        MIPRadio->setGeometry(QRect(20, 20, 131, 17));
        MIPRadio->setCheckable(false);
        firstHitRadio = new QRadioButton(renderingBox);
        firstHitRadio->setObjectName(QStringLiteral("firstHitRadio"));
        firstHitRadio->setGeometry(QRect(20, 50, 111, 17));
        firstHitRadio->setCheckable(false);
        gpuBox = new QCheckBox(centralwidget);
        gpuBox->setObjectName(QStringLiteral("gpuBox"));
        gpuBox->setGeometry(QRect(660, 70, 231, 17));
        gpuBox->setCheckable(false);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(650, 280, 321, 51));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 22, 221, 16));
        sampling = new QDoubleSpinBox(groupBox_4);
        sampling->setObjectName(QStringLiteral("sampling"));
        sampling->setGeometry(QRect(250, 20, 62, 21));
        sampling->setMinimum(0.01);
        sampling->setMaximum(16);
        sampling->setSingleStep(0.01);
        sampling->setValue(1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 985, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Visualisierung 1", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open ...", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        labelTop->setText(QApplication::translate("MainWindow", "No data loaded", 0));
        interpolationBox->setTitle(QApplication::translate("MainWindow", "Interpolation:", 0));
        nearestRadio->setText(QApplication::translate("MainWindow", "Nearest Neighbour", 0));
        trilinearRadio->setText(QApplication::translate("MainWindow", "Trilinear", 0));
        transformationBox->setTitle(QApplication::translate("MainWindow", "Transformations:", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Rotation", 0));
        zaxis->setText(QApplication::translate("MainWindow", "Z", 0));
        xaxis->setText(QApplication::translate("MainWindow", "X", 0));
        yaxis->setText(QApplication::translate("MainWindow", "Y", 0));
        label_2->setText(QApplication::translate("MainWindow", "Axis:", 0));
        label->setText(QApplication::translate("MainWindow", "Velocity:", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Translation", 0));
        label_3->setText(QApplication::translate("MainWindow", "Move", 0));
        downButton->setText(QApplication::translate("MainWindow", "DOWN", 0));
        leftButton->setText(QApplication::translate("MainWindow", "LEFT", 0));
        rightButton->setText(QApplication::translate("MainWindow", "RIGHT", 0));
        upButton->setText(QApplication::translate("MainWindow", "UP", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Zoom", 0));
        label_4->setText(QApplication::translate("MainWindow", "Zoom Faktor (+/-):", 0));
        gradientCheckBox->setText(QApplication::translate("MainWindow", "Gradient (Alpha)", 0));
        renderingBox->setTitle(QApplication::translate("MainWindow", "Rendering:", 0));
        MIPRadio->setText(QApplication::translate("MainWindow", "Maximum Intensity Proj", 0));
        firstHitRadio->setText(QApplication::translate("MainWindow", "First Hit", 0));
        gpuBox->setText(QApplication::translate("MainWindow", "Make use of the GPU (CPU only otherwise)", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Sampling:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Sampling step size (Optimal results with 1.0):", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
