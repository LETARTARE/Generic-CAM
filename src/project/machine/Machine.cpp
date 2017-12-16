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

#include <wx/txtstrm.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <wx/textfile.h>
#include <wx/log.h>
#include <GL/gl.h>
#include <float.h>
#include <algorithm>

Machine::Machine()
{
	ClearComponents();
	Reset();
	initialized = false;
	microstepMode = distanceBased;
	microstepDistance = 0.001; // = 1mm;
	microstepPosition = 0;

	for(size_t n = 0; n < NR_IKAXIS; n++){
		IKaxis[n] = 0.0;
		IKaxisused[n] = false;
	}
	calculateIK = false;

//	CNCPosition x(0, 0, 0, 0.3, -0.4, 0.1);
//	AffineTransformMatrix m = x.GetMatrix();
//	m = m.Inverse();
//	m.TakeMatrixApart();
//	CNCPosition y(m);
//	AffineTransformMatrix n = y.GetMatrix();
//	n.TakeMatrixApart();
//	n.TakeMatrixApart();

}

Machine::Machine(const Machine &other)
{
	throw("'Machine::Copy constructor' is unimplemented!");
}

Machine& Machine::operator =(const Machine &other)
{
	if(&other == this) return *this;
	throw("'Machine::operator=' is unimplemented!");
	return *this;
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
			wxLogError(_T("Opening of the file failed!"));
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
		wxLogError(_("File format for machine descriptions not supported."));
		return false;
	}

	EvaluateDescription();
	Reset();
	return IsInitialized();
}

void Machine::ToXml(wxXmlNode* parentNode)
{
	wxXmlNode *temp, *temp2;
	wxXmlNode *nodeObject = NULL;

	// Find out, if object already exists in XML tree.
	temp = parentNode->GetChildren();
	while(temp != NULL && nodeObject == NULL){
		if(temp->GetName() == _T("machine")
				&& temp->GetPropVal(_T("name"), _T(""))
						== fileName.GetFullName()) nodeObject = temp;
		temp = temp->GetNext();
	}
	if(nodeObject == NULL){
		nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("machine"));
		nodeObject->AddProperty(_T("name"), fileName.GetFullName());
		parentNode->InsertChild(nodeObject, NULL);
	}

	// Remove the subelements, that will be updated
	temp = nodeObject->GetChildren();
	while(temp != NULL){
		temp2 = NULL;
		if(temp->GetName() == _T("filename")) temp2 = temp;
		if(temp->GetName() == _T("description")) temp2 = temp;
		temp = temp->GetNext();
		if(temp2 != NULL){
			nodeObject->RemoveChild(temp2);
			delete (temp2);
		}
	}

	temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("filename"));
	nodeObject->InsertChild(temp, NULL);
	temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
			fileName.GetFullPath());
	temp->InsertChild(temp2, NULL);

	temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("description"));
	nodeObject->InsertChild(temp, NULL);
	temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
			machineDescription);
	temp->InsertChild(temp2, NULL);

}

bool Machine::FromXml(wxXmlNode* node)
{
	//	objectName = node->GetPropVal(_T("name"), _T(""));
	if(node->GetName() != _T("machine")) return false;

	wxXmlNode *temp = node->GetChildren();
	while(temp != NULL){
		if(temp->GetName() == _T("filename")){
			fileName = temp->GetNodeContent();
		}
		if(temp->GetName() == _T("description")){
			machineDescription = temp->GetNodeContent();
		}
		temp = temp->GetNext();
	}
	return true;
}

void Machine::EvaluateDescription(void)
{
	wxLogMessage(_T("Machine::InsertMachineDescription"));
	evaluator.LinkToMachine(this);
	if(evaluator.EvaluateProgram()){

		// Initialize IK
		calculateIK = false;
		double A0[NR_IKAXIS];
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
			if(P.Distance(P0) > FLT_EPSILON){
				IKaxisused[n] = true;
				calculateIK = true;
			}
		}
		for(size_t n = 0; n < NR_IKAXIS; n++)
			IKaxis[n] = 0.0;
		toolLengthOffset = 0.0;
		currentpos = CNCPosition();
		evaluator.EvaluateAssembly();
		offset0 = CNCPosition(workpiecePosition.Inverse() * toolPosition);
		initialized = true;
	}else{
		initialized = false;
	}

	textOut = evaluator.GetOutput();
}

void Machine::Copy(double* res, double* A)
{
	for(size_t n = 0; n < NR_IKAXIS; n++)
		res[n] = A[n];
}

double Machine::GetE(void) const
{
	AffineTransformMatrix tpos = (currentpos + offset0).GetMatrix();
	tpos.TranslateLocal(0, 0, toolLengthOffset);
	AffineTransformMatrix cpos = workpiecePosition.Inverse() * toolPosition;

	// Scalar product of the normal vectors (0,0,1) for both matrices.
	const double normalaligned = tpos.a[8] * cpos.a[8] + tpos.a[9] * cpos.a[9]
			+ tpos.a[10] * cpos.a[10];

	Vector3 tc = tpos.GetCenter();
	Vector3 cc = cpos.GetCenter();

	// Keep the axes rather straight.
	double bend = 0.0;
	for(size_t n = 0; n < NR_IKAXIS; n++){
		if(IKaxisused[n]) bend += IKaxis[n] * IKaxis[n];
	}

	return (tc - cc).Abs() + 3 * fabs(normalaligned - 1.0) + sqrt(bend) / 1000;
//	return cpos.Distance(tpos);
}

void Machine::Assemble()
{
	if(!initialized) return;

	if(!calculateIK){
		evaluator.EvaluateAssembly();
		return;
	}

	// Nelder-Mead Solver
	// https://en.wikipedia.org/wiki/Nelder%E2%80%93Mead_method

	const double alpha = 1;
	const double gamma = 2;
	const double rho = 0.5;
	const double sigma = 0.5;

	const double Elimit = 0.01;
	const double eps = 0.5;

	size_t N = 0;
	double E[NR_IKAXIS + 1];
	double C[(NR_IKAXIS + 1) * NR_IKAXIS];
	for(size_t n = 0; n < (NR_IKAXIS + 1); n++){
		Copy(C + n * NR_IKAXIS, IKaxis);
		if(n < NR_IKAXIS){
			C[n * (1 + NR_IKAXIS)] += eps;
			if(IKaxisused[n]) N++;
		}
	}
	for(size_t n = 0; n < (NR_IKAXIS + 1); n++){
		if(IKaxisused[n]){
			Copy(IKaxis, C + n * NR_IKAXIS);
			evaluator.EvaluateAssembly();
			E[n] = GetE();
		}else{
			E[n] = FLT_MAX;
		}
	}
	for(size_t m = 0; m < 100; m++){

		// 1.) Sort
		bool flag = true;
		while(flag){
			flag = false;
			for(size_t n = 0; n < NR_IKAXIS; n++){
				if(E[n] > E[n + 1]){
					std::swap_ranges(C + n * NR_IKAXIS, C + (n + 1) * NR_IKAXIS,
							C + (n + 1) * NR_IKAXIS);
					std::swap(E[n], E[n + 1]);
					flag = true;
				}
			}
		}

		if(E[0] < Elimit) break;

		// 2.) Calculate centroid
		double cent[NR_IKAXIS];
		for(size_t n = 0; n < NR_IKAXIS; n++)
			cent[n] = 0;
		for(size_t n = 0; n < (NR_IKAXIS * N); n++)
			cent[n % NR_IKAXIS] += C[n];
		for(size_t n = 0; n < NR_IKAXIS; n++)
			cent[n] /= (double) N;

		// 3.) Reflection
		double refl[NR_IKAXIS];
		for(size_t n = 0; n < NR_IKAXIS; n++)
			refl[n] = cent[n] + alpha * (cent[n] - C[n + NR_IKAXIS * N]);
		Copy(IKaxis, refl);
		evaluator.EvaluateAssembly();
		double Erefl = GetE();
		if(E[0] <= Erefl && Erefl < E[N - 1]){
			Copy(C + NR_IKAXIS * N, refl);
			E[N] = Erefl;
			continue;
		}

		// 4.) Expansion
		if(Erefl < E[0]){
			double expa[NR_IKAXIS];
			for(size_t n = 0; n < NR_IKAXIS; n++)
				expa[n] = cent[n] + gamma * (refl[n] - cent[n]);
			Copy(IKaxis, expa);
			evaluator.EvaluateAssembly();
			double Eexpa = GetE();
			if(Eexpa < Erefl){
				Copy(C + NR_IKAXIS * N, expa);
				E[N] = Eexpa;
				continue;
			}else{
				Copy(C + NR_IKAXIS * N, refl);
				E[N] = Erefl;
				continue;
			}
		}

		// 5.) Contraction
		double cont[NR_IKAXIS];
		for(size_t n = 0; n < NR_IKAXIS; n++)
			cont[n] = cent[n] + rho * (C[n + NR_IKAXIS * N] - cent[n]);
		Copy(IKaxis, cont);
		evaluator.EvaluateAssembly();
		double Econt = GetE();
		if(Econt < E[N]){
			Copy(C + NR_IKAXIS * N, cont);
			E[N] = Econt;
			continue;
		}

		// 6.) Shrink
		for(size_t n = NR_IKAXIS; n < (NR_IKAXIS * (N + 1)); n++)
			C[n] = C[n % NR_IKAXIS] + sigma * (C[n] - C[n % NR_IKAXIS]);
		for(size_t n = 1; n < (NR_IKAXIS + 1); n++){
			Copy(IKaxis, C + n * NR_IKAXIS);
			evaluator.EvaluateAssembly();
			E[n] = GetE();
		}
	}
	Copy(IKaxis, C);
	evaluator.EvaluateAssembly();
}

bool Machine::IsInitialized(void) const
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

	::glPushMatrix();
	::glMultMatrixd(workpiecePosition.a);
	PaintCoordinateSystem(0.1);
//	AffineTransformMatrix temp = workpiecePosition.Inverse() * toolPosition;
//	::glMultMatrixd(temp.a);

	AffineTransformMatrix temp = (currentpos + offset0).GetMatrix();
	temp.TranslateLocal(0, 0, toolLengthOffset);
//	temp = temp.Inverse();
	::glMultMatrixd(temp.a);
	if(selectedToolSlot > 0 && selectedToolSlot <= tools.GetCount()){
		::glColor3f(0.7, 0.7, 0.7);
		tools[selectedToolSlot - 1].Paint();
	}else{
		PaintNullTool(0.05, 0.03);
	}
	::glPopMatrix();
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

void Machine::PaintCoordinateSystem(double diameter) const
{
	glBegin(GL_LINES);
	glNormal3f(1, 0, 0);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3d(diameter / 2.0, 0, 0);
	glNormal3f(0, 1, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3d(0, diameter / 2.0, 0);
	glNormal3f(0, 0, 1);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3d(0, 0, diameter / 2.0);
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
		wxLogMessage(_T("Inside Zip file."));
		return LoadGeometryIntoComponentFromZip(machinedirectory, filename,
				component, matrix);
	}

	// Case 1: Test if there is a zip file named like the lua file.
	wxFileName zipFile(machinedirectory);
	zipFile.SetExt(_T("zip"));
	if(zipFile.IsFileReadable()){
		wxLogMessage(_T("Zip file found."));
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
	wxLogMessage(zipFile.GetFullPath());
	if(zipFile.IsFileReadable()){
		wxLogMessage(_T("Extra-Zip file found."));
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
				wxLogMessage(_T("Geometries other than STL are not supported (yet)."));
			}
			break;
		}
	}
	return false;
}

void Machine::Reset()
{
	currentpos = CNCPosition();
	for(size_t i = 0; i < 10; i++)
		coordSystem[i] = CNCPosition();
	selectedCoordSystem = 1;
	selectedTool = 0;
	selectedToolSlot = 0;
	feedRate = 0.01; // Feed = 1 cm/s
	rapidMovement = false; // Move at feedrate
	spindleSpeed = 0.0; // Spindle stopped
	controlledpoint = CNCPosition();
	mistCoolant = false;
	floodCoolant = false;
	activeUnits = mms;
	selectedPlane = XY;
	toolLengthOffset = 0.0;
	codestate = GCodeBlock();
	microsteps.clear();
	for(size_t n = 0; n < NR_IKAXIS; n++)
		IKaxis[n] = 0.0;
	Assemble();
}

Vector3 Machine::GetCenter(void) const
{
	return workpiecePosition.GetCenter();
}

void Machine::TouchoffPoint(const CNCPosition &point)
{
	CNCPosition diff = point - coordSystem[1];
	codestate.X -= diff.X;
	codestate.Y -= diff.Y;
	codestate.Z -= diff.Z;
	coordSystem[1] = point;
}

void Machine::TouchoffHeight(const double height)
{
	AffineTransformMatrix temp;
	temp.TranslateLocal(0, 0, height);
	TouchoffPoint(CNCPosition(temp) - offset0);
}

bool Machine::InterpretGCode(GCodeBlock* block, bool generateMicroSteps)
{
	lastpos = currentpos;
	currentpos.dt = 0.0;
	block->t = currentpos.t;
	block->duration = 0.0;
	codestate.CopySelective(*block);

	if(codestate.F > 0) feedRate = codestate.F;

	// Change tool
	if(codestate.M[6] == 6){
		codestate.M[6] = -1;
		currentpos = coordSystem[0];
		Interpolate(&lastpos, &currentpos, generateMicroSteps);
		lastpos = currentpos;
		block->duration += currentpos.dt;
		currentpos.dt = 0.0;
		selectedTool = codestate.T;
		selectedToolSlot = 0;
		toolLengthOffset = 0.0;
		for(size_t n = 0; n < tools.GetCount(); n++){
			if(tools[n].slotNr == selectedTool){
				selectedToolSlot = n + 1;
				toolLengthOffset = tools[n].GetToolLength();
			}
		}
	}
	if(codestate.M[7] == 3) spindleSpeed = codestate.S;
	if(codestate.M[7] == 4) spindleSpeed = -codestate.S;
	if(codestate.M[7] == 5) spindleSpeed = 0;

	const bool machineCoordinates = (codestate.G[0] == 530);

	if(codestate.G[12] == 540) selectedCoordSystem = 1;
	if(codestate.G[12] == 550) selectedCoordSystem = 2;
	if(codestate.G[12] == 560) selectedCoordSystem = 3;
	if(codestate.G[12] == 570) selectedCoordSystem = 4;
	if(codestate.G[12] == 580) selectedCoordSystem = 5;
	if(codestate.G[12] == 590) selectedCoordSystem = 6;
	if(codestate.G[12] == 591) selectedCoordSystem = 7;
	if(codestate.G[12] == 592) selectedCoordSystem = 8;
	if(codestate.G[12] == 593) selectedCoordSystem = 9;

	const unsigned char c = (machineCoordinates)? 0 : selectedCoordSystem;

	currentpos.X = codestate.X + coordSystem[c].X;
	currentpos.Y = codestate.Y + coordSystem[c].Y;
	currentpos.Z = codestate.Z + coordSystem[c].Z;
	currentpos.A = codestate.A + coordSystem[c].A;
	currentpos.B = codestate.B + coordSystem[c].B;
	currentpos.C = codestate.C + coordSystem[c].C;
	currentpos.U = codestate.U + coordSystem[c].U;
	currentpos.V = codestate.V + coordSystem[c].V;
	currentpos.W = codestate.W + coordSystem[c].W;

	Interpolate(&lastpos, &currentpos, generateMicroSteps);
	block->duration += currentpos.dt;
	return block->duration > FLT_EPSILON;
}

bool Machine::Step(void)
{
	if((microstepPosition + 1) >= microsteps.size()) return false;
	microstepPosition++;
	controlledpoint = microsteps[microstepPosition];
	return true;
}

void Machine::Interpolate(CNCPosition *a, CNCPosition *b,
		bool generateMicroSteps)
{
	CNCPosition dp = *b - *a;
	const double L = dp.AbsXYZ();
	if(feedRate > 0.0){
		b->dt = L / feedRate;
	}else{
		b->dt = 0.0;
	}
	b->t = a->t + a->dt;
	if(!generateMicroSteps) return;
	if(L <= FLT_EPSILON) return;
	const double r = fmin(fmin(gridDelta.X, gridDelta.Y), gridDelta.Z);
	const size_t N = floor(L / r);
	if(N == 0) return;
	dp /= (double) N;
	assert(dp.AbsXYZ() > 0);
	CNCPosition p = *a + dp;
	for(size_t n = 2; n < N; n++){
		microsteps.push_back(p);
		p += dp;
	}
	microsteps.push_back(*b);
}
