#pragma once

//GLEW
#include <GL/glew.h>

//GLFW
//#include <GLFW/glfw3.h>

//Others
#include <iostream>
#include <fstream>
#include <string>

class Shader {
public:
	//contructor, takes relative path to vertex and fragment shader as inputs
	Shader(const std::string& vertexShader,
		const std::string& fragmentShader);

	//deconstructor, deletes program and shaders
	~Shader();

	//handle of the program
	GLuint programHandle;

private:
	//loads a shader from disk
	void loadShader(const std::string& shader,
		GLenum shaderType,
		GLuint& handle);

	//links vertex and fragment shader into a program
	void link();

	GLuint vertexHandle;
	GLuint fragmentHandle;
};
