///////////////////////////////////////////////////////////////////////////////
// Name               : Project.cpp
// Purpose            :
// Thread Safe        : Yes
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
#include "../Config.h"
#include "../3D/BooleanBox.h"
#include "../generator/ToolpathGeneratorThread.h"

#include <GL/gl.h>
#include <math.h>

//TODO: Rewrite the XML load/store to LUA script store/load.

Project::Project()
{
	doc.SetFileEncoding(_T("UTF-8"));
	//doc.SetVersion(_T(_GENERICCAM_VERSION));
	doc.SetVersion(_T("1.0"));

	Clear();
}

Project::~Project()
{
}

void Project::Clear(void)
{
	name = _("Untitled");

	processToolpath = false;
	interruptProcessing = false;

	run.Empty();
	workpieces.Empty();
	objects.Empty();

	displayType = displayObjects;

	displayGeometry = true;
	displayBoundingBox = false;
	displayMachine = false;
	displayStock = false;
	displayTargets = false;
	displayToolpath = false;
	displayOutLines = false;

	FlipDrillPattern temp;
	temp.name = _T("Testpattern 1");
	pattern.Add(temp);
}

bool Project::GenerateToolpaths(void)
{
	// Prevent the toolpath generation from being started in more than
	// one thread.
	if(mtx_generator.TryLock() != wxMUTEX_NO_ERROR) return false;

	// Wait for the last command to finish. (For these
	// are the only other function locking the project.)
	mtx_project.Lock();

	PropagateChanges();

	// Select and start the next generators to have a go
	// The selection is done workpiece-wise, even if spread across multiple runs.
	for(size_t workpieceNr = 0; workpieceNr < workpieces.GetCount();
			workpieceNr++){
		if(workpieces[workpieceNr].hasRunningGenerator) continue;
		for(size_t runNr = 0; runNr < run.GetCount(); runNr++){
			if(run[runNr].workpieceNr != workpieceNr) continue;

			// Find the first generator, that has not generated its toolpath.
			for(size_t toolpathNr = 0;
					toolpathNr < run[runNr].toolpaths.GetCount(); toolpathNr++){
				if(run[runNr].toolpaths[toolpathNr].generator->toolpathGenerated) continue;

				// Generate a detached thread. on exit it signals the workpiece to be free for
				// other generators.
				workpieces[workpieceNr].hasRunningGenerator = true;
				wxThread * thread = new ToolpathGeneratorThread(this, runNr,
						toolpathNr);
				if(thread->Create() != wxTHREAD_NO_ERROR){
					workpieces[workpieceNr].hasRunningGenerator = false;
					wxLogError(
							_(
									"Could not create new thread for toolpath generation."));
				}else{
					thread->Run();
				}
				break;
			}
			if(workpieces[workpieceNr].hasRunningGenerator) break;
		}
	}

	mtx_project.Unlock();

	mtx_generator.Unlock();
	return true;
}

// Recursive tree deletion.
void Project::XMLRemoveAllChildren(wxXmlNode* node)
{
	wxXmlNode *temp, *temp2;
	temp = node->GetChildren();
	while(temp != NULL){
		XMLRemoveAllChildren(temp);
		temp2 = temp;
		temp = temp->GetNext();
		node->RemoveChild(temp2);
		delete (temp2);
	}
}

bool Project::Save(wxFileName fileName)
{

	if(!fileName.IsOk()) return false;

	wxXmlNode* root = doc.GetRoot();
	if(root == NULL){
		root = new wxXmlNode(wxXML_ELEMENT_NODE, _T("GenericCAMProjectFile"));
		doc.SetRoot(root);
	}

	wxXmlNode *nodeObject = NULL;
	wxXmlNode *nodeMachine = NULL;
	wxXmlNode *nodeTool = NULL;
	wxXmlNode *nodeTarget = NULL;
	wxXmlNode *nodeRun = NULL;

	wxXmlNode *temp;

	temp = root->GetChildren();

	// Check if there are already all necessary nodes in the document.
	while(temp != NULL){
		if(temp->GetName() == _T("Objects")) nodeObject = temp;
		if(temp->GetName() == _T("Machine")) nodeMachine = temp;
		if(temp->GetName() == _T("Tools")) nodeTool = temp;
		if(temp->GetName() == _T("Targets")) nodeTarget = temp;
		if(temp->GetName() == _T("Runs")) nodeRun = temp;
		temp = temp->GetNext();
	}
	// If a node is missing, generate it!
	if(nodeObject == NULL){
		nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("Objects"));
		root->InsertChild(nodeObject, NULL);
	}
	if(nodeMachine == NULL){
		nodeMachine = new wxXmlNode(wxXML_ELEMENT_NODE, _T("Machine"));
		root->InsertChildAfter(nodeMachine, nodeObject);
	}
	if(nodeTool == NULL){
		nodeTool = new wxXmlNode(wxXML_ELEMENT_NODE, _T("Tools"));
		root->InsertChildAfter(nodeTool, nodeMachine);
	}
	if(nodeTarget == NULL){
		nodeTarget = new wxXmlNode(wxXML_ELEMENT_NODE, _T("Targets"));
		root->InsertChildAfter(nodeTarget, nodeTool);
	}
	if(nodeRun == NULL){
		nodeRun = new wxXmlNode(wxXML_ELEMENT_NODE, _T("Runs"));
		root->InsertChildAfter(nodeRun, nodeTarget);
	}

	// Insert Data into the nodes.
	size_t i;
	for(i = 0; i < objects.GetCount(); i++)
		objects[i].ToXml(nodeObject);
//	machine.ToXml(nodeMachine);

	XMLRemoveAllChildren(nodeTarget);
	//	for(i = 0; i < targets.GetCount(); i++)
	//		targets[i].ToXml(nodeTarget);
	for(i = 0; i < run.GetCount(); i++)
		run[i].ToXml(nodeRun);

	if(!doc.Save(fileName.GetFullPath(), wxXML_NO_INDENTATION)) return false;
	this->fileName = fileName;
	return true;
}

bool Project::Load(wxFileName fileName)
{
	wxXmlDocument* tempTree = new wxXmlDocument();
	//tempTree->SetFileEncoding(_T("UTF-8"));
	//tempTree->SetVersion(_T(_GENERICCAM_VERSION));

	if(!tempTree->Load(fileName.GetFullPath(), wxT("UTF-8"))){
		delete tempTree;
		wxLogWarning(
				_T(
						"Project::Load: Coud not load ") + fileName.GetFullPath() + _T(" file!"));
		return false;
	}
	// Swap XML trees
	this->doc = *tempTree;

	// Take the tree apart
	wxXmlNode *temp = doc.GetRoot();
	if(temp == NULL){
		wxLogWarning(_T("File contains no data (i.e. no root)!"));
		return false;
	}
	if(temp->GetName() != _T("GenericCAMProjectFile")){
		wxLogWarning(_T("Not a Generic CAM datafile!"));
		return false;
	}

	Clear();

	Object* tempObject = NULL;
//	Tool* tempTool = NULL;
//	Target* tempTarget = NULL;
	Run* tempRun = NULL;

	wxXmlNode *temp2;

	temp = temp->GetChildren();
	while(temp != NULL){

		//		wxLogMessage(_T("Node found: ") + temp->GetName());

		if(temp->GetName() == _T("Objects")){
			temp2 = temp->GetChildren();
			while(temp2 != NULL){
				//				wxLogMessage(_T("Objects node found: ") + temp2->GetName());
				tempObject = new Object();
				if(tempObject->FromXml(temp2))
					objects.Add(tempObject);
				else
					delete tempObject;

				temp2 = temp2->GetNext();
			}
			//			wxLogMessage(_T("Objects node found!"));
		}
//		if(temp->GetName() == _T("Machine")){
//			temp2 = temp->GetChildren();
//			while(temp2 != NULL){
//				machine.FromXml(temp2);
//				temp2 = temp2->GetNext();
//			}
		//			wxLogMessage(_T("Machine node found!"));
//		}
//		if(temp->GetName() == _T("Tools")){
		//			temp2 = temp->GetChildren();
		//			while(temp2 != NULL){
		//				tempObject = new Object();
		//				tempObject->FromXml(temp2);
		//				objects.Add(tempObject);
		//				temp2 = temp2->GetNext();
		//			}
		//			wxLogMessage(_T("Tools node found!"));
//		}
		//		if(temp->GetName() == _T("Targets")){
		//			temp2 = temp->GetChildren();
		//			while(temp2 != NULL){
		//				tempTarget = new Target();
		//				if(tempTarget->FromXml(temp2))
		//					targets.Add(tempTarget);
		//				else
		//					delete tempTarget;
		//				temp2 = temp2->GetNext();
		//			}
		//
		//
		//			//			wxLogMessage(_T("Targets node found!"));
		//		}
//
//		if(temp->GetName() == _T("Runs")){
//			temp2 = temp->GetChildren();
//			while(temp2 != NULL){
//				tempRun = new Run();
//				if(tempRun->FromXml(temp2))
//					run.Add(tempRun);
//				else
//					delete tempRun;
//				temp2 = temp2->GetNext();
//			}
//
//			//			wxLogMessage(_T("Runs node found!"));
//		}
//		temp = temp->GetNext();
	}
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

	switch(displayType){
	case displayObjects:
		glLoadName(1);
		for(i = 0; i < objects.GetCount(); i++){
			glPushName(i + 1);
			objects[i].Paint();
			glPopName();
		}
		break;

	case displayWorkpieces:
		glLoadName(2);
		for(i = 0; i < workpieces.GetCount(); i++){
			if(!workpieces[i].selected) continue;
			glPushName(i);
			workpieces[i].Paint(objects);
			glPopName();
		}
		break;
	case displayRun:
		glLoadName(3);
		for(i = 0; i < run.GetCount(); i++){
			if(!run[i].selected) continue;

			::glPushName(i);
			run[i].Paint(objects, workpieces);
			::glPopName();
		}
		break;
	}
	::glLoadName(0);
}

void Project::PropagateChanges(void)
{
	// Testing preconditions.
	// Propagate modifcation flag from object to workpiece
	for(size_t workpieceNr = 0; workpieceNr < workpieces.GetCount();
			workpieceNr++){
		for(size_t placementNr = 0;
				placementNr < workpieces[workpieceNr].placements.GetCount();
				placementNr++){
			int objectNr =
					workpieces[workpieceNr].placements[placementNr].objectNr;
			if(objectNr >= 0){
				if(objects[objectNr].modified) workpieces[workpieceNr].modified =
				true;
			}
		}
	}

	// Propagate modification flag from workpiece to run to the generators
	for(size_t runNr = 0; runNr < run.GetCount(); runNr++){
		int workpieceNr = run[runNr].workpieceNr;
		if(workpieceNr >= 0){
			if(workpieces[workpieceNr].modified) run[runNr].modified = true;
		}
		if(run[runNr].modified){
			for(size_t toolpathNr = 0;
					toolpathNr < run[runNr].toolpaths.GetCount(); toolpathNr++){
				run[runNr].toolpaths[toolpathNr].generator->toolpathGenerated =
				false;
			}
		}
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

