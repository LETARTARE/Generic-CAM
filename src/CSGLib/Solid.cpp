
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#include "Solid.h"

#include "VectorSet.h"
#include "ColorSet.h"
#include "IntSet.h"

#if 0	//@@ Not Used
#include <fstream>

Solid::Solid(const std::string & sFileName, const gxColor & colBase, int dRed, int dGreen, int dBlue)
{
	// Load from file here.

	m_pModel = new gxModel();

	loadCoordinateFile(sFileName, colBase, dRed, dGreen, dBlue);
}
#endif

// There is another constructor that calls super - java class Shape3D::super();

Solid::Solid(VectorSet * vertices, IntSet * indices, ColorSet * colors)
{
//@@	m_pModel = new gxModel();

	setData(*vertices, *indices, *colors);		
}

Solid::~Solid()
{
//@@	delete m_pModel;

	// vertices, colors and indices are all stack allocated
	//delete vertices;
	//delete colors;
	//delete indices;
}

//---------------------------------------GETS-----------------------------------//

VectorSet * Solid::getVertices()
{
	// This thing makes a fresh copy and hands the requestor the copy.

	VectorSet * newVertices = new VectorSet();

	for(int i = 0; i < vertices.length; i++)
	{
		newVertices->AddVector(vertices[i]);
	}

	return newVertices;
}

IntSet * Solid::getIndices()
{
	IntSet * newIndices = new IntSet();

	for(int i = 0; i < indices.length; i++)
	{
		newIndices->AddInt(indices[i]);
	}

	return newIndices;
}

ColorSet * Solid::getColors()
{
	ColorSet * newColors = new ColorSet();

	for(int i = 0; i < colors.length; i++)
	{
		newColors->AddColor(colors[i]);
	}

	return newColors;
}

bool Solid::isEmpty()
{
	if(indices.length <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------SETS-----------------------------------//

/**
 * Sets the solid data. An exception may occur in the case of abnormal arrays 
 * (indices making references to inexistent vertices, there are less colors 
 * than vertices...)
 * 
 * @param vertices array of points defining the solid vertices
 * @param indices array of indices for a array of vertices
 * @param colors array of colors defining the vertices colors 
 */
void Solid::setData(VectorSet & vertices, IntSet & indices, ColorSet & colors)
{
	// Clear them...
	//this->vertices = new VectorSet();
	//this->colors = new ColorSet();
	//this->indices = new IntSet();

	//this->vertices.Clear();
	//this->colors.Clear();
	//this->indices.Clear();

	if(indices.length > 0)
	{
		for(int i=0; i<vertices.length; i++)
		{
			// Should add cloning to vectorset, and other 2 sets

			this->vertices.AddVector(vertices[i]);
			this->colors.AddColor(colors[i]);
			//this->indices.AddInt(indices[i]);
		}
	
		for(int i=0; i<indices.length; i++)
		{
			this->indices.AddInt(indices[i]);
		}

		defineGeometry();
	}
}

/**
 * Sets the solid color (all the vertices with the same color)
 * 
 * @param color solid color
 */
void Solid::setColor(const gxColor & color)
{
	for(int i=0; i < vertices.length; i++)
	{
		colors.SetColor(i, color);
	}
}

//-------------------------GEOMETRICAL_TRANSFORMATIONS-------------------------//

void Solid::ApplyTransform(mlTransformWithScale & t)
{
	for(int i=0;i<vertices.length;i++)
	{
		vertices[i] = t.TransformPoint(vertices[i]);
	}
	
	defineGeometry();
}

//-----------------------------------PRIVATES--------------------------------//
int g_nSolidLoadCount = 0;
		
/** Creates a geometry based on the indexes and vertices set for the solid */
void Solid::defineGeometry()
{
	// Need to send data to the gxModel
	// Maybe this should inherit from it! (Since Solid inherits from Shape3D)

	// Incidentally, do the normals get used by the boolean modeller? Of course they do!

	// Refresh the model.

	// Wipe the model
//@@	m_pModel->Clear();
	// Iterate all the triangles, and make the fuckers

	int nNumTriangles = indices.GetSize() / 3;

	for(int i = 0; i < nNumTriangles; i++)
	{
		int nIndex1 = *indices.GetInt(i * 3 + 0);
		int nIndex2 = *indices.GetInt(i * 3 + 1);
		int nIndex3 = *indices.GetInt(i * 3 + 2);

		mlVector3D vP1 = *vertices.GetVector(nIndex1);
		mlVector3D vP2 = *vertices.GetVector(nIndex2);
		mlVector3D vP3 = *vertices.GetVector(nIndex3);

		float fScale = 20.0f;
		mlVector3D vTranslation(50,20,50);

		vP1 *= fScale;
		vP2 *= fScale;
		vP3 *= fScale;

		vP1 += vTranslation;
		vP2 += vTranslation;
		vP3 += vTranslation;

		gxColor col1 = *colors.GetColor(nIndex1);
		gxColor col2 = *colors.GetColor(nIndex2);
		gxColor col3 = *colors.GetColor(nIndex3);

//@@		m_pModel->m_triangles.push_back(gxRenderingTriangle(col1, col2, col3, vP1, vP2, vP3));
	}
}

/**
 * Gets the solid mean
 * 
 * @return point representing the mean
 */
mlVector3D Solid::getMean()
{
	mlVector3D mean;
	for(int i=0;i<vertices.length;i++)
	{
		mean.x += vertices[i].x;
		mean.y += vertices[i].y;
		mean.z += vertices[i].z;
	}
	mean.x /= vertices.length;
	mean.y /= vertices.length;
	mean.z /= vertices.length;
	
	return mean;
}

#if 0	//@@ Not Used
// Loading function!!

/**
 * Loads a coordinates file, setting vertices and indices 
 * 
 * @param solidFile file used to create the solid
 * @param color solid color
 */
void Solid::loadCoordinateFile(const std::string & sFileName, const gxColor & colBase, int dRed, int dGreen, int dBlue)
{
	std::ifstream modelFile;

	modelFile.open(sFileName.c_str());

	g_nSolidLoadCount++;

	int nNumVertices = 0;
	modelFile >> nNumVertices;

	for(int i = 0; i < nNumVertices; i++)
	{
		// Read in a vector.
		int nVertexID = 0;

		mlVector3D vPosition;

		modelFile >> nVertexID;

		modelFile >> vPosition.x;
		modelFile >> vPosition.y;
		modelFile >> vPosition.z;

		vertices.AddVector(vPosition);
	}

	// Now load up the indices.

	int nNumTriangles = 0;
	modelFile >> nNumTriangles;

	for(int i = 0; i < nNumTriangles; i++)
	{
		int nTriangleID = 0;

		int nTriIndex1 = 0;
		int nTriIndex2 = 0;
		int nTriIndex3 = 0;

		modelFile >> nTriangleID;

		modelFile >> nTriIndex1;
		modelFile >> nTriIndex2;
		modelFile >> nTriIndex3;

		indices.AddInt(nTriIndex1);
		indices.AddInt(nTriIndex2);
		indices.AddInt(nTriIndex3);
	}

	modelFile.close();

	for(int i = 0; i < nNumVertices; i++)
	{
		gxColor col = colBase;

		if(dRed < 0) col.red -= rand() % (-1*dRed); else if(dRed > 0) col.red += rand() % dRed;
		if(dGreen < 0) col.green -= rand() % (-1*dGreen); else if(dGreen > 0) col.green += rand() % dGreen;
		if(dBlue < 0) col.blue -= rand() % (-1*dBlue); else if(dBlue > 0) col.blue += rand() % dBlue;

		colors.AddColor(col);
	}

	defineGeometry();
}
#endif