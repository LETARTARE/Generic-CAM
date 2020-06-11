///////////////////////////////////////////////////////////////////////////////
// Name               : Machine.cpp
// Purpose            : CNC machine
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "Machine.h"

#include "../../math/NelderMeadOptimizer.h"

#include <wx/txtstrm.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <wx/textfile.h>
#include <wx/log.h>
#include <float.h>
#include <algorithm>

#include "../../3D/OpenGL.h"
#include "../../Config.h"

Machine::Machine()
{
	initialized = false;
	toolLength = 0.0;
	// 0 = Machine coordinate system, 1 = first work coordinate system
	selectedCoordSystem = 0;

	for(size_t n = 0; n < NR_IKAXIS; n++){
		IKaxis[n] = 0.0;
		IKaxisused[n] = false;
	}
	ClearComponents();
	MoveToGlobalZero();

//	CNCPosition x(0, 0, 0, 0.3, -0.4, 0.1);
//	AffineTransformMatrix m = x.GetMatrix();
//	m = m.Inverse();
//	m.TakeMatrixApart();
//	CNCPosition y(m);
//	AffineTransformMatrix n = y.GetMatrix();
//	n.TakeMatrixApart();
//	n.TakeMatrixApart();
}

Machine::~Machine()
{
}

void Machine::ClearComponents(void)
{
	componentWithMaterial = NULL;
	componentWithTool = NULL;
	components.clear();
	AddComponent(_T("Base"));
}

void Machine::MoveToGlobalZero()
{
	setposition = CNCPosition();
	reachedposition = CNCPosition();
	selectedCoordSystem = 0;
	for(size_t n = 0; n < NR_IKAXIS; n++)
		IKaxis[n] = 0.0;
	Assemble();
}

bool Machine::Load(wxFileName const &fileName)
{
	if(!fileName.IsOk()) return false;
	this->fileName = fileName;
	return ReLoad();
}

bool Machine::ReLoad(void)
{
	if(!fileName.IsFileReadable()) return false;

	bool flag = false;
	if(fileName.GetExt().CmpNoCase(_T("lua")) == 0
			|| fileName.GetExt().CmpNoCase(_T("txt")) == 0){
		flag = true;
		wxTextFile file(fileName.GetFullPath());
		if(!file.Open(wxConvLocal) && !file.Open(wxConvFile)){
			wxLogError
			(_T("Opening of the file failed!"));
			return false;
		}
		wxString str;
		machineDescription.Empty();
		for(str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine()){
			machineDescription += str + _T("\n");
		}
	}
	if(fileName.GetExt().CmpNoCase(_T("zip")) == 0){
//		wxLogMessage(fileName.GetFullPath());
		wxFFileInputStream in(fileName.GetFullPath());
		wxZipInputStream inzip(in);
		wxZipEntry* entry;
		while((entry = inzip.GetNextEntry())){
			wxFileName temp(entry->GetName());
			if(temp.GetExt().CmpNoCase(_T("lua")) == 0){
				inzip.OpenEntry(*entry);
				wxTextInputStream textin(inzip);
				wxString str;
				machineDescription.Empty();
				while(inzip.CanRead()){
					str = textin.ReadLine();
					machineDescription += str + _T("\n");
				}
				inzip.CloseEntry();
				flag = true;
				break;
			}
		}
	}

	if(!flag){
		wxLogError
		(_("File format for machine descriptions not supported."));
		return false;
	}
	EvaluateDescription();
	MoveToGlobalZero();
	return IsLoaded();
}

void Machine::EvaluateDescription(void)
{
	evaluator.LinkToMachine(this);
	if(machineDescription.IsEmpty()){
		if(initialized){
			initialized = false;
			ClearComponents();
			MoveToGlobalZero();
		}
		return;
	}
	if(evaluator.EvaluateProgram()){

		// Initialize IK
		AffineTransformMatrix P0;
		const double magicnumber = M_PI_4 / M_E;
		for(size_t n = 0; n < NR_IKAXIS; n++)
			IKaxis[n] = 0.0;
		evaluator.EvaluateAssembly();
		P0 = workpiecePosition.Inverse() * toolPosition;
		for(size_t n = 0; n < NR_IKAXIS; n++){
			for(size_t m = 0; m < NR_IKAXIS; m++)
				IKaxis[m] = (n == m)? magicnumber : 0.0;
			evaluator.EvaluateAssembly();
			AffineTransformMatrix P = workpiecePosition.Inverse()
					* toolPosition;
			if(P.Distance(P0) > FLT_EPSILON) IKaxisused[n] = true;
		}
		for(size_t n = 0; n < NR_IKAXIS; n++)
			IKaxis[n] = 0.0;

		evaluator.EvaluateAssembly();
		coordSystem[0] = workpiecePosition.Inverse() * toolPosition;
		initialized = true;
	}else{
		initialized = false;
	}
	AffineTransformMatrix tpos = toolPosition;
	tpos.TranslateLocal(0, 0, -toolLength);
	reachedposition = workpiecePosition.Inverse() * tpos;
	textOut = evaluator.GetOutput();
}

double Machine::GetError(void) const
{
	const double distance = reachedposition.Abs2(setposition);
	const double normalangle = fabs(1.0 - reachedposition.Dot(setposition));

	// Keep the axes rather straight.
	double bend = 0.0;
	for(size_t n = 0; n < NR_IKAXIS; n++){
		if(IKaxisused[n]) bend += IKaxis[n] * IKaxis[n];
	}

	return distance + 2.0 * normalangle + 1e-5 * sqrt(bend);
}

void Machine::Assemble()
{
	if(!initialized) return;

//	if(!calculateIK){
//		evaluator.EvaluateAssembly();
//		return;
//	}

	NelderMeadOptimizer optim;
	for(size_t n = 0; n < NR_IKAXIS; n++){
		if(IKaxisused[n]) optim.param.push_back(IKaxis[n]);
	}
	optim.reevalBest = true;
//	optim.keepSimplex = true;
	optim.simplexSpread = 0.1;
	optim.errorLimit = 1e-6;
	optim.evalLimit = 100;

	optim.Start();
	while(optim.IsRunning()){
		size_t m = 0;
		for(size_t n = 0; n < NR_IKAXIS; n++){
			if(IKaxisused[n]) IKaxis[n] = optim.param[m++];
		}
		evaluator.EvaluateAssembly();
		AffineTransformMatrix tpos = toolPosition;
		tpos.TranslateLocal(0, 0, -toolLength);
		reachedposition = workpiecePosition.Inverse() * tpos;
		optim.SetError(GetError());
	}
}

bool Machine::IsLoaded(void) const
{
	return initialized;
}

void Machine::Paint(void) const
{
	for(std::list <MachineComponent>::const_iterator i = components.begin();
			i != components.end(); ++i)
		i->Paint();

//	::glPushMatrix();
//	::glMultMatrixd(toolPosition.a);
//	PaintNullTool(0.10, 0.02);
//	::glPopMatrix();

	if(DEBUG){
		::glPushMatrix();
		workpiecePosition.GLMultMatrix();

//	AffineTransformMatrix temp = workpiecePosition.Inverse() * toolPosition;
//	::glMultMatrixd(temp.a);

		AffineTransformMatrix temp = setposition.GetMatrix();
		temp.Paint(0.1);
//	temp.TranslateLocal(0, 0, toolLength);
//	temp = temp.Inverse();
		temp.GLMultMatrix();
//	if(selectedToolSlot > 0 && selectedToolSlot <= tools.GetCount()){
//		::glColor3f(0.7, 0.7, 0.7);
//		tools[selectedToolSlot - 1].Paint();
//	}else{
		PaintNullTool(0.05, 0.03);
//	}
		::glPopMatrix();
	}
}

void Machine::PaintNullTool(double length, double diameter) const
{
	const double radius = diameter / 2.0;
	glBegin(GL_LINES);
	glColor3f(0.6, 0.6, 1.0);
	glNormal3f(0, 0, -1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, -length);
	glColor3f(1.0, 0.6, 0.6);
	glNormal3f(-1, 0, 0);
	glVertex3d(-radius, 0, 0);
	glNormal3f(1, 0, 0);
	glVertex3d(radius, 0, 0);
	glColor3f(0.6, 1.0, 0.6);
	glNormal3f(0, -1, 0);
	glVertex3d(0, -radius, 0);
	glNormal3f(0, 1, 0);
	glVertex3d(0, radius, 0);
	glEnd();
}

bool Machine::AddComponent(wxString const& nameOfComponent)
{
	for(std::list <MachineComponent>::iterator i = components.begin();
			i != components.end(); ++i){
		if(i->nameOfComponent.Cmp(nameOfComponent) == 0) return false;
	}
	MachineComponent temp(nameOfComponent);
	components.push_back(temp);
	return true;
}

bool Machine::PlaceComponent(wxString const& nameOfComponent,
		AffineTransformMatrix const& matrix)
{
	bool flag = false;
	for(std::list <MachineComponent>::iterator i = components.begin();
			i != components.end(); ++i){
		if(i->nameOfComponent.Cmp(nameOfComponent) == 0){
			flag = true;
			i->matrix.Set(matrix);

			// Sideeffect of placing the components:
			// The tool and the material matrices are set up.
			if(&(*i) == componentWithMaterial){
				workpiecePosition.Set(workpiecePositionRelativ);
				workpiecePosition = matrix * workpiecePosition;
			}
			if(&(*i) == componentWithTool){
				toolPosition.Set(toolPositionRelativ);
				toolPosition = matrix * toolPosition;
			}
		}
	}
	return flag;
}

bool Machine::LoadGeometryIntoComponent(const wxString& filename,
		MachineComponent* component, const AffineTransformMatrix& matrix)
{
	assert(component!=NULL);
	if(component == NULL) return false;
	wxFileName machinedirectory(this->fileName);
	machinedirectory.Normalize(
			wxPATH_NORM_DOTS | wxPATH_NORM_ENV_VARS | wxPATH_NORM_TILDE);

	wxFileName componentFile(filename);
	wxArrayString path = componentFile.GetDirs();

	// Case 0: The lua file is inside a zip, so is the rest of the data.
	if(machinedirectory.GetExt().CmpNoCase(_T("zip")) == 0){
		wxLogMessage
		(_T("Inside Zip file."));
		return LoadGeometryIntoComponentFromZip(machinedirectory, filename,
				component, matrix);
	}

	// Case 1: Test if there is a zip file named like the lua file.
	wxFileName zipFile(machinedirectory);
	zipFile.SetExt(_T("zip"));
	if(zipFile.IsFileReadable()){
		wxLogMessage
		(_T("Zip file found."));
		return LoadGeometryIntoComponentFromZip(zipFile, filename, component,
				matrix);
	}

	// Case 2: The componentfile point directly to a directory.
	componentFile = machinedirectory.GetPathWithSep()
			+ componentFile.GetFullPath();
	if(componentFile.IsFileReadable()){
		return component->InsertSTL(matrix, componentFile);
	}

	// Case 3: Zip file with the name of the first part of the componentname.
	if(path.GetCount() == 0) return false;
	zipFile.SetName(path[0]);
	zipFile.SetExt(_T("zip"));
	zipFile.SetPath(machinedirectory.GetPath());
	wxLogMessage
	(zipFile.GetFullPath());
	if(zipFile.IsFileReadable()){
		wxLogMessage
		(_T("Extra-Zip file found."));
		return LoadGeometryIntoComponentFromZip(zipFile, filename, component,
				matrix);
	}
//	wxLogMessage(_T("componentFile:") + componentFile.GetPath());
//	wxLogMessage(_T("machineDirectory:") + machinedirectory.GetPath());

	textOut += filename;
	textOut += _T("\nFile not found at all!\n");
	return false;
}

bool Machine::LoadGeometryIntoComponentFromZip(const wxFileName &zipFile,
		const wxString &filename, MachineComponent* component,
		const AffineTransformMatrix& matrix)
{
	assert(component!=NULL);
	if(component == NULL) return false;
	wxFileName componentFile = filename;
	wxFileName componentFile2 = componentFile;
	if(componentFile2.GetDirCount() > 0) componentFile2.RemoveDir(0);

	wxFFileInputStream in(zipFile.GetFullPath());
	wxZipInputStream inzip(in);
	wxZipEntry* entry;
	while((entry = inzip.GetNextEntry())){
		wxFileName temp(entry->GetName());
		if(temp == componentFile || temp == componentFile2){
			if(temp.GetExt().CmpNoCase(_T("stl")) == 0){
				inzip.OpenEntry(*entry);
				component->InsertSTL(matrix, inzip);
				inzip.CloseEntry();
				return true;
			}else{
				wxLogMessage
				(_T("Geometries other than STL are not supported (yet)."));
			}
			break;
		}
	}
	return false;
}

//bool Machine::InterpretGCode(GCodeBlock* block, bool generateMicroSteps)
//{
//	lastpos = currentpos;
//	currentpos.dt = 0.0;
//	block->t = currentpos.t;
//	block->duration = 0.0;
//	codestate.CopySelective(*block);
//
//	if(codestate.F > 0) feedRate = codestate.F;
//
//	// Change tool
//	if(codestate.M[6] == 6){
//		codestate.M[6] = -1;
//		currentpos = coordSystem[0];
//		Interpolate(&lastpos, &currentpos, generateMicroSteps);
//		lastpos = currentpos;
//		block->duration += currentpos.dt;
//		currentpos.dt = 0.0;
//		selectedTool = codestate.T;
//		selectedToolSlot = 0;
//		toolLengthOffset = 0.0;
//		for(size_t n = 0; n < tools.GetCount(); n++){
//			if(tools[n].slotNr == selectedTool){
//				selectedToolSlot = n + 1;
//				toolLengthOffset = tools[n].GetToolLength();
//			}
//		}
//	}
//	if(codestate.M[7] == 3) spindleSpeed = codestate.S;
//	if(codestate.M[7] == 4) spindleSpeed = -codestate.S;
//	if(codestate.M[7] == 5) spindleSpeed = 0;
//
//	const bool machineCoordinates = (codestate.G[0] == 530);
//
//	if(codestate.G[12] == 540) selectedCoordSystem = 1;
//	if(codestate.G[12] == 550) selectedCoordSystem = 2;
//	if(codestate.G[12] == 560) selectedCoordSystem = 3;
//	if(codestate.G[12] == 570) selectedCoordSystem = 4;
//	if(codestate.G[12] == 580) selectedCoordSystem = 5;
//	if(codestate.G[12] == 590) selectedCoordSystem = 6;
//	if(codestate.G[12] == 591) selectedCoordSystem = 7;
//	if(codestate.G[12] == 592) selectedCoordSystem = 8;
//	if(codestate.G[12] == 593) selectedCoordSystem = 9;
//
//	const unsigned char c = (machineCoordinates)? 0 : selectedCoordSystem;
//
//	currentpos.X = codestate.X + coordSystem[c].X;
//	currentpos.Y = codestate.Y + coordSystem[c].Y;
//	currentpos.Z = codestate.Z + coordSystem[c].Z;
//	currentpos.A = codestate.A + coordSystem[c].A;
//	currentpos.B = codestate.B + coordSystem[c].B;
//	currentpos.C = codestate.C + coordSystem[c].C;
//	currentpos.U = codestate.U + coordSystem[c].U;
//	currentpos.V = codestate.V + coordSystem[c].V;
//	currentpos.W = codestate.W + coordSystem[c].W;
//
//	Interpolate(&lastpos, &currentpos, generateMicroSteps);
//	block->duration += currentpos.dt;
//	return block->duration > FLT_EPSILON;
//}

void Machine::SetWorkCoordinateSystem(unsigned char index,
		const AffineTransformMatrix& coordsys)
{
}

void Machine::SetToolLength(double toolLength)
{
	this->toolLength = toolLength;
}

void Machine::SetPosition(const CNCPosition& position)
{
	setposition = position;
}

CNCPosition Machine::GetCurrentPosition(void) const
{
	return setposition;
}
