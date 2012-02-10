///////////////////////////////////////////////////////////////////////////////
// Name               : FileSTL.cpp
// Purpose            : Reads a STL File
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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#include "FileSTL.h"

#include <wx/file.h>
#include <wx/textfile.h>
#include <wx/log.h>
#include <wx/string.h>
#include <stdint.h>

FileSTL::FileSTL()
{
}

FileSTL::~FileSTL()
{
}

bool FileSTL::ReadFile(wxString fileName)
{
	wxFile file;

	wxLogMessage(wxString::Format(_T("Opening File:") + fileName));

	if(!file.Open(fileName)){
		wxLogError(_T("STL: Can't open ") + fileName + _T("!"));
		return false;
	}

	// Find the header of the STL file:
	char header[81];
	wxString temp;

	if(file.Read(header, 80) != 80){
		wxLogError(_T("File to short!"));
		return false;
	}
	temp.From8BitData(header, 80);
	temp.Trim(false);


	// Set up a new geometry object.
	Geometry* g = new Geometry();
	g->objectName = fileName;

	geometry.Clear(); // Clear the old geometry and
	geometry.Add(g); //insert the new one.
	size_t nGeometry = geometry.GetCount() - 1;
	wxASSERT(nGeometry==0);

	if(temp.StartsWith(_T("solid"))){
		// Ascii STL File
		file.Close();
		wxTextFile tfile;
		if(!tfile.Open(fileName)){
			wxLogError(_T("STL: Can't open ") + fileName + _T(" as ascii text file!"));
			return false;
		}
		wxLogMessage(_T("STL text file found!"));


		//TODO: STL loading code for text files missing...

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

		wxASSERT(sizeof(float)==4);

		uint16_t nrOfAttributeBytes;

		Triangle tri;
		for(i = 0; i < nrOfTriangles; i++){
			if(file.Read(&coord, 12 * sizeof(float)) != 12 * sizeof(float)){
				wxLogError(_T("File to short!"));
				return false;
			}
			if(file.Read(&nrOfAttributeBytes, 2) != 2){
				wxLogError(_T("File to short!"));
				return false;
			}

			tri.n[0].x = coord[0];
			tri.n[0].y = coord[1];
			tri.n[0].z = coord[2];
			for(j = 0; j < 3; j++){
				tri.p[j].x = coord[3 + j * 3];
				tri.p[j].y = coord[4 + j * 3];
				tri.p[j].z = coord[5 + j * 3];
			}


			// The normal vectors seem to be defect for some files.
			// if(false)... = Calculate normals
			// if(true)...  = Use normals from file
			if(false){
				geometry[nGeometry].AddTriangleWithNormals(tri.p[0], tri.p[1],
						tri.p[2], tri.n[0], tri.n[0], tri.n[0]);
			}else{
				geometry[nGeometry].AddTriangle(tri.p[0], tri.p[1], tri.p[2]);
			}


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
