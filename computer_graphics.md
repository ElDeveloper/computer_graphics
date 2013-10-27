# Computer Graphics

*August 29, 2013*

Class is packed, get here early.

Ben the TA should help with Open GL and stuff. Monday, Tuesday and Wednesday.
Check the moodle to get Ben's personal information.

All the things will be done in Open GL to avoid re-inventing the wheel.

No test and no exams (woohoo!).

The class project will be the last part of the semester.

Basics (1/3)
	How do you set up projections, line clipping, projections, text, etc.

Advanced (1/3)
	Illumination, shading, transparency, texture mapping and shadders.
	Shadders are sub-programs that run directly on your video card. There won't
	be that much of this in this class, there is more in the next course.

Project (1/3)
	Working on your project, visualization, modeling, etc. Just whatever that
	you are interested in.

	Re-writting Google Earth shouldn't be that hard to do.

The engine itself should be fairly portable.

OpenGL is a standard as set by the kronos group.

Willem A Schreuder aka Vlakkies

willem@prinmath.com

4229 or 5229 to begin the mail subject otherwise the e-mail is going to be
rejected by his e-mail filter.

Weekday office hours are from 6:30 am to 9:00 pm.

The office hasn't been set yet.

Assumptions:
	You know how to program.
	You are fluent in C.
	Unless there is a good reason stick to C or C++.
	He hates Java with fury (for historical reasons).

	You are comfortable with linear algebra.
	Matrix and vector multiplication.
	Dot and cross products.
	Rotation matrices.

The goal is not to get an A, the goal is to impress your friends (lol).

Assignments are due Thursday evening 11:59 pm, these must be submitted on time.
	Grace period is until 8:00 am next morning.

Stealing is fine? If you find code on the  web it's good to use it as a starting
point but that should only be the starting point.

	YOU MUST GIVE CREDIT.
	You must take full ownership and responsability of any code you are using.

You have to take the code from good to great if you are using someone else's
code.

If there's feedback but there was not grade then the assignment was not good
enough.

OpenGL a primer, what this book deals with is how OpenGL does things. The
author is fairly good at explaining stuff.

Computer Graphics Principles and PRactice, use 3rd edition, nothing lower than
that. Useful if you want to go deeper in the knowledge.

iPhone 3D programming; from O'Reilly, fairly good.

Next assignment is due tuesday september 3 at 11:59 pm
	moodle.cs.colorado.edu
	42295229
	Add a picture.
	Name and area of study
	Platform, hardware, graphics, os
	Background and interest in computer graphics
	Project Ideas

Compile and run the gears program.

glxinfo and check that direct rendering equals yes.

*Assignments*

Example 6 is your friend for assignment two. Thursday sept 19th.

Assignment 3, thursday september 26. Add 3D objects to assignment 2.

Assignment 4, look at diffeerente projections and look at different ways of
adding different projections.

Assignment 5, is terribly difficult assignment.

Project Deadlines
	Grad students should put more effort in this project.
	Project is due October 17, the earlier the better.
	Project is half the grade of the class.

Assignments are reviewed under Ubuntu 12.04
Set #ifdef so it can be compiled
	make clean
	make
name executables as hw1, hw2, etc
Window Title Assignment X: Your Name
	Set number of hours.


The only thing you need to include when using GLUT, you need 

	#define GL_GLEXT_PROTOTYPES
	#include <GL/glut.h>

	To link the libraries you may only need -l glut
	For OS X -framework GLUT -framework OpenGL

Open GL uses camel casing an prefixes things with gl and suffixed by the number
of dimensions that you are using.

	glDoSomthingXy()

GLU and GLUT are not compatible, this could cause some issues if not taken into
account.

GL works with degrees.

Special functions are called upon the action of one of the special keys being
pressed.

Image Tearing, artifacts are added to the render. Double buffering makes this
problem disappear.

**----------------------------------------------------------------------------**

*September 5, 2013*

OpenGL is event driven, you don't call us we will call you. Users have to in
turn register callbacks.

Do never call display() call instead glutPostRedsisplay().

Calling sleep() will make the program to stall on screen, hence if you want to
do things based on time you should use glutTimerFunc().

You don't want to clutter the processing pipeline, you want to give as much time
as possible to glut.

About lines, there are two types of lines the line strip which will be a
continuous one, lines which will be interrupted lines and line polygon which
will be a closed polygon.

GL_TRIANGLES is similar to GL_LINES, that is you will draw a triangle every
three points, in other case if you use GL_TRIANGLES_STRIP the result will be
a set of conected triangles.

As a last variation of these primitives, we will have GL_QUADS.

Note that some errors could be coming out of not using plural in these names.

Things in OpenGL come in packs of four, for example with colors there's R, G, B
and the alpha component (this by the way is known in X11 as TrueColor).

Displaying a scene in a nutshell:

	glutDisplayFnc()
	glClear()
	DrawSomething
	glFlush() // clean up the buffers
	glutSwapBuffers() // If you are doing double buffering
	glutPostRedisplay() // we are not calling the display function by ourselves

Types of transformations
========================

Translations: Allow you to move one thing to another coordinate in a three
dimensional space.

Scaling: changes the factor which are used to display things in three dimensions

Rotations: Allows you to rotate in any axis passing a unit vector and the
amount of rotation is specified in degrees.

Push Matrix and Pop Matrix
==========================

Basically a stack of transformations of previous and next stages that allows
you to go from one state to the other.

Projections
===========

glOrtho is an orthographic projection, the easiest to use. 

gluLookAt provides a way to set the perspective from where you are seeing
things in a scene.

Text
====

Stroked fonts are lines in the scene.

Bitmap fonts are images themselves.

Be careful with window defaults, it can be very tricky and it is very hardware
specific. glEnable and glDisable are functions that will allow you to modify
these values, and can be changed at any point.

glGetError() resets all the errors  and gets you only the last error.

Channels of information are definitely different than dimensions and we will
require them because we will only be dealing with three dimensions.

Professor's phone number 303 548 9089.

The clipping algorithm is mainly based on logical AND operations that happen
whether or not points are visible is determined by this. Refer to the
2d-clipping algorithm document for a further explanation on this.

The trick to clipping is clipping by hemispheres, first one hemisphere and then
another hemisphere.

*October 3, 2013*

Light
=====

Ray-tracing useful for light calculations; though it's usually not that useful,
it's better to do recursive ray-tracing i. e. the objects that appear on the
scene each generate a set a set of rames back to the eye.

The lighting calculations all get calculated at a vertex, nothing else besides
that; everything else is an interpolation around that surface.

