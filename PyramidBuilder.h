#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GLFW/glfw3.h"
// GLM include
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



	// Var declaration for shader, window size, initialization, buffer and array objects
	GLint shaderProgram, WindowWidth = 800, WindowHeight = 600;
	GLuint VBO, VAO, EBO, texture;
	
#define WINDOW_TITLE "3D Piramida"
	// Shader program macro
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version "\n" #Source
#endif

// Vertex shader source
	const GLchar* vertexShaderSource =
		GLSL(330,

			layout(location = 0) in vec3 position; layout(location = 1) in vec3 color;

	out vec3 mobileColor;

	// Global vars for transform matrices
	uniform mat4 model; uniform mat4 view; uniform mat4 projection;

	void main() { gl_Position = projection * view * model * vec4(position, 1.0f); mobileColor = color; });

	// Fragment shader source
	const GLchar* fragmentShaderSource = GLSL(330,

		in vec3 mobileColor;

	out vec4 gpuColor;

	void main() { gpuColor = vec4(mobileColor, 1.0); });



	// Function prototypes
	void UResizeWindow(int, int);
	void URenderGraphics(void);
	void UCreateShader(void);
	void UCreateBuffers(void);
	//global variables
	float translateX  ;
	float translateY;
	float translateZ;
	float rotateX; 
	float rotateY;
	float rotateZ;
	float angle;
	float scale;


	


