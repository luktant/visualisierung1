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
    QDoubleSpinBox *rotationSpeed;
    QLabel *label;
    QRadioButton *xaxis;
    QRadioButton *yaxis;
    QRadioButton *zaxis;
    QLabel *label_2;
    QGroupBox *renderingBox;
    QRadioButton *MIPRadio;
    QRadioButton *firstHitRadio;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QLabel *label_3;
    QCheckBox *gpuBox;
    QDoubleSpinBox *zoomFaktor;
    QLabel *label_4;
    QMenuBar *menubar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(821, 564);
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
        interpolationBox->setGeometry(QRect(650, 70, 161, 81));
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
        transformationBox->setGeometry(QRect(650, 230, 161, 151));
        rotationSpeed = new QDoubleSpinBox(transformationBox);
        rotationSpeed->setObjectName(QStringLiteral("rotationSpeed"));
        rotationSpeed->setGeometry(QRect(10, 30, 62, 22));
        rotationSpeed->setSingleStep(0.1);
        label = new QLabel(transformationBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 30, 81, 20));
        xaxis = new QRadioButton(transformationBox);
        xaxis->setObjectName(QStringLiteral("xaxis"));
        xaxis->setGeometry(QRect(10, 80, 82, 17));
        xaxis->setCheckable(false);
        yaxis = new QRadioButton(transformationBox);
        yaxis->setObjectName(QStringLiteral("yaxis"));
        yaxis->setGeometry(QRect(10, 100, 82, 17));
        yaxis->setCheckable(false);
        yaxis->setChecked(false);
        zaxis = new QRadioButton(transformationBox);
        zaxis->setObjectName(QStringLiteral("zaxis"));
        zaxis->setGeometry(QRect(10, 120, 82, 17));
        zaxis->setCheckable(false);
        label_2 = new QLabel(transformationBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 111, 16));
        renderingBox = new QGroupBox(centralwidget);
        renderingBox->setObjectName(QStringLiteral("renderingBox"));
        renderingBox->setGeometry(QRect(650, 150, 161, 81));
        MIPRadio = new QRadioButton(renderingBox);
        MIPRadio->setObjectName(QStringLiteral("MIPRadio"));
        MIPRadio->setGeometry(QRect(20, 20, 131, 17));
        MIPRadio->setCheckable(false);
        firstHitRadio = new QRadioButton(renderingBox);
        firstHitRadio->setObjectName(QStringLiteral("firstHitRadio"));
        firstHitRadio->setGeometry(QRect(20, 50, 111, 17));
        firstHitRadio->setCheckable(false);
        upButton = new QPushButton(centralwidget);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(704, 387, 54, 23));
        downButton = new QPushButton(centralwidget);
        downButton->setObjectName(QStringLiteral("downButton"));
        downButton->setGeometry(QRect(704, 433, 54, 23));
        leftButton = new QPushButton(centralwidget);
        leftButton->setObjectName(QStringLiteral("leftButton"));
        leftButton->setGeometry(QRect(650, 410, 54, 23));
        rightButton = new QPushButton(centralwidget);
        rightButton->setObjectName(QStringLiteral("rightButton"));
        rightButton->setGeometry(QRect(758, 410, 54, 23));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(720, 410, 41, 21));
        gpuBox = new QCheckBox(centralwidget);
        gpuBox->setObjectName(QStringLiteral("gpuBox"));
        gpuBox->setGeometry(QRect(650, 510, 70, 17));
        gpuBox->setCheckable(false);
        zoomFaktor = new QDoubleSpinBox(centralwidget);
        zoomFaktor->setObjectName(QStringLiteral("zoomFaktor"));
        zoomFaktor->setGeometry(QRect(650, 470, 62, 22));
        zoomFaktor->setMinimum(-30);
        zoomFaktor->setMaximum(30);
        zoomFaktor->setValue(0);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(720, 472, 91, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 821, 21));
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
        transformationBox->setTitle(QApplication::translate("MainWindow", "Transformation Settings:", 0));
        label->setText(QApplication::translate("MainWindow", "Rotation Speed", 0));
        xaxis->setText(QApplication::translate("MainWindow", "X", 0));
        yaxis->setText(QApplication::translate("MainWindow", "Y", 0));
        zaxis->setText(QApplication::translate("MainWindow", "Z", 0));
        label_2->setText(QApplication::translate("MainWindow", "Rotatation Axis", 0));
        renderingBox->setTitle(QApplication::translate("MainWindow", "Rendering:", 0));
        MIPRadio->setText(QApplication::translate("MainWindow", "Maximum Intensity Proj", 0));
        firstHitRadio->setText(QApplication::translate("MainWindow", "First Hit", 0));
        upButton->setText(QApplication::translate("MainWindow", "UP", 0));
        downButton->setText(QApplication::translate("MainWindow", "DOWN", 0));
        leftButton->setText(QApplication::translate("MainWindow", "LEFT", 0));
        rightButton->setText(QApplication::translate("MainWindow", "RIGHT", 0));
        label_3->setText(QApplication::translate("MainWindow", "Move", 0));
        gpuBox->setText(QApplication::translate("MainWindow", "use GPU", 0));
        label_4->setText(QApplication::translate("MainWindow", "Zoom Faktor (+/-)", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
