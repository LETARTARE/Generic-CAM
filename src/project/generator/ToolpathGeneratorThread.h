///////////////////////////////////////////////////////////////////////////////
// Name               : ToolpathGeneratorThread.h
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

#ifndef TOOLPATHGENERATORTHREAD_H_
#define TOOLPATHGENERATORTHREAD_H_

/*!\class ToolpathGeneratorThread
 * \ingroup GeneratorBasics
 * \brief Thread to control the toolpath generation for a workpiece
 *
 * ...
 */

#if(_GENERICCAM_USEMULTITHREADING == 1)

#include <stddef.h>
#include <wx/thread.h>

class Project;

class ToolpathGeneratorThread:public wxThread{
public:
	ToolpathGeneratorThread(Project * project, size_t runNr, size_t toolpathNr);
	virtual ~ToolpathGeneratorThread();

	virtual wxThread::ExitCode Entry(void);

private:
	Project * project;
	size_t runNr;
	size_t toolpathNr;

};

#endif

#endif /* TOOLPATHGENERATORTHREAD_H_ */
