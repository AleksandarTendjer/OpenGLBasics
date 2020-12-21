﻿/*
 * Pyramid3D.cpp
 *
 *
 *      Author: Aleksandar Tendjer
 */

#include <iostream>
#include "PyramidBuilder.h"

using namespace std;

// Resize windiw to fit primitives
void UResizeWindow(int w, int h) {
	WindowWidth = w;
	WindowHeight = h;
	glViewport(0, 0, WindowWidth, WindowHeight);
}


//Starting Graphics rendering
/*
void URenderGraphics(void) {
	// Enable z-depth
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate the vertex array object beforte renderingand transforming them
	glBindVertexArray(VAO);

	// Declare a 4x4 identity matrix uniform variable to handle transformations
	glm::mat4 model(1.0f);

	// Place the object at the center of the viewport
	model = glm::translate(model, glm::vec3(0.0, 0.0f, 0.0f));

	// Rotate the object 15 degrees on the x-axis
	// I also realized that the transform for my model was way off. Using the updated
	// code with my old transform made it impossible to see clearly
	model = glm::rotate(model, -270.0f, glm::vec3(1.0, 0.0f, 0.0f));

	// Rotate the object 45 degrees on the Y-axis
	model = glm::rotate(model, 45.0f, glm::vec3(0.0, 1.0f, 0.0f));

	// Increase the object size by a scale of 2
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	// transforms the camera and set the
	// I also did not set the view using the (1.0f) param
	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.5f, 0.0f, -5.0f));

	// Perspective projection
	glm::mat4 projection;
	projection = glm::perspective(45.0f,
		(GLfloat)WindowWidth / (GLfloat)WindowHeight, 0.1f, 100.0f);

	// Retrieves and passes transform matirices to the shader program
	GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
	GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
	GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glutPostRedisplay();

	// Draws the triangles
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glutSwapBuffers();

} */
//changed Graphics rendering
void URenderGraphics() {
	// Enable z-depth
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate the vertex array object beforte renderingand transforming them
	glBindVertexArray(VAO);

	// Declare a 4x4 identity matrix uniform variable to handle transformations
	glm::mat4 model(1.0f);

	// Place the object at the center of the viewport
	model = glm::translate(model, glm::vec3(translateX, translateY, translateZ));

	//defining for how much are we going to rotate which  axis
	//1.0 is set on rx,ry,rz for the axis that we want to use, otherwise
	//all pthers are 0
	//angle is value from -360 to +360
	model = glm::rotate(model, angle, glm::vec3(rotateX, rotateY, rotateZ));


	// Increase the object size by a scale of sc value
	model = glm::scale(model, glm::vec3(scale, scale, scale));

	// transforms the camera and set the
	// I also did not set the view using the (1.0f) param
	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(zoomX, zoomY, zoomZ));

	// Perspective projection
	glm::mat4 projection;
	projection = glm::perspective(45.0f,
		(GLfloat)WindowWidth / (GLfloat)WindowHeight, 0.1f, 100.0f);

	// Retrieves and passes transform matirices to the shader program
	GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
	GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
	GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glutPostRedisplay();

	// Draws the triangles
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glutSwapBuffers();

}

void setUniformMVP(GLuint Location, glm::vec3 const& Translate, glm::vec3 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 ViewTranslate = glm::translate(
		glm::mat4(1.0f), Translate);
	glm::mat4 ViewRotateX = glm::rotate(
		ViewTranslate, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	glm::mat4 View = glm::rotate(ViewRotateX,
		Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(
		glm::mat4(1.0f), glm::vec3(0.5f));
	glm::mat4 MVP = Projection * View * Model;
	glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(MVP));
}

// Creates the shader program
void UCreateShader() {
	// Vertex shader
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Fragment shader
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	;
	glLinkProgram(shaderProgram);
	// Delete the vertex and fragment shaders once linked
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}


// creates the buffer and array objects
// One such issue I had was the position of the vertices which where
// Arranged in such a way as the model was flat
void UCreateBuffers() {

	// Position and color data
	GLfloat verticies[] = {

		// Vertex Positions    // Color Data			// Vertex position
				-0.5f, -0.5f, 0.0f, 1.0, 0.0f, 0.0f,		// 0
				0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,		// 1
				0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,		// 2
				-0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 1.0f,		// 3
				0.5f, -0.5f, -1.0f, 0.5f, 0.5f, 1.0f,		// 4
	};
	// Index data to share postion data
	GLuint indices[] = {

	0, 1, 2,	// Front Triangle
			0, 3, 1,	// Right Side triangle
			3, 1, 4,	// Back triangle
			4, 1, 2,	// Left back side triangle
			0, 3, 4,	// Bottom Triangle
			0, 4, 2		// Bottom triangle

	};

	// Generate buffer ids
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Activate the vertex array object before binding and settomg any VBOs or vertex attribute pointers
	glBindVertexArray(VAO);

	// Activate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	// Activate the lement buffer object / indicies
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);

	// set attribute pointer 0 to hold position data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Set attribute pointer 1 to hold Color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Sets polygon mode allows me to see wireframe view
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(0);
}


void processSpecialKeys(unsigned char key, int x, int y)
{
	// Press ALT or  SHIFT or  CTRL in combination with other keys.
	//printf("key_code =%d  \n", key);
	cout << "print special keys" << endl;
		//	int mod = glutGetModifiers();


		switch (key)
		{
		case 'k':
			scale += .5;
			break;
		case 'j':
			scale -= .5;
			break;

		case 'r':
			rotateX = 1.0f;
			angle += 2.0f;
			if (angle > 360)
				angle -= 360;
			cout << angle;

			break;
		case	'e':
			rotateX = 1.0f;
			angle -= 2.0f;
			if (angle > 360)
				angle -= 360;
			cout << angle;

			break;
		case 'a': //move left
			translateX -= step;
			cout << "GLUT_KEY_LEFT %d\n" + key << endl;
			break;
		case 'd': //move right
			translateX += step;
			cout << "GLUT_KEY_LEFT %d\n" + key << endl;
			break;
		case 'w': //move up
			translateY += step;
			cout << "GLUT_KEY_UP %d\n" + key;
			break;
		case 's': // move down
			translateY -= step;
			cout << "GLUT_KEY_DOWN %d\n" + key << endl;
			break;
		case 32:
			cout << "space"<<endl;
			break;
		default:
			break;
		}
	
	glutPostRedisplay();
}


void processNormalKeys(unsigned char key, int x, int y)
{

	switch (key)
	{
	
	case 27:      break;
	default:break;
	}


}
int main(int argc, char* argv[]) {
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//use core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	*/

	glutInit(&argc, argv);
	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WINDOW_TITLE);

	//GLFWwindow*window= glfwCreateWindow(WindowWidth, WindowHeight, "3D piramida", NULL, NULL);
	glutReshapeFunc(UResizeWindow);
	//glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//Shading 
	UCreateShader();
	//buffer data
	UCreateBuffers();


	// User the shader program
	glUseProgram(shaderProgram);


	// Set background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutKeyboardFunc(processSpecialKeys);

	glutDisplayFunc(URenderGraphics);
	//glutKeyboardFunc(processNormalKeys);
	


	// Create and run OpenGL Loop
	glutMainLoop();
	//Sets a callback to a function 



	// Deletes buffer objects once used
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;
}

