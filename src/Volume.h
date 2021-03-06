#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <glm.hpp>
#include <gtx/string_cast.hpp>
#include <gtc/matrix_transform.hpp>
#include <QProgressBar>


//-------------------------------------------------------------------------------------------------
// Voxel
//-------------------------------------------------------------------------------------------------

class Voxel
{
	public:

		Voxel();
		Voxel(const Voxel &other);
		Voxel(const float value);

		~Voxel();


		// VOXEL VALUE

		void					setValue(const float value);
		const float				getValue() const;


		// OPERATORS

		const bool				operator==(const Voxel &other) const;
		const bool				operator!=(const Voxel &other) const;
		const bool				operator>(const Voxel &other) const;
		const bool				operator>=(const Voxel &other) const;
		const bool				operator<(const Voxel &other) const;
		const bool				operator<=(const Voxel &other) const;

		const Voxel				operator+(const Voxel &other) const;
		const Voxel				operator-(const Voxel &other) const;
		const Voxel				operator*(const float &value) const;
		const Voxel				operator/(const float &value) const;
		
		const Voxel&			operator+=(const Voxel &other);
		const Voxel&			operator-=(const Voxel &other);
		const Voxel&			operator*=(const float &value);
		const Voxel&			operator/=(const float &value);


	private:

		float					m_Value;

};

//-------------------------------------------------------------------------------------------------
// vec3
//-------------------------------------------------------------------------------------------------

struct vec3{
	float x;
	float y;
	float z;
};

//-------------------------------------------------------------------------------------------------
// plane
//-------------------------------------------------------------------------------------------------

class Plane
{
public:
	glm::vec3					p1;
	glm::vec3					p2;
	glm::vec3					p3;
	glm::vec3					p4;
	glm::vec3					middle;
	glm::vec3					pivot;
	glm::vec3					v;
	glm::vec3					x;
	glm::vec3					y;
};


//-------------------------------------------------------------------------------------------------
// Volume
//-------------------------------------------------------------------------------------------------

class Volume
{

	public:

		Volume();
		~Volume();


		// VOLUME DATA

		const Voxel&			voxel(const int i) const;
		const Voxel&			voxel(const int x, const int y, const int z) const;
		const Voxel*			voxels() const;

		const int				width() const;
		const int				height() const;
		const int				depth() const;

		int						m_Size;
		double					samplingStepSize;
		const int				size() const;
		enum					Axis { X, Y, Z };
		bool					trilinear;
		bool					gradient = false;
		enum					Rendering { MIP, FIRSTHIT, ALPHACOMP };
		double					firstHitThreshold = 0;

		Axis					rAxis;
		Rendering				rendering;
		bool					loadFromFile(QString filename, QProgressBar* progressBar);
		std::vector<float>		processVolume(QString filename, QProgressBar* progressBar);
		std::vector<float>		rayCast();
		bool					lineIntersection(glm::vec3 p1, glm::vec3 p2, glm::vec3 v, glm::vec3& intersec1, glm::vec3& intersec2);
		bool					searchForIntersection(glm::vec3 p1, glm::vec3 v, bool& firstIntersectFound, glm::vec3& intersec1, glm::vec3& intersec2, Axis axis, float fixPoint);
		bool					checkIfInBB(glm::vec3 p);
		void					initPlane();
		void					rotate(float theta);
		void					translate(int direction);
		void					zoom(int z);
	private:

		std::vector<Voxel>		m_Voxels;
		Plane					p;
		int						m_Width;
		int						m_Height;
		int						m_Depth;		
		bool					start = true;
		bool					backface = false;
		float averageIntensityOf9x9Neighbourhood(float x_start, float y_start, float z_start);
		float interpolate(float x_start, float y_start, float z_start);
};
