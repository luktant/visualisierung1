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
		if (start){
			initPlane();
			start = false;
		}
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
		
	//the vector in which the values are stored and printed out
	//from 0.0 to 1.0 values only!!
	std::vector<float> out;
	out.resize(PIXEL_X * PIXEL_Y);

	float sample_step_size = 32.f;

	//start of the ray | end of the ray | first intersection | second intersection
	vec3 start, end, intersec1, intersec2;

	//loop that runs thorugh every pixel of the plane and shoots a ray
	for (int i = 0; i < PIXEL_Y; i++){
		for (int j = 0; j < PIXEL_X; j++){
		
			//start of ray
			start.x = p.p4.x + (p.x.x * j) + (p.y.x * i);
			start.y = p.p4.y + (p.x.y * j) + (p.y.y * i);
			start.z = p.p4.z + (p.x.z * j) + (p.y.z * i);

			//end of ray
			end.x = start.x + p.v.x;
			end.y = start.y + p.v.y;
			end.z = start.z + p.v.z;

			//returns bool | if true the an intersection is found and both intersections are stored in intersec1 and intersec2
			bool intersecting = lineIntersection(start, end, p.v, intersec1, intersec2);
			
			float maximumIntensity = 0;
			float intensities = 0;

			if (intersecting)
			{
				float x_start = intersec1.x;
				float y_start = intersec1.y;
				float z_start = intersec1.z;

				float x_end = intersec2.x;
				float y_end = intersec2.y;
				float z_end = intersec2.z;

				float dX = x_end - x_start;
				float dY = y_end - y_start;
				float dZ = z_end - z_start;

				float stepsize_z = sample_step_size;
				float stepsize_x = (dX>0?dX*stepsize_z/dZ:0);
				float stepsize_y = (dY>0?dY*stepsize_z/dZ:0);

				float val;
				while (z_start < z_end)
				{
					val = m_Voxels[round(x_start) + m_Width*(round(y_start) + m_Depth*round(z_start))].getValue();

					if (val > maximumIntensity) maximumIntensity = val;

					x_start += stepsize_x;
					y_start += stepsize_y;
					z_start += stepsize_z;
				}
			}
			out[i*PIXEL_X + j] = maximumIntensity;
		}
	}
	return out;
}

float Volume::averageIntensityOf9x9Neighbourhood(float x_start, float y_start, float z_start)
{
	float intensities = 0;
	int norm = 0;
	//Lower-left
	if (x_start>0 && y_start>0) {
		intensities += m_Voxels[(x_start - 1) + m_Width*((y_start - 1) + m_Depth*round(z_start))].getValue();
		norm++;
	}
	//Lower-center
	if (y_start>0) {
		intensities += m_Voxels[x_start + m_Width*((y_start - 1) + m_Depth*round(z_start))].getValue();
		norm++;
	}
	//Lower-right
	if (x_start<m_Width && y_start>0) {
		intensities += m_Voxels[(x_start + 1) + m_Width*((y_start - 1) + m_Depth*round(z_start))].getValue();
		norm++;
	}
	//Center-left
	if (x_start>0) {
		intensities += m_Voxels[(x_start - 1) + m_Width*(y_start + m_Depth*round(z_start))].getValue();
		norm++;
	}
	//Center
	intensities += m_Voxels[x_start + m_Width*(y_start + m_Depth*round(z_start))].getValue();
	norm++;
	//Center-right
	if (x_start<m_Width) {
		intensities += m_Voxels[(x_start + 1) + m_Width*(y_start + m_Depth*round(z_start))].getValue();
		norm++;
	}
	//Upper-left
	if (x_start > 0 && y_start<m_Height) {
		intensities += m_Voxels[(x_start - 1) + m_Width*((y_start + 1) + m_Depth*round(z_start))].getValue();
		norm++;
	}
	//Upper-center
	if (y_start<m_Height) {
		intensities += m_Voxels[x_start + m_Width*((y_start + 1) + m_Depth*round(z_start))].getValue();
		norm++;
	}
	//Upper-right
	if (x_start<m_Width && y_start<m_Height) {
		intensities += m_Voxels[(x_start + 1) + m_Width*((y_start + 1) + m_Depth*round(z_start))].getValue();
		norm++;
	}
	return intensities/norm;
}

float Volume::maxIntensityOf9x9Neighbourhood(float x_start, float y_start, float z_start){
	float maximumIntensity = INT_MIN;
	//Lower-left
	if (x_start>0 && y_start>0) {
		if (m_Voxels[(x_start - 1) + m_Width*((y_start - 1) + m_Depth*round(z_start))].getValue() > maximumIntensity)maximumIntensity = m_Voxels[(x_start - 1) + m_Width*((y_start - 1) + m_Depth*round(z_start))].getValue();
	}
	//Lower-center
	if (y_start>0) {
		if (m_Voxels[x_start + m_Width*((y_start - 1) + m_Depth*round(z_start))].getValue() > maximumIntensity)maximumIntensity = m_Voxels[x_start + m_Width*((y_start - 1) + m_Depth*round(z_start))].getValue();
	}
	//Lower-right
	if (x_start<m_Width && y_start>0) {
		if (m_Voxels[(x_start + 1) + m_Width*((y_start - 1) + m_Depth*round(z_start))].getValue() > maximumIntensity)maximumIntensity = m_Voxels[(x_start + 1) + m_Width*((y_start - 1) + m_Depth*round(z_start))].getValue();
	}
	//Center-left
	if (x_start>0) {
		if (m_Voxels[(x_start - 1) + m_Width*(y_start + m_Depth*round(z_start))].getValue() > maximumIntensity)maximumIntensity = m_Voxels[(x_start - 1) + m_Width*(y_start + m_Depth*round(z_start))].getValue();
	}
	//Center
	if (m_Voxels[x_start + m_Width*(y_start + m_Depth*round(z_start))].getValue() > maximumIntensity)maximumIntensity = m_Voxels[x_start + m_Width*(y_start + m_Depth*round(z_start))].getValue();
	//Center-right
	if (x_start<m_Width) {
		if (m_Voxels[(x_start + 1) + m_Width*(y_start + m_Depth*round(z_start))].getValue() > maximumIntensity)maximumIntensity = m_Voxels[(x_start + 1) + m_Width*(y_start + m_Depth*round(z_start))].getValue();
	}
	//Upper-left
	if (x_start > 0 && y_start<m_Height) {
		if (m_Voxels[(x_start - 1) + m_Width*((y_start + 1) + m_Depth*round(z_start))].getValue() > maximumIntensity)maximumIntensity = m_Voxels[(x_start - 1) + m_Width*((y_start + 1) + m_Depth*round(z_start))].getValue();
	}
	//Upper-center
	if (y_start<m_Height) {
		if (m_Voxels[x_start + m_Width*((y_start + 1) + m_Depth*round(z_start))].getValue() > maximumIntensity)maximumIntensity = m_Voxels[x_start + m_Width*((y_start + 1) + m_Depth*round(z_start))].getValue();
	}
	//Upper-right
	if (x_start<m_Width && y_start<m_Height) {
		if (m_Voxels[(x_start + 1) + m_Width*((y_start + 1) + m_Depth*round(z_start))].getValue() > maximumIntensity)maximumIntensity = m_Voxels[(x_start + 1) + m_Width*((y_start + 1) + m_Depth*round(z_start))].getValue();
	}
	return maximumIntensity;
}

bool Volume::lineIntersection(vec3 p1, vec3 p2, vec3 v, vec3& intersec1, vec3& intersec2){
	
	//discard rays that aren't in the area
	if (p1.x < 0 && p2.x < 0) return false;
	if (p1.x > m_Width && p2.x > m_Width) return false;

	if (p1.y < 0 && p2.y < 0) return false;
	if (p1.y > m_Height && p2.y > m_Height) return false;

	if (p1.z < 0 && p2.z < 0) return false;
	if (p1.z > m_Depth && p2.z > m_Depth) return false;

	bool firstIntersectFound = false;
	vec3 temp;

	// check if parralel
	if (v.x == 0){
		if (v.y != 0 && v.z != 0){
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Y, 0)) return true;
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Y, m_Height)) return true;
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Z, 0)) return true;
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Z, m_Depth)) return true;
			return false;
		}
		else{
			if (v.y == 0){
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Z, 0)) return true;
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Z, m_Depth)) return true;
				return false;
			}
			if (v.z == 0){
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Y, 0)) return true;
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Y, m_Height)) return true;
				return false;
			}
		}
	}

	if (v.y == 0){
		if (v.x != 0 && v.z != 0){
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, X, 0)) return true;
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, X, m_Width)) return true;
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Z, 0)) return true;
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Z, m_Depth)) return true;
			return false;
		}
		else{
			if (v.x == 0){
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Z, 0)) return true;
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Z, m_Depth)) return true;
				return false;
			}
			if (v.z == 0){
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, X, 0)) return true;
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, X, m_Width)) return true;
				return false;
			}
		}
	}

	if (v.z == 0){
		if (v.x != 0 && v.y != 0){
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, X, 0)) return true;
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, X, m_Width)) return true;
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Y, 0)) return true;
			if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Y, m_Height)) return true;
			return false;
		}
		else{
			if (v.y == 0){
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, X, 0)) return true;
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, X, m_Width)) return true;
				return false;
			}
			if (v.x == 0){
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Y, 0)) return true;
				if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Y, m_Height)) return true;
				return false;
			}
		}
	}

	//not parallel
	if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, X, 0)) return true;
	if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, X, m_Width)) return true;
	if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Y, 0)) return true;
	if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Y, m_Height)) return true;
	if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Z, 0)) return true;
	if (searchForIntersection(p1, v, firstIntersectFound, intersec1, intersec2, Z, m_Depth)) return true;
	return false;
}

bool Volume::searchForIntersection(vec3 p1, vec3 v, bool& firstIntersectFound, vec3& intersec1, vec3& intersec2, Axis axis, float fixPoint){
	vec3 temp;

	if (axis == X){
		float s = (fixPoint - p1.x) / v.x;
		temp.x = fixPoint;
		temp.y = p1.y + s * v.y;
		temp.z = p1.z + s * v.z;
	}

	if (axis == Y){
		float s = (fixPoint - p1.y) / v.y;
		temp.x = p1.x + s * v.x;
		temp.y = fixPoint;
		temp.z = p1.z + s * v.z;
	}

	if (axis == Z){
		float s = (fixPoint - p1.z) / v.z;
		temp.x = p1.x + s * v.x;
		temp.y = p1.y + s * v.y;
		temp.z = fixPoint;
	}

	if (checkIfInBB(temp)){
		if (!firstIntersectFound){
			intersec1 = temp;
			firstIntersectFound = true;
			return false;
		}else{
			if (!(intersec1.x == temp.x && intersec1.y == temp.y && intersec1.z == temp.z)){
				intersec2 = temp;
				return true;
			}
		}
	}
	return false;
}

bool Volume::checkIfInBB(vec3 p){
	if (p.x < 0 || p.x > m_Width || p.y < 0 || p.y > m_Height || p.z < 0 || p.z > m_Depth) return false;
	return true;
}

void Volume::initPlane(){
	p.pivot.x = m_Width / 2;
	p.pivot.y = m_Height / 2;
	p.pivot.z = m_Depth / 2;

	p.p1.x = p.pivot.x - PIXEL_X / 2;
	p.p1.y = p.pivot.y - PIXEL_Y / 2;
	p.p1.z = -1000;

	p.p2.x = p.pivot.x + PIXEL_X / 2;
	p.p2.y = p.pivot.y - PIXEL_Y / 2;
	p.p2.z = -1000;

	p.p3.x = p.pivot.x + PIXEL_X / 2;
	p.p3.y = p.pivot.y + PIXEL_Y / 2;
	p.p3.z = -1000;

	p.p4.x = p.pivot.x - PIXEL_X / 2;
	p.p4.y = p.pivot.y + PIXEL_Y / 2;
	p.p4.z = -1000;

	p.middle.x = p.pivot.x;
	p.middle.y = p.pivot.y;
	p.middle.z = -1000;

	p.v.x = 0;
	p.v.y = 0;
	p.v.z = -p.middle.z + std::max(m_Width, std::max(m_Height, m_Depth));

	p.x.x = p.p3.x - p.p4.x;
	p.x.y = p.p3.y - p.p4.y;
	p.x.z = p.p3.z - p.p4.z;

	p.y.x = p.p1.x - p.p4.x;
	p.y.y = p.p1.y - p.p4.y;
	p.y.z = p.p1.z - p.p4.z;

	//normalize
	p.x.x = p.x.x / PIXEL_X;
	p.x.y = p.x.y / PIXEL_X;
	p.x.z = p.x.z / PIXEL_X;

	p.y.x = p.y.x / PIXEL_Y;
	p.y.y = p.y.y / PIXEL_Y;
	p.y.z = p.y.z / PIXEL_Y;
}