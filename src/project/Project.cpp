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
#include "generator/ToolpathGeneratorThread.h"

#include "../3D/FileSTL.h"

#include <wx/zipstrm.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>

#include <GL/gl.h>
#include <math.h>

Project::Project()
{
	Clear();
}

Project::~Project()
{
}

void Project::Clear(void)
{
	name = _("Untitled");

//	processToolpath = false;
//	interruptProcessing = false;

	objects.Clear();
	workpieces.Clear();
	run.Clear();

//	displayType = displayObjects;
//
//	displayGeometry = true;
//	displayBoundingBox = false;
//	displayMachine = false;
//	displayStock = false;
//	displayTargets = false;
//	displayToolpath = false;
//	displayOutLines = false;

//	FlipDrillPattern temp;
//	temp.name = _T("Testpattern 1");
//	pattern.Add(temp);
}

//bool Project::GenerateToolpaths(void)
//{
//
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
//	for(size_t workpieceNr = 0; workpieceNr < workpieces.GetCount();
//			workpieceNr++){
//		if(workpieces[workpieceNr].hasRunningGenerator) continue;
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
//
//}

bool Project::Save(wxFileName fileName)
{
	if(!fileName.IsOk()) return false;

	wxFFileOutputStream out(fileName.GetFullPath());
	wxZipOutputStream zip(out);
	wxTextOutputStream txt(zip);

	zip.PutNextEntry(_T("project.txt"));
	txt << _T("Name:") << endl;
	txt << this->name << endl;

	txt << wxString::Format(_T("Objects: %u"), objects.GetCount()) << endl;
	for(int n = 0; n < objects.GetCount(); n++){
		txt << wxString::Format(_T("Object: %u"), n) << endl;
		objects[n].ToStream(txt, n);
	}

	txt << wxString::Format(_T("Workpieces: %u"), workpieces.GetCount())
			<< endl;
	for(int n = 0; n < workpieces.GetCount(); n++){
		txt << wxString::Format(_T("Workpiece: %u"), n) << endl;
		workpieces[n].ToStream(txt);
	}
	txt << wxString::Format(_T("Run: %u"), run.GetCount()) << endl;
	for(int n = 0; n < run.GetCount(); n++){
		txt << wxString::Format(_T("Run: %u"), n) << endl;
		run[n].ToStream(txt);
	}

	for(int n = 0; n < objects.GetCount(); n++){
		for(int m = 0; m < objects[n].geometries.GetCount(); m++){
			wxString tempName = wxString::Format(
					_T("object_%u_geometry_%u.stl"), n, m);
			zip.PutNextEntry(tempName);
			FileSTL::WriteStream(zip, objects[n].geometries[m]);
		}
	}

	return true;
}

bool Project::Load(wxFileName fileName)
{
	if(!fileName.IsOk()) return false;

	wxFFileInputStream in(fileName.GetFullPath());
	wxZipInputStream zip(in);
	wxTextInputStream txt(zip);

	Clear();

	in.SeekI(0, wxFromStart);
	wxZipEntry* entry;
	while((entry = zip.GetNextEntry()))
		if(entry->GetName().Cmp(_T("project.txt")) == 0) break;
	if(entry == NULL) return false;

	zip.OpenEntry(*entry);

	wxString temp;
	size_t N, n, m;
	temp = txt.ReadLine();
	if(temp.Cmp(_T("Name:")) != 0) return false;
	name = txt.ReadLine();
	temp = txt.ReadWord();
	if(temp.Cmp(_T("Objects:")) != 0) return false;
	N = txt.Read32();
	objects.Clear();
	Object object;
	for(n = 0; n < N; n++){
		temp = txt.ReadWord();
		if(temp.Cmp(_T("Object:")) != 0) return false;
		m = txt.Read32();
		if(m != n) return false;
		object.FromStream(txt);
		objects.Add(object);
	}

	temp = txt.ReadWord();
	if(temp.Cmp(_T("Workpieces:")) != 0) return false;
	N = txt.Read32();
	workpieces.Clear();
	Workpiece workpiece;
	for(n = 0; n < N; n++){
		temp = txt.ReadWord();
		if(temp.Cmp(_T("Workpiece:")) != 0) return false;
		m = txt.Read32();
		if(m != n) return false;
		workpiece.FromStream(txt);
		workpieces.Add(workpiece);
	}

	temp = txt.ReadWord();
	if(temp.Cmp(_T("Run:")) != 0) return false;
	N = txt.Read32();
	run.Clear();
	Run * tempRun;
	for(n = 0; n < N; n++){
		temp = txt.ReadWord();
		if(temp.Cmp(_T("Run:")) != 0) return false;
		m = txt.Read32();
		if(m != n) return false;
		tempRun = new Run();
		tempRun->FromStream(txt, n, this);
		run.Add(tempRun);
	}
	zip.CloseEntry();

	// Load objects
	//TODO: Rewind zip

	while((entry = zip.GetNextEntry())){
		temp = entry->GetName();
		if(!temp.StartsWith(wxT("object_"), &temp)) continue;
		long p;
		temp.BeforeFirst('_').ToLong(&p);
		n = p;
		temp = temp.AfterFirst('_');
		if(!temp.StartsWith(wxT("geometry_"), &temp)) continue;
		temp.BeforeFirst('.').ToLong(&p);
		m = p;
		temp = temp.AfterFirst('.');
		if(!temp.StartsWith(wxT("stl"))) continue;

		if(n < 0 || n >= objects.GetCount()) continue;
		if(m < 0 || m >= objects[n].geometries.GetCount()) continue;

		FileSTL stl;
		zip.OpenEntry(*entry);
		stl.ReadStream(zip);
		objects[n].geometries[m].triangles = stl.geometry[0].triangles;
		zip.CloseEntry();
	}

	for(n = 0; n < objects.GetCount(); n++)
		objects[n].Update();
	for(n = 0; n < workpieces.GetCount(); n++)
		workpieces[n].Update();

	return true;
}

void Project::Paint(void)
{

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

	size_t i;

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

//wxString Project::TollPathGenerateCurrent(void)
//{
//	// TODO: Const correctness for this function.
//	if(generator_workpieceNr >= workpieces.GetCount()) return _T("");
//	if(generator_runNr >= run.GetCount()) return _T("");
//	if(generator_workpieceNr >= run[generator_runNr].toolpaths.GetCount()) return _T(
//			"");
//	return (workpieces[generator_workpieceNr].name + _T(" - ")
//			+ run[generator_runNr].toolpaths[generator_toolpathNr].generator->GetName());
//}

void Project::LoadPattern(wxFileName filename)
{
}

void Project::Update(void)
{
	for(size_t i = 0; i < workpieces.GetCount(); i++){
		workpieces[i].parent = this;
		workpieces[i].Update();
	}
	for(size_t i = 0; i < run.GetCount(); i++){
		run[i].parent = this;
		run[i].Update();
	}
}
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

//wxTextFile f;
//		if(fileName.FileExists()){
//			f.Open(fileName.GetFullPath());
//			f.Clear();
//		}else{
//			f.Create(fileName.GetFullPath());
//		}
//		size_t n;
//		for(n = 0; n < project.run.GetCount(); n++)
//			project.run[n].WriteToFile(f);
//		f.Write();
//		f.Close();

