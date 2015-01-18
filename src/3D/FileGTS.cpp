///////////////////////////////////////////////////////////////////////////////
// Name               : FileGTS.cpp
// Purpose            : Reads a GTS File
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.06.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////


#include "FileGTS.h"

#include <wx/file.h>
#include <wx/textfile.h>
#include <wx/log.h>
#include <wx/string.h>
#include <wx/tokenzr.h>

FileGTS::FileGTS()
{
}

FileGTS::~FileGTS()
{
}

bool FileGTS::ReadFile(wxString fileName)
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

	// Set up a new geometry object.
	Geometry* g = new Geometry();
	g->objectName = fileName;

	geometry.Clear(); // Clear the old geometry and
	geometry.Add(g); //insert the new one.
	size_t nGeometry = geometry.GetCount() - 1;
	wxASSERT(nGeometry==0);

	long nv;
	long ne;
	long nf;
	tokenizer.GetNextToken().ToLong(&nv);
	tokenizer.GetNextToken().ToLong(&ne);
	tokenizer.GetNextToken().ToLong(&nf);

	long i;
	double x, y, z;
	ArrayOfVector3 vectors;
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
		*vec = matrix.Transform(*vec);
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

	wxLogMessage(wxString::Format(_T("vectors.GetCount() = %lu"), vectors.GetCount()));

	unsigned long u[6];
	unsigned long t;
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


		// Sort the rotation of the triangles
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

		geometry[nGeometry].AddTriangle(vectors[u[0]], vectors[u[2]],
				vectors[u[4]]);


		//      unsigned char j;
		//		if(i <= 10){
		//			wxLogMessage(wxString::Format(_T("n: %.3f %.3f %.3f"), tri->n[0].x,
		//					tri->n[0].y, tri->n[0].z));
		//			for(j = 0; j < 3; j++)
		//				wxLogMessage(wxString::Format(_T("p: %.3f %.3f %.3f"),
		//						tri->p[j].x, tri->p[j].y, tri->p[j].z));
		//		}

	}



	file.Close();
	return true;
}
