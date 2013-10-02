#ifndef __CSCI5229__
#define __CSCI5229__

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

//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

//  Maximum length of text string
#define MAX_STRING_LENGTH 8192

void Print(const char* format , ...);
void draw_cylinder(double x, double y, double z, unsigned int steps, float colors[3][3]);
#endif