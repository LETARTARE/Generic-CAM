///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorLoadFromFile.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 09.02.2015
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

#ifndef GENERATORLOADFROMFILE_H_
#define GENERATORLOADFROMFILE_H_

/*!\class GeneratorLoadFromFile
 * \ingroup Generator
 * \brief ...
 *
 * ...
 */
#include "Generator.h"

#include <wx/filename.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <stddef.h>

class wxFilePickerCtrl;

#include "GeneratorFactory.h"

class GeneratorLoadFromFile:public Generator {
public:
	GeneratorLoadFromFile(size_t ID);
	virtual void CopyParameterFrom(const Generator * other);
	virtual ~GeneratorLoadFromFile();
	virtual size_t GetType(void) const
		{
			return TYPE_GENERATORLOADFROMFILE;
		}
	virtual wxString GetTypeName(void) const;
	virtual wxSizer * AddToPanel(wxPanel * panel, CollectionUnits* settings) const;
	virtual void TransferDataToPanel(wxPanel* panel,
			CollectionUnits* settings) const;
	virtual void TransferDataFromPanel(CollectionUnits* settings);
	virtual bool operator==(const Generator &b) const;
	virtual void GenerateToolpath(const Run &run,
			const std::vector <Object> &objects, const Tool &tool,
			const DexelTarget &base);

private:

	wxFileName filename;

	mutable wxStaticText* m_staticTextLoadFile;
	mutable wxFilePickerCtrl* m_filePicker;
};

#endif /* GENERATORLOADFROMFILE_H_ */
