#pragma once
#include <iostream>

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <GL/freeglut.h>

// GLM include
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



	// Var declaration for shader, window size, initialization, buffer and array objects
	GLint shaderProgram, WindowWidth = 800, WindowHeight = 600;
	GLuint VBO, VAO, EBO, texture;
	GLuint VBOSquare, VAOSquare, EBOSquare, textureSquare;


	// Function prototypes
	void UResizeWindow(int, int);
	void URenderGraphics(void);
	void UCreateShader(void);
	void UCreateBuffers(void);
	//global variables
	float translateX = 0.0f;
	float translateY = 0.0f;
	float translateZ = 0.0f;
	float rotateX = 1.0f;
	float rotateY = 0.0f;
	float rotateZ = 0.0f;
	float angle = 45.0f;
	float scale = 2.0f;
	float step = 0.1f;
	float zoomX = 0.5f;
	float zoomY = 0.0f;
	float zoomZ = -0.5f;
	int ortho = 0;
	int winId;
	glm::vec3  cameraPos = glm::vec3(0.663740635f, -0.492421985f, 0.562995136f);

	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3  	UP = glm::vec3(0.0f, 1.0f, 0.0f);
	GLuint squareOffset;
	
#define WINDOW_TITLE "3D Piramida"
	// Shader program macro
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version "\n" #Source
#endif

// Vertex shader source
	const GLchar* vertexShaderSource =
		GLSL(330,layout(location = 0) in vec3 position; layout(location = 1)
			in vec3 color;

	out vec3 mobileColor;

	// Global vars for transform matrices
	uniform mat4 model; uniform mat4 view; uniform mat4 projection;

	void main() { gl_Position = projection * view * model * vec4(position, 1.0f); mobileColor = color; });

	// Fragment shader source
	const GLchar* fragmentShaderSource = GLSL(330,in vec3 mobileColor;

	out vec4 gpuColor;

	void main() { gpuColor = vec4(mobileColor, 1.0); });



	

