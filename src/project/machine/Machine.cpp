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

Machine::Machine()
{
	initialized = false;
	Reset();
	ClearComponents();
}

Machine::Machine(const Machine& other)
{
	throw("'Machine::Copy constructor' is unimplemented!");
}

Machine& Machine::operator =(const Machine& other)
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

bool Machine::Load(wxFileName const& fileName)
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
	//wxLogMessage(machineDescription);
	return IsInitialized();
}

void Machine::EvaluateDescription(void)
{
	wxLogMessage(_T("Machine::InsertMachineDescription"));
	evaluator.LinkToMachine(this);
	if(evaluator.EvaluateProgram())
		initialized = true;
	else
		initialized = false;
	Assemble();
	textOut = evaluator.GetOutput();
}

bool Machine::IsInitialized(void) const
{
	return initialized;
}

void Machine::Assemble()
{
	if(initialized) evaluator.EvaluateAssembly();
}

void Machine::Paint(void) const
{
	for(std::list <MachineComponent>::const_iterator i = components.begin();
			i != components.end(); ++i)
		i->Paint();
	if(toolSlot > 0 && toolSlot <= tools.GetCount()){
		::glPushMatrix();
		::glMultMatrixd(toolPosition.a);
		::glColor3f(0.7, 0.7, 0.7);
		tools[toolSlot - 1].Paint();
		::glPopMatrix();
	}
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
				wxLogMessage(
						_T(
								"Geometries other than STL are not supported (yet)."));
			}
			break;
		}
	}
	return false;
}

Vector3 Machine::GetCenter(void) const
{
	return workpiecePosition.GetCenter();
}

void Machine::DryRunToolPath(ToolPath* tp)
{
	double F = 1e-3;
	double t = 0;
	uint_fast8_t actc = 1;
	uint_fast8_t mode = 1;
	MachinePosition pos;
	MachinePosition old;
	MachinePosition off[10];
	for(size_t i = 0; i < tp->positions.GetCount(); i++){
		double dt = 0.0;
		old = pos;
		if(tp->positions[i].F > -FLT_EPSILON) F = tp->positions[i].F;
		if(tp->positions[i].G[0] == 40) dt += tp->positions[i].P;
		const bool machineCoordinates = (tp->positions[i].G[0] == 530);
		if(tp->positions[i].G[12] == 540) actc = 1;
		if(tp->positions[i].G[12] == 550) actc = 2;
		if(tp->positions[i].G[12] == 560) actc = 3;
		if(tp->positions[i].G[12] == 570) actc = 4;
		if(tp->positions[i].G[12] == 580) actc = 5;
		if(tp->positions[i].G[12] == 590) actc = 6;
		if(tp->positions[i].G[12] == 591) actc = 7;
		if(tp->positions[i].G[12] == 592) actc = 8;
		if(tp->positions[i].G[12] == 593) actc = 9;
		if(tp->positions[i].G[1] == 0) mode = 0;
		if(tp->positions[i].G[1] == 10) mode = 1;
		if(tp->positions[i].G[1] == 20) mode = 2;
		if(tp->positions[i].G[1] == 30) mode = 3;
		if(tp->positions[i].XFlag) pos.X = tp->positions[i].X;
		if(tp->positions[i].YFlag) pos.Y = tp->positions[i].Y;
		if(tp->positions[i].ZFlag) pos.Z = tp->positions[i].Z;
		if(tp->positions[i].AFlag) pos.A = tp->positions[i].A;
		if(tp->positions[i].BFlag) pos.B = tp->positions[i].B;
		if(tp->positions[i].CFlag) pos.C = tp->positions[i].C;
		if(tp->positions[i].UFlag) pos.U = tp->positions[i].U;
		if(tp->positions[i].VFlag) pos.V = tp->positions[i].V;
		if(tp->positions[i].WFlag) pos.W = tp->positions[i].W;
		if(!machineCoordinates){
			pos += off[actc];
		}
		tp->positions[i].length = sqrt(
				(pos.X - old.X) * (pos.X - old.X)
						+ (pos.Y - old.Y) * (pos.Y - old.Y)
						+ (pos.Z - old.Z) * (pos.Z - old.Z));
		switch(mode){
		case 0:
			dt += tp->positions[i].length / F;
			break;
		case 1:
			dt += tp->positions[i].length / F;
			break;
		default:
			break;
		}
		tp->positions[i].duration = dt;
		tp->positions[i].tStart = t;
		t += dt;
	}
}

void Machine::Reset()
{
	position = MachinePosition();
	activeCoordinateSystem = 1;
	activeTool = 0;
	feed = 0.01; // Feed = 1 cm/s
	movement = feedrate; // Move at feedrate
	spindle = 0.0; // Spindle stopped
	current = GCodeBlock();
	Assemble();
	SetTouchoffHeight();
}

void Machine::SetTouchoffHeight(double height)
{
//	workpiecePosition.TakeMatrixApart();
	Vector3 wpOrigin = workpiecePosition.GetCenter() - toolPosition.GetCenter();
	origin[1].X = wpOrigin.x;
	origin[1].Y = wpOrigin.y;
	origin[1].Z = wpOrigin.z + height;
}

void Machine::ProcessGCode(const GCodeBlock& block, const double pos)
{
	InterpolatePosition(DBL_MAX);
	base = position;
	current.CopySelective(block);
	if(current.F > 0) feed = current.F;

	// Change tool
	if(current.M[6] == 6){
		current.M[6] = -1;
		activeTool = current.T;
		toolSlot = 0;
		toolLength = 0.0;
		for(size_t n = 0; n < tools.GetCount(); n++){
			if(tools[n].slotNr == activeTool){
				toolSlot = n + 1;
				toolLength = tools[n].GetPositiveLength();
			}
		}
	}
	if(current.M[7] == 3) spindle = current.S;
	if(current.M[7] == 4) spindle = -current.S;
	if(current.M[7] == 5) spindle = 0;
	const bool machineCoordinates = (current.G[0] == 530);
	if(current.G[12] == 540) activeCoordinateSystem = 1;
	if(current.G[12] == 550) activeCoordinateSystem = 2;
	if(current.G[12] == 560) activeCoordinateSystem = 3;
	if(current.G[12] == 570) activeCoordinateSystem = 4;
	if(current.G[12] == 580) activeCoordinateSystem = 5;
	if(current.G[12] == 590) activeCoordinateSystem = 6;
	if(current.G[12] == 591) activeCoordinateSystem = 7;
	if(current.G[12] == 592) activeCoordinateSystem = 8;
	if(current.G[12] == 593) activeCoordinateSystem = 9;

	InterpolatePosition(DBL_MAX);
}

void Machine::Step(const double pos)
{
}

void Machine::InterpolatePosition(double t)
{
	const unsigned char c = (current.G[0] == 530)? 0 : activeCoordinateSystem;
	if(t >= (current.tStart + current.duration - FLT_EPSILON)){
		if(current.XFlag) position.X = current.X + origin[c].X;
		if(current.YFlag) position.Y = current.Y + origin[c].Y;
		if(current.ZFlag) position.Z = current.Z + origin[c].Z + toolLength; // TODO: Move into coordinate system setup.
		if(current.AFlag) position.A = current.A + origin[c].A;
		if(current.BFlag) position.B = current.B + origin[c].B;
		if(current.CFlag) position.C = current.C + origin[c].C;
		if(current.UFlag) position.U = current.U + origin[c].U;
		if(current.VFlag) position.V = current.V + origin[c].V;
		if(current.WFlag) position.W = current.W + origin[c].W;
		return;
	}
	if(t < (current.tStart + FLT_EPSILON)){
		position.X = base.X;
		position.Y = base.Y;
		position.Z = base.Z;
		position.A = base.A;
		position.B = base.B;
		position.C = base.C;
		position.U = base.U;
		position.V = base.V;
		position.W = base.W;
		return;
	}
	const double fn = fmin(fmax((t - current.tStart) / current.duration, 0.0),
			1.0);
	const double fo = 1.0 - fn;
	position.X = base.X * fo;
	position.Y = base.Y * fo;
	position.Z = base.Z * fo;
	position.A = base.A * fo;
	position.B = base.B * fo;
	position.C = base.C * fo;
	position.U = base.U * fo;
	position.V = base.V * fo;
	position.W = base.W * fo;
	if(current.XFlag) position.X += (current.X + origin[c].X) * fn;
	if(current.YFlag) position.Y += (current.Y + origin[c].Y) * fn;
	if(current.ZFlag) position.Z += (current.Z + origin[c].Z + toolLength) * fn;
	if(current.AFlag) position.A += (current.A + origin[c].A) * fn;
	if(current.BFlag) position.B += (current.B + origin[c].B) * fn;
	if(current.CFlag) position.C += (current.C + origin[c].C) * fn;
	if(current.UFlag) position.U += (current.U + origin[c].U) * fn;
	if(current.VFlag) position.V += (current.V + origin[c].V) * fn;
	if(current.WFlag) position.W += (current.W + origin[c].W) * fn;
}
