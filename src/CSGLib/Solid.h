
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#ifndef SOLID_H
#define SOLID_H

//#include "ML_Transform.h"
#include "ML_TransformTest.h"
#include "GX_Color.h"

//@@#include "GX_Model.h"

#include "IntSet.h"
#include "VectorSet.h"
#include "ColorSet.h"

//
//
//class IntSet;
//class VectorSet;
//class ColorSet;

class Solid
{
public:

	//IntSet * indices;
	//VectorSet * vertices;
	//ColorSet * colors;

	IntSet indices;
	VectorSet vertices;
	ColorSet colors;
	
//@@	Solid(const std::string & sFileName, const gxColor & colBase, int dRed, int dGreen, int dBlue);
	Solid(VectorSet * vertices, IntSet * indices, ColorSet * colors);
	virtual ~Solid();
	// Solid(File solidFile, Color3f color) - some file loading version
	
	VectorSet * getVertices();
	IntSet * getIndices();
	ColorSet * getColors();

	bool isEmpty();

	void setData(VectorSet & vertices, IntSet & indices, ColorSet & colors);
	
	void setColor(const gxColor & color);
	
	void ApplyTransform(mlTransformWithScale & t);

//@@	gxModel * m_pModel;

//private:

	void defineGeometry();

//@@	void loadCoordinateFile(const std::string & sFileName, const gxColor & colBase, int dRed, int dGreen, int dBlue);

	mlVector3D getMean();
};

#endif // SOLID_H
