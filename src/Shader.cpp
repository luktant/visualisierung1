#include "Shader.h"

using namespace std;

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader) {

	//get a program handle
	programHandle = glCreateProgram();

	//see if it is valid
	if (programHandle == 0) {
		cout << "did not get valid programm handle" << endl;
		system("pause");
		exit(-1);
	}

	//Load Shader
	loadShader(vertexShader, GL_VERTEX_SHADER, vertexHandle);
	loadShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentHandle);

	//Link Shader
	link();

}

Shader::~Shader() {
	glDeleteProgram(programHandle);
	glDeleteShader(vertexHandle);
	glDeleteShader(fragmentHandle);
}

void Shader::loadShader(const std::string& shader, GLenum shaderType, GLuint& handle) {
	//loads a shader from disk

	//open file handle to shaderpath
	std::ifstream shaderFile(shader);

	//see if it is valid
	if (shaderFile.good()) {

		//create a stream buffer and  iterator
		std::string code = std::string(
			std::istreambuf_iterator<char>(shaderFile),
			std::istreambuf_iterator<char>());

		//close file handle
		shaderFile.close();

		//get a shader handle
		handle = glCreateShader(shaderType);

		//see if it is valid
		if (handle == 0)
		{
			std::cout << "Failed to create shader" << std::endl;
			system("PAUSE");
			exit(-1);
		}

		//compile te shader
		auto codePtr = code.c_str();
		glShaderSource(handle, 1, &codePtr, nullptr);
		glCompileShader(handle);

		//see if compilation succeeded
		GLint succeded;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &succeded);

		//generate a meaningful output for debugging
		if (succeded == GL_FALSE || !glIsShader(handle))
		{
			// read log and output it to std::cout
			GLint logSize;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logSize);
			auto message = new char[logSize];

			glGetShaderInfoLog(handle, logSize, nullptr, message);
			std::cout << "Failed to compile shader" << std::endl;
			std::cout << message << std::endl;
			system("PAUSE");
			delete[] message;
			exit(-1);
		}

	}
	else {
		cout << "failed to load shader file" << endl;
		system("pause");
		exit(-1);
	}
}

void Shader::link() {

	//bind shaders
	glAttachShader(programHandle, vertexHandle);
	glAttachShader(programHandle, fragmentHandle);

	glBindFragDataLocation(programHandle, 0, "fragColor");

	//link into program
	glLinkProgram(programHandle);

	//see if succeeded
	GLint succeded;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &succeded);

	//generate a meaningful output for debugging
	if (!succeded)
	{
		// output errors
		GLint logSize;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logSize);

		auto message = new char[logSize];
		glGetProgramInfoLog(programHandle, logSize, NULL, message);

		std::cout << "Failed to link shader program" << std::endl;
		std::cout << message << std::endl;
		system("PAUSE");

		delete[] message;
		exit(-1);
	}

}

