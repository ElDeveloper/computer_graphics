/*
 *  Object Examples
 *  'm' to switch modes (objects)
 *  'a' to toggle axes
 *  '0' snaps angles to 0,0
 *  arrows to rotate the world
 */

#include "csci5229.h"

#include <assert.h>
#include <math.h>

int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
double zh=0;      //  Rotation of teapot
int axes=1;       //  Display axes
int mode=0;       //  What to display

static void draw_cilinder(double x, double y, double z, unsigned int steps);

static void draw_cilinder(double x, double y, double z, unsigned int steps){
	double circle_points[steps][2];
	float di=360/steps, angle=0;
	static float r = 1, h = 1;
	int i = 0;

	// generate the points
	for (i = 0; i<steps; i++ ){
		angle+=di;

		circle_points[i][0] = r*cos(i);
		circle_points[i][1] = r*sin(i);
	}

	//  Save transformation
	glPushMatrix();
	glTranslated(x,y,z);

	// other side
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(x, y, z);
	for (i=0; i<steps; i++){
		glVertex3d(circle_points[i][0],circle_points[i][1], z);
	}
	glVertex3d(circle_points[0][0], circle_points[0][1], z);
	glEnd();

	// one side
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(x, y, z+h);
	for (i=0; i<steps; i++){
		glVertex3d(circle_points[i][0],circle_points[i][1], z+h);
	}
	glVertex3d(circle_points[0][0], circle_points[0][1], z+h);
	glEnd();

	// draw the strip connecting the two circles using the differential value in
	// height (Z) between the two circles; the value is the same for all other
	glBegin(GL_QUAD_STRIP);
	for (i=0; i<steps; i++){
		glVertex3d(circle_points[i][0],circle_points[i][1], z);
		glVertex3d(circle_points[i][0],circle_points[i][1], z+h);
	}
	glVertex3d(circle_points[0][0],circle_points[0][1], z);
	glVertex3d(circle_points[0][0],circle_points[0][1], z+h);
	glEnd();

	//  Undo transformations
	glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
	const double len=1.5;  //  Length of axes
	//  Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	//  Undo previous transformations
	glLoadIdentity();
	//  Set view angle
	glRotatef(ph,1,0,0);
	glRotatef(th,0,1,0);

	glColor3f(1,0,0);
	//draw_cilinder(double x, double y, double z, double r, double h, unsigned int steps);

	glPushMatrix();
	glRotatef(zh, 1, 0, 0);
	//glScalef(0.5, 1, 0, 0);
	draw_cilinder(0, 0, 0, 100);
	glPopMatrix();

	//  White
	glColor3f(1,1,1);
	//  Draw axes
	if (axes)
	{
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
	}
	//  Five pixels from the lower left corner of the window
	glWindowPos2i(5,5);
	//  Print the text string
	Print("Angle=%d,%d",th,ph);
	//  Render the scene
	glFlush();
	//  Make the rendered scene visible
	glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
	//  Right arrow key - increase angle by 5 degrees
	if (key == GLUT_KEY_RIGHT)
		th += 5;
	//  Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT)
		th -= 5;
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP)
		ph += 5;
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN)
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
void key(unsigned char ch,int x,int y)
{
	//  Exit on ESC
	if (ch == 27)
		exit(0);
	//  Reset view angle
	else if (ch == '0')
		th = ph = 0;
	//  Toggle axes
	else if (ch == 'a' || ch == 'A')
		axes = 1-axes;
	//  Switch display mode
	else if (ch == 'm')
		mode = (mode+1)%7;
	else if (ch == 'M')
		mode = (mode+6)%7;
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
	const double dim=2.5;
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
 *  GLUT calls this toutine when there is nothing else to do
 */
void idle()
{
	double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
	zh = fmod(90*t,360);
	glutPostRedisplay();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
	//  Initialize GLUT and process user parameters
	glutInit(&argc,argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitWindowSize(600,600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	//  Create the window
	glutCreateWindow("Yoshiki Vazquez Baeza");
	//  Tell GLUT to call "idle" when there is nothing else to do
	glutIdleFunc(idle);
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
