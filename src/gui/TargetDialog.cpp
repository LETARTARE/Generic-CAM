///////////////////////////////////////////////////////////////////////////////
// Name               : TargetDialog.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 06.07.2011
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


#include "TargetDialog.h"

TargetDialog::TargetDialog(wxWindow* parent) :
	GUITargetDialog(parent)
{
}

TargetDialog::~TargetDialog()
{
}

void TargetDialog::OnClose(wxCommandEvent& event)
{
	Close();
}
void TargetDialog::InsertProject(Project *project)
{
	linkedProject = project;


	//linkedProject->Distance.GetOtherName()


	TransferDataToWindow();
}

bool TargetDialog::TransferDataToWindow(void)
{
	Unit temp = linkedProject->Distance;

	m_textCtrlSliceThickness->SetValue(wxString::Format(_T("%.1f"),
			temp.FromSI(linkedProject->stock.stockMaterials[0].sz)));

	m_textCtrlSliceNumber->SetValue(wxString::Format(_T("%i"), (int) ceil(
			linkedProject->objects[linkedProject->activeObject].bbox.GetSizeZ()
					/ linkedProject->stock.stockMaterials[0].sz)));

	m_textCtrlSlotWidth->SetValue(wxString::Format(_T("%.1f"), temp.FromSI(
			linkedProject->slotWidth)));

	m_textCtrlSupportDistance->SetValue(wxString::Format(_T("%.1f"),
			temp.FromSI(linkedProject->supportDistance)));

	m_textCtrlSupportWidth->SetValue(wxString::Format(_T("%.1f"), temp.FromSI(
			linkedProject->supportWidth)));

	m_textCtrlSupportHeight->SetValue(wxString::Format(_T("%.1f"), temp.FromSI(
			linkedProject->supportHeight)));

	return true;
}
bool TargetDialog::TransferDataFromWindow(void)
{

	return true;
}

void TargetDialog::OnFromStock(wxCommandEvent& event)
{
	TransferDataFromWindow();
//	linkedProject->stock.stockMaterials[0].sz
//			= linkedProject->stock.stockMaterials[linkedProject->activeStock].sz;
	TransferDataToWindow();
}

void TargetDialog::OnGenerate(wxCommandEvent& event)
{
	linkedProject->GenerateTargets();
	this->GetParent()->Refresh();

}
