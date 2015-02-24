///////////////////////////////////////////////////////////////////////////////
// Name               : ToolpathGeneratorThread.cpp
// Purpose            : 
// Thread Safe        : Certainly not
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 23.02.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "ToolpathGeneratorThread.h"

#include "../project/Project.h"

ToolpathGeneratorThread::ToolpathGeneratorThread(Project* project, size_t runNr,
		size_t toolpathNr)
{
	this->project = project;
	this->runNr = runNr;
	this->toolpathNr = toolpathNr;
}

ToolpathGeneratorThread::~ToolpathGeneratorThread()
{
}

wxThread::ExitCode ToolpathGeneratorThread::Entry(void)
{
	assert(runNr < project->run.GetCount());
	size_t workpieceNr = project->run[runNr].workpieceNr;
	assert(workpieceNr >= 0);
	assert(toolpathNr >= 0);
	project->run[runNr].toolpaths[toolpathNr].generator->GenerateToolpath();
	project->workpieces[workpieceNr].hasRunningGenerator = false;
	return 0;
}
