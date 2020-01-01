///////////////////////////////////////////////////////////////////////////////
// Name               : Project.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.06.2011
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

#include "Project.h"

#include "../3D/BooleanBox.h"

#include "../3D/FileSTL.h"
#include "../gui/IDs.h"
#include "../Config.h"

#include <wx/zipstrm.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>
#include <sstream>
#include <GL/gl.h>
#include <math.h>
#include <float.h>
#include <algorithm>

IMPLEMENT_DYNAMIC_CLASS(Project, wxDocument)

Project::Project() :
		wxDocument()
{
	minResolution = 0.5e-3; // = 0.5 mm
	maxCells = 1e5;

	SetTitle(_("Untitled"));
	maxObjectID = 0;
	maxRunID = 0;
	maxGeneratorID = 0;

	Tool temp;
	temp.guid = "#1";
	temp.BMC = "carbide";
	temp.GRADE = "Generic Mill";
	temp.type = Tool::flat_end_mill;
	temp.geometry.DC = 6e-3;
	temp.geometry.LCF = 40e-3;
	temp.geometry.LB = 60e-3;
	temp.unit = "mm";
	temp.description = "Cylindric endmill - 6 mm";
	temp.vendor = "Someplace in China";
	temp.postprocess.number = 1;
	tools.push_back(temp);

}

Project::~Project()
{
	printf("Project::Destructor\n");
}

bool Project::Has(const Selection& sel) const
{
	if(sel.IsType(Selection::Object)){
		std::set <size_t>::const_iterator itsel = sel.begin();
		std::map <size_t, Object>::const_iterator itobj = objects.begin();
		while(itsel != sel.end()){
			if(itobj == objects.end() || *itsel < itobj->first) return false;
			if(!(itobj->first < *itsel)) ++itsel;
			++itobj;
		}
		return true;
	}
	if(sel.IsType(Selection::Run)){
		std::set <size_t>::const_iterator itsel = sel.begin();
		std::map <size_t, Run>::const_iterator itrun = run.begin();
		while(itsel != sel.end()){
			if(itrun == run.end() || *itsel < itrun->first) return false;
			if(!(itrun->first < *itsel)) ++itsel;
			++itrun;
		}
		return true;
	}
	if(sel.IsType(Selection::Generator) && sel.IsBaseType(Selection::BaseRun)){
		size_t baseID = sel.GetBaseID();

		if(run.find(baseID) == run.end()) return false;

		const Run &temp = run.at(baseID);

		std::set <size_t>::const_iterator itsel = sel.begin();
		std::map <size_t, Generator*>::const_iterator itgenerator =
				temp.generators.begin();
		while(itsel != sel.end()){
			if(itgenerator == temp.generators.end()
					|| *itsel < itgenerator->first) return false;
			if(!(itgenerator->first < *itsel)) ++itsel;
			++itgenerator;
		}
		return true;
	}
	return false;
}

bool Project::Has(const Selection::Type type, const size_t ID) const
{
	if(type == Selection::Object && objects.find(ID) != objects.end()) return true;
	if(type == Selection::Run && run.find(ID) != run.end()) return true;
	return false;
}

size_t Project::GetMaxObjectID(void) const
{
	return maxObjectID;
}

size_t Project::GetMaxRunID(void) const
{
	return maxRunID;
}

size_t Project::GetToolCount(void) const
{
	return tools.size();
}

const std::vector <Tool> * Project::GetTools(void) const
{
	return &tools;
}

std::set <size_t> Project::GetAllObjectIDs(void) const
{
	std::set <size_t> temp;
	for(std::map <size_t, Object>::const_iterator it = objects.begin();
			it != objects.end(); ++it)
		temp.insert(it->first);
	return temp;
}

std::set <size_t> Project::GetAllRunIDs(void) const
{
	std::set <size_t> temp;
	for(std::map <size_t, Run>::const_iterator it = run.begin();
			it != run.end(); ++it)
		temp.insert(it->first);
	return temp;
}

std::set <size_t> Project::GetAllGeneratorIDs(size_t runID) const
{
	std::set <size_t> temp;
	if(run.find(runID) != run.end()){
		for(std::map <size_t, Generator*>::const_iterator it =
				run.at(runID).generators.begin();
				it != run.at(runID).generators.end(); ++it)
			temp.insert(it->first);
	}
	return temp;
}

const Object& Project::GetObject(size_t ID) const
{
	if(objects.find(ID) == objects.end()) throw(std::range_error(
			"Project::GetObject - Object not found."));
	return objects.at(ID); //TODO: Rewrite by [] lookup
}

const std::map <size_t, Object>* Project::GetObjects(void) const
{
	return &objects;
}
const Run& Project::GetRun(size_t ID) const
{
	if(run.find(ID) == run.end()) throw(std::range_error(
			"Project::GetRun - Run not found."));
	return run.at(ID); //TODO: Rewrite by [] lookup
}

const Generator * Project::GetGenerator(size_t runID, size_t ID)
{
	if(run.find(runID) == run.end()) throw(std::range_error(
			"Project::GetGenerator - Run not found."));
	if(run.at(runID).generators.find(ID) == run.at(runID).generators.end()) throw(std::range_error(
			"Project::GetGenerator - Generator not found."));
	return run.at(ID).generators.at(ID);
}

const Tool& Project::GetTool(size_t index) const
{
	if(index >= tools.size()) throw(std::range_error(
			"Project::GetTools - index out of range."));
	return tools.at(index); //TODO: Rewrite by [] lookup
}
size_t Project::GetMaxGeneratorID(void) const
{
	return maxGeneratorID;
}

BoundingBox Project::GetBBox(const Selection &selected) const
{
	BoundingBox temp;
	if(selected.IsType(Selection::Object)){
		std::set <size_t> set = selected.GetSet();
		for(std::set <size_t>::const_iterator it = set.begin(); it != set.end();
				++it){
			if(!this->Has(Selection::Object, *it)) continue;
			temp.Insert(objects.at(*it).bbox);
		}
	}
	return temp;
}

bool Project::GenerateToolpaths(void)
{
	Update();

//	const AffineTransformMatrix rotx0 = AffineTransformMatrix::Identity();
//	const AffineTransformMatrix rotx180 = AffineTransformMatrix::RotationXYZ(
//	M_PI, 0, 0);

	for(std::vector <Tool>::iterator it = tools.begin(); it != tools.end();
			++it)
		it->Update();

	for(std::map <size_t, Run>::iterator run = this->run.begin();
			run != this->run.end(); ++run){
		run->second.GenerateToolpaths();
	}

	return true;
//#if(_GENERICCAM_USEMULTITHREADING == 1)
//
//	// Prevent the toolpath generation from being started in more than
//	// one thread.
//	if(mtx_generator.TryLock() != wxMUTEX_NO_ERROR) return false;
//
//	// Wait for the last command to finish. (For these
//	// are the only other function locking the project.)
//	mtx_project.Lock();
//
//	PropagateChanges();
//

//	// Select and start the next generators to have a go
//	// The selection is done workpiece-wise, even if spread across multiple runs.
//	for(std::map<size_t, Run>::iterator run = this->run.begin();run!=this->run.end();++run){
////		if(workpieces[workpieceNr].hasRunningGenerator) continue;
//		for(size_t runNr = 0; runNr < run.GetCount(); runNr++){
//			if(run[runNr].workpieceNr != workpieceNr) continue;
//
//			// Find the first generator, that has not generated its toolpath.
//			for(size_t toolpathNr = 0;
//					toolpathNr < run[runNr].toolpaths.GetCount(); toolpathNr++){
//				if(run[runNr].toolpaths[toolpathNr].generator->toolpathGenerated) continue;
//
//				// Generate a detached thread. on exit it signals the workpiece to be free for
//				// other generators.
//				workpieces[workpieceNr].hasRunningGenerator = true;
//				wxThread * thread = new ToolpathGeneratorThread(this, runNr,
//						toolpathNr);
//				if(thread->Create() != wxTHREAD_NO_ERROR){
//					workpieces[workpieceNr].hasRunningGenerator = false;
//					wxLogError(
//							_(
//									"Could not create new thread for toolpath generation."));
//				} else{
//					thread->Run();
//				}
//				break;
//			}
//			if(workpieces[workpieceNr].hasRunningGenerator) break;
//		}
//	}
//
//	mtx_project.Unlock();
//
//	mtx_generator.Unlock();
//	return true;
//#else
//	return false;
//#endif

}

void Project::Update(void)
{
	for(std::map <size_t, Object>::iterator it = objects.begin();
			it != objects.end(); ++it)
		it->second.Update();

	for(std::map <size_t, Run>::iterator it = run.begin(); it != run.end();
			++it)
		it->second.Update(this);

	UpdateAllViews();
}

bool Project::DoSaveDocument(const wxString& file)
{
	return Save(wxFileName(file));
}

bool Project::DoOpenDocument(const wxString& file)
{
	return Load(wxFileName(file));
}

bool Project::Save(wxFileName fileName)
{
	if(!fileName.IsOk()) return false;

	setlocale(LC_ALL, "C");

	wxFFileOutputStream out(fileName.GetFullPath());
	wxZipOutputStream zip(out);
	wxTextOutputStream txt(zip);

	zip.PutNextEntry(_T("project.txt"));
	txt << _T("Name:") << endl;
	txt << this->GetTitle() << endl;

	txt << wxString::Format(_T("Objects: %zu"), objects.size()) << endl;

	for(std::map <size_t, Object>::const_iterator obj = objects.begin();
			obj != objects.end(); ++obj){
		txt << wxString::Format(_T("Object: %zu"), obj->first) << endl;
		obj->second.ToStream(txt, obj->first);
	}

	txt << wxString::Format(_T("Run: %zu"), run.size()) << endl;
	for(std::map <size_t, Run>::const_iterator it = run.begin();
			it != run.end(); ++it){
		txt << wxString::Format(_T("Run: %zu"), it->first) << endl;
		it->second.ToStream(txt);
	}

	for(std::map <size_t, Object>::const_iterator obj = objects.begin();
			obj != objects.end(); ++obj){

		wxString tempName = wxString::Format(_T("object_%zu.obj"), obj->first);
		zip.PutNextEntry(tempName);
		std::ostringstream out;
		out << obj->second.geometry;
		txt << out.str();
	}

	setlocale(LC_ALL, "");
	this->SetFilename(fileName.GetFullPath(), true);
	std::cout << "Project::Save(" << fileName.GetFullPath() << ") - saved.\n";
	return true;
}

bool Project::Load(wxFileName fileName)
{
	if(!fileName.IsOk()) return false;
	setlocale(LC_ALL, "C");
	wxFFileInputStream in(fileName.GetFullPath());

	if(!in.IsOk()){
		std::cout << "File is not OK: ";
		std::cout << fileName.GetFullPath().ToAscii();
		std::cout << "\n";
		return false;
	}

	wxZipInputStream zip(in);
	wxTextInputStream txt(zip);

	tools.clear();
	objects.clear();
	run.clear();

	in.SeekI(0, wxFromStart);
	wxZipEntry* entry;
	while((entry = zip.GetNextEntry()))
		if(entry->GetName().Cmp(_T("project.txt")) == 0) break;
	if(entry == NULL){
		setlocale(LC_ALL, "");
		return false;
	}

	zip.OpenEntry(*entry);

	wxString temp;
	temp = txt.ReadLine();
	if(temp.Cmp(_T("Name:")) != 0){
		setlocale(LC_ALL, "");
		return false;
	}
	SetTitle(txt.ReadLine());

	temp = txt.ReadWord();
	if(temp.Cmp(_T("Objects:")) != 0){
		setlocale(LC_ALL, "");
		return false;
	}
	const size_t N = txt.Read32();
	for(size_t n = 0; n < N; n++){
		temp = txt.ReadWord();
		if(temp.Cmp(_T("Object:")) != 0){
			setlocale(LC_ALL, "");
			return false;
		}
		size_t objID = txt.Read32();
		Object object;
		object.FromStream(txt);
		objects[objID] = object;
	}

	temp = txt.ReadWord();
	if(temp.Cmp(_T("Run:")) != 0){
		setlocale(LC_ALL, "");
		return false;
	}
	const size_t N3 = txt.Read32();
	run.clear();
	for(size_t n = 0; n < N3; n++){
		temp = txt.ReadWord();
		if(temp.Cmp(_T("Run:")) != 0){
			setlocale(LC_ALL, "");
			return false;
		}
		size_t runID = txt.Read32();
		Run tempRun;
		tempRun.FromStream(txt, runID, this);
		run[runID] = tempRun;
	}
	zip.CloseEntry();

	// Load objects
	//TODO: Rewind zip, because there may be object models before the main project file.

	while((entry = zip.GetNextEntry())){
		temp = entry->GetName();
		if(!temp.StartsWith(wxT("object_"), &temp)) continue;
		long p;
		temp.BeforeFirst('.').ToLong(&p);
		size_t objID = p;
		temp = temp.AfterFirst('.');
		if(!temp.StartsWith(wxT("obj"))) continue;
		if(objects.find(objID) == objects.end()) continue;

		zip.OpenEntry(*entry);
		size_t N = entry->GetSize();

		char* buffer = new char[N + 1];
		zip.Read(buffer, N);
		size_t L = zip.LastRead();
		assert(L <= N);
		std::istringstream in(std::string(buffer, L));
		Hull temphull;
		in >> temphull;
		objects[objID].geometry = temphull;
		objects[objID].geometry.CalcNormals();
		objects[objID].geometry.CalcGroups();
		objects[objID].geometry.ApplyTransformation();
		delete[] buffer;

//		try{
//		}
//		catch(const std::exception &ex){
//			std::cout << "Exception caught: " << ex.what() << "\n";
//		}
		zip.CloseEntry();
	}
	setlocale(LC_ALL, "");
	this->SetFilename(fileName.GetFullPath(), true);
	this->Update();
	return true;
}

//void Project::PropagateChanges(void)
//{
//	// Testing preconditions.
//	// Propagate modifcation flag from object to workpiece
//	for(size_t workpieceNr = 0; workpieceNr < workpieces.GetCount();
//			workpieceNr++){
//		for(size_t placementNr = 0;
//				placementNr < workpieces[workpieceNr].placements.GetCount();
//				placementNr++){
//			int objectNr =
//					workpieces[workpieceNr].placements[placementNr].objectNr;
//			if(objectNr >= 0){
//				if(objects[objectNr].modified) workpieces[workpieceNr].modified =
//						true;
//			}
//		}
//	}
//
//	// Propagate modification flag from workpiece to run to the generators
//	for(size_t runNr = 0; runNr < run.GetCount(); runNr++){
//		int workpieceNr = run[runNr].workpieceNr;
//		if(workpieceNr >= 0){
//			if(workpieces[workpieceNr].modified) run[runNr].modified = true;
//		}
//		if(run[runNr].modified){
//			for(size_t toolpathNr = 0;
//					toolpathNr < run[runNr].toolpaths.GetCount(); toolpathNr++){
//				run[runNr].toolpaths[toolpathNr].generator->toolpathGenerated =
//						false;
//			}
//		}
//	}
//
//}

//size_t Project::ToolpathToGenerate(void)
//{
//	size_t maxNr = 0;
//	for(size_t workpieceNr = 0; workpieceNr < workpieces.GetCount();
//			workpieceNr++){
//		if(workpieces[workpieceNr].hasRunningGenerator) continue;
//		for(size_t runNr = 0; runNr < run.GetCount(); runNr++){
//			if(run[runNr].workpieceNr != workpieceNr) continue;
//			maxNr += run[runNr].toolpaths.GetCount();
//		}
//	}
//
//	generator_workpieceNr = 0;
//	generator_runNr = 0;
//	generator_toolpathNr = 0;
//
//	return maxNr;
//}
//
//bool Project::ToolpathGenerate(void)
//{
//	if(generator_workpieceNr >= workpieces.GetCount()) return false;
//
//	bool flag = true;
//	if(flag && workpieces[generator_workpieceNr].hasRunningGenerator) flag =
//			false;
//
//	if(flag && run[generator_runNr].workpieceNr != generator_workpieceNr) flag =
//			false;
//
//	if(flag
//			&& run[generator_runNr].toolpaths[generator_toolpathNr].generator->toolpathGenerated) flag =
//			false;
//
//	if(flag){
//		run[generator_runNr].toolpaths[generator_toolpathNr].generator->GenerateToolpath();
//		workpieces[generator_workpieceNr].hasRunningGenerator = false;
//	}
//
//	generator_toolpathNr++;
//	if(generator_toolpathNr >= run[generator_runNr].toolpaths.GetCount()){
//		generator_toolpathNr = 0;
//		generator_runNr++;
//	}
//	if(generator_runNr >= run.GetCount()){
//		generator_runNr = 0;
//		generator_workpieceNr++;
//	}
//	if(generator_workpieceNr >= workpieces.GetCount()) return false;
//	return true;
//}

//wxString Project::ToolPathGenerateCurrent(void)
//{
//	// TODO: Const correctnessl for this function.
//	if(generator_workpieceNr >= workpieces.GetCount()) return _T("");
//	if(generator_runNr >= run.GetCount()) return _T("");
//	if(generator_workpieceNr >= run[generator_runNr].toolpaths.GetCount()) return _T(
//			"");
//	return (workpieces[generator_workpieceNr].name + _T(" - ")
//			+ run[generator_runNr].toolpaths[generator_toolpathNr].generator->GetName());
//}

bool Project::SaveToolpath(wxFileName fileName, int runNr)
{
//	if(runNr < 0 || runNr > run.GetCount()) return false;
//	return run[runNr].SaveToolpaths(fileName);
	return false;
}

// Experimental stuff:
//	BooleanBox x;
//	BooleanBox y(0.4, 0.4, 0.4);
//	y.matrix.TranslateGlobal(0.1, -0.1, 0.5);
//	x -= y;
//	y.matrix.TranslateGlobal(0.1, 0.1, 0.1);
//	x -= y;
//	BooleanBox z = x;
//	z.matrix.TranslateGlobal(0.3, 0.3, 0.3);
//	x -= z;
//	::glColor4f(0.75, 0.75, 0.0, 1);
//	x.Paint(true);
//	::glColor4f(0.75, 0.75, 0.75, 0.4);
//	x.Paint();
//	y.Paint();
//
//	size_t i;
//
//	switch(displayType){
//	case displayObjects:
//		glLoadName(1);
//		for(i = 0; i < objects.GetCount(); i++){
//			glPushName(i + 1);
//			objects[i].Paint();
//			glPopName();
//		}
//		break;
//
//	case displayWorkpieces:
//		glLoadName(2);
//		for(i = 0; i < workpieces.GetCount(); i++){
//			if(!workpieces[i].selected) continue;
//			glPushName(i);
//			workpieces[i].Paint(objects);
//			glPopName();
//		}
//		break;
//	case displayRun:
//		glLoadName(3);
//		for(i = 0; i < run.GetCount(); i++){
//			if(!run[i].selected) continue;
//
//			::glPushName(i);
//			run[i].Paint(objects, workpieces);
//			::glPopName();
//		}
//		break;
//	}
//	::glLoadName(0);

//void Project::PaintWorkpiece(void) const
//{
//	const int i = GetFirstSelectedWorkpiece();
//	if(i < 0) return;
//	Vector3 center = workpieces[i].GetCenter();
//	glPushMatrix();
//	glTranslatef(-center.x, -center.y, -center.z);
//	RenderCoordinateSystem();
//	glPushName(i + 1);
//	workpieces[i].Paint();
//	glPopName();
//	glPopMatrix();
//}
//
//void Project::PaintRun(void) const
//{
//	const int i = GetFirstSelectedRun();
//	if(i < 0) return;
//	Vector3 center = run[i].GetCenter();
//	glPushMatrix();
//	glTranslatef(-center.x, -center.y, -center.z);
//	glPushName(i + 1);
//	run[i].Paint();
//	glPopName();
//	glPopMatrix();
//}

//void Project::PaintDepthField(unsigned int runNr,
//		unsigned int objectReferenceNr)
//{
//}

//void Project::FlipRun(void)
//{
//	size_t n = run[activeRun].placements.GetCount();
//	if(n < 4) return;
//	size_t i, j, m, p;
//	Vector3 temp;
//	double dx, dy;
//	for(i = 1; i < n; i++){
//		m = run[activeRun].placements[i].outLine.elements.GetCount();
//
//		if(run[activeRun].placements[i].isKeepout){
//			for(j = 0; j < m; j++)
//				run[activeRun].placements[i].outLine.elements[j].y =
//						-run[activeRun].placements[i].outLine.elements[j].y;
//
//			temp = run[activeRun].placements[i].matrix.GetCenter();
//			run[activeRun].placements[i].matrix.TranslateGlobal(0.0,
//					(middleY - temp.y) * 2, 0.0);
//
//		}else{
//			p = run[activeRun].placements[i].targetNumber;
//			dx = targets[p].GetSizeX() / 2;
//			dy = targets[p].GetSizeY() / 2;
//
//			for(j = 0; j < m; j++)
//				run[activeRun].placements[i].outLine.elements[j].y = dy * 2
//						- run[activeRun].placements[i].outLine.elements[j].y;
//
//			run[activeRun].placements[i].matrix.TranslateLocal(+dx, +dy, 0.0);
//
//			temp = run[activeRun].placements[i].matrix.GetCenter();
//			double alpha = atan2(run[activeRun].placements[i].matrix.a[1],
//					run[activeRun].placements[i].matrix.a[0]);
//
//			AffineTransformMatrix tr;
//			tr = AffineTransformMatrix::RotateXYZ(0.0, 0.0, -2 * alpha);
//			run[activeRun].placements[i].matrix =
//					run[activeRun].placements[i].matrix * tr;
//
//			run[activeRun].placements[i].matrix.TranslateGlobal(0.0,
//					2 * (middleY - temp.y), 0.0);
//
//			run[activeRun].placements[i].matrix.TranslateLocal(-dx, -dy, 0.0);
//
//		}
//
//	}
//	for(i = 0; i < targets.GetCount(); i++){
//		targets[i].FlipX();
//		targets[i].toolpathFlipped = targets[i].toolpath;
//		targets[i].toolpath.Clear();
//		targets[i].refresh = true;
//	}
//}

