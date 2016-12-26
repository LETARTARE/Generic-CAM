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
#include "generator/GeneratorCollection.h"

#include <wx/log.h>
#include <GL/gl.h>
#include <float.h>
#include <assert.h>

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArrayOfRun)

Run::Run()
{
	selected = false;
//	modified = false;
	name = _T("Run #");
	refWorkpiece = -1;
//	toolbox.Empty();
	selectedTool = 0;
	parent = NULL;
}

Run::Run(const Run& other)
{
	throw("'Run::Copy constructor' is unimplemented!");
}

Run& Run::operator=(const Run& other)
{
	if(&other == this) return *this;
	throw("'Run::operator=' is unimplemented!");
	return *this;
}

Run::~Run()
{
	for(size_t i = 0; i < generators.GetCount(); i++)
		delete generators[i];
}

void Run::GenerateToolpaths(void)
{
	Update();
	for(size_t i = 0; i < generators.GetCount(); i++){
		assert(generators[i] != NULL);
		generators[i]->GenerateToolpath();
	}
}

void Run::Update(void)
{
	for(size_t i = 0; i < generators.GetCount(); i++){
		assert(generators[i] != NULL);
		generators[i]->parent = this;
	}
}

void Run::Paint(void) const
{
	const Project * pr = parent;
	if(pr == NULL) return;

	machine.Paint();

	::glPushMatrix();

	if(refWorkpiece > -1){
		::glPushMatrix();
		::glMultMatrixd(machine.workpiecePosition.a);
		::glMultMatrixd(workpiecePlacement.a);
		pr->workpieces[refWorkpiece].Paint();
		for(size_t n = 0; n < generators.GetCount(); n++){
			assert(generators[n] != NULL);
			generators[n]->Paint();
		}
		::glPopMatrix();
	}
	::glPopMatrix();
	if(selectedTool >= 0 && selectedTool < tools.GetCount()){
		::glPushMatrix();
		::glMultMatrixd(machine.toolPosition.a);
		::glColor3f(0.7, 0.7, 0.7);
		tools[selectedTool].Paint();
		::glPopMatrix();
	}
}

void Run::ToolpathToStream(wxTextOutputStream & stream)
{
//	toolPath.ToolpathToStream(f);
	throw(__FILE__ "Not yet implemented.");
}

void Run::ToStream(wxTextOutputStream& stream)
{
	stream << _T("Name:") << endl;
	stream << name << endl;
	stream << wxString::Format(_T("WorkpieceRef: %u"), refWorkpiece) << endl;
	stream << wxString::Format(_T("Tools: %u"), tools.GetCount()) << endl;
	for(size_t n = 0; n < tools.GetCount(); n++){
		stream << wxString::Format(_T("Tool: %u"), n) << endl;
		tools[n].ToStream(stream);
	}
	stream << _T("Machine:") << endl;
	stream << machine.fileName.GetFullPath() << endl;
	GeneratorCollection gc;
	stream << wxString::Format(_T("Generators: %u"), generators.GetCount())
			<< endl;
	for(size_t n = 0; n < generators.GetCount(); n++){
		stream << wxString::Format(_T("Generator: %u"), n) << endl;
		size_t g;
		if(!gc.FindGenerator(generators[n], &g)) throw(__FILE__ "Cannot find generator.");
		stream << gc.GetName(g) << endl;
		generators[n]->ToStream(stream);
	}
}

bool Run::FromStream(wxTextInputStream& stream, int runNr, Project * project)
{
	wxString temp;
	temp = stream.ReadLine();
	if(temp.Cmp(_T("Name:")) != 0) return false;
	name = stream.ReadLine();
	temp = stream.ReadWord();
	if(temp.Cmp(_T("WorkpieceRef:")) != 0) return false;
	refWorkpiece = stream.Read32S();
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Tools:")) != 0) return false;
	size_t NTools = stream.Read32S();
	tools.Clear();
	for(size_t n = 0; n < NTools; n++){
		temp = stream.ReadWord();
		if(temp.Cmp(_T("Tool:")) != 0) return false;
		size_t index = stream.Read32S();
		if(index != n) return false;
		Tool temp;
		temp.FromStream(stream);
		tools.Add(temp);
	}
	temp = stream.ReadLine();
	if(temp.Cmp(_T("Machine:")) != 0) return false;
	wxFileName fileName(stream.ReadLine());
	machine.Load(fileName);
	temp = stream.ReadWord();
	if(temp.Cmp(_T("Generators:")) != 0) return false;
	size_t N = stream.Read32();

	for(size_t n = 0; n < generators.GetCount(); n++)
		delete generators[n];
	generators.Clear();
	GeneratorCollection gc;
	for(size_t n = 0; n < N; n++){
		temp = stream.ReadWord();
		if(temp.Cmp(_T("Generator:")) != 0) return false;
		size_t index = stream.Read32S();
		if(index != n) return false;
		temp = stream.ReadLine();
		size_t generatorNr;
		if(!gc.FindGenerator(temp, &generatorNr)) return false;
		Generator* tempGen = gc.NewGenerator(generatorNr);
		tempGen->FromStream(stream);
		generators.Add(tempGen);
	}
	return true;
}

