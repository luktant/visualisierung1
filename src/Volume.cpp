#include "Volume.h"

#include <math.h>

//has to be the same as in OGLWidget
static const int PIXEL_X = 640;
static const int PIXEL_Y = 480;

//-------------------------------------------------------------------------------------------------
// Voxel
//-------------------------------------------------------------------------------------------------

Voxel::Voxel()
{
	setValue(0.0f);
}

Voxel::Voxel(const Voxel &other)
{
	setValue(other.getValue());
}

Voxel::Voxel(const float value)
{
	setValue(value);
}

Voxel::~Voxel()
{
}

void Voxel::setValue(const float value)
{
	m_Value = value;
}

const float Voxel::getValue() const
{
	return m_Value;
};

const bool Voxel::operator==(const Voxel &other) const
{
	return (getValue() == other.getValue());
};

const bool Voxel::operator!=(const Voxel &other) const
{
	return !(*this == other);
};

const bool Voxel::operator>(const Voxel &other) const
{
	return getValue() > other.getValue();
};

const bool Voxel::operator>=(const Voxel &other) const
{
	return getValue() >= other.getValue();
};

const bool Voxel::operator<(const Voxel &other) const
{
	return getValue() < other.getValue();
};

const bool Voxel::operator<=(const Voxel &other) const
{
	return getValue() <= other.getValue();
};

const Voxel& Voxel::operator+=(const Voxel &other)
{
	m_Value += other.m_Value;
	return *this;
};

const Voxel& Voxel::operator-=(const Voxel &other)
{
	m_Value -= other.m_Value;
	return *this;
};

const Voxel& Voxel::operator*=(const float &value)
{
	m_Value *= value;
	return *this;
};

const Voxel& Voxel::operator/=(const float &value)
{
	m_Value /= value;
	return *this;
};

const Voxel Voxel::operator+(const Voxel &other) const
{
	Voxel voxNew = *this;
	voxNew += other;
	return voxNew;
};

const Voxel Voxel::operator-(const Voxel &other) const
{
	Voxel voxNew = *this;
	voxNew -= other;
	return voxNew;
};

const Voxel Voxel::operator*(const float &value) const
{
	Voxel voxNew = *this;
	voxNew *= value;
	return voxNew;
};

const Voxel Voxel::operator/(const float &value) const
{
	Voxel voxNew = *this;
	voxNew /= value;
	return voxNew;
};


//-------------------------------------------------------------------------------------------------
// Volume
//-------------------------------------------------------------------------------------------------

Volume::Volume()
	: m_Width(1), m_Height(1), m_Depth(1), m_Size(0), m_Voxels(1)
{
}

Volume::~Volume()
{
}

const Voxel& Volume::voxel(const int x, const int y, const int z) const
{
	return m_Voxels[x + y*m_Width + z*m_Width*m_Height];
}

const Voxel& Volume::voxel(const int i) const
{
	return m_Voxels[i];
}

const Voxel* Volume::voxels() const
{
	return &(m_Voxels.front());
};

const int Volume::width() const
{
	return m_Width;
};

const int Volume::height() const
{
	return m_Height;
};

const int Volume::depth() const
{
	return m_Depth;
};

const int Volume::size() const
{
	return m_Size;
};


//-------------------------------------------------------------------------------------------------
// Volume
//-------------------------------------------------------------------------------------------------

std::vector<float> Volume::processVolume(QString filename, QProgressBar* progressBar){
	
	bool success = loadFromFile(filename, progressBar);

	std::vector<float> pixel;
	pixel.resize(1);

	if (success){

		pixel = rayCast();

	}else{

		pixel[0] = -1;

	}

	return pixel;

}

bool Volume::loadFromFile(QString filename, QProgressBar* progressBar)
{
	// load file
	FILE *fp = NULL;
	fopen_s(&fp, filename.toStdString().c_str(), "rb");
	if (!fp)
	{
		std::cerr << "+ Error loading file: " << filename.toStdString() << std::endl;
		return false;
	}

	// progress bar

	progressBar->setRange(0, m_Size + 10);
	progressBar->setValue(0);


	// read header and set volume dimensions

	unsigned short uWidth, uHeight, uDepth;
	fread(&uWidth, sizeof(unsigned short), 1, fp);
	fread(&uHeight, sizeof(unsigned short), 1, fp);
	fread(&uDepth, sizeof(unsigned short), 1, fp);
	
	m_Width = int(uWidth);
	m_Height = int(uHeight);
	m_Depth = int(uDepth);

	// check dataset dimensions
	if (
			m_Width <= 0 || m_Width > 1000 ||
			m_Height <= 0 || m_Height > 1000 ||
			m_Depth <= 0 || m_Depth > 1000)
	{
		std::cerr << "+ Error loading file: " << filename.toStdString() << std::endl;
		std::cerr << "Unvalid dimensions - probably loaded .dat flow file instead of .gri file?" << std::endl;
		return false;
	}

	// compute dimensions
	int slice = m_Width * m_Height;
	m_Size = slice * m_Depth;
	int test = INT_MAX;
	m_Voxels.resize(m_Size);


	// read volume data

	// read into vector before writing data into volume to speed up process
	std::vector<unsigned short> vecData;
	vecData.resize(m_Size);
	fread((void*)&(vecData.front()), sizeof(unsigned short), m_Size, fp);
	fclose(fp);

	progressBar->setValue(10);


	// store volume data

	for (int i = 0; i < m_Size; i++)
	{
		// data is converted to FLOAT values in an interval of [0.0 .. 1.0];
		// uses 4095.0f to normalize the data, because only 12bit are used for the
		// data values, and then 4095.0f is the maximum possible value
		const float value = std::fmax(0.0f, std::fmin(1.0f, (float(vecData[i]) / 4095.0f)));
		m_Voxels[i] = Voxel(value);
		
		progressBar->setValue(10 + i);
	}

	progressBar->setValue(0);

	std::cout << "Loaded VOLUME with dimensions " << m_Width << " x " << m_Height << " x " << m_Depth << std::endl;

	return true;
}

std::vector<float> Volume::rayCast(){
	
	p.p1.resize(3);
	p.p2.resize(3);
	p.p3.resize(3);
	p.p4.resize(3);
	p.pivot.resize(3);

	p.pivot[0] = m_Width / 2;
	p.pivot[1] = m_Height / 2;
	p.pivot[2] = m_Depth / 2;

	p.p1[0] = -m_Width;
	p.p1[1] = -m_Height;
	p.p1[2] = -m_Depth;

	p.p2[0] = 2*m_Width;
	p.p2[1] = -m_Height;
	p.p2[2] = -m_Depth;

	p.p3[0] = 2*m_Width;
	p.p3[1] = 2*m_Height;
	p.p3[2] = -m_Depth;

	p.p4[0] = -m_Width;
	p.p4[1] = 2*m_Height;
	p.p4[2] = -m_Depth;

	std::vector<float> x, y;
	x.resize(3);
	y.resize(3);

	x[0] = p.p3[0] - p.p4[0];
	x[1] = p.p3[1] - p.p4[1];
	x[2] = p.p3[2] - p.p4[2];

	y[0] = p.p1[0] - p.p4[0];
	y[1] = p.p1[1] - p.p4[1];
	y[2] = p.p1[2] - p.p4[2];

	float deltaX, deltaY, lengthX, lengthY;

	//normalize
	lengthX = sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
	lengthY = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);

	x[0] = (1 / lengthX) * x[0];
	x[1] = (1 / lengthX) * x[1];
	x[2] = (1 / lengthX) * x[2];

	y[0] = (1 / lengthY) * y[0];
	y[1] = (1 / lengthY) * y[1];
	y[2] = (1 / lengthY) * y[2];

	deltaX = lengthX / PIXEL_X;
	deltaY = lengthY / PIXEL_Y;
	
	std::vector<float> out;
	out.resize(PIXEL_X * PIXEL_Y);

	std::vector<float> currentPos;
	currentPos.resize(3);

	for (int i = 0; i < PIXEL_Y; i++){
		for (int j = 0; j < PIXEL_X; j++){
		
			currentPos[0] = p.p4[0] + (x[0] * deltaX * j) + (y[0] * deltaY * i);
			currentPos[1] = p.p4[1] + (x[1] * deltaX * j) + (y[1] * deltaY * i);
			currentPos[2] = p.p4[2] + (x[2] * deltaX * j) + (y[2] * deltaY * i);

			if (i % 2 == 1){
				out[i*PIXEL_X + j] = 0.5;
			}else{
				out[i*PIXEL_X + j] = 0;
			}
		}
	}
	
	return out;

}