///////////////////////////////////////////////////////////////////////////////
// Name               : DialogStockMaterial.cpp
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


#include "DialogStockMaterial.h"

DialogStockMaterial::DialogStockMaterial(wxWindow* parent) :
GUIStockMaterial(parent)
{
	linkedProject = NULL;
	selectedStockMaterial = 0;

}

DialogStockMaterial::~DialogStockMaterial()
{
}
void DialogStockMaterial::OnClose(wxCommandEvent& event)
{
	Close();
}

void DialogStockMaterial::InsertProject(Project* project)
{
	linkedProject = project;

	TransferDataToWindow();
}

bool DialogStockMaterial::TransferDataToWindow(void)
{
	if(linkedProject == NULL) return false;

	ArrayOfStockMaterial* temp = &(linkedProject->stock.stockMaterials);

	wxSize sz = m_listCtrl->GetClientSize();
	unsigned int w = sz.x / 10;
	m_listCtrl->ClearAll();

	m_listCtrl->InsertColumn(1, _("Name"), wxLIST_FORMAT_LEFT, 3* w );
	m_listCtrl->InsertColumn(2, _("X"), wxLIST_FORMAT_LEFT, 1* w );
	m_listCtrl->InsertColumn(3, _("Y"), wxLIST_FORMAT_LEFT, 1* w );
	m_listCtrl->InsertColumn(4, _("Z"), wxLIST_FORMAT_LEFT, 1* w );
	m_listCtrl->InsertColumn(5, _("max. Speed"), wxLIST_FORMAT_LEFT, 2* w );
	m_listCtrl->InsertColumn(6, _("max. Feedrate"), wxLIST_FORMAT_LEFT, 2* w );

	size_t i;
	for(i = 0; i < temp->GetCount(); i++){

		m_listCtrl->InsertItem(i, temp->Item(i).materialName);
		m_listCtrl->SetItem(i, 1, wxString::Format(_T("%f"), temp->Item(i).sx));
		m_listCtrl->SetItem(i, 2, wxString::Format(_T("%f"), temp->Item(i).sy));
		m_listCtrl->SetItem(i, 3, wxString::Format(_T("%f"), temp->Item(i).sz));
		m_listCtrl->SetItem(i, 4, wxString::Format(_T("%f"),
				temp->Item(i).maxSpeed));
		m_listCtrl->SetItem(i, 5, wxString::Format(_T("%f"),
				temp->Item(i).maxFeedrate));

	}

	return true;

}
bool DialogStockMaterial::TransferDataFromWindow(void)
{

	return true;
}

