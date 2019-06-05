//
// Created by fernando9825 on 04-03-19.
//


#include "GL_DrawingFuncs.h"

#define ERROR_MESSAGE_POINTS  "The minimum amount of points is a positive integer value, aborting drawing a "
#define ERROR_MESSAGE_LENGTH "The minimum length is a positive floating point value, aborting drawing a "
#define CIRCLE2D "circle"

#define SQUARE2D "square"

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

double fixVerticalPosition(double posY) {
	/*
	 * Assuming that orthogonal view is glOrtho(-30.0, 30.0, -16.00, 16.0, -30.0, 30.0);
	 * 30.0 left and right, 16.0 top and bottom, 30 near and far, then
	 * 16 / 30 = 0.5333333 approximately, so posY must be multiplied to fix coordinates
	 */
	 //return posY * (16.0 / 30.0);
	return posY;
}

// cartesion plane
void cartesianPlane(int units) {
	int fixedY = 3;

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	// horizontal axis
	glVertex2d(-units, 0.0);
	glVertex2d(units, 0.0);

	// vertical axis
	glVertex2d(0.0, -units);
	glVertex2d(0.0, units);
	glEnd();

	// draw units
	units = abs(units);
	glBegin(GL_LINES);
	for (int i = -units; i <= units; i++) {
		// Y axis units
		glVertex2d(-0.1, i);
		glVertex2d(0.1, i);

		// X axis units
		glVertex2d(i, -0.1);
		glVertex2d(i, 0.1);
	}
	glEnd();

	// close the cartesian plane
	glBegin(GL_LINES);
	// top line
	glVertex2d(-units, units); // top left
	glVertex2d(units, units); // top right

	// right line
	glVertex2d(units, units); // top right
	glVertex2d(units, -units); // bottom right

	// bottom line
	glVertex2d(units, -units); // bottom right
	glVertex2d(-units, -units); // bottom left

	// left line
	glVertex2d(-units, -units); // bottom left
	glVertex2d(-units, units); // top left
	glEnd();
}




// colors
/*
GLfloat * RGB(byte red, byte green, byte blue) {
	GLfloat RGB[3];
	RGB[0] = (to_integer<int>(red) / (GLfloat) 255);
	RGB[1] = (to_integer<int>(green) / (GLfloat) 255);
	RGB[2] = (to_integer<int>(blue) / (GLfloat) 255);

	cout << "red " << RGB[0] <<" green " << RGB[1] << " blue " << RGB[2] << endl;
	return RGB;
}*/

/*double convertRadiansToDegrees(double radians) {
	return (180*radians)/M_PI;
}*/

void colorSet(GLfloat RGB[3]) {
	glColor3f(RGB[0], RGB[1], RGB[2]);
}

double convertDegreesToRadians(double degrees) {
	return (degrees * PI) / 180;
}

// Jack Bresenham algorithm to draw a line
void draw_pixel(int x, int y) {
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void drawBresenhamline(int x1, int y1, int x2, int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x, y;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1;
	y = y1;
	if (dx > dy) {
		draw_pixel(x, y);
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}

	}
	else {
		draw_pixel(x, y);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}

// FUNCTIONS TO DRAW A CIRCLE
void LineDegrees2d(double posX, double posY, double distance, double degrees,
	GLfloat RGB[4]) {


	glPointSize(2.0f);
	colorSet(RGB);
	glColor4f(RGB[0], RGB[1], RGB[2], RGB[3]);
	glBegin(GL_LINES);

	double x = 0, y = 0;

	double increment = convertDegreesToRadians(degrees);
	//cout << "increment " << increment << endl;
	//cout << "final " << convertDegreesToRadians(final) << endl;
	x = posX + distance * cos(increment);
	y = posY + distance * sin(increment);
	glVertex2d(posX, posY);
	glVertex2d(x, y);
	//increment += PI / amountOfPoints;

	glEnd();
}

// FUNCTIONS TO DRAW A CIRCLE
void circle2d(double posX, double posY, double radius, double amountOfPoints, double degreesStart, double degreesEnd,
	GLfloat RGB[3]) {

	if (amountOfPoints <= 0) {
		cout << "The minimum amount of points is a positive integer value, aborting drawing a circle" << endl;
		return;
	}


	// fixing Y coordinate
	posY = fixVerticalPosition(posY);

	glPointSize(2.0f);
	colorSet(RGB);
	glBegin(GL_POINTS);

	double x = 0, y = 0, final = 0;

	final = degreesStart + degreesEnd;

	double increment = convertDegreesToRadians(degreesStart);
	//cout << "increment " << increment << endl;
	//cout << "final " << convertDegreesToRadians(final) << endl;
	while (increment < convertDegreesToRadians(final)) {
		x = posX + radius * cos(increment);
		y = posY + radius * sin(increment);
		glVertex2d(x, y);
		increment += PI / amountOfPoints;
	}

	glEnd();
}

void solidCircle2d(double posX, double posY, double radius, double amountOfPoints, double degreesStart, double degreesEnd,
	GLfloat RGB[3]) {

	if (amountOfPoints <= 0) {
		cout << "The minimum amount of points is a positive integer value, aborting drawing a circle" << endl;
		return;
	}

	if (amountOfPoints > 500) {
		amountOfPoints = 500;
	}


	// fixing Y coordinate
	posY = fixVerticalPosition(posY);

	colorSet(RGB);
	glBegin(GL_POLYGON);

	double x = 0, y = 0, final = 0;

	final = degreesStart + degreesEnd;

	double increment = convertDegreesToRadians(degreesStart);
	//cout << "increment " << increment << endl;
	//cout << "final " << convertDegreesToRadians(final) << endl;
	while (increment < convertDegreesToRadians(final)) {
		x = posX + radius * cos(increment);
		y = posY + radius * sin(increment);
		glVertex2d(x, y);
		increment += PI / amountOfPoints;
	}

	glEnd();
}



// function to draw a line with degrees
void wiredCircle2d(double posX, double posY, double radius, int amountOfPoints, double degreesStart, double degreesEnd,
	GLfloat RGB[3]) {
	if (amountOfPoints <= 0) {
		cout << ERROR_MESSAGE_POINTS << CIRCLE2D << endl;
		return;
	}

	if (amountOfPoints > 500) {
		amountOfPoints = 500;
	}

	// fixing Y coordinate
	posY = fixVerticalPosition(posY);

	colorSet(RGB);
	glBegin(GL_LINES);

	double x = 0, y = 0, final = 0;

	final = degreesStart + degreesEnd;

	double increment = convertDegreesToRadians(degreesStart);
	//cout << "increment " << increment << endl;
	//cout << "final " << convertDegreesToRadians(final) << endl;
	while (increment < convertDegreesToRadians(final)) {
		x = posX + radius * cos(increment);
		y = posY + radius * sin(increment);
		glVertex2d(posX, posY);
		glVertex2d(x, y);
		increment += PI / amountOfPoints;
	}

	glEnd();
}

// FUNCTIONS TO DRAW A SQUARE

void SolidSquare2d(double posX, double posY, double length) {
	//order is top-left -> top-right; top-right -> bottom-right; bottom-right -> bottom-left; bottom-left -> top-left

	if (length <= 0) {
		cout << ERROR_MESSAGE_LENGTH << SQUARE2D << endl;
	}

	// Y values must be fixed
	glBegin(GL_QUADS);

	/*
	glVertex2d(-0.5, 0.5); // top-left
	glVertex2d(0.5 , 0.5); // top-right

	glVertex2d(0.5, -0.5); // bottom-right
	glVertex2d(-0.5, -0.5); // bottom-left
	*/

	glVertex2d(posX, posY); // top-left
	glVertex2d(posX + length, posY); // top-right

	glVertex2d(posX + length, posY - length); // bottom-right
	glVertex2d(posX, posY - length); // bottom-left


	/*glVertex2d(-posX, -fixVerticalPosition(length)); // bottom-left
	glVertex2d(posX, fixVerticalPosition(posY)); // top-left*/

	glEnd();

}

void square2d(double posX, double posY, double length) {
	//order is top-left -> top-right; top-right -> bottom-right; bottom-right -> bottom-left; bottom-left -> top-left

	if (length <= 0) {
		cout << ERROR_MESSAGE_LENGTH << SQUARE2D << endl;
	}

	// Y values must be fixed
	glBegin(GL_LINES);

	// top line
	glVertex2d(posX, posY); // top-left
	glVertex2d(posX + length, posY); // top-right

	// right line
	glVertex2d(posX + length, posY); // top-right
	glVertex2d(posX + length, posX - length); // bottom-right

	// bottom line
	glVertex2d(posX + length, posY - length); // bottom-right
	glVertex2d(posX, posY - length); // bottom-left

	// left line
	glVertex2d(posX, posY - length); // bottom-left
	glVertex2d(posX, posY); // top-left

	glEnd();
}


// FUNCTIONS TO DRAW A RECTANGLE

void rectangle2d(double posX, double posY, double base, double height) {
	//order is top-left -> top-right; top-right -> bottom-right; bottom-right -> bottom-left; bottom-left -> top-left

	if (base <= 0 || height <= 0) {
		cout << ERROR_MESSAGE_LENGTH << SQUARE2D << endl;
	}

	// Y values must be fixed
	glBegin(GL_LINES);

	// top line
	glVertex2d(posX, posY); // top-left
	glVertex2d(posX + base, posY); // top-right

	// right line
	glVertex2d(posX + base, posY); // top-right
	glVertex2d(posX + base, posY - height); // bottom-right

	// bottom line
	glVertex2d(posX + base, posY - height); // bottom-right
	glVertex2d(posX, posY - height); // bottom-left

	// left line
	glVertex2d(posX, posY - height); // bottom-left
	glVertex2d(posX, posY); // top-left

	glEnd();
}

