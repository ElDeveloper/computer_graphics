#include "csci5229.h"

#include <assert.h>
#include <math.h>

int th=0;			//  Azimuth of view angle
int ph=0;			//  Elevation of view angle

int axes=0;			//  Display axes
int mode=0;			//  Projection mode
int fov=55;			//  Field of view (for the perspective projection)
double asp=1;		//  Aspect ratio
double dim=5.0;		//  Size of world

// the crazy cylinder that rotates
double cylinder_rotation=0;

// keep track of the position of the flying house
float house_x, house_y, house_z, t_mobious=0;

static void draw_house(double x, double y, double z, float colors[3][3]);
static void draw_house(double x, double y, double z, float colors[3][3]){
	draw_cylinder(x, y, z, 5, colors);
}

/*
 *  Set projection
 */
static void Project()
{
	//  Tell OpenGL we want to manipulate the projection matrix
	glMatrixMode(GL_PROJECTION);
	//  Undo previous transformations
	glLoadIdentity();
	//  Perspective transformation
	if (mode){
		gluPerspective(fov,asp,dim,10*dim);
	}
	//  Orthogonal projection
	else{
		glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
	}
	//  Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	//  Undo previous transformations
	glLoadIdentity();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display(){
	float cylinder_color_a[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	float cylinder_color_b[3][3] = {{252.0/255.0, 141.0/255.0, 89/255.0},
		{1, 1, 191/255.0}, {145/255.0, 207/255.0, 96/255.0}};

	//  Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	//  Undo previous transformations
	glLoadIdentity();
	//  Set view angle

	// MAKE the projection transformations after loading the identity matrix
	if (mode){
		double Ex = -2*dim*Sin(th)*Cos(ph);
		double Ey = +2*dim        *Sin(ph);
		double Ez = +2*dim*Cos(th)*Cos(ph);
		gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
	}
	//  Orthogonal - set world orientation
	else{
		glRotatef(ph,1,0,0);
		glRotatef(th,0,1,0);
	}

	// cylinder one
	glPushMatrix();
	glRotatef(cylinder_rotation, 1, 0, 0);
	glRotatef(cylinder_rotation/0.5, 0, 1, 0);
	glScaled(0.9, 0.78, 0.4);
	draw_cylinder(0, 0, 0, 500, cylinder_color_a);
	glPopMatrix();

	// cylinder two
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	draw_cylinder(2, 2, 2, 500, cylinder_color_b);
	glPopMatrix();

	// house one
	glPushMatrix();
	draw_house(-2, -2, -2, cylinder_color_b);
	glPopMatrix();

	// house two
	glPushMatrix();
	draw_house(0.5, -.8, -2, cylinder_color_b);
	glPopMatrix();

	// house 3
	glPushMatrix();
	draw_house(house_x, house_y, house_z, cylinder_color_a);
	glPopMatrix();

	//  White
	glColor3f(1,1,1);
	//  Draw axes
	if (axes){
		glBegin(GL_LINES);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(dim-0.5,0.0,0.0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(0.0,dim-0.5,0.0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(0.0,0.0,dim-0.5);
		glEnd();
		//  Label axes
		glRasterPos3d(dim-0.5,0.0,0.0);
		Print("X");
		glRasterPos3d(0.0,dim-0.5,0.0);
		Print("Y");
		glRasterPos3d(0.0,0.0,dim-0.5);
		Print("Z");
	}

	//  Five pixels from the lower left corner of the window
	glWindowPos2i(5,5);
	//  Print the text string
	Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");
	//  Render the scene
	glFlush();
	//  Make the rendered scene visible
	glutSwapBuffers();
}

/*
 *  GLUT calls this routine when there is nothing else to do
 */
void idle(){
	double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
	cylinder_rotation = fmod(90*t,360);

	t_mobious = fmod(t, 360);

	house_x = (1 + 2*cos(0.5*t_mobious))*cos(t_mobious);
	house_y = (1 + 2*sin(0.5*t_mobious))*sin(t_mobious);
	house_z = 2*sin(0.5*t_mobious);

	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y){
	//  Right arrow key - increase angle by 5 degrees
	if (key == GLUT_KEY_RIGHT){
		th += 5;
	}
	//  Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT){
		th -= 5;
	}
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP){
		ph += 5;
	}
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN){
		ph -= 5;
	}
	//  PageUp key - increase dim
	else if (key == GLUT_KEY_PAGE_UP){
		dim += 0.1;
	}
	//  PageDown key - decrease dim
	else if (key == GLUT_KEY_PAGE_DOWN && dim>1){
		dim -= 0.1;
	}
	//  Keep angles to +/-360 degrees
	th %= 360;
	ph %= 360;
	//  Update projection
	Project();
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y){
	//  Exit on ESC
	if (ch == 27){
		exit(0);
	}
	//  Reset view angle
	else if (ch == '0'){
		th = ph = 0;
	}
	//  Toggle axes
	else if (ch == 'a' || ch == 'A'){
		axes = 1-axes;
	}
	//  Switch display mode
	else if (ch == 'm' || ch == 'M'){
		mode = 1-mode;
	}
	// decrease the size of the world
	else if (ch == 'd'){
		dim -= 0.1;
	}
	// increase the size of the world
	else if (ch == 'D'){
		dim += 0.1;
	}
	//  Change field of view angle
	else if (ch == '-' && ch>1){
		fov--;
	}
	else if (ch == '+' && ch<179){
		fov++;
	}
	//  Reproject
	Project();
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height){
	//  Ratio of the width to the height of the window
	asp = (height>0) ? (double)width/height : 1;
	//  Set the viewport to the entire window
	glViewport(0,0, width,height);
	//  Set projection
	Project();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[]){
	//  Initialize GLUT
	glutInit(&argc,argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutCreateWindow("Yoshiki Vazquez Baeza");
	//  Set callbacks for GL
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	//  Pass control to GLUT so it can interact with the user
	glutMainLoop();
	return 0;
}
