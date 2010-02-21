/*
 * MainFrame.cpp
 *
 *  Created on: 18.09.2009
 *      Author: toby
 */
#include "MainFrame.h"

MainFrame::MainFrame(wxWindow* parent) :
	MainFrameGui(parent)
{
	cogShift = 0;
	takeFrom = 0;
}

MainFrame::~MainFrame()
{

}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxString temp;
	temp.Append(_T("Generic Gear Game Version "));
	temp.Append(_T(_GEARGAME_VERSION));
	temp.Append(_T("\n"));
	temp.Append(_T(_GEARGAME_AUTHORS));
	temp.Append(_T(", 2009."));
	wxMessageBox(temp, _("About Gear Game"), wxOK | wxICON_INFORMATION, this);

}

void MainFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void MainFrame::OnNew(wxCommandEvent& event)
{
	engine.mainField.InitField();
	Refresh();
	Update();
}

float DistanceBetweenGears(wxSize &sz)
{
	int mx = sz.GetWidth();
	int my = sz.GetHeight();
	int s = (mx < my)? mx : my;
	return (float) s / 12;
}

wxPoint GearPos(unsigned int nr, wxSize &sz)
{
	int i, j;
	i = nr / 10;
	j = nr % 10;

	int mx = sz.GetWidth();
	int my = sz.GetHeight();
	mx /= 2;
	my /= 2;

	float d = DistanceBetweenGears(sz);

	wxPoint temp(0, 0);

	if(j < 10 - i){
		temp.x = mx + ((float) j + (float) i / 2 - 4.5) * d;
		temp.y = my - ((float) i - 4.5) * d * sqrt(3) / 2;
	}
	return temp;
}

void DrawCog(wxPaintDC &dc, wxPoint &p, float d, float shift)
{

	wxPoint g[18];
	unsigned char i;
	for(i = 0; i < 9; i++){
		g[i * 2 + 0].x = cos(M_PI / 9 * (i * 2 + 0) + shift) * d / 5 * 3;
		g[i * 2 + 0].y = sin(M_PI / 9 * (i * 2 + 0) + shift) * d / 5 * 3;
		g[i * 2 + 1].x = cos(M_PI / 9 * (i * 2 + 1) + shift) * d / 5 * 2;
		g[i * 2 + 1].y = sin(M_PI / 9 * (i * 2 + 1) + shift) * d / 5 * 2;
	}
	dc.DrawPolygon(18, g, p.x, p.y);
}

void MainFrame::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	wxSize sz = GetClientSize();

	dc.SetPen(*wxBLACK_PEN);

	float d = DistanceBetweenGears(sz);

	int i;
	wxPoint temp;
	wxString text;
	wxBrush gold(wxColor(255, 255, 128), wxSOLID);

	wxBrush blueSpecial(*wxBLUE, wxBDIAGONAL_HATCH);
	wxBrush redSpecial(*wxRED, wxBDIAGONAL_HATCH);

	dc.SetTextForeground(wxColor(255, 255, 255));
	wxFont font(d / 3, wxFONTFAMILY_SWISS, wxNORMAL, wxBOLD);
	dc.SetFont(font);

	float shift;
	for(i = 0; i < 100; i++){
		temp = GearPos(i, sz);
		if(temp.x != 0 || temp.y != 0){
			shift = 0;
			if(engine.mainField.TurnsRight(i)) shift += cogShift;
			if(engine.mainField.TurnsLeft(i)) shift -= cogShift;

			if(engine.mainField.HasGoldCog(i)){
				dc.SetBrush(gold);
				DrawCog(dc, temp, d, shift);
				dc.SetBrush(*wxBLACK_BRUSH);
				dc.DrawCircle(temp, d / 6);
			}
			if(engine.mainField.HasRedCog(i)){
				if(i == takeFrom && i != 0){
					dc.SetBrush(redSpecial);
				}else{
					dc.SetBrush(*wxRED_BRUSH);
				}
				DrawCog(dc, temp, d, shift);
				dc.SetBrush(*wxBLACK_BRUSH);
				dc.DrawCircle(temp, d / 6);
			}
			if(engine.mainField.HasBlueCog(i)){
				if(i == takeFrom && i != 0){
					dc.SetBrush(blueSpecial);
				}else{
					dc.SetBrush(*wxBLUE_BRUSH);
				}
				DrawCog(dc, temp, d, shift);
				dc.SetBrush(*wxBLACK_BRUSH);
				dc.DrawCircle(temp, d / 6);
			}

			dc.SetBrush(*wxLIGHT_GREY_BRUSH);
			dc.DrawCircle(temp, d / 7);
		}


		//		text.Empty();
		//		if(engine.mainField[i] & FIELD_LEFT) text += _T("L");
		//		if(engine.mainField[i] & FIELD_RIGHT) text += _T("R");
		//		if(engine.mainField[i] & FIELD_CONNECTEDWITHBLUE) text += _T("1");
		//		if(engine.mainField[i] & FIELD_CONNECTEDWITHRED) text += _T("2");
		//		if(engine.mainField[i] & FIELD_CONNECTEDWITHGOLD) text += _T("3");
		//
		//
		//
		//		dc.DrawText(text, temp.x, temp.y);

	}


	//	text = wxString::Format(_T("%u Zahnräder übrig"), 0);
	//	dc.DrawText(text, 10, 10);
}

void MainFrame::OnMotion(wxMouseEvent& event)
{

}

void MainFrame::Animate(void)
{
	float i;
	for(i = 0; i < 2*M_PI; i += M_PI / 20){
		cogShift = i;
		Refresh();
		Update();
		wxMilliSleep(10);
	}
}

void MainFrame::OnLeftDown(wxMouseEvent& event)
{
	unsigned char i;
	wxPoint temp;
	float x;
	wxSize sz = GetClientSize();
	float d = DistanceBetweenGears(sz);

	for(i = 0; i < 100; i++){
		temp = GearPos(i, sz);
		if(temp.x != 0 || temp.y != 0){
			temp -= event.GetPosition();
			x = sqrt(temp.x * temp.x + temp.y * temp.y);

			if(x < d / 3){

				if(engine.mainField.CanGrab(i, FIELD_BLUE)){
					takeFrom = i;

				}else{
					if(engine.mainField.CheckMove(takeFrom * 100 + i,
							FIELD_BLUE)){
						engine.mainField.DoMove(takeFrom * 100 + i, FIELD_BLUE);
						Animate();
						engine.FindNextMove();
						Animate();
					}
					takeFrom = 0;
				}
				m_statusBar->SetStatusText(wxString::Format(
						_T("Blau = %.2f Rot = %.2f"),
						engine.mainField.heuristicForActive,
						engine.mainField.heuristicForPassive));
				Refresh();
				Update();
			}
		}
	}
}
