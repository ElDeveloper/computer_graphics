/*
 *  Assignment 2
 *  Based on ex7.c from CSCI5229 Fall 2013
 *
 *  Write a three dimensional OpenGL visualization of the Lorenz Attractor.
 *

 author: Yoshiki Vazquez Baeza
 e-mail: yoshiki89@gmail.com
 creation: September 19, 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle

double s  = 10;
double b  = 2.6666;
double r  = 28;

//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...){

	char    buf[LEN];
	char*   ch=buf;
	va_list args;
	//  Turn the parameters into a character string
	va_start(args,format);
	vsnprintf(buf,LEN,format,args);
	va_end(args);
	//  Display the characters one at a time at the current raster position
	while (*ch)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 * Z component of projection
 */
double Zp(double x,double y,double z){
	return -Sin(th)*Cos(ph)*x + Sin(ph)*y + Cos(th)*Cos(ph)*z;
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display(){
	const double len=5;  //  Length of axes

	int i;
	/*  Coordinates  */
	double x = 1;
	double y = 1;
	double z = 1;
	/*  Time step  */
	double dt = 0.001;

	double dx = 0;
	double dy = 0;
	double dz = 0;

	//  Erase the window and the depth buffer
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//  Undo previous transformations
	glLoadIdentity();

	//  Set view angle
	glRotatef(ph,1,0,0);
	glRotatef(th,0,1,0);

	glEnable(GL_DEPTH_TEST);

	//  White
	glColor3f(1,1,1);

	//  Draw axes
	glBegin(GL_LINES);

	glVertex3d( x/10, y/10, z/10);
	/*
	 *  Integrate 50,000 steps (50 time units with dt = 0.001)
	 *  Explicit Euler integration
	 */
	for (i=0;i<50000;i++){
		dx = s*(y-x);
		dy = x*(r-z)-y;
		dz = x*y - b*z;
		x += dt*dx;
		y += dt*dy;
		z += dt*dz;
		glColor3f(1/x,1/y,1/z);
		glVertex3d( x/10, y/10, z/10);
	}

	glEnd();

	// axes are white
	glColor3f(0, 0, 0);

	glBegin(GL_LINES);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(len,0.0,0.0);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(0.0,len,0.0);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(0.0,0.0,len);
	glEnd();

	//  Label axes
	glRasterPos3d(len,0.0,0.0);
	Print("X");
	glRasterPos3d(0.0,len,0.0);
	Print("Y");
	glRasterPos3d(0.0,0.0,len);
	Print("Z");

	//  Five pixels from the lower left corner of the window
	glWindowPos2i(5,5);
	//  Print the text string
	Print("R: %.3f S: %.3f B: %.3f", r, s, b);

	//  Render the scene
	glFlush();
	//  Make the rendered scene visible
	glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y){

	//  Right arrow key - increase angle by 5 degrees
	if (key == GLUT_KEY_RIGHT)
		th += 5;
	//  Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT)
		th -= 5;
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN)
		ph += 5;
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_UP)
		ph -= 5;
	//  Keep angles to +/-360 degrees
	th %= 360;
	ph %= 360;
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y){

	//  Exit on ESC
	if (ch == 27)
		exit(0);
	//  Reset view angle
	else if (ch == '0')
		th = ph = 0;

	// increase the value of s
	else if (ch == 's')
		s = s + 0.1;
	// decrease the value of s
	else if (ch == 'S')
		s = s - 0.1;

	// increase the value or r
	else if (ch == 'r')
		r = r + 0.1;
	// decrease the value of r
	else if (ch == 'R')
		r = r - 0.1;

	// increase the value of b
	else if (ch == 'b')
		b = b + 0.1;
	// decrease the value of b
	else if (ch == 'B')
		b = b - 0.1;

	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height){

	const double dim=10;
	//  Ratio of the width to the height of the window
	double w2h = (height>0) ? (double)width/height : 1;
	//  Set the viewport to the entire window
	glViewport(0,0, width,height);
	//  Tell OpenGL we want to manipulate the projection matrix
	glMatrixMode(GL_PROJECTION);
	//  Undo previous transformations
	glLoadIdentity();
	//  Orthogonal projection
	glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
	//  Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	//  Undo previous transformations
	glLoadIdentity();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[]){
	//  Initialize GLUT and process user parameters
	glutInit(&argc,argv);
	//  Request double buffered, true color window with Z buffering
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	//  Request 500 x 500 pixel window
	glutInitWindowSize(500,500);
	//  Create the window
	glutCreateWindow("Visibility");
	//  Tell GLUT to call "display" when the scene should be drawn
	glutDisplayFunc(display);
	//  Tell GLUT to call "reshape" when the window is resized
	glutReshapeFunc(reshape);
	//  Tell GLUT to call "special" when an arrow key is pressed
	glutSpecialFunc(special);
	//  Tell GLUT to call "key" when a key is pressed
	glutKeyboardFunc(key);
	//  Pass control to GLUT so it can interact with the user
	glutMainLoop();

	return 0;
}
