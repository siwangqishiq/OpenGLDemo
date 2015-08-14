#ifndef _GEASS_H_
#define _GEASS_H_

#include <stdio.h>

struct _Point3D{
	float x;
	float y;
	float z;
};

typedef struct _Point3D Point3D;

void printPoint3D(Point3D * pPoint3D);

#endif