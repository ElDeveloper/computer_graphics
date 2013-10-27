#include "CSCIx229.h"
// A lot of the code in this file is heavily based on example 13 from CSSCI5229

void draw_cylinder(double x, double y, double z, unsigned int steps,
	float colors[3][3], unsigned int front_texture, unsigned int body_texture){
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

	// enable the textures for this object
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,front_texture); // texture for the front face

	// one side
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, -1);
	glColor3f(colors[0][0], colors[0][1], colors[0][2]);
	for (i=0; i<steps; i++){
		glVertex3d(0, 0, z);
		glVertex3d(circle_points[i][0],circle_points[i][1], z);
		glTexCoord2f(circle_points[i][0],circle_points[i][1]);
	}
	glVertex3d(0, 0, z);
	glVertex3d(circle_points[0][0],circle_points[0][1], z);
	glEnd();

	// other side
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, 1);
	glColor3f(colors[1][0], colors[1][1], colors[1][2]);
	for (i=0; i<steps; i++){
		glVertex3d(0, 0, z+h);
		glVertex3d(circle_points[i][0],circle_points[i][1], z+h);
		glTexCoord2f(circle_points[i][0],circle_points[i][1]);
	}
	glVertex3d(0, 0, z+h);
	glVertex3d(circle_points[0][0],circle_points[0][1], z+h);
	glEnd();

	// draw the strip connecting the two circles using the differential value in
	// height (Z) between the two circles; the value is the same for all other
	glBegin(GL_QUAD_STRIP);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,front_texture); // texture for the front face

	glColor3f(colors[2][0], colors[2][1], colors[2][2]);
	for (i=0; i<steps; i++){
		glNormal3f(circle_points[i][0], circle_points[i][1], 0);
		glVertex3d(circle_points[i][0],circle_points[i][1], z);
		glVertex3d(circle_points[i][0],circle_points[i][1], z+h);
		// glTexCoord2f(circle_points[i][0],circle_points[i][1]);
	}
	glVertex3d(circle_points[0][0],circle_points[0][1], z);
	glVertex3d(circle_points[0][0],circle_points[0][1], z+h);
	glEnd();

	//  Undo transformations
	glPopMatrix();
}

void draw_house(double x, double y, double z, float colors[3][3],
	unsigned int front_texture, unsigned int body_texture){
	draw_cylinder(x, y, z, 5, colors, front_texture, body_texture);
}

