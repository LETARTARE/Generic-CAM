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
///////////////////////////////////////////////////////////////////////////////

#include "FileSTL.h"

#include <wx/file.h>
#include <wx/textfile.h>
#include <wx/log.h>
#include <wx/string.h>
#include <stdint.h>

// Verify, that float is 32 bit on this architecture.
#define __ASSERT(e) typedef char __ASSERT__[(e)?1:-1]
__ASSERT(sizeof(float) == sizeof(uint32_t));

FileSTL::FileSTL()
{
}

FileSTL::~FileSTL()
{
}

bool FileSTL::ReadFile(wxString fileName)
{
	error.Clear();
	this->filename = fileName;
	wxFFileInputStream inStream(fileName);

//	wxLogMessage(wxString::Format(_T("Opening File:") + fileName));

	if(!inStream.IsOk()){
		error += _T("STL File ") + fileName + _T(": File won't open.\n");
		return false;
	}

	return ReadStream(inStream);
}

bool FileSTL::ReadStream(wxInputStream & stream)
{
	// Find the header of the STL file:
	char header[6];
	header[5] = 0;

	if(stream.Read(header, 5).LastRead() != 5){
		error +=
		_T("STL File ") + filename + _T(": File contains no header.\n");
		return false;
	}
	if(strncmp(header, "solid", 5) == 0){

		// Make sure, that number are written with a dot and not a comma.
		setlocale(LC_ALL, "C");
		bool flag = ReadStreamAscii(stream, true);
		setlocale(LC_ALL, "");

		return flag;
	}else{
		return ReadStreamBinary(stream, true);
	}

}

bool FileSTL::ReadStreamBinary(wxInputStream & stream, bool hasRead5Byte)
{
	// NOTE: When changing to std::istream, check https://stackoverflow.com/questions/5605125/why-is-iostreameof-inside-a-loop-condition-i-e-while-stream-eof-cons

//	wxString temp;
	wxDataInputStream binaryStream(stream);

	unsigned char header[81];
	header[80] = 0;
	if(hasRead5Byte){
		binaryStream.Read8(header, 80 - 5);
	}else{
		binaryStream.Read8(header, 80);
	}
	if(stream.Eof()){
		error += _T(
				"STL File ") + filename + _T(": File contains no header.\n");
		return false;
	}
	// Set up a new geometry object.
	Geometry* g = new Geometry();
	g->name = filename;
	g->color = color;
	g->colorNewObjects = color;

	geometry.Clear(); // Clear the old geometry and
	geometry.Add(g); //insert the new one.
	size_t nGeometry = geometry.GetCount() - 1;
	wxASSERT(nGeometry == 0);

	// Binary STL File
	uint32_t nrOfTriangles = binaryStream.Read32();

	if(stream.Eof()){
		error += _T("STL File ") + filename + _T(": File to short!");
		return false;
	}

	uint32_t i;
	unsigned char j;
	float coord[12];

	wxASSERT(sizeof(float) == 4);

	uint16_t attribute;

	Triangle tri;
	for(i = 0; i < nrOfTriangles; i++){
		binaryStream.Read32((uint32_t *) &coord, 12);

		if(stream.Eof()){
			error += _T("STL File ") + filename + _T(": File to short!");
			return false;
		}
		attribute = binaryStream.Read16();

		if(stream.Eof()){
			error += _T( "STL File ") + filename + _T(": File to short!");
			return false;
		}

		Vector3 color;
		if(attribute & (1 << 15)){
			color.x = (float) ((attribute >> 0) & 31) / 31.0;
			color.y = (float) ((attribute >> 5) & 31) / 31.0;
			color.z = (float) ((attribute >> 10) & 31) / 31.0;
		}else{
			color = geometry[nGeometry].colorNewObjects;
		}

		for(j = 0; j < 3; j++){
			tri.p[j].x = coord[3 + j * 3];
			tri.p[j].y = coord[4 + j * 3];
			tri.p[j].z = coord[5 + j * 3];
			tri.n[j].x = coord[0];
			tri.n[j].y = coord[1];
			tri.n[j].z = coord[2];
			tri.c[j] = color;
		}

		// The normal vectors seem to be defect for some files.
		// if(false)... = Calculate normals
		// if(true)...  = Use normals from file
//		if(false){
//			geometry[nGeometry].AddTriangleWithNormals(tri.p[0], tri.p[1],
//					tri.p[2], tri.n[0], tri.n[0], tri.n[0]);
//		}else{
//			geometry[nGeometry].AddTriangle(tri.p[0], tri.p[1], tri.p[2]);
//		}

		geometry[nGeometry].AddTriangle(tri, false);

		//			if(i <= 1){
		//				wxLogMessage(wxString::Format(_T("n: %.1f %.1f %.1f"),
		//						tri->n.x, tri->n.y, tri->n.z));
		//				for(j = 0; j < 3; j++)
		//
		//					wxLogMessage(wxString::Format(_T("p: %.1f %.1f %.1f"),
		//							tri->p[j].x, tri->p[j].y, tri->p[j].z));
		//			}
	}
	return true;
}

void FileSTL::WriteStream(wxOutputStream& stream, Geometry & g)
{
	wxDataOutputStream binaryStream(stream);

	wxUint8 header[81] =
			"Generated by FileSTL::WriteStream                                               ";

	binaryStream.Write8(header, 80);
	binaryStream.Write32(wxUint32(g.triangles.GetCount()));
	for(size_t n = 0; n < g.triangles.GetCount(); n++){
		float coord[12];
		coord[0] = g.triangles[n].n[0].x;
		coord[1] = g.triangles[n].n[0].y;
		coord[2] = g.triangles[n].n[0].z;
		coord[3] = g.triangles[n].p[0].x;
		coord[4] = g.triangles[n].p[0].y;
		coord[5] = g.triangles[n].p[0].z;
		coord[6] = g.triangles[n].p[1].x;
		coord[7] = g.triangles[n].p[1].y;
		coord[8] = g.triangles[n].p[1].z;
		coord[9] = g.triangles[n].p[2].x;
		coord[10] = g.triangles[n].p[2].y;
		coord[11] = g.triangles[n].p[2].z;
		binaryStream.Write32((uint32_t*) coord, 12);
		uint16_t col = (1 << 15); // bit 15 set = color valid
		col |= ((int) floor(g.triangles[n].c[0].z * 32)) & 31;
		col |= (((int) floor(g.triangles[n].c[0].y * 32)) & 31) << 5;
		col |= (((int) floor(g.triangles[n].c[0].x * 32)) & 31) << 10;
		binaryStream.Write16(col);
	}
}

bool FileSTL::ReadStreamAscii(wxInputStream & stream, bool hasRead5Byte)
{

	wxTextInputStream textStream(stream);
	wxString word, line;

	if(!hasRead5Byte)
		word = textStream.ReadLine().Trim(false);
	else
		word = _T("solid ") + textStream.ReadLine().Trim(false);

	if(!word.StartsWith(_T("solid"))){
		error += _T( "STL Text File ") + filename + _T(": Incorrect file.");
		return false;
	}

	float normal[3];
	float coord[12];
	Triangle tri;
	unsigned int n;
	unsigned char j, m;
	wxString temp;

	geometry.Clear();

	while(word.StartsWith(_T("solid"), &temp)){
		temp = temp.Trim(false);
		// Set up a new geometry object.
		Geometry* g = new Geometry();
		if(temp.IsEmpty()){
			g->name = filename;
		}else{
			g->name = temp;
		}
		g->color = color;
		g->colorNewObjects = color;
		geometry.Add(g);
		n = geometry.GetCount() - 1;

		word = textStream.ReadWord().Trim(false);
		while(word.Cmp(_T("facet")) == 0){
			word = textStream.ReadWord().Trim(false);
			if(word.Cmp(_T("normal")) == 0){
				textStream >> normal[0] >> normal[1] >> normal[2];

			}else{
				normal[0] = normal[1] = normal[2] = 0.0;
			}
			word = textStream.ReadWord().Trim(false);
			if(word.Cmp(_T("outer")) != 0){
				error += _T(
						"STL Text File ") + filename + _T(": 'outer' missing.");
				return false;
			}
			word = textStream.ReadWord().Trim(false);
			if(word.Cmp(_T("loop")) != 0){
				error += _T(
						"STL Text File ") + filename + _T(": 'loop' missing.");
				return false;
			}
			for(m = 0; m < 3; m++){
				word = textStream.ReadWord().Trim(false);
				if(word.Cmp(_T("vertex")) != 0){
					error +=
					_T("STL Text File ") + filename + _T(": 'vertex' missing.");
					return false;
				}
				textStream >> coord[m * 3 + 0] >> coord[m * 3 + 1]
						>> coord[m * 3 + 2];
			}
			word = textStream.ReadWord().Trim(false);
			if(word.Cmp(_T("endloop")) != 0){
				error +=
				_T("STL Text File ") + filename + _T(": 'endloop' missing.");
				return false;
			}
			word = textStream.ReadWord().Trim(false);
			if(word.Cmp(_T("endfacet")) != 0){
				error +=
				_T("STL Text File ") + filename + _T(": 'endfacet' missing.");
				return false;
			}

			for(j = 0; j < 3; j++){
				tri.p[j].x = coord[0 + j * 3];
				tri.p[j].y = coord[1 + j * 3];
				tri.p[j].z = coord[2 + j * 3];
				tri.n[j].x = normal[0];
				tri.n[j].y = normal[1];
				tri.n[j].z = normal[2];
				tri.c[j] = geometry[n].colorNewObjects;
			}

			// The normal vectors seem to be defect for some files.
			// if(false)... = Calculate normals
			// if(true)...  = Use normals from file
			geometry[n].AddTriangle(tri, false);
//			if(false){
//				geometry[n].AddTriangleWithNormals(tri.p[0], tri.p[1], tri.p[2],
//						tri.n[0], tri.n[0], tri.n[0]);
//			}else{
//				geometry[n].AddTriangle(tri.p[0], tri.p[1], tri.p[2]);
//			}

			word = textStream.ReadWord().Trim(false);
		}
		if(word.Cmp(_T("endsolid")) != 0){
			error += _T(
					"STL Text File ") + filename + _T(": 'endsolid' missing.");
			return false;
		}
		word = textStream.ReadLine().Trim(false);
		if(!word.StartsWith(_T("solid"))) word = textStream.ReadLine().Trim(
				false);
	}

	return true;
}

