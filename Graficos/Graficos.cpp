// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <iostream>
#include "Vertice.h"
#include "Shader.h"
using namespace std;

GLfloat red, green, blue;

vector<Vertice> triangulo;
GLuint poicionID;
GLuint vertexArrayID;
GLuint bufferID;
Shader *shader;

void actualizar()
{
	//Aqui esta bien para actualizar los valores
	//De la version del programa!

	/*red += 0.01;
	green += 0.02;
	blue += 0.03;

	if (red > 1) red = 0;
	if (green > 1) green = 0;
	if (blue > 1) blue = 0;*/

}



int main()
{
	//Declaraci�n de Ventana
	GLFWwindow *window;
	
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		//Si no se inicia bien termina la ejecuci�n
		exit(EXIT_FAILURE);
	}

	//Inicializaci�n de la ventana
	window = glfwCreateWindow(ancho, alto, "Gr�ficos", NULL, NULL);

	//Verificaci�n de creaci�n de ventana
	if (!window)
	{
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecuci�n
		exit(EXIT_FAILURE);
	}


	//Establecer "windows" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;

	//Inicializar GLEW
	GLenum glewError = glewInit();

	//Verificar si GLEW se inicializo bien
	if (glewError != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL:" << version << endl;

	red = green = blue = 0.0f;

	//Inicializar triangulo
	Vertice v1 = { vec3(-1,-0.5f,0.0f),vec4(1.0f,1.0f,1.0f,1.0f) };
	Vertice v2 = { vec3(0.0f,0.5f,0.0f),vec4(1.0f,1.0f,1.0f,1.0f) };
	Vertice v3 = { vec3(1.0f,-0.5f,0.0f),vec4(1.0f,1.0f,1.0f,1.0f) };

	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);
	//Crar instancia del shader
	const char * rutaVertex = "vShaderSimple.shader";
	const char * rutaFragment = "fShaderSimple.shader";

	shader = new Shader(rutaVertex, rutaFragment);
	//Ciclo de Dibujo
	while (!glfwWindowShouldClose(window))
	{
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia
		glClearColor(red, green, blue, 1);
		
		//Limpiar pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de Dibujo
		actualizar();
		

		//Intercambio de Buffers
		glfwSwapBuffers(window);
		//Buscar nueva se�al de entrada
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

