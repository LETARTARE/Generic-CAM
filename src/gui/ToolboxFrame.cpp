//============================================================================
// Name        : ToolboxFrame.cpp
// Author      : Tobias Schaefer
// Version     : 0.1
// Created on  : 14.03.2010
// Copyright   : (c) 2010
// Description : CAM Software
//============================================================================


#include "ToolboxFrame.h"

ToolboxFrame::ToolboxFrame(wxWindow* parent) :
	GUIToolboxFrame(parent)
{
	linkedToolbox = NULL;
	selectedTool = 0;
	selectedElement = 0;

	m_menuSettings->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
}

ToolboxFrame::~ToolboxFrame()
{
}

void ToolboxFrame::OnClose(wxCommandEvent &event)
{
	Close();
}

void ToolboxFrame::SetController(Control3D* control)
{
	m_canvas->SetController(control);
}

void ToolboxFrame::OnChangeStereo3D(wxCommandEvent &event)
{
	if(m_canvas->stereoMode == 1){
		m_canvas->stereoMode = 0;
	}else{
		m_canvas->stereoMode = 1;
	}
	m_menuSettings->Check(wxID_VIEWSTEREO3D, m_canvas->stereoMode == 1);
}

void ToolboxFrame::InsertToolBox(Toolbox* toolbox)
{
	linkedToolbox = toolbox;

	UpdateDisplay();

}

void ToolboxFrame::UpdateDisplay(void)
{
	if(linkedToolbox == NULL) return;

	unsigned int i, j;

	m_comboBoxToolSelector->Clear();
	for(i = 0; i < linkedToolbox->tools.Count(); i++){
		m_comboBoxToolSelector->Append(linkedToolbox->tools[i].toolName);
	}
	m_comboBoxToolSelector->Select(selectedTool);

	if(selectedTool < linkedToolbox->tools.Count()){
		m_panel->InsertTool(&(linkedToolbox->tools[selectedTool]));
		m_canvas->InsertTool(&(linkedToolbox->tools[selectedTool]));
	}

	if(selectedTool < linkedToolbox->tools.Count()){
		m_textCtrlShaftDiameter->SetValue(wxString::Format(_T("%f"),
				linkedToolbox->tools[selectedTool].shaftDiameter));
		m_textCtrlShaftLength->SetValue(wxString::Format(_T("%f"),
				linkedToolbox->tools[selectedTool].shaftLength));
		m_textCtrlMaxSpeed->SetValue(wxString::Format(_T("%.0f"),
				linkedToolbox->tools[selectedTool].maxSpeed));
		m_textCtrlFeedCoefficient->SetValue(wxString::Format(_T("%f"),
				linkedToolbox->tools[selectedTool].feedCoefficient));
		m_textCtrlNrOfTeeth->SetValue(wxString::Format(_T("%u"),
				linkedToolbox->tools[selectedTool].nrOfTeeth));
		m_textCtrlComment->SetValue(linkedToolbox->tools[selectedTool].comment);

		wxSize sz = m_listCtrl->GetClientSize();
		unsigned int w = sz.x / 14;
		m_listCtrl->ClearAll();
		m_listCtrl->InsertColumn(0, _T("Type"), wxLIST_FORMAT_LEFT, 2* w );
		m_listCtrl->InsertColumn(1, _T("Diameter"), wxLIST_FORMAT_LEFT, 3* w );
		m_listCtrl->InsertColumn(2, _T("height"), wxLIST_FORMAT_LEFT, 3* w );
		m_listCtrl->InsertColumn(3, _T("Radius"), wxLIST_FORMAT_LEFT, 3* w );
		m_listCtrl->InsertColumn(4, _T("Cutting"), wxLIST_FORMAT_LEFT, 3* w );

		for(j = 0; j < linkedToolbox->tools[selectedTool].elements.Count(); j++){

			wxLogMessage(wxString::Format(_T("Element: %u Type %u"), j,
					linkedToolbox->tools[selectedTool].elements[j].t));

			switch(linkedToolbox->tools[selectedTool].elements[j].t){
			case 0:
				m_listCtrl->InsertItem(j, _T("L"));
				break;
			case 1:
				m_listCtrl->InsertItem(j, _T("CDH"));
				break;
			case 2:
				m_listCtrl->InsertItem(j, _T("CHD"));
				break;
			case 3:
				m_listCtrl->InsertItem(j, _T("SRU"));
				break;
			case 4:
				m_listCtrl->InsertItem(j, _T("SRL"));
				break;
			}

			m_listCtrl->SetItem(j, 1, wxString::Format(_T("%f"),
					linkedToolbox->tools[selectedTool].elements[j].d));
			m_listCtrl->SetItem(j, 2, wxString::Format(_T("%f"),
					linkedToolbox->tools[selectedTool].elements[j].h));
			m_listCtrl->SetItem(j, 3, wxString::Format(_T("%f"),
					linkedToolbox->tools[selectedTool].elements[j].r));

			if(linkedToolbox->tools[selectedTool].elements[j].cutting){
				m_listCtrl->SetItem(j, 4, _T("yes"));
			}else{
				m_listCtrl->SetItem(j, 4, _T("no"));
			}

			m_listCtrl->SetItemState(j, 0, wxLIST_STATE_SELECTED);

			if(selectedElement
					< linkedToolbox->tools[selectedTool].elements.Count()){

				m_listCtrl->SetItemState(selectedElement,
						wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);

				m_choiceType->Select(
						linkedToolbox->tools[selectedTool].elements[selectedElement].t);

				m_textCtrlDiameter->SetValue(
						wxString::Format(
								_T("%f"),
								linkedToolbox->tools[selectedTool].elements[selectedElement].d));
				m_textCtrlHeight->SetValue(
						wxString::Format(
								_T("%f"),
								linkedToolbox->tools[selectedTool].elements[selectedElement].h));
				m_textCtrlRadius->SetValue(
						wxString::Format(
								_T("%f"),
								linkedToolbox->tools[selectedTool].elements[selectedElement].r));

				m_checkBoxCutting ->SetValue(
						linkedToolbox->tools[selectedTool].elements[selectedElement].cutting);

			}
		}
	}
}
