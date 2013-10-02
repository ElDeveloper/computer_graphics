#include "csci5229.h"

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
void Print(const char* format , ...){
	char buf[MAX_STRING_LENGTH];
	char *ch=buf;
	va_list args;

	//  Turn the parameters into a character string
	va_start(args,format);
	vsnprintf(buf,MAX_STRING_LENGTH,format,args);
	va_end(args);

	//  Display the characters one at a time at the current raster position
	while (*ch){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
	}
}

void draw_cylinder(double x, double y, double z, unsigned int steps, float colors[3][3]){
	double circle_points[steps][2];
	float di=360/steps, angle=0;

	// ideally we don't want to change it, but leave it there ... just in case
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
	glColor3f(colors[0][0], colors[0][1], colors[0][2]);
	for (i=0; i<steps; i++){
		glVertex3d(circle_points[i][0],circle_points[i][1], z);
	}
	glEnd();

	// one side
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(colors[1][0], colors[1][1], colors[1][2]);
	for (i=0; i<steps; i++){
		glVertex3d(circle_points[i][0],circle_points[i][1], z+h);
	}
	glEnd();

	// draw the strip connecting the two circles using the differential value in
	// height (Z) between the two circles; the value is the same for all other
	glBegin(GL_QUAD_STRIP);
	glColor3f(colors[2][0], colors[2][1], colors[2][2]);
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