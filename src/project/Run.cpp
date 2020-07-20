///////////////////////////////////////////////////////////////////////////////
// Name               : Run.cpp
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

#include "Run.h"

#include "Project.h"
#include "generator/CNCSimulator.h"

#include "../icon/touchpoint.xpm"

#include <wx/log.h>
#include <float.h>
#include <assert.h>
#include <iostream>

#include "../Config.h"
#include "../3D/OpenGL.h"
#include "../math/JSON.h"
#include "generator/GeneratorFactory.h"

Run::Run(size_t ID) :
		ID(ID)
{
	parent = NULL;
	object = 0;
	stocktype = BoxBottom;

	coordX.Add(Selection::Axis, 0);
	coordY.Add(Selection::Axis, 1);
	coordZ.Add(Selection::Axis, 2);

	touchpoint = wxImage(touchpoint_xpm);
	touchpoint.SetAlphaColor(255, 255, 255);

	base.displayField = true;

	if(DEBUG) printf("Run::Run - Created run %p with DexelTarget base %p\n",
			this, &base);
}

Run::~Run()
{
	for(std::vector <Generator *>::iterator it = generators.begin();
			it != generators.end(); ++it){
		delete (*it);
	}
}

bool Run::operator ==(const size_t ID) const
{
	return (this->ID == ID);
}

size_t Run::GetID(void) const
{
	return ID;
}
void Run::Update(Project * project)
{
	if(project == NULL) return;
	parent = project;
	origin.SetIdentity();
	// Calculate coordinate system
	if(coordX.Has(Selection::Axis, 0)) origin.SetEx(Vector3(1, 0, 0));
	if(coordX.Has(Selection::Axis, 1)) origin.SetEx(Vector3(0, 1, 0));
	if(coordX.Has(Selection::Axis, 2)) origin.SetEx(Vector3(0, 0, 1));

	if(coordY.Has(Selection::Axis, 0)) origin.SetEy(Vector3(1, 0, 0));
	if(coordY.Has(Selection::Axis, 1)) origin.SetEy(Vector3(0, 1, 0));
	if(coordY.Has(Selection::Axis, 2)) origin.SetEy(Vector3(0, 0, 1));
	origin.CalculateEz();
	if(coordZ.Has(Selection::Axis, 0)) origin.SetEz(Vector3(1, 0, 0));
	if(coordZ.Has(Selection::Axis, 1)) origin.SetEz(Vector3(0, 1, 0));
	if(coordZ.Has(Selection::Axis, 2)) origin.SetEz(Vector3(0, 0, 1));
	origin.CalculateEx();
	origin.CalculateEy();
	origin.Normalize();

	if(stocktype == sObject && stockobject.IsType(Selection::Object)){
		stock = parent->GetBBox(stockobject);
	}
	if(stocktype == BoxTop || stocktype == BoxCenter || stocktype == BoxBottom){
		BoundingBox bbox = parent->GetBBox(object);
		Vector3 boxorigin((bbox.xmax + bbox.xmin - stocksize.x) / 2.0,
				(bbox.ymax + bbox.ymin - stocksize.y) / 2.0,
				(bbox.zmax + bbox.zmin - stocksize.z) / 2.0);
		const double diff = (bbox.GetSizeZ() - stocksize.z) / 2.0;

		if(stocktype == BoxTop) stock.SetSize(stocksize.x, stocksize.y,
				stocksize.z, boxorigin.x, boxorigin.y, boxorigin.z + diff);
		if(stocktype == BoxCenter) stock.SetSize(stocksize.x, stocksize.y,
				stocksize.z, boxorigin.x, boxorigin.y, boxorigin.z);
		if(stocktype == BoxBottom) stock.SetSize(stocksize.x, stocksize.y,
				stocksize.z, boxorigin.x, boxorigin.y, boxorigin.z - diff);

	}
	AffineTransformMatrix M = stock.GetCoordinateSystem();
	origin.SetOrigin(M.Transform(stockorigin));

}

void Run::Paint(void) const
{
	const Project * pr = parent;
	if(pr == NULL) return;

	OpenGLMaterial::EnableColors();

	// Paint semi-transparent stock object
	if(stocktype == BoxTop || stocktype == BoxCenter || stocktype == BoxBottom){
		if(OpenGLMaterial::ColorsAllowed()){
			glColor4f(0.2, 0.2, 0.2, 0.6);
			glPushName((GLuint) Selection::TriangleGroup);
			stock.Paint();
			glPopName();
			if(DEBUG){
				glPushMatrix();
				glTranslatef(stock.xmin, stock.ymin, stock.zmin);
				glTranslatef(-base.GetSizeX(), 0, 0);
				base.Paint();
				glPopMatrix();
			}
		}
	}

	if(OpenGLMaterial::ColorsAllowed()){

		// Draw the "Touchpoint" symbol
		const float s = 0.03;
		glPushName(0);
		glPushName(0);

		glPushMatrix();
		origin.GLMultMatrix();
		// Move the images a little bit out of the object, to display correctly.
		glTranslatef(stockorigin.x * 1e-4, stockorigin.y * 1e-4, 0);
		glScalef(s, s, s);
		glRotatef(90, 1, 0, 0);
		touchpoint.Paint();
		glRotatef(90, 0, 1, 0);
		touchpoint.Paint();
		glRotatef(90, 0, 1, 0);
		touchpoint.Paint();
		glRotatef(90, 0, 1, 0);
		touchpoint.Paint();
		glPopMatrix();

		glPopName();
		glPopName();
	}

//	::glPushMatrix();
//	if(refWorkpiece > -1){
//		Vector3 center = pr->workpieces[refWorkpiece].GetCenter();
//		::glTranslatef(-center.x, -center.y, -center.z);
//	}
//
//	machine.Paint();
//
//	if(refWorkpiece > -1){
//		::glPushMatrix();
//		machine.workpiecePosition.GLMultMatrix();
//
//		if(showSimulation){
//			simulator.Paint();
//		}else{
//
//			bool anySelected = false;
//			for(std::map <size_t, Generator *>::iterator it = generators.begin();
//	it != generators.end(); ++it){
//				assert(generators[n] != NULL);
//				if(generators[n]->selected) anySelected = true;
//			}
//
//			for(std::map <size_t, Generator *>::iterator it = generators.begin();
//	it != generators.end(); ++it){
//				assert(generators[n] != NULL);
//				if(!anySelected || generators[n]->selected){
//					generators[n]->Paint();
//				}
//			}
//
//			::glPushMatrix();
//			workpiecePlacement.GLMultMatrix();
//			pr->workpieces[refWorkpiece].Paint();
//			::glPopMatrix();
//		}
//
//	}
//	::glPopMatrix();
}

void Run::PaintVertices(void) const
{
	OpenGLMaterial::EnableColors();
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glPushName(Selection::Vertex);
	// Paint the corner vertices and one extr vertex on the surfaces
	stock.PaintVertices(1, 10);
	glPopName();
}

void Run::GenerateToolpaths(void)
{

//	Workpiece* const workpiece = &(parent->workpieces[this->refWorkpiece]);
//	assert(workpiece != NULL);

	Update(parent);

	// Prepare the workpiece to run the simulations on
	const double A = stock.GetSizeX() * stock.GetSizeY();
	size_t N = (A / (parent->minResolution * parent->minResolution));
	N = (N > parent->maxCells)? (parent->maxCells) : N;
	N = (N < 4)? 4 : N;
	double res = sqrt(A / (double) N);
	base.SetupBox(stock.GetSizeX(), stock.GetSizeY(), stock.GetSizeZ(), res,
			res);

	if(stocktype == sObject && stockobject.IsType(Selection::Object)
			&& stockobject.Size() >= 1){
		const Object * obj = parent->Get3DObject(stockobject[0]);
		base.InitImprinting();

		AffineTransformMatrix M = obj->matrix;
		M.TranslateGlobal(-obj->bbox.xmin, -obj->bbox.ymin, -obj->bbox.zmin);
		M.TranslateGlobal(-stock.xmin + obj->bbox.xmin,
				-stock.ymin + obj->bbox.ymin, -stock.zmin + obj->bbox.zmin);
		base.InsertObject(*obj, M);
		base.FinishImprint();
	}else{
		base.Fill();
	}
	start = base;
	const std::vector <Tool> * tools = parent->GetTools();

	CNCSimulator simulator;
	simulator.SetTools(tools);

	double t = 0.0;

	toolpath.clear();

	for(std::vector <Generator *>::iterator it = generators.begin();
			it != generators.end(); ++it){
		assert((*it) != NULL);

		// Find the tool in the tool-library
		const Tool * tool = NULL;
		//TODO: Use std::find
		for(size_t n = 0; n < tools->size(); ++n){
			if(tools->at(n).base.guid.compare((*it)->toolguid) == 0){
				tool = &(tools->at(n));
				break;
			}
		}
		if(tool == NULL){
			(*it)->output = _T("Tool empty.");
			(*it)->errorOccured = true;
			continue;
		}

		(*it)->GenerateToolpath(*this, *(parent->GetObjects()), *tool, base);

		Vector3 temp(stock.xmin, stock.ymin, stock.zmin);
		if(!(*it)->toolpath.empty()){
			const size_t N = (*it)->toolpath.size();
			for(size_t n = 0; n < N; ++n){
				(*it)->toolpath[n].toolSlot = tool->postprocess.number;
				(*it)->toolpath[n].S = 200; // 1/s
//					m.S = tool.startvalues.n;
				(*it)->toolpath[n].F = 0.025; // m/s
//					m.F = tool.startvalues.fn;

				// Shift origin into absolute coordinates.
				(*it)->toolpath[n].position += temp;

			}
		}
		t = RecalculateTiming(&((*it)->toolpath), t);
		simulator.origin.SetOrigin(Vector3(stock.xmin, stock.ymin, stock.zmin));
		simulator.InsertBase(&base);
		simulator.InsertToolPath(&((*it)->toolpath));
		toolpath.insert(toolpath.end(), (*it)->toolpath.begin(),
				(*it)->toolpath.end());
		simulator.FullSimulation();
		base = *(simulator.GetResult());
	}
}

double Run::RecalculateTiming(std::vector <CNCPosition> * toolpath, double t0)
{
	const double minimumFeed = 1e-9; // 1 nm/s (If this should ever be a problem, I would love to know the field of application.)

	if(toolpath == NULL || toolpath->size() == 0) return t0;
	const size_t N = toolpath->size();
	double t = t0;
	for(size_t n = 0; (n + 1) < N; ++n){
		(*toolpath)[n].t = t;
		const double d = (*toolpath)[n].Abs((*toolpath)[n + 1]);
		(*toolpath)[n].dt = d / fmax((*toolpath)[n].F, minimumFeed);
		t += (*toolpath)[n].dt;
	}
	if(N > 0) (*toolpath)[N - 1].t = t;
	return t;
}

//
//bool Run::SaveToolpaths(wxFileName fileName)
//{
//	ToolPath generated;
//	for(std::map <size_t, Generator *>::iterator it = generators.begin();
//it != generators.end(); ++it){
//		assert(generators[i] != NULL);
//
//		//TODO: Remove this?
////		AffineTransformMatrix matrix;
////		matrix.TranslateGlobal(generators[i]->area.xmin,
////				generators[i]->area.ymin, generators[i]->area.zmin);
////		ToolPath moved = generators[i]->toolpath;
////		moved.ApplyTransformation(matrix);
////		generated += moved;
//		generated += generators[i]->toolpath;
//	}
//
//	// Move toolpath down by the touchoff height.
//	AffineTransformMatrix matrix;
//	matrix.TranslateGlobal(0, 0, -touchoffHeight);
//	const bool flipZ = true;
//	if(flipZ) matrix.ScaleGlobal(1, 1, -1);
//	generated.ApplyTransformation(matrix);
//
//	generated.CleanPath(0.0003);
//	generated.DiffPath(0.0003);
//
//	ToolPath startup;
//	startup.positions.Add(GCodeBlock(_T("G64 P2 (Cut corners)")));
//	startup.positions.Add(GCodeBlock(_T("S10000 (Spindle speed rpm)")));
//	startup.positions.Add(GCodeBlock(_T("M3 (Start spindel)")));
//	startup.positions.Add(
//			GCodeBlock(
//					_T("G4 P3 (wait for 3 seconds for the spindle to start)")));
//
//	ToolPath temp = ToolPath::SafetyBlock() + startup + generated
//			+ ToolPath::EndBlock();
//
////	temp.Translate(dialect);
//
//	setlocale(LC_ALL, "C"); // To get a 3.1415 instead 3,1415 or else on every computer.
//	wxTextFile f;
//	if(fileName.FileExists()){
//		f.Open(fileName.GetFullPath());
//		f.Clear();
//	}else{
//		f.Create(fileName.GetFullPath());
//	}
//
////	if(dialect == ToolPath::FanucM){
////		// For the fanucm.exe g-code simulator.
////		const wxTextFileType fileType = wxTextFileType_Dos;
////		f.AddLine(_T("G21"), fileType);
////		temp.CalculateMinMaxValues();
////		// Touch-off always from to of the workpiece for Fanuc-M.
////		for(size_t i = 0; i < temp.positions.GetCount(); i++)
////			temp.positions[i].Z -= temp.maxPosition.Z;
////		f.AddLine(
////				wxString::Format(_T("[billet x%g y%g z%g"),
////						(temp.maxPosition.X - temp.minPosition.X) * 1000.0,
////						(temp.maxPosition.Y - temp.minPosition.Y) * 1000.0,
////						(temp.maxPosition.Z - temp.minPosition.Z) * 1000.0
////								+ 0.1), fileType);
////		f.AddLine(
////				wxString::Format(_T("[edgemove x%g y%g"),
////						temp.minPosition.X * 1000.0,
////						temp.minPosition.Y * 1000.0), fileType);
////		for(size_t i = 0; i < machine.tools.GetCount(); i++){
////			f.AddLine(
////					wxString::Format(_T("[tooldef t%u d%g z%g"),
////							machine.tools[i].slotNr,
////							machine.tools[i].GetMaxDiameter() * 1000.0,
////							machine.tools[i].GetToolLength() * 1000.0),
////					fileType);
////		}
////	}
//
//	bool flag = temp.WriteToFile(f);
//	f.Write();
//	f.Close();
//	setlocale(LC_ALL, "");
//
//	return flag;
//}

//void Run::ToolpathToStream(wxTextOutputStream & stream)
//{
////	toolPath.ToolpathToStream(f);
//	throw(__FILE__ "Not yet implemented.");
//}

void Run::ToJSON(JSON& js) const
{
	js.SetObject(true);
	js["ID"].SetNumber(ID);
	js["Name"].SetString(name.ToStdString());

	coordX.ToJSON(js["CoordX"]);
	coordY.ToJSON(js["CoordY"]);
	coordZ.ToJSON(js["CoordZ"]);
	object.ToJSON(js["Object"]);

	switch(stocktype){
	case sObject:
		js["StockType"].SetString("Object");
		break;
	case BoxTop:
		js["StockType"].SetString("BoxTop");
		break;
	case BoxCenter:
		js["StockType"].SetString("BoxCenter");
		break;
	case BoxBottom:
		js["StockType"].SetString("BoxBottom");
		break;
	}

	stockobject.ToJSON(js["StockObject"]);

	js["StockSize"].SetObject(true);
	js["StockSize"]["X"].SetNumber(stocksize.x);
	js["StockSize"]["Y"].SetNumber(stocksize.y);
	js["StockSize"]["Z"].SetNumber(stocksize.z);

	js["StockOrigin"].SetObject(true);
	js["StockOrigin"]["X"].SetNumber(stockorigin.x);
	js["StockOrigin"]["Y"].SetNumber(stockorigin.y);
	js["StockOrigin"]["Z"].SetNumber(stockorigin.z);

	js["Machine"].SetString(machinefile.GetName().ToStdString());

	JSON &g = js["Generator"];
	g.SetArray(generators.size());
	size_t n = 0;
	for(std::vector <Generator *>::const_iterator it = generators.begin();
			it != generators.end(); ++it)
		(*it)->ToJSON(g[n++]);
}

bool Run::FromJSON(const JSON& js)
{
	if(!js.HasKey("ID")) return false;
	ID = (size_t) round(js["ID"].GetNumber());
	if(!js.HasKey("Name")) return false;
	name = js["Name"].GetString();

	coordX.FromJSON(js["CoordX"]);
	coordY.FromJSON(js["CoordY"]);
	coordZ.FromJSON(js["CoordZ"]);
	object.FromJSON(js["Object"]);

	std::string temp = js["StockType"].GetString();
	if(temp.compare("Object") == 0) stocktype = sObject;
	if(temp.compare("BoxTop") == 0) stocktype = BoxTop;
	if(temp.compare("BoxCenter") == 0) stocktype = BoxCenter;
	if(temp.compare("BoxBottom") == 0) stocktype = BoxBottom;

	stockobject.FromJSON(js["StockObject"]);
	const JSON &jsss = js["StockSize"];
	stocksize.x = jsss["X"].GetNumber();
	stocksize.y = jsss["Y"].GetNumber();
	stocksize.z = jsss["Z"].GetNumber();
	const JSON &jsso = js["StockOrigin"];
	stockorigin.x = jsso["X"].GetNumber();
	stockorigin.y = jsso["Y"].GetNumber();
	stockorigin.z = jsso["Z"].GetNumber();

	machinefile.SetName(js["Machine"].GetString());



	const JSON &g = js["Generator"];
	for(size_t n = 0; n < g.Size(); ++n){
		size_t generatortype = g[n]["Type"].GetNumber();
		size_t generatorid = g[n]["ID"].GetNumber();
		Generator* generator = GeneratorFactory::NewGenerator(generatortype,
				generatorid);
		generator->FromJSON(g[n]);
		generators.push_back(generator);
	}
	return true;
}
