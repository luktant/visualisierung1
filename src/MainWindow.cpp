#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_Volume(0), m_VectorField(0)
{
	m_Ui = new Ui_MainWindow();
	m_Ui->setupUi(this);

	connect(m_Ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFileAction()));
	connect(m_Ui->actionClose, SIGNAL(triggered()), this, SLOT(closeAction()));
	connect(m_Ui->nearestRadio, SIGNAL(toggled(bool)), this, SLOT(interpolationChanged()));
	connect(m_Ui->trilinearRadio, SIGNAL(toggled(bool)), this, SLOT(interpolationChanged()));
	connect(m_Ui->MIPRadio, SIGNAL(toggled(bool)), this, SLOT(renderingChanged()));
	connect(m_Ui->firstHitRadio, SIGNAL(toggled(bool)), this, SLOT(renderingChanged()));
	connect(m_Ui->xaxis, SIGNAL(toggled(bool)), this, SLOT(rotationChanged()));
	connect(m_Ui->yaxis, SIGNAL(toggled(bool)), this, SLOT(rotationChanged()));
	connect(m_Ui->zaxis, SIGNAL(toggled(bool)), this, SLOT(rotationChanged()));
	connect(m_Ui->rotationSpeed, SIGNAL(valueChanged(double)), this, SLOT(setRotationSpeed(double)));
	connect(m_Ui->upButton, SIGNAL(pressed()), this, SLOT(moveUp()));
	connect(m_Ui->downButton, SIGNAL(pressed()), this, SLOT(moveDown()));
	connect(m_Ui->leftButton, SIGNAL(pressed()), this, SLOT(moveLeft()));
	connect(m_Ui->rightButton, SIGNAL(pressed()), this, SLOT(moveRight()));
	connect(m_Ui->gpuBox, SIGNAL(toggled(bool)), this, SLOT(useGPU(bool)));
	connect(m_Ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));
}

MainWindow::~MainWindow()
{
	delete m_Volume;
	delete m_VectorField;
	delete m_MultiSet;
}


//-------------------------------------------------------------------------------------------------
// Slots
//-------------------------------------------------------------------------------------------------

void MainWindow::openFileAction()
{
	QString filename = QFileDialog::getOpenFileName(this, "Data File", 0, tr("Data Files (*.dat *.gri *.csv)"));

	if (!filename.isEmpty())
	{
		// store filename
		m_FileType.filename = filename;
		std::string fn = filename.toStdString();
		bool success = false;
		std::vector<float> data;

		// progress bar and top label
		m_Ui->progressBar->setEnabled(true);
		m_Ui->labelTop->setText("Loading data ...");

		// load data according to file extension
		if (fn.substr(fn.find_last_of(".") + 1) == "dat")		// LOAD VOLUME
		{
			// create VOLUME
			m_FileType.type = VOLUME;
			m_Volume = new Volume();

			// load file
			data = m_Volume->processVolume(filename, m_Ui->progressBar);

			if (data[0] != -1){
				success = true;
				m_Ui->openGLWidget->setVolume(m_Volume);
				m_Ui->openGLWidget->data = data;
			}

		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "gri")		// LOAD VECTORFIELD
		{
			// create VECTORFIELD
			m_FileType.type = VECTORFIELD;
			m_VectorField = new VectorField();

			// load file
			success = m_VectorField->loadFromFile(filename, m_Ui->progressBar);
		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "csv")		// LOAD MULTIVARIATE DATA
		{
			// create MULTIVARIATE
			m_FileType.type = MULTIVARIATE;
			m_MultiSet = new MultiSet();

			// load file
			success = m_MultiSet->loadFromFile(filename, m_Ui->progressBar);
		}

		m_Ui->progressBar->setEnabled(false);

		// status message
		if (success)
		{
			QString type;
			if (m_FileType.type == VOLUME) type = "VOLUME";
			else if (m_FileType.type == VECTORFIELD) type = "VECTORFIELD";
			else if (m_FileType.type == MULTIVARIATE) type = "MULTIVARIATE";
			m_Ui->labelTop->setText("File LOADED [" + filename + "] - Type [" + type + "]");
		}
		else
		{
			m_Ui->labelTop->setText("ERROR loading file " + filename + "!");
			m_Ui->progressBar->setValue(0);
		}

		if (success)
		{
			m_Ui->nearestRadio->setCheckable(true);
			m_Ui->nearestRadio->setChecked(true);
			m_Ui->trilinearRadio->setCheckable(true);
			m_Ui->MIPRadio->setCheckable(true);
			m_Ui->MIPRadio->setChecked(true);
			m_Ui->firstHitRadio->setCheckable(true);
			m_Ui->xaxis->setCheckable(true);
			m_Ui->yaxis->setCheckable(true);
			m_Ui->yaxis->setChecked(true);
			m_Ui->zaxis->setCheckable(true);
			m_Ui->rotationSpeed->setDisabled(false);
			m_Ui->openGLWidget->fileLoaded=true;
			m_Ui->gpuBox->setCheckable(true);
			m_Ui->openGLWidget->initializeShaderAndBuffer();
		}
	}
}

void MainWindow::closeAction()
{
	close();
}

void MainWindow::interpolationChanged(){
	if (m_Ui->nearestRadio->isChecked()) m_Ui->openGLWidget->changeInterpolation(Interpolation::NEAREST);
	else m_Ui->openGLWidget->changeInterpolation(Interpolation::TRILINEAR);
}
void MainWindow::renderingChanged(){
	if (m_Ui->MIPRadio->isChecked()) m_Ui->openGLWidget->changeRendering(Rendering::MIP);
	else m_Ui->openGLWidget->changeRendering(Rendering::FIRSTHIT);
}
void MainWindow::rotationChanged(){
	if (m_Ui->xaxis->isChecked()) m_Ui->openGLWidget->changeRotationAxis(RotationAxis::X);
	else if (m_Ui->yaxis->isChecked()) m_Ui->openGLWidget->changeRotationAxis(RotationAxis::Y);
	else m_Ui->openGLWidget->changeRotationAxis(RotationAxis::Z);
}
void MainWindow::setRotationSpeed(double s){
	m_Ui->openGLWidget->rotationSpeed = s;
}
void MainWindow::moveUp(){
	m_Ui->openGLWidget->move(Direction::UP);
}
void MainWindow::moveDown(){
	m_Ui->openGLWidget->move(Direction::DOWN);
}
void MainWindow::moveLeft(){
	m_Ui->openGLWidget->move(Direction::LEFT);
}
void MainWindow::moveRight(){
	m_Ui->openGLWidget->move(Direction::RIGHT);
}
void MainWindow::zoom(int newValue){
	m_Ui->openGLWidget->zoom(newValue);	
}
void MainWindow::useGPU(bool use){
	m_Ui->openGLWidget->useGPU = use;
}