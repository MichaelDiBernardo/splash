/* readtex.h */

/**
 * THIS IS NOT -- I REPEAT ****NOT**** MY CODE! It is a freely available SGI texture
 * reader that is part of the 'bluepony' demo developed aeons ago by Silicon Graphics.
 * I borrowed it from the version of 'bluepony' that ships with the Apple Developer Examples.
 *
 */
#ifndef READTEX_H
#define READTEX_H

#ifdef __mac
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

extern GLboolean LoadRGBMipmaps(const char *imageFile, GLint intFormat);

#endif
