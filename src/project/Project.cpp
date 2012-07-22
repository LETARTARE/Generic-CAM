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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////


#include "Project.h"
#include "../Config.h"
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfProject)

#include <GL/gl.h>
#include <math.h>

Project::Project()
{
	doc.SetFileEncoding(_T("UTF-8"));
	//doc.SetVersion(_T(_GENERICCAM_VERSION));
	doc.SetVersion(_T("1.0"));
	ClearProject();

	middleY = 0.212;
	offsetX = 0.100;

}

Project::~Project()
{
}

void Project::ClearProject(void)
{
	objects.Empty();
	runs.Empty();

	modified = false;
	projectName = _("Untitled");

	activeObject = 0;
	activeTarget = 0;
	activeStock = 0;
	activeRun = 0;

	displayGeometry = true;
	displayBoundingBox = false;
	displayMachine = false;
	displayStock = false;
	displayWorkpiece = false;
	displayRun = true;
	displayTargets = true;
	displayToolpath = true;
	displayOutLines = true;

	Tolerance.Setup(_T("m"), _T("mm"), (double) 1 / 1000);
	Distance.Setup(_T("m"), _T("mm"), (double) 1 / 1000);
	RotationalSpeed.Setup(_T("1/s"), _T("rpm"), (double) 1 / 60);
	LinearSpeed.Setup(_T("m/s"), _T("mm/s"), (double) 1 / 1000);

	slotWidth = 0.010;
	supportDistance = 0.05;
	supportWidth = 0.005;
	supportHeight = 0.005;

	resolution = 0.0005;
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
	machine.ToXml(nodeMachine);
	//TODO: Rework the tool system!

	XMLRemoveAllChildren(nodeTarget);
	//	for(i = 0; i < targets.GetCount(); i++)
	//		targets[i].ToXml(nodeTarget);
	for(i = 0; i < runs.GetCount(); i++)
		runs[i].ToXml(nodeRun);

	if(!doc.Save(fileName.GetFullPath(), wxXML_NO_INDENTATION)) return false;
	modified = false;
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
		wxLogWarning(_T("Project::Load: Coud not load ")
				+ fileName.GetFullPath() + _T(" file!"));
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

	ClearProject();

	Object* tempObject = NULL;
	Tool* tempTool = NULL;
	Target* tempTarget = NULL;
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
		if(temp->GetName() == _T("Machine")){
			temp2 = temp->GetChildren();
			while(temp2 != NULL){
				machine.FromXml(temp2);
				temp2 = temp2->GetNext();
			}
			//			wxLogMessage(_T("Machine node found!"));
		}
		if(temp->GetName() == _T("Tools")){
			//TODO: Rework tool system!
			//			temp2 = temp->GetChildren();
			//			while(temp2 != NULL){
			//				tempObject = new Object();
			//				tempObject->FromXml(temp2);
			//				objects.Add(tempObject);
			//				temp2 = temp2->GetNext();
			//			}
			//			wxLogMessage(_T("Tools node found!"));
		}
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

		if(temp->GetName() == _T("Runs")){
			temp2 = temp->GetChildren();
			while(temp2 != NULL){
				tempRun = new Run();
				if(tempRun->FromXml(temp2))
					runs.Add(tempRun);
				else
					delete tempRun;
				temp2 = temp2->GetNext();
			}


			//			wxLogMessage(_T("Runs node found!"));
		}
		temp = temp->GetNext();
	}
	return true;
}

void Project::Assemble(void)
{
	machine.Assemble();
	if(machine.IsInitialized()) stock.stockMaterials[0].matrix
			= machine.workpiecePosition;

}

void Project::Paint(void)
{
	size_t i, j;
	if(displayGeometry){
		for(i = 0; i < objects.GetCount(); i++)
			objects[i].Paint();


		octree.Paint();

	}
	if(displayMachine) machine.Paint();

	if(displayRun){
		for(i = 0; i < runs.GetCount(); i++){
			runs[i].Paint();
			for(j = 0; j < runs[i].placements.GetCount(); j++){
				::glPushMatrix();
				::glMultMatrixd(runs[i].placements[j].matrix.a);

				if(displayOutLines) runs[i].placements[j].outLine.Paint();
				if(displayTargets){
					if(!runs[i].placements[j].isKeepout){
						targets[runs[i].placements[j].targetNumber].Paint();
					}
				}
				::glPopMatrix();

			}

		}
	}

	if(displayStock) stock.Paint();
	//if(displayWorkpiece) workpiece.Paint();
	//if(displayBoundingBox) bbox.Paint();
}

//bool Project::LoadObject(wxFileName)


size_t Project::SetupMachineBed(bool flipped)
{
	TargetPlacement tempPlace;
	Run* run = new Run;
	runs.Empty();
	targets.Empty();


	// TODO: Remove next line to get full machinebed.
	if(true){


		// The groundplane im machine coordinates
		tempPlace.Clear();
		tempPlace.outLine.InsertPoint(0.064, 0.082, 0.0);
		tempPlace.outLine.InsertPoint(0.533, 0.083, 0.0);
		tempPlace.outLine.InsertPoint(0.532, 0.342, 0.0);
		tempPlace.outLine.InsertPoint(0.064, 0.342, 0.0);
		tempPlace.outLine.Close();
		tempPlace.isMovable = false;
		tempPlace.isKeepout = true;
		run->placements.Add(tempPlace);


		// Screws in the plane
		tempPlace.SetKeepout(0.078, 0.097, 0.010, 0.010);
		run->placements.Add(tempPlace);

		tempPlace.SetKeepout(0.509, 0.096, 0.010, 0.010);
		run->placements.Add(tempPlace);

		tempPlace.SetKeepout(0.507, 0.318, 0.010, 0.010);
		run->placements.Add(tempPlace);

		tempPlace.SetKeepout(0.079, 0.316, 0.010, 0.010);
		run->placements.Add(tempPlace);

		InsertDrillGrid(*run, 0.380, 0.230, flipped);

	}

	runs.Add(run);
	return (runs.GetCount() - 1);
}

void Project::FlipRun(void)
{
	size_t n = runs[activeRun].placements.GetCount();
	if(n < 4) return;
	size_t i, j, m, p;
	Vector3 temp;
	double dx, dy;
	for(i = 1; i < n; i++){
		m = runs[activeRun].placements[i].outLine.elements.GetCount();

		if(runs[activeRun].placements[i].isKeepout){
			for(j = 0; j < m; j++)
				runs[activeRun].placements[i].outLine.elements[j].y
						= -runs[activeRun].placements[i].outLine.elements[j].y;

			temp = runs[activeRun].placements[i].matrix.GetCenter();
			runs[activeRun].placements[i].matrix.TranslateGlobal(0.0, (middleY
					- temp.y) * 2, 0.0);

		}else{
			p = runs[activeRun].placements[i].targetNumber;
			dx = targets[p].GetSizeX() / 2;
			dy = targets[p].GetSizeY() / 2;

			for(j = 0; j < m; j++)
				runs[activeRun].placements[i].outLine.elements[j].y = dy * 2
						- runs[activeRun].placements[i].outLine.elements[j].y;

			runs[activeRun].placements[i].matrix.TranslateLocal(+dx, +dy, 0.0);

			temp = runs[activeRun].placements[i].matrix.GetCenter();
			double alpha = atan2(runs[activeRun].placements[i].matrix.a[1],
					runs[activeRun].placements[i].matrix.a[0]);

			AffineTransformMatrix tr;
			tr = AffineTransformMatrix::RotateXYZ(0.0, 0.0, -2 * alpha);
			runs[activeRun].placements[i].matrix
					= runs[activeRun].placements[i].matrix * tr;

			runs[activeRun].placements[i].matrix.TranslateGlobal(0.0, 2
					* (middleY - temp.y), 0.0);

			runs[activeRun].placements[i].matrix.TranslateLocal(-dx, -dy, 0.0);

		}

	}
	for(i = 0; i < targets.GetCount(); i++){
		targets[i].FlipX();
		targets[i].toolpathFlipped = targets[i].toolpath;
		targets[i].toolpath.Clear();
		targets[i].refresh = true;
	}

}

void Project::CollectToolPath(void)
{
	size_t i, n;
	ToolPath temp;
	runs[activeRun].toolPath.Clear();
	MachinePosition mp;
	if(true){ // Startup move, to prevent WinPC-NC from messing up the toolpath.
		mp.axisX = 0.0;
		mp.axisY = 0.0;
		mp.axisZ = this->stock.stockMaterials[activeStock].z + 0.010;
		mp.isCutting = false;
		runs[activeRun].toolPath.positions.Add(mp);
		mp.axisZ = this->stock.stockMaterials[activeStock].z + 0.011;
		mp.isCutting = true;
		runs[activeRun].toolPath.positions.Add(mp);
	}

	for(i = 0; i < runs[activeRun].placements.GetCount(); i++){
		if(!runs[activeRun].placements[i].isKeepout){
			n = runs[activeRun].placements[i].targetNumber;
			if(!targets[n].toolpath.IsEmpty()){
				temp = targets[n].toolpath;
				temp.ApplyTransformation();
				temp.ApplyTransformation(runs[activeRun].placements[i].matrix);
				runs[activeRun].toolPath += temp;
			}
		}
	}
}

void Project::GenerateToolPath(void)
{
	size_t i, j;
	bool isUsed;
	for(i = 0; i < targets.GetCount(); i++){
		if(targets[i].toolpath.IsEmpty()){

			isUsed = false;
			for(j = 0; j < runs[activeRun].placements.GetCount(); j++){
				if(!runs[activeRun].placements[j].isKeepout
						&& runs[activeRun].placements[j].targetNumber == i) isUsed
						= true;
			}

			if(isUsed){

				wxLogMessage(wxString::Format(
						_T("Generating toolpath for target %u:"), i));

				runs[activeRun].ToolPathGenerator.GenerateToolpath(targets[i],
						toolbox.tools[0]);
			}
		}
	}
	CollectToolPath();
}

void Project::InsertDrillGrid(Run &run, double sizex, double sizey,
		bool flipped)
{
	Target temp;
	TargetPlacement tempPlace;
	temp.SetupDrill(toolbox.tools[0], 0.0082, 0.012);
	targets.Add(temp);
	tempPlace.outLine = temp.outLine;
	tempPlace.isMovable = false;
	tempPlace.targetNumber = targets.GetCount() - 1;
	tempPlace.matrix.SetIdentity();
	tempPlace.matrix.TranslateGlobal(offsetX, middleY - sizey / 2,
			run.stockMaterial.z);

	run.placements.Add(tempPlace);
	tempPlace.matrix.SetIdentity();
	tempPlace.matrix.TranslateGlobal(offsetX, middleY + sizey / 2,
			run.stockMaterial.z);
	run.placements.Add(tempPlace);
	tempPlace.matrix.SetIdentity();
	if(flipped){
		tempPlace.matrix.TranslateGlobal(offsetX + sizex, middleY - sizey / 2,
				run.stockMaterial.z);
	}else{
		tempPlace.matrix.TranslateGlobal(offsetX + sizex, middleY + sizey / 2,
				run.stockMaterial.z);
	}
	run.placements.Add(tempPlace);
}

void Project::GenerateTargets(void)
{

	Target temp, temp2;
	TargetPlacement tempPlace;
	Run* run = new Run;

	run->stockMaterial = stock.stockMaterials[0];

	AffineTransformMatrix shift;

	Object* obj = &(objects[activeObject]);
	AffineTransformMatrix oldPos = obj->matrix;

	obj->UpdateBoundingBox();

	size_t i, n;
	n = ceil(obj->bbox.zmax / stock.stockMaterials[activeStock].z);

	Target discSlot;
	discSlot.SetupDisc(slotWidth, resolution, resolution);

	slotWidth = 0.025;
	Target discSlot2;
	discSlot2.SetupDisc(slotWidth, resolution, resolution);

	i = SetupMachineBed(true);
	run = &(runs[i]);


	//	discSlot.matrix.TranslateGlobal(0.1, -0.1, 0);
	//	targets.Add(discSlot);


	wxLogMessage(wxString::Format(
			_T("%u Targets after stockmaterial placement."),
			run->placements.GetCount()));


	//	// Hole@:
	//	tempPlace.SetKeepout(0.23858 - 0.010, 0.329268 - 0.010, 0.020, 0.020);
	//	run->placements.Add(tempPlace);


	// Screw 1:
	tempPlace.SetKeepout(0.0785 - 0.010, 0.114 - 0.010, 0.020, 0.020);
	run->placements.Add(tempPlace);


	// Screw 2:
	tempPlace.SetKeepout(0.0755 - 0.010, 0.301 - 0.010, 0.020, 0.020);
	run->placements.Add(tempPlace);


	// Screw 3:
	tempPlace.SetKeepout(0.469 - 0.010, 0.099 - 0.010, 0.020, 0.020);
	run->placements.Add(tempPlace);

	wxLogMessage(wxString::Format(_T("%u Targets after keepout placement."),
			run->placements.GetCount()));

	wxLogMessage(wxString::Format(_T("%u Targets after drill placement."),
			run->placements.GetCount()));

	double gridx = 0.0;
	double gridy = 0.0;
	double gridsx = obj->bbox.xmax + 4 * slotWidth;
	double gridsy = obj->bbox.ymax + 4 * slotWidth;


	//if(n > 2) n = 2; // TODO: Remove this line!
	for(i = 4; i < 9; i++){
		//for(i = 0; i <= 2; i++){


		if(true){
			temp.SetupBox(obj->bbox.xmax + 4 * slotWidth, obj->bbox.ymax + 4
					* slotWidth, stock.stockMaterials[activeStock].z,
					resolution, resolution);

			shift.SetIdentity();
			shift.TranslateGlobal(2.0 * slotWidth, 2.0 * slotWidth, (double) i
					* -stock.stockMaterials[activeStock].z);

		}else{
			temp.SetupBox(obj->bbox.xmax, obj->bbox.ymax,
					stock.stockMaterials[activeStock].z, resolution, resolution);

			shift.SetIdentity();
			shift.TranslateGlobal(0.0, 0.0, (double) i
					* -stock.stockMaterials[activeStock].z);
		}

		obj->matrix = shift * oldPos;
		temp.InsertObject(*obj);
		temp.CleanOutlier();


		//		temp.matrix.TranslateGlobal(obj->bbox.xmax + 4 * slotWidth, 0, 0);
		//		targets.Add(temp);
		if(true) //TODO: Remove this line
		{
			temp2 = temp;

			if(i == 0){
				temp2.FoldRaise(discSlot2);
			}else{
				temp2.FoldRaise(discSlot);
			}

			temp.outLine = temp2.GenerateConvexOutline();

			if(temp.outLine.elements.GetCount() >= 2){

				temp.supportLine = temp2.GeneratePolygon(-1, -1);
				temp.supportLine.PolygonSmooth();
				temp.supportLine.PolygonSmooth();
				temp.supportLine.PolygonSmooth();


				//temp.FillOutsidePolygon(temp.outline);
				temp2.HardInvert();
				temp += temp2;

				temp.AddSupport(temp.supportLine, supportDistance,
						supportHeight, supportWidth, slotWidth);
			}
		}

		tempPlace.Clear();
		tempPlace.matrix.TranslateGlobal(gridx, gridy, 0.0);
		//		tempPlace.matrix = AffineTransformMatrix::RotateXYZ(0.0, 0.0,
		//				(double) (i % 2) * 2 * M_PI) * tempPlace.matrix;

		temp.refresh = true;

		targets.Add(temp);
		tempPlace.targetNumber = targets.GetCount() - 1;
		tempPlace.outLine = temp.outLine;
		run->placements.Add(tempPlace);

		gridx += gridsx;
		if(gridx + gridsx > stock.stockMaterials[activeStock].x){
			gridx = 0.0;
			gridy += gridsy;
		}


		//		Target mill;
		//		mill.SetupDisc(3.0/1000,temp.GetSizeRX(),temp.GetSizeRY());
		//		temp.FoldRaise(mill);
		//
		//		temp.InvertTop();
		//
		//		temp.matrix.TranslateGlobal(obj->bbox.xmax + 4 * slotWidth, 0, 0);
		//		targets.Add(temp);


		//temp.matrix.TranslateGlobal(obj->bbox.xmax + 4 * slotWidth, 0, 0);

		//		if(temp.outLine.elements.GetCount() >= 2){


		//temp.ClearField();


		//			ToolPathGenerator.GenerateToolpath(temp, *obj, toolbox.tools[0]);


	}

	wxLogMessage(wxString::Format(_T("%u Targets after target placement."),
			run->placements.GetCount()));


	//run->SortTargets();

	runs.Add(run);

	obj->matrix = oldPos;

	displayGeometry = false;
	displayStock = true;
	displayTargets = true;
	if(false){
		GenerateToolPath();

		n = targets.GetCount() - 1;

		temp = targets[n];
		temp.Simulate();
		targets.Add(temp);
		tempPlace.targetNumber = targets.GetCount() - 1;
		tempPlace.matrix.SetIdentity();
		tempPlace.matrix.TranslateGlobal(2 * temp.GetSizeX(), 0.0, 0.0);
		runs[0].placements.Add(tempPlace);

		temp = targets[n];

		Target discTool;
		discTool.SetupDisc(0.003, temp.GetSizeRX(), temp.GetSizeRY());

		temp.FoldRaise(discTool);
		temp.Limit();
		temp.InvertTop();

		targets.Add(temp);
		tempPlace.targetNumber = targets.GetCount() - 1;
		tempPlace.matrix.SetIdentity();
		tempPlace.matrix.TranslateGlobal(temp.GetSizeX(), 0.0, 0.0);
		runs[0].placements.Add(tempPlace);
	}

}

