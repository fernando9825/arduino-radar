#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <locale.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SOIL2/SOIL2.h"
#include "SerialPort/SerialPort.h"
#include "GL_DrawingFuncs/GL_DrawingFuncs.h"

using namespace std;

const GLint WIDTH = 800, HEIGHT = 800;

void display(SerialPort &arduino);
int get_int(int, std::string prompt);
const vector<string> explode(const string& s, const char& c);

int grados = 0;
bool giroCompleto = false;

char datos[MAX_LONGINTUD_DATOS];


int main() {
	// set spanish
	setlocale(LC_ALL, "Spanish");

	
	// connect to arduino
	//int port = get_int(0, "\n¿Cúal es el puerto en el que está conectado el arduino? ");
	int port = 9;

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
	

	int screenWidth, screenHeight;

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	
	double monitorScreenWidth = mode->width;
	double monitorScreenHeight = mode->height;

	GLFWwindow * window = glfwCreateWindow(mode->width, mode->height, "Arduino Radar UES-FMO", nullptr, nullptr);


	

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwSetWindowPos(window, 0, 0); // init pos

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

	double ratio = monitorScreenHeight / monitorScreenWidth;
	cout << "width: " << monitorScreenWidth << " height: " << monitorScreenHeight << endl;
	cout << "El ratio es: " << ratio << endl;
	glOrtho(-10, 10, -10*ratio, 10 * ratio, -100, 100);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); 

		// DRAW OPENGL
		display(arduino);
		// END OF THE DRAWS

		glfwSwapBuffers(window);
	}
	
	return EXIT_SUCCESS;
}

// ALL DRAWS HERE
void display(SerialPort &arduino) {

	arduino.leerPuertoSerie(datos, MAX_LONGINTUD_DATOS);
	
	//vector<string> v{ explode(datos, ' ') };
	//for (auto n : v) cout << n << endl;


	/*vector<string> v{ explode(datos, ' ') };
	for (auto n : v) {
		vector<string> separado{ explode(n, '.') };
		for (auto valor : separado) {
			cout << valor << endl;
		}
		//cout << n << endl;
	}*/

	int valoresss[2];
	long int contador = 0;

	//para los datos
	long int gradosArduino = 0;
	long int distancia = 0;

	vector<string> v{ explode(datos, ' ') };
	for (auto n : v) {
		vector<string> separado{ explode(n, '.') };
		for (auto valor : separado) {
			// separacion de las comas
			vector<string> comas{ explode(valor, ',') };
			for (auto c : comas) {
				contador++;

				if (contador % 2 != 0) {
					//cout << "GRADOS: " << c << endl;
					string gra = c;
					gradosArduino = stoi(gra);
				}
				else {
					//cout << "DISTANCIA: " << c << endl;
					string dis = c;
					distancia = stoi(dis);
				}
				
			}

		}
	}

	cout << "grados = " << gradosArduino << endl;
	cout << "distancia = " << distancia << endl;


	int x = distancia * cos(gradosArduino);
	int y = (distancia * sin(gradosArduino)) - 5;
	solidCircle2d(x, y, 0.5, 10000, 0, 360, new GLfloat[3]{ 1.0f, 0.0f, 0.0f });

	//LineDegrees2d(x, y, 8, 0, new GLfloat[4]{ 1.0f, 0.0f, 0.0f, 1.0});

	

	// green circles meter
	for (int i = 2; i < 12; i+=2) {
		circle2d(0, -5, i, 10000, 0, 360, new GLfloat[3]{ 0.0f, 1.0f, 0.0f });
	}

	// red circle
	solidCircle2d(0, -5.0, 1, 10000, 0, 360, new GLfloat[3]{ 1.0f, 0.0f, 0.0f });

	// white circle
	solidCircle2d(0, -5.0, 0.2, 10000, 0, 360, new GLfloat[3]{ 1.0f, 1.0f, 1.0f });

	LineDegrees2d(0, -5.0, 10.0, grados, new GLfloat[4]{ 1.0f, 1.0f, 1.0f, 0.4f });

	if (grados <= 180 && !giroCompleto) {
		grados++;
		
		if (grados == 180) {
			giroCompleto = !giroCompleto;
		}
	}
		
	else {
		grados--;

		if (grados == 0) {
			giroCompleto = !giroCompleto;
		}
	}
		
	
	//LineDegrees2d(0, -5.0, 10.0, 45, new GLfloat[3]{ 1.0f, 1.0f, 1.0f });
}

const vector<string> explode(const string& s, const char& c)
{
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
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
		std::cerr << "El valor ingresado debe ser mayor o igual que cero >= " << min << ". Por favor, intente nuevamente.\n";
	}
}

/*// load an image file directly as a new OpenGL texture
	GLuint tex_2d = SOIL_load_OGL_texture
	(
		"resources/textura.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	// check for an error during the load process
	if (0 == tex_2d)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	// Frente
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glBegin(GL_POLYGON);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);*/