
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#ifndef GX_COLOR_H
#define GX_COLOR_H

#include "ML_Maths.h"

//#include <GL/gl.h>

class gxColor
{
public:

	gxColor();
	gxColor(int redv, int greenv, int bluev);
	gxColor(int redv, int greenv, int bluev, int alphav);

	void SetOpenGLColor() const;

	int red;
	int green;
	int blue;
	int alpha;
};

gxColor gxColorAdd(const gxColor & colorA, const gxColor & colorB);
gxColor gxColorSubtract(const gxColor & colorA, const gxColor & colorB);
gxColor gxColorAverage(const gxColor & colorA, const gxColor & colorB);
gxColor gxColorWeightedAverage(const gxColor & colorA, const gxColor & colorB, mlFloat fWeight);

gxColor gxMakeRandomColor();

extern const gxColor gxColorRed;
extern const gxColor gxColorGreen;
extern const gxColor gxColorBlue;
extern const gxColor gxColorWhite;
extern const gxColor gxColorBlack;

extern const gxColor gxColorYellow;
extern const gxColor gxColorPurple;
extern const gxColor gxColorAqua;

#endif // GX_COLOR_H
