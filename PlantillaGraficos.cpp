// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>


#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <math.h>

#include <iostream>

#include "Shader.h"
#include "Vertice.h"
#include <vector>
using namespace std;

//Cada elemento que queramos renderear necesita un vertex array y un buffer
vector<Vertice> triangulo;
GLuint vertexArrayTriangulo;
GLuint vertexArrayTrianguloID;
GLuint bufferTrianguloID;

vector<Vertice> cuadrado;
GLuint vertexArrayCuadradoID;
GLuint bufferCuadradoID;

//Instancia del shader
Shader *shader;
//identificadores para mapeo de atributos de entrada
//del vertex shader
GLuint posicionID;
GLuint colorID;

void inicializarCuadrado() {
	//Primer cuadrado
	Vertice v1 = {
		vec3(-0.9f,-0.4f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};
	Vertice v2 = {
		vec3(0.9f,-0.4f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};
	Vertice v3 = {
		vec3(0.9f,-0.5f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};
	Vertice v4 = {
		vec3(-0.9f,-0.5f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};
	//segundo cuadrado
	Vertice v5 = {
		vec3(-0.8f,-0.3f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};
	Vertice v6 = {
		vec3(0.8f,-0.3f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};
	Vertice v7 = {
		vec3(0.8f,-0.4f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};
	Vertice v8 = {
		vec3(-0.8f,-0.4f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};

	//tercer cuadrado
	Vertice v9 = {
		vec3(-0.7f,-0.2f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};
	Vertice v10 = {
		vec3(0.7f,-0.2f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};
	Vertice v11 = {
		vec3(0.7f,-0.3f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};
	Vertice v12 = {
		vec3(-0.7f,-0.3f,0.0f),
		vec4(0.1f,0.8f,0.2f,1.0f)
	};

	cuadrado.push_back(v1);
	cuadrado.push_back(v2);
	cuadrado.push_back(v3);
	cuadrado.push_back(v4);

	cuadrado.push_back(v5);
	cuadrado.push_back(v6);
	cuadrado.push_back(v7);
	cuadrado.push_back(v8);

	cuadrado.push_back(v9);
	cuadrado.push_back(v10);
	cuadrado.push_back(v11);
	cuadrado.push_back(v12);

}

void inicializarTriangulo() {
	Vertice v1 = {
		vec3(0.0f,0.3f,0.0f),
		vec4(0.8f,0.1f,0.0f,1.0f)
	};
	Vertice v2 = {
		vec3(-0.3,0.3,0.0f),
		vec4(0.8f,0.1f,0.0f,1.0f)
	};
	Vertice v3 = {
		vec3(0.3f,-0.3f,0.0f),
		vec4(0.8f,0.1f,0.0f,1.0f)
	};
	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);
}

void dibujar() {
	//Elegir shader
	shader->enlazar();
	//Elegor el vertex array
	glBindVertexArray(vertexArrayTrianguloID);
	//Dibujar
	glDrawArrays(GL_TRIANGLES, 0, triangulo.size());

	//Proceso dibujo de cuadrado
	glBindVertexArray(vertexArrayCuadradoID);
	glDrawArrays(GL_QUADS, 0, cuadrado.size());

	//Soltar vertex array
	glBindVertexArray(0);

	//Desenlazar shader
	shader->desenlazar();
}

int main()
{
//Declarar una ventana
	GLFWwindow* window;

	//si no se pudo iniciar GLFW
	//Terminamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	// si se pudo iniciar GLFW
	//Inicalizamos la ventana

	window = glfwCreateWindow(600, 600, "Ventana", NULL, NULL);

	// si no se pudo crear la ventana
	// terminamos ejecucuon
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos la ventana con contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK) {
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);
	cout << "Version openGL:" << versionGL;

	inicializarTriangulo();
	inicializarCuadrado();

	const char* rutaVertexShader = "VertexShader.shader";
	const char* rutaFragmentShader = "FragmentShader.shader";
	shader = new Shader(rutaVertexShader, rutaFragmentShader);

	//Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");

	shader->desenlazar();

	//Crear el vertex array del triangulo
	glGenVertexArrays(1, &vertexArrayTrianguloID);
	glBindVertexArray(vertexArrayTrianguloID);

	//Vertex buffer
	glGenBuffers(1, &bufferTrianguloID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferTrianguloID);
	//Asociar datos al buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * triangulo.size(), triangulo.data(), GL_STATIC_DRAW);
	//Habilitar atributos de shader
	glEnableVertexAttribArray(posicionID);
	glDisableVertexAttribArray(colorID);
	//Especificar a OpenGL como comunicarse
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));

	//Proceso de inicializar Vertex Array para el cuadrado
	glGenVertexArrays(1, &vertexArrayCuadradoID);
	glBindVertexArray(vertexArrayCuadradoID);
	glGenBuffers(1, &bufferCuadradoID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferCuadradoID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * cuadrado.size(), cuadrado.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));

	//Soltar el vertex arry y el buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 600, 600);
		//Establecer el color de borrado
		glClearColor(1, 0.8, 0, 1);
		//Borrar!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//actualizar valores y dibujar
		dibujar();


		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//Despúes del ciclo de dibujo
	//Eliminamos venta y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
