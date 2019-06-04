//
// Created by fernando9825 on 04-03-19.
//

#ifndef OPENGL_DRAWS_GL_DRAWINGFUNCS_H
#define OPENGL_DRAWS_GL_DRAWINGFUNCS_H

#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>


using namespace std;

// cartesion plane
void cartesianPlane(int units);


//double convertRadiansToDegrees(double radians);
double convertDegreesToRadians(double degrees);

// Jack Bresenham algorithm
void drawBresenhamline(int x1, int y1, int x2, int y2);

// line with degrees
void LineDegrees2d(double posX, double posY, double distance, double degrees, GLfloat RGB[4]);


//  colors
//GLfloat[] RGB(byte red, byte green, byte blue);

// FUNCTIONS TO DRAW A CIRCLE
void circle2d(double posX, double posY, double radius, double amountOfPoints, double degreesStart, double degreesEnd,
	GLfloat RGB[3]);

void
solidCircle2d(double posX, double posY, double radius, double amountOfPoints, double degreesStart, double degreesEnd,
	GLfloat RGB[3]);

void wiredCircle2d(double posX, double posY, double radius, int amountOfPoints, double degreesStart, double degreesEnd,
	GLfloat RGB[3]);

// FUNCTIONS TO DRAW A SQUARE
void SolidSquare2d(double posX, double posY, double length);

void square2d(double posX, double posY, double length);

// FUNCTIONS TO DRAW A RECTANGLE

void rectangle2d(double posX, double posY, double base, double height);

#endif //OPENGL_DRAWS_GL_DRAWINGFUNCS_H
