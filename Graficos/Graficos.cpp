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
GLuint posicionID;
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
void dibujar()
{
	//Enlazar el shader
	shader->enlazarShader();
	//Especificar el vertex array
	glBindVertexArray(vertexArrayID);
	//Dibujar
	glDrawArrays(GL_TRIANGLES, 0, triangulo.size());
	//Soltar el vertex array
	glBindVertexArray(0);
	//Soltar el shader
	shader->desenlazarShader();
}


int main()
{
	//Declaración de Ventana
	GLFWwindow *window;
	
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicialización de GLFW
	if (!glfwInit())
	{
		//Si no se inicia bien termina la ejecución
		exit(EXIT_FAILURE);
	}

	//Inicialización de la ventana
	window = glfwCreateWindow(ancho, alto, "Gráficos", NULL, NULL);

	//Verificación de creación de ventana
	if (!window)
	{
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecución
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



	//Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(),"posicion");
	//Desenlazar shader 
	shader->desenlazarShader();
	
	//Crear un vertex array
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	//Crear vertex buffer
	glGenBuffers(1, &bufferID);
	//De aqui en adelante se trabaja con este buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	//Llenar el buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice)* triangulo.size(), triangulo.data(), GL_STATIC_DRAW);
	//Habilitar el atributo
	glEnableVertexAttribArray(posicionID);
	//Especificar a OpenGL como usar la memoria con ese atributo
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	//Soltarlos
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

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
		dibujar();
		

		//Intercambio de Buffers
		glfwSwapBuffers(window);
		//Buscar nueva señal de entrada
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

