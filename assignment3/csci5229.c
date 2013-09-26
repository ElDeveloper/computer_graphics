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
