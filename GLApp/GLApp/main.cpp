#include <iostream>
#include <sstream>
#include <locale.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SerialPort/SerialPort.h"

const GLint WIDTH = 600, HEIGHT = 600;

void display();
int get_int(int, std::string prompt);

int main() {
	// set spanish
	setlocale(LC_ALL, "Spanish");

	// connect to arduino
	int port = get_int(0, "\n¿Cúal es el puerto en el que está conectado el arduino? ");

	std::string portName = "\\.\\COM" + std::to_string(port);
	const char* nombrepuerto = portName.c_str();
	
	SerialPort arduino(nombrepuerto); // Constructor

	if (arduino.estaConectado()) {
		std::cout << "Conectado en el puerto serial COM" << port << std::endl;
	}
	else {
		// if something went wrong exit...
		std::cout << "Saliendo..." << std::endl;
		system("pause");

		return EXIT_FAILURE;
	}

	// if everything its ok, create OpenGL context

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Arduino Radar UES-FMO", nullptr, nullptr);


	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwSetWindowPos(window, 5, 30); // init pos

	if (nullptr == window) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialize GLEW" << std::endl;

		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glOrtho(-10, 10, -10, 10, -100, 100);


	

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); 

		// DRAW OPENGL
		display();
		// END OF THE DRAWS

		glfwSwapBuffers(window);
	}
	
	return EXIT_SUCCESS;
}

// ALL DRAWS HERE
void display() {
	glBegin(GL_LINES);
	glVertex2d(0, 0);
	glVertex2d(1, 1);
	glEnd();
}

// input validation
int get_int(int min, std::string prompt)
{
	int ret_integer;
	std::string str_number;

	while (true) {

		std::cout << prompt;
		std::getline(std::cin, str_number); //get string input
		std::stringstream convert(str_number); //turns the string into a stream

		//checks for complete conversion to integer and checks for minimum value
		if (convert >> ret_integer && !(convert >> str_number) && ret_integer >= min) return ret_integer;

		std::cin.clear(); //just in case an error occurs with cin (eof(), etc)
		std::cerr << "Input must be >= " << min << ". Please try again.\n";
	}
}