// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Hacky header to allow for easier compilation across multiple platforms. Even
// though the WIN32 stuff is here, there's no chance in heck that this project
// would compile in WIN32 :D
//
// If any OpenGL stuff is needed, include this file instead of including OpenGL
// headers directly.
#ifndef __OS_H__
#define __OS_H__

#ifdef WIN32
#include <windows.h>
#include <locale.h>
#endif
#ifdef __mac
#include <string.h>
#include <GLUT/glut.h>
#endif
#ifdef __linux
#include <string.h>
#include <GL/glut.h>
#endif

#endif
