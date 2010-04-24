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
#include <wx/tokenzr.h>

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfTriangles)
WX_DEFINE_OBJARRAY(ArrayOfVectors)

Triangle::Triangle()
{
}
Triangle::~Triangle()
{
}
void Triangle::Paint(void)
{
	::glNormal3f(n[0].x, n[0].y, n[0].z);
	unsigned char i;
	for(i = 0; i < 3; i++)
		::glVertex3f(p[i].x, p[i].y, p[i].z);
}
void Triangle::CalculateNormal()
{
	n[0] = (p[1] - p[0]) * (p[2] - p[1]);
	n[0].Normalize();
}

Geometry::Geometry()
{
}
Geometry::~Geometry()
{
}

void Geometry::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	unsigned long i;
	for(i = 0; i < triangles.Count(); i++){
		triangles[i].p[0] = matrix.Transform(triangles[i].p[0]);
		triangles[i].p[1] = matrix.Transform(triangles[i].p[1]);
		triangles[i].p[2] = matrix.Transform(triangles[i].p[2]);
		triangles[i].n[0] = matrix.Transform(triangles[i].n[0]);
	}
}

void Geometry::Paint(void) const
{
	unsigned long i;
	::glBegin(GL_TRIANGLES);
	for(i = 0; i < triangles.Count(); i++){
		triangles[i].Paint();
	}
	::glEnd();
}

void Geometry::AddTriangle(const AffineTransformMatrix &matrix,
		const Vector3 &a, const Vector3 &b, const Vector3 &c)
{
	Triangle* tri = new Triangle;
	tri->p[0] = matrix.Transform(a);
	tri->p[1] = matrix.Transform(b);
	tri->p[2] = matrix.Transform(c);
	tri->CalculateNormal();
	triangles.Add(tri);
}
void Geometry::AddQuad(const AffineTransformMatrix &matrix, const Vector3 &a,
		const Vector3 &b, const Vector3 &c, const Vector3 &d)
{
	Triangle* tri0 = new Triangle;
	Triangle* tri1 = new Triangle;
	tri0->p[0] = matrix.Transform(a);
	tri0->p[1] = matrix.Transform(b);
	tri0->p[2] = matrix.Transform(c);
	tri1->p[0] = tri0->p[2];
	tri1->p[1] = matrix.Transform(d);
	tri1->p[2] = tri0->p[0];
	tri0->CalculateNormal();
	tri1->n[0] = tri0->n[0];
	triangles.Add(tri0);
	triangles.Add(tri1);
}

bool Geometry::ReadSTL(wxString fileName)
{
	wxFile file;

	if(!file.Open(fileName)){
		wxLogError(_T("STL: Can't open ") + fileName + _T(" as binary!"));
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
			wxLogError(_T("STL: Can't open ") + fileName + _T(" as ascii!"));
			return false;
		}
		wxLogMessage(_T("STL text file found!"));


		//TODO: STL loading code missing...

		tfile.Close();
	}else{
		// Binary STL File
		wxLogMessage(_T("STL binary file found!"));

		uint32_t nrOfTriangles;

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
			tri->n[0].x = coord[0];
			tri->n[0].y = coord[1];
			tri->n[0].z = coord[2];
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

bool Geometry::ReadGTS(wxString fileName)
{
	wxTextFile file;

	if(!file.Open(fileName)){
		wxLogError(_T("GTS: Can't open ") + fileName + _T(" !"));
		return false;
	}

	wxString temp;
	wxStringTokenizer tokenizer;
	if(file.Eof()){
		wxLogError(_T("File is empty!"));
		return false;
	}
	temp = file.GetFirstLine();
	if(temp.IsEmpty()){
		wxLogError(_T("File is empty!"));
		return false;
	}
	tokenizer.SetString(temp);
	if(tokenizer.CountTokens() < 3){
		wxLogError(_T("File is not a valid GTS file!"));
		return false;
	}
	long nv;
	long ne;
	long nf;
	tokenizer.GetNextToken().ToLong(&nv);
	tokenizer.GetNextToken().ToLong(&ne);
	tokenizer.GetNextToken().ToLong(&nf);

	long i;
	double x, y, z;
	ArrayOfVectors vectors;
	Vector3* vec;
	Triangle* tri;

	for(i = 0; i < nv; i++){
		if(file.Eof()){
			wxLogError(_T("File is empty!"));
			return false;
		}
		temp = file.GetNextLine();
		temp.Replace(_T("."), _T(","));
		tokenizer.SetString(temp);
		if(tokenizer.CountTokens() < 3){
			wxLogError(
					_T("File is not a valid GTS file (too little vertices)!"));
			return false;
		}

		tokenizer.GetNextToken().ToDouble(&x);
		tokenizer.GetNextToken().ToDouble(&y);
		tokenizer.GetNextToken().ToDouble(&z);
		vec = new Vector3(x, y, z);
		//		vec->x = x;
		//		vec->y = y;
		//		vec->z = z;
		vectors.Add(vec);
	}

	wxArrayLong e1, e2;
	long u1, u2;

	for(i = 0; i < ne; i++){
		if(file.Eof()){
			wxLogError(_T("File is empty!"));
			return false;
		}
		temp = file.GetNextLine();
		tokenizer.SetString(temp);
		if(tokenizer.CountTokens() < 2){
			wxLogError(_T("File is not a valid GTS file (too little edges)!"));
			return false;
		}
		tokenizer.GetNextToken().ToLong(&u1);
		tokenizer.GetNextToken().ToLong(&u2);
		e1.Add(u1);
		e2.Add(u2);
	}

	unsigned long v1, v2, v3;

	wxLogMessage(wxString::Format(_T("vectors.Count() = %lu"), vectors.Count()));

	unsigned long u[6];
	unsigned long t;
	unsigned char j;
	for(i = 0; i < nf; i++){
		if(file.Eof()){
			wxLogError(_T("File is empty!"));
			return false;
		}
		temp = file.GetNextLine();
		tokenizer.SetString(temp);
		if(tokenizer.CountTokens() < 3){
			wxLogError(
					_T("File is not a valid GTS file (too little triangles)!"));
			return false;
		}
		tri = new Triangle;
		tokenizer.GetNextToken().ToULong(&v1);
		tokenizer.GetNextToken().ToULong(&v2);
		tokenizer.GetNextToken().ToULong(&v3);
		u[0] = e1[v1 - 1] - 1;
		u[1] = e2[v1 - 1] - 1;
		u[2] = e1[v2 - 1] - 1;
		u[3] = e2[v2 - 1] - 1;
		u[4] = e1[v3 - 1] - 1;
		u[5] = e2[v3 - 1] - 1;

		if(u[1] != u[2] && u[1] != u[3]){
			t = u[0];
			u[0] = u[1];
			u[1] = t;
		}
		if(u[2] != u[1]){
			t = u[2];
			u[2] = u[3];
			u[3] = t;
		}
		if(u[5] != u[0]){
			t = u[4];
			u[4] = u[5];
			u[5] = t;
		}

		tri->p[0] = vectors[u[0]];
		tri->p[1] = vectors[u[2]];
		tri->p[2] = vectors[u[4]];
		tri->CalculateNormal();
		triangles.Add(tri);

		if(i <= 10){
			wxLogMessage(wxString::Format(_T("n: %.3f %.3f %.3f"), tri->n[0].x,
					tri->n[0].y, tri->n[0].z));
			for(j = 0; j < 3; j++)
				wxLogMessage(wxString::Format(_T("p: %.3f %.3f %.3f"),
						tri->p[j].x, tri->p[j].y, tri->p[j].z));
		}

	}

	//http://gts.sourceforge.net/reference/gts-surfaces.html#GTS-SURFACE-WRITE

	file.Close();
	return true;
}
