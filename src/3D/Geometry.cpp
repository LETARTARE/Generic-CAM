//============================================================================
// Name        : Geometry.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 28.02.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "Geometry.h"
#include <GL/gl.h>
#include <wx/file.h>
#include <wx/textfile.h>
#include <wx/log.h>

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfTriangles)

Triangle::Triangle()
{
}
Triangle::~Triangle()
{
}
void Triangle::Paint(void)
{
	::glNormal3f(n.x, n.y, n.z);
	unsigned char i;
	for(i = 0; i < 3; i++)
		::glVertex3f(p[i].x, p[i].y, p[i].z);
}
void Triangle::CalculateNormal()
{
	n = (p[1] - p[0]) * (p[2] - p[1]);
	n.Normalize();
}

Geometry::Geometry()
{
}
Geometry::~Geometry()
{
}
void Geometry::Paint(void)
{
	unsigned long i;
	::glBegin(GL_TRIANGLES);
	for(i = 0; i < triangles.Count(); i++){
		triangles[i].Paint();
	}
	::glEnd();
}

bool Geometry::ReadSTL(wxString fileName)
{
	wxFile file;

	if(!file.Open(fileName)){
		wxLogError(_T("Can't open ") + fileName + _T(" !"));
		return false;
	}

	// Find the header of th STL file:
	char header[81];
	wxString temp;

	if(file.Read(header, 80) != 80){
		wxLogError(_T("File to short!"));
		return false;
	}
	temp.From8BitData(header, 80);
	temp.Trim(false);

	if(temp.StartsWith(_T("solid"))){
		// Ascii STL File
		file.Close();
		wxTextFile tfile;
		if(!tfile.Open(fileName)){
			wxLogError(_T("Can't open ") + fileName + _T(" !"));
			return false;
		}
		wxLogMessage(_T("STL text file found!"));


		//TODO: STL loading code missing...

		tfile.Close();
	}else{
		// Binary STL File
		wxLogMessage(_T("STL binary file found!"));

		int32_t nrOfTriangles;

		if(file.Read(&nrOfTriangles, 4) != 4){
			wxLogError(_T("File to short!"));
			return false;
		}
		wxLogMessage(
				wxString::Format(_T("Nr of Triangles: %lu"), nrOfTriangles));

		uint32_t i;
		unsigned char j;
		float coord[12];
		uint16_t nrOfAttributeBytes;
		Triangle *tri;
		for(i = 0; i < nrOfTriangles; i++){
			if(file.Read(&coord, 12 * sizeof(float)) != 12 * sizeof(float)){
				wxLogError(_T("File to short!"));
				return false;
			}
			if(file.Read(&nrOfAttributeBytes, 2) != 2){
				wxLogError(_T("File to short!"));
				return false;
			}

			tri = new Triangle;
			tri->n.x = coord[0];
			tri->n.y = coord[1];
			tri->n.z = coord[2];
			for(j = 0; j < 3; j++){
				tri->p[j].x = coord[3 + j * 3];
				tri->p[j].y = coord[4 + j * 3];
				tri->p[j].z = coord[5 + j * 3];
			}
			tri->CalculateNormal();
			triangles.Add(tri);
//			if(i <= 1){
//				wxLogMessage(wxString::Format(_T("n: %.1f %.1f %.1f"),
//						tri->n.x, tri->n.y, tri->n.z));
//				for(j = 0; j < 3; j++)
//
//					wxLogMessage(wxString::Format(_T("p: %.1f %.1f %.1f"),
//							tri->p[j].x, tri->p[j].y, tri->p[j].z));
//			}
		}
		file.Close();
	}
	return true;
}
