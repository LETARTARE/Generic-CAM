///////////////////////////////////////////////////////////////////////////////
// Name               : ToolBox.cpp
// Purpose            : Holds a collection of tools.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 16.03.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "ToolBox.h"

#include <exception>

#include "JSON.h"

ToolBox::ToolBox()
{
	isLoaded = false;
}

ToolBox::~ToolBox()
{
}

bool ToolBox::Load(void)
{
	if(filename.empty()) return false;
	if(isLoaded) return false;
	return this->Load(filename);
}

bool ToolBox::Load(std::string filename)
{
	JSON js;
	try{
		js.Load(filename);
	}
	catch(std::exception &x){
		std::cout << x.what() << "\n";
		return false;
	}
	if(!js.IsKey("data")) return false;
	const JSON & toolarray = js["data"];
	if(!toolarray.IsArray()) return false;
	tools.clear();
	tools.resize(toolarray.Size());
	for(size_t n = 0; n < toolarray.Size(); ++n){
		const JSON &tool = toolarray[n];
		LoadContour(tools[n].base, tool);
		if(tool.IsKey("GRADE")) tools[n].GRADE = tool["GRADE"].GetString();
		if(tool.IsKey("BMC")) tools[n].BMC = tool["BMC"].GetString();
		if(tool.IsKey("last_modified")) tools[n].lastmodified =
				tool["last_modified"].GetNumber();
		if(tool.IsKey("addtonewprojects")) tools[n].addtonewprojects =
				tool["addtonewprojects"].GetBool();
		if(tool.IsKey("geometry")){
			tools[n].hasGeometry = true;
			const JSON & geometry = tool["geometry"];

			if(geometry.IsKey("CSP")) tools[n].geometry.CSP =
					geometry["CSP"].GetBool();
			if(geometry.IsKey("DC")) tools[n].geometry.DC =
					geometry["DC"].GetNumber();
			if(geometry.IsKey("HAND")) tools[n].geometry.HAND =
					geometry["HAND"].GetBool();
			if(geometry.IsKey("LB")) tools[n].geometry.LB =
					geometry["LB"].GetNumber();
			if(geometry.IsKey("LCF")) tools[n].geometry.LCF =
					geometry["LCF"].GetNumber();
			if(geometry.IsKey("NOF")) tools[n].geometry.NOF =
					geometry["NOF"].GetNumber();
			if(geometry.IsKey("NT")) tools[n].geometry.NT =
					geometry["NT"].GetNumber();
			if(geometry.IsKey("OAL")) tools[n].geometry.OAL =
					geometry["OAL"].GetNumber();
			if(geometry.IsKey("RE")) tools[n].geometry.RE =
					geometry["RE"].GetNumber();
			if(geometry.IsKey("SFDM")) tools[n].geometry.SFDM =
					geometry["SFDM"].GetNumber();
			if(geometry.IsKey("SIG")) tools[n].geometry.SIG =
					geometry["SIG"].GetNumber();
			if(geometry.IsKey("TA")) tools[n].geometry.TA =
					geometry["TA"].GetNumber();
			if(geometry.IsKey("TP")) tools[n].geometry.TP =
					geometry["TP"].GetNumber();
			if(geometry.IsKey("shoulder-length")) tools[n].geometry.shoulderlength =
					geometry["shoulder-length"].GetNumber();
			if(geometry.IsKey("thread-profile-angle")) tools[n].geometry.threadprofileangle =
					geometry["thread-profile-angle"].GetNumber();
			if(geometry.IsKey("tip-diameter")) tools[n].geometry.tipdiameter =
					geometry["tip-diameter"].GetNumber();
			if(geometry.IsKey("tip-length")) tools[n].geometry.tiplength =
					geometry["tip-length"].GetNumber();
			if(geometry.IsKey("tip-offset")) tools[n].geometry.tipoffset =
					geometry["tip-offset"].GetNumber();
		}
		if(tool.IsKey("holder")){
			tools[n].hasHolder = true;
			LoadContour(tools[n].holder, tool["holder"]);
		}
		if(tool.IsKey("shaft")){
			tools[n].hasShaft = true;
			LoadContour(tools[n].shaft, tool["shaft"]);
		}
		if(tool.IsKey("start-values") && tool["start-values"].Size() > 0){
			tools[n].hasStartValues = true;
			const JSON & sv = tool["start-values"].Begin();
			if(sv.IsKey("name")) tools[n].startvalues.name =
					sv["name"].GetString();
			if(sv.IsKey("guid")) tools[n].startvalues.guid =
					sv["guid"].GetString();
			if(sv.IsKey("description")) tools[n].startvalues.description =
					sv["description"].GetString();
			if(sv.IsKey("tool-coolant")) tools[n].startvalues.toolcoolant =
					sv["tool-coolant"].GetString();
			if(sv.IsKey("f_n")) tools[n].startvalues.fn = sv["f_n"].GetNumber();
			if(sv.IsKey("f_z")) tools[n].startvalues.fz = sv["f_z"].GetNumber();
			if(sv.IsKey("n")) tools[n].startvalues.n = sv["n"].GetNumber();
			if(sv.IsKey("n_ramp")) tools[n].startvalues.nramp =
					sv["n_ramp"].GetNumber();
			if(sv.IsKey("v_c")) tools[n].startvalues.vc = sv["v_c"].GetNumber();
			if(sv.IsKey("v_f")) tools[n].startvalues.vf = sv["v_f"].GetNumber();
			if(sv.IsKey("v_f_leadIn")) tools[n].startvalues.vfleadin =
					sv["v_f_leadIn"].GetNumber();
			if(sv.IsKey("v_f_leadOut")) tools[n].startvalues.vfleadout =
					sv["v_f_leadOut"].GetNumber();
			if(sv.IsKey("v_f_plunge")) tools[n].startvalues.vfplunge =
					sv["v_f_plunge"].GetNumber();
			if(sv.IsKey("v_f_ramp")) tools[n].startvalues.vframp =
					sv["v_f_ramp"].GetNumber();
			if(sv.IsKey("v_f_retract")) tools[n].startvalues.vfretract =
					sv["v_f_retract"].GetNumber();
		}
		if(tool.IsKey("post-process")){
			tools[n].hasPostProcess = true;
			const JSON & pp = tool["post-process"];

			if(pp.IsKey("break-control")) tools[n].postprocess.breakcontrol =
					pp["break-control"].GetBool();
			if(pp.IsKey("comment")) tools[n].postprocess.comment =
					pp["comment"].GetString();
			if(pp.IsKey("diameter-offset")) tools[n].postprocess.diameteroffset =
					pp["diameter-offset"].GetNumber();
			if(pp.IsKey("length-offset")) tools[n].postprocess.lengthoffset =
					pp["length-offset"].GetNumber();

			if(pp.IsKey("live")) tools[n].postprocess.live =
					pp["live"].GetBool();
			if(pp.IsKey("manual-tool-change")) tools[n].postprocess.manualtoolchange =
					pp["manual-tool-change"].GetBool();
			if(pp.IsKey("number")) tools[n].postprocess.number =
					pp["number"].GetNumber();
			if(pp.IsKey("turret")) tools[n].postprocess.turret =
					pp["turret"].GetNumber();
			if(pp.IsKey("tool-coolant")) tools[n].postprocess.toolcoolant =
					pp["tool-coolant"].GetString();
		}
		tools[n].ConvertToSI();
		tools[n].Update();
	}
	isLoaded = true;
	return true;
}

void ToolBox::LoadContour(Tool::Contour & contour, const JSON & json)
{
	if(json.IsKey("description")) contour.description =
			json["description"].GetString();
	if(json.IsKey("guid")) contour.guid = json["guid"].GetString();
	if(json.IsKey("vendor")) contour.vendor = json["vendor"].GetString();
	if(json.IsKey("product-id")) contour.productid =
			json["product-id"].GetString();
	if(json.IsKey("product-link")) contour.productlink =
			json["product-link"].GetString();
	if(json.IsKey("type")){
		std::string type = json["type"].GetString();
		contour.type = Tool::no_type;
		if(type.compare("flat end mill") == 0) contour.type =
				Tool::flat_end_mill;
		if(type.compare("radius mill") == 0) contour.type = Tool::radius_mill;
		if(type.compare("camfer mill") == 0) contour.type = Tool::camfer_mill;
		if(type.compare("bull nose end mill") == 0) contour.type =
				Tool::bull_nose_end_mill;
		if(type.compare("ball end mill") == 0) contour.type =
				Tool::ball_end_mill;
		if(type.compare("holder") == 0) contour.type = Tool::tool_holder;
		if(type.compare("shaft") == 0) contour.type = Tool::tool_shaft;
		if(type.compare("probe") == 0) contour.type = Tool::probe;
	}
	if(json.IsKey("unit")){
		std::string unit = json["unit"].GetString();
		contour.unit = Tool::unit_none;
		if(unit.compare("inches") == 0) contour.unit = Tool::unit_inch;
		if(unit.compare("millimeters") == 0) contour.unit =
				Tool::unit_millimeter;
		if(unit.compare("meters") == 0) contour.unit = Tool::unit_SI;
		if(unit.compare("inch") == 0) contour.unit = Tool::unit_inch;
		if(unit.compare("millimeter") == 0) contour.unit =
				Tool::unit_millimeter;
		if(unit.compare("meter") == 0) contour.unit = Tool::unit_SI;
	}
	if(json.IsKey("segments")){
		contour.hasSegments = true;
		const JSON & segments = json["segments"];
		contour.segments.resize(segments.Size());
		for(size_t m = 0; m < segments.Size(); ++m){
			const JSON & segment = segments[m];
			if(segment.IsKey("height")) contour.segments[m].height =
					segment["height"].GetNumber();
			if(segment.IsKey("lower-diameter")) contour.segments[m].lowerdiameter =
					segment["lower-diameter"].GetNumber();
			if(segment.IsKey("upper-diameter")) contour.segments[m].upperdiameter =
					segment["upper-diameter"].GetNumber();
		}
	}else{
		contour.hasSegments = false;
	}
}

//void ToolBox::SaveJSON(std::string filename) const
//{
//}

size_t ToolBox::Size(void) const
{
	return tools.size();
}

Tool& ToolBox::operator [](size_t index)
{
	return tools.at(index);
}

const Tool& ToolBox::operator [](size_t index) const
{
	return tools.at(index);
}

std::string ToolBox::GetName(void) const
{
	const size_t n = filename.find_last_of("/\\");
	if(n == std::string::npos) return std::string("");
	const size_t m = filename.find_last_of(".");
	if(m == std::string::npos) return filename.substr(n + 1);
	return filename.substr(n + 1, m - n - 1);
}

bool ToolBox::IsLoaded(void) const
{
	return isLoaded;
}
