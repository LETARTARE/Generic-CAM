///////////////////////////////////////////////////////////////////////////////
// Name               : DialogTestGCode.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 12.07.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "DialogTestGCode.h"

#include "../project/generator/GCodeBlock.h"
#include <float.h>

#include "FrameMain.h"
#include "FrameParent.h"

DialogTestGCode::DialogTestGCode(wxWindow* parent) :
		GUITestGCode(parent)
{
	m_textCtrlInput->SetFocus();
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
	CollectionUnits* settings = &(frame->GetParentFrame()->units);
	wxString temp = settings->Distance.GetOtherName();
	if(temp.Cmp(_T("in")) == 0 || temp.Cmp(_T("ft")) == 0){
		m_radioBtnG20->SetValue(true);
		m_radioBtnG21->SetValue(false);
	}else{
		m_radioBtnG20->SetValue(false);
		m_radioBtnG21->SetValue(true);
	}
}

DialogTestGCode::~DialogTestGCode()
{
}

void DialogTestGCode::OnText(wxCommandEvent& event)
{
	TransferDataToWindow();
}

bool DialogTestGCode::TransferDataToWindow(void)
{
	FrameMain * frame = wxStaticCast(GetParent(), FrameMain);
//	Project* project = wxStaticCast(frame->GetDocument(), Project);
//	wxCommandProcessor * cmdProc = frame->GetDocument()->GetCommandProcessor();
	CollectionUnits* settings = &(frame->GetParentFrame()->units);
	double cf = 0.0;
	if(m_radioBtnG20->GetValue()) cf = 0.0254;
	if(m_radioBtnG21->GetValue()) cf = 0.001;

	GCodeBlock temp(std::string(m_textCtrlInput->GetValue().mb_str()), cf);
	if(!temp.error.empty()){
		m_textCtrlOutput->SetValue(temp.error);
		return true;
	}
	if(temp.G[6] == 200 || temp.G[6] == 210){
		if(temp.G[6] == 200) cf = 0.0254;
		if(temp.G[6] == 210) cf = 0.001;
		temp = GCodeBlock(std::string(m_textCtrlInput->GetValue().mb_str()),
				cf);
	}

	wxString out;
	if(!temp.Comment.empty()){
		if(temp.message){
			out = _("Message: ") + temp.Comment + "\n";
		}else{
			out = _("Comment: ") + temp.Comment + "\n";
		}
	}
	if(temp.block_delete) out += _("Block-delete possible for this block.\n");
	if(temp.N >= 0) out += wxString::Format(_("N (line number): %i\n"),
			temp.N);
	if(temp.F >= -FLT_EPSILON) out +=
			_("F (feed rate): ") + settings->LinearSpeed.TextFromSIWithUnit(temp.F)+ "\n";
	if(temp.S >= -FLT_EPSILON) out +=
			_("S (spindle speed): ") + settings->RotationalSpeed.TextFromSIWithUnit(temp.S)+ "\n";

	if(temp.T >= 0) out += wxString::Format(_("T (tool for selection): %i\n"),
			temp.T);
	if(temp.D >= 0) out += wxString::Format(
			_("D (tool for compensation): %i\n"), temp.D);
	if(temp.H >= 0) out += wxString::Format(
			_("H (tool for length offset): %i\n"), temp.H);
	if(temp.L >= 0) out += wxString::Format(_("L (cycle loop count): %i\n"),
			temp.L);
	if(temp.P >= -FLT_EPSILON) out += wxString::Format(
			_("P (parameter): %g\n"), temp.P);
	if(temp.Q >= -FLT_EPSILON) out +=
			_("Q (peck increment): ") + settings->SmallDistance.TextFromSIWithUnit(temp.Q)+ "\n";

	for(unsigned char n = 0; n < 15; n++){

		if(temp.G[n] < 0) continue;
		switch(n){
		case 0:
			out += _("Non-Modal:\n   ");
			break;
		case 1:
			out += _("Motion:\n   ");
			break;
		case 2:
			out += _("Plane Selection:\n   ");
			break;
		case 3:
			out += _("Distance Mode:\n   ");
			break;
		case 5:
			out += _("Feedrate Mode:\n   ");
			break;
		case 6:
			out += _("Units:\n   ");
			break;
		case 7:
			out += _("Cutter Radius Compensation:\n   ");
			break;
		case 8:
			out += _("Tool Length Offset:\n   ");
			break;
		case 10:
			out += _("Return Mode in Canned Cycles:\n   ");
			break;
		case 12:
			out += _("Coordinate System Selection:\n   ");
			break;
		case 13:
			out += _("Path Control Mode:\n   ");
			break;
		case 14:
			out += _("Extra:\n   ");
			break;
		default:
			out += _T("   ");
			break;
		}

		switch(temp.G[n]){
		case 0:
			out += _("G0 - Rapid Linear Motion\n");
			break;
		case 10:
			out += _("G1 - Linear Motion at Feed Rate\n");
			break;
		case 20:
			out += _("G2 - Arc at Feed Rate - Clockwise\n");
			break;
		case 30:
			out += _("G3 - Arc at Feed Rate - Counter-Clockwise\n");
			break;
		case 40:
			if(temp.P < 0){
				out += _("G4 - Dwell, but pause time is not set -> Error\n");
			}else{
				if(temp.P < 500){
					out +=
							wxString::Format(
									_("G4 - Dwell for %g s (maybe ms, check your machine's manual)\n"),
									temp.P);
				}else{
					out +=
							wxString::Format(
									_("G4 - Dwell for %g ms (maybe s, check your machine's manual)\n"),
									temp.P);
				}
			}
			break;
		case 100:
			if(temp.P < 0){
				out +=
						_("G10 - Set Coordinate System Data. P-number is missing -> Error\n");
			}else{
				if(temp.P >= 1 && temp.P <= 10){
					out += wxString::Format(
							_("G10 - Set Coordinate System Data for %g\n"),
							temp.P);
				}else{
					out +=
							wxString::Format(
									_("G10 - Set Coordinate System Data. P-number out of range (1-10) -> %g -> Error\n"),
									temp.P);
				}
			}
			break;
		case 170:
			out += _("G17 - Plane Selection: XY\n");
			break;
		case 180:
			out += _("G18 - Plane Selection: XZ\n");
			break;
		case 190:
			out += _("G19 - Plane Selection: YZ\n");
			break;
		case 200:
			out += _("G20 - Length Units: inches\n");
			break;
		case 210:
			out += _("G21 - Length Units: mm\n");
			break;
		case 280:
			out += _("G28 - Return to Home - 1st programmed position\n");
			break;
		case 300:
			out += _("G30 - Return to Home - 2nd programmed position\n");
			break;
		case 382:
			out += _("G38.2 - Straight Probe\n");
			break;

		case 400:
			out += _("G40 - Cutter Radius Compensation in XY plane\n");
			break;
		case 410:
			out += _("G41 - Cutter Radius Compensation in XZ plane\n");
			break;
		case 420:
			out += _("G42 - Cutter Radius Compensation in YZ plane\n");
			break;

		case 430:
			out += _("G43 - Tool Length Compensation: on\n");
			break;
		case 490:
			out += _("G49 - Tool Length Compensation: off\n");
			break;
		case 500:
			out += _("G50 - Cancel Scaling Function\n");
			break;
		case 530:
			out += _("G53 - Absolute Coordinate System (only in this block)\n");
			break;
		case 540:
			out += _("G54 - Select Coordinate System 1\n");
			break;
		case 550:
			out += _("G55 - Select Coordinate System 2\n");
			break;
		case 560:
			out += _("G56 - Select Coordinate System 3\n");
			break;
		case 570:
			out += _("G57 - Select Coordinate System 4\n");
			break;
		case 580:
			out += _("G58 - Select Coordinate System 5\n");
			break;
		case 590:
			out += _("G59 - Select Coordinate System 6\n");
			break;
		case 591:
			out += _("G59.1 - Select Coordinate System 7\n");
			break;
		case 592:
			out += _("G59.2 - Select Coordinate System 8\n");
			break;
		case 593:
			out += _("G59.3 - Select Coordinate System 9\n");
			break;

		case 610:
			out += _("G61 - Path Control Mode - exact path mode\n");
			break;
		case 611:
			out += _("G61.1 - Path Control Mode - exact stop mode\n");
			break;
		case 640:
			out += _("G64 - Path Control Mode - continuous mode\n");
			break;

		case 800:
			out += _("G80 - Cancel Modal Motion\n");
			break;

		case 810:
			out += _("G81 - Canned Cycle - drilling\n");
			break;
		case 820:
			out += _("G82 - Canned Cycle - drilling with pause\n");
			break;
		case 830:
			out +=_("G83 - Canned Cycle - peck drilling\n");
			break;
		case 840:
			out +=	_("G84 - Canned Cycle - right-hand tapping with a tap tool\n");
			break;
		case 850:
			out += _("G85 - Canned Cycle - boring or reaming\n");
			break;
		case 860:
			out += _("G86 - Canned Cycle - boring\n");
			break;
		case 870:
			out += _("G87 - Canned Cycle - back boring\n");
			break;
		case 880:
			out += _("G88 - Canned Cycle - boring with dwell\n");
			break;
		case 890:
			out += _("G89 - Canned Cycle - boring with dwell\n");
			break;

		case 900:
			out += _("G90 - Set Distance Mode - absolute distance mode\n");
			break;
		case 910:
			out += _("G91 - Set Distance Mode - incremental distance mode\n");
			break;
		case 912:
			out +=	_("G92 - Coordinate System Offsets - shift coordinate system\n");
			break;
		case 921:
			out +=	_("G92.1 - Coordinate System Offsets - reset coordinate system\n");
			break;
		case 922:
			out +=_("G92.2 - Coordinate System Offsets - reset coordinate system and parameters\n");
			break;
		case 923:
			out +=_("G92.3 - Coordinate System Offsets - restore coordinate system from parameters\n");
			break;

		case 930:
			out += _("G93 - Set Feed Rate Mode - units per minute mode\n");
			break;
		case 940:
			out +=_("G94 - Set Feed Rate Mode - inverse time mode (per minute feed)\n");
			break;
		case 980:
			out +=	_("G98 - Canned Cycle Return Level - retract to the start position of the cycle\n");
			break;
		case 990:
			out += _("G99 - Canned Cycle Return Level - retract to R\n");
			break;
		default:
			out += wxString::Format(_T("G%g - ?\n"),
					((double) temp.G[n]) / 10.0);
			break;
		}
	}

	for(unsigned char n = 0; n < 11; n++){
		if(temp.M[n] < 0) continue;

		switch(n){
		case 4:
			out += _("Stopping:\n   ");
			break;
		case 6:
			out += _("Tool Change:\n   ");
			break;
		case 7:
			out += _("Spindle Turning:\n   ");
			break;
		case 8:
			out += _("Coolant:\n   ");
			break;
		case 9:
			out += _("Override Switches:\n   ");
			break;
		default:
			out +="   ";
			break;
		}
		switch(temp.M[n]){

		case 0:
			out += _("M0 - Program Stop\n");
			break;
		case 1:
			out += _("M1 - Optional Program Stop\n");
			break;
		case 2:
			out += _("M2 - Program End\n");
			break;
		case 3:
			out += _("M3 - Turn Spindle Clockwise\n");
			break;
		case 4:
			out += _("M4 - Turn Spindle Counter-Clockwise\n");
			break;
		case 5:
			out += _("M5 - Stop Spindle Turning\n");
			break;
		case 6:
			out += _("M6 - Tool Change\n");
			break;
		case 7:
			out += _("M7 - Mist Coolant On\n");
			break;
		case 8:
			out += _("M8 - Flood Coolant On\n");
			break;
		case 9:
			out += _("M9 - Mist and Flood Coolant Off\n");
			break;
		case 30:
			out += _("M30 - Program End, Pallet Shuttle, and Reset\n");
			break;
		case 48:
			out += _("M48 - Enable Speed and Feed Overrides\n");
			break;
		case 49:
			out += _("M49 - Disable Speed and Feed Overrides\n");
			break;
		case 60:
			out += _("M60 - Pallet Shuttle and Program Stop\n");
			break;
		default:
			out += wxString::Format(_T("M%u - ?\n"), temp.M[n]);
			break;
		}
	}

	if(temp.XFlag) out += ("X: ") + settings->Distance.TextFromSIWithUnit(temp.X) + "\n";
	if(temp.YFlag) out += ("Y: ") + settings->Distance.TextFromSIWithUnit(temp.Y) + "\n";
	if(temp.ZFlag) out += ("Z: ") + settings->Distance.TextFromSIWithUnit(temp.Z) + "\n";
	if(temp.AFlag) out += ("A: ") + settings->Angle.TextFromSIWithUnit(temp.A) + "\n";
	if(temp.BFlag) out += ("B: ") + settings->Angle.TextFromSIWithUnit(temp.B) + "\n";
	if(temp.CFlag) out += ("C: ") + settings->Angle.TextFromSIWithUnit(temp.C) + "\n";
	if(temp.UFlag) out += ("U: ") + settings->Distance.TextFromSIWithUnit(temp.U) + "\n";

	if(temp.VFlag) out += ("V: ") + settings->Distance.TextFromSIWithUnit(temp.V) + "\n";
	if(temp.WFlag) out += ("W: ") + settings->Distance.TextFromSIWithUnit(temp.W) + "\n";
	if(temp.IFlag) out += ("I: ") + settings->Distance.TextFromSIWithUnit(temp.I) + "\n";
	if(temp.JFlag) out += ("J: ") + settings->Distance.TextFromSIWithUnit(temp.J) + "\n";
	if(temp.KFlag) out += ("K: ") + settings->Distance.TextFromSIWithUnit(temp.K) + "\n";
	if(temp.RFlag) out +=	_("R (radius): ") + settings->Distance.TextFromSIWithUnit(temp.X)+ "\n";

	m_textCtrlOutput->SetValue(out);
	setlocale(LC_ALL, "C"); // To get a 3.1415 instead 3,1415 or else on every computer.
	m_textCtrlRecreated->SetValue(temp.GetCode());
	setlocale(LC_ALL, "");
	return true;
}

void DialogTestGCode::OnClear(wxCommandEvent& event)
{
	m_textCtrlInput->SetValue(_T(""));
	m_textCtrlOutput->SetValue(_T(""));
	m_textCtrlRecreated->SetValue(_T(""));
}
