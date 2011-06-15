///////////////////////////////////////////////////////////////////////////////
// Name               : StockFrame.cpp
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


#include "StockFrame.h"

StockFrame::StockFrame(wxWindow* parent) :
	GUIStockFrame(parent)
{
	linkedStock = NULL;
	selectedStockMaterial = 0;

}

StockFrame::~StockFrame()
{
}
void StockFrame::OnClose(wxCommandEvent& event)
{
	Close();
}

void StockFrame::InsertStock(ArrayOfStockMaterial& stock)
{
	linkedStock = &stock;

	UpdateDisplay();
}

void StockFrame::UpdateDisplay(bool direction)
{
	if(linkedStock == NULL) return;

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
	for(i = 0; i < linkedStock->GetCount(); i++){

		m_listCtrl->InsertItem(i, linkedStock->Item(i).materialName);
		m_listCtrl->SetItem(i, 1, wxString::Format(_T("%f"), linkedStock->Item(
				i).x));
		m_listCtrl->SetItem(i, 2, wxString::Format(_T("%f"), linkedStock->Item(
				i).y));
		m_listCtrl->SetItem(i, 3, wxString::Format(_T("%f"), linkedStock->Item(
				i).z));
		m_listCtrl->SetItem(i, 4, wxString::Format(_T("%f"), linkedStock->Item(
				i).maxSpeed));
		m_listCtrl->SetItem(i, 5, wxString::Format(_T("%f"), linkedStock->Item(
				i).maxFeedrate));

	}

	if(linkedStock->GetCount() < selectedStockMaterial - 1) return;

}
