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
#include <fstream>
#include <iostream>

#include "../math/JSON.h"

ToolBox::ToolBox()
{
	isLoaded = false;
	version = 0;
}

ToolBox::~ToolBox()
{
}

bool ToolBox::Load(void)
{
	if(filename.empty()) return false;
	if(isLoaded) return false;
	return Load(filename);
}

bool ToolBox::Load(std::string filename)
{
	JSON js;
	try{
		js = JSON::Load(filename);
	}
	catch(std::exception &x){
		std::cout << x.what() << "\n";
		return false;
	}
	return ParseTools(js);
}

bool ToolBox::Load(std::istream& in)
{
	JSON js;
	try{
		js = JSON::Load(in);
	}
	catch(std::exception &x){
		std::cout << x.what() << "\n";
		return false;
	}
	return ParseTools(js);
}

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

void ToolBox::Save(std::string filename) const
{
	std::ofstream out;
	out.open(filename.c_str(), std::ofstream::out | std::ios::binary);
	Save(out);
}

void ToolBox::Save(std::ostream &out) const
{
	JSON js;
	StoreTools(js);
	js.Save(out);
}

bool ToolBox::ParseTools(const JSON &js)
{
	if(!js.HasKey("data")) return false;
	const JSON & toolarray = js["data"];
	if(!toolarray.IsArray()) return false;
	tools.clear();
	tools.resize(toolarray.Size());
	for(size_t n = 0; n < toolarray.Size(); ++n){
		const JSON &tool = toolarray[n];
		if(!ParseTool(tool, tools[n])) return false;
	}
	if(js.HasKey("version")) version = js["version"].GetNumber();
	isLoaded = true;
	return true;
}

bool ToolBox::ParseTool(const JSON& js, Tool& tool)
{
	ParseContour(js, tool.base);
	if(js.HasKey("GRADE")) tool.GRADE = js["GRADE"].GetString();
	if(js.HasKey("BMC")) tool.BMC = js["BMC"].GetString();
	if(js.HasKey("last_modified")) tool.lastmodified =
			js["last_modified"].GetNumber();
	if(js.HasKey("addtonewprojects")) tool.addtonewprojects =
			js["addtonewprojects"].GetBool();
	if(js.HasKey("geometry")){
		tool.hasGeometry = true;
		ParseGeometry(js["geometry"], tool.geometry);
	}
	if(js.HasKey("holder")){
		tool.hasHolder = true;
		ParseContour(js["holder"], tool.holder);
	}
	if(js.HasKey("shaft")){
		tool.hasShaft = true;
		ParseContour(js["shaft"], tool.shaft);
	}
	if(js.HasKey("start-values") && js["start-values"].IsObject()){
		size_t N = js["start-values"].Size();
		tool.startvalues.resize(N, Tool::StartValues());
		for(size_t n = 0; n < N; ++n){
			const JSON & sv = js["start-values"][n];
			ParseStartValues(sv, tool.startvalues[n]);
		}
	}
	if(js.HasKey("post-process")){
		tool.hasPostProcess = true;
		ParsePostProcess(js["post-process"], tool.postprocess);
	}
	tool.ConvertToSI();
	tool.Update();
	return true;
}

void ToolBox::ParseGeometry(const JSON& js, Tool::Geometry& ge)
{
	if(js.HasKey("CSP")) ge.CSP = js["CSP"].GetBool();
	if(js.HasKey("DC")) ge.DC = js["DC"].GetNumber();
	if(js.HasKey("HAND")) ge.HAND = js["HAND"].GetBool();
	if(js.HasKey("LB")) ge.LB = js["LB"].GetNumber();
	if(js.HasKey("LCF")) ge.LCF = js["LCF"].GetNumber();
	if(js.HasKey("NOF")) ge.NOF = js["NOF"].GetNumber();
	if(js.HasKey("NT")) ge.NT = js["NT"].GetNumber();
	if(js.HasKey("OAL")) ge.OAL = js["OAL"].GetNumber();
	if(js.HasKey("RE")) ge.RE = js["RE"].GetNumber();
	if(js.HasKey("SFDM")) ge.SFDM = js["SFDM"].GetNumber();
	if(js.HasKey("SIG")) ge.SIG = js["SIG"].GetNumber();
	if(js.HasKey("TA")) ge.TA = js["TA"].GetNumber();
	if(js.HasKey("TP")) ge.TP = js["TP"].GetNumber();
	if(js.HasKey("shoulder-length")) ge.shoulderlength =
			js["shoulder-length"].GetNumber();
	if(js.HasKey("thread-profile-angle")) ge.threadprofileangle =
			js["thread-profile-angle"].GetNumber();
	if(js.HasKey("tip-diameter")) ge.tipdiameter =
			js["tip-diameter"].GetNumber();
	if(js.HasKey("tip-length")) ge.tiplength = js["tip-length"].GetNumber();
	if(js.HasKey("tip-offset")) ge.tipoffset = js["tip-offset"].GetNumber();
}

void ToolBox::ParseStartValues(const JSON& js, Tool::StartValues& sv)
{
	if(js.HasKey("name")) sv.name = js["name"].GetString();
	if(js.HasKey("guid")) sv.guid = js["guid"].GetString();
	if(js.HasKey("description")) sv.description = js["description"].GetString();
	if(js.HasKey("tool-coolant")) sv.toolcoolant =
			js["tool-coolant"].GetString();
	if(js.HasKey("f_n")) sv.fn = js["f_n"].GetNumber();
	if(js.HasKey("f_z")) sv.fz = js["f_z"].GetNumber();
	if(js.HasKey("n")) sv.n = js["n"].GetNumber();
	if(js.HasKey("n_ramp")) sv.nramp = js["n_ramp"].GetNumber();
	if(js.HasKey("v_c")) sv.vc = js["v_c"].GetNumber();
	if(js.HasKey("v_f")) sv.vf = js["v_f"].GetNumber();
	if(js.HasKey("v_f_leadIn")) sv.vfleadin = js["v_f_leadIn"].GetNumber();
	if(js.HasKey("v_f_leadOut")) sv.vfleadout = js["v_f_leadOut"].GetNumber();
	if(js.HasKey("v_f_plunge")) sv.vfplunge = js["v_f_plunge"].GetNumber();
	if(js.HasKey("v_f_ramp")) sv.vframp = js["v_f_ramp"].GetNumber();
	if(js.HasKey("v_f_retract")) sv.vfretract = js["v_f_retract"].GetNumber();
}

void ToolBox::ParsePostProcess(const JSON& js, Tool::PostProcess& pp)
{
	if(js.HasKey("break-control")) pp.breakcontrol =
			js["break-control"].GetBool();
	if(js.HasKey("comment")) pp.comment = js["comment"].GetString();
	if(js.HasKey("diameter-offset")) pp.diameteroffset =
			js["diameter-offset"].GetNumber();
	if(js.HasKey("length-offset")) pp.lengthoffset =
			js["length-offset"].GetNumber();

	if(js.HasKey("live")) pp.live = js["live"].GetBool();
	if(js.HasKey("manual-tool-change")) pp.manualtoolchange =
			js["manual-tool-change"].GetBool();
	if(js.HasKey("number")) pp.number = js["number"].GetNumber();
	if(js.HasKey("turret")) pp.turret = js["turret"].GetNumber();
	if(js.HasKey("tool-coolant")) pp.toolcoolant =
			js["tool-coolant"].GetString();
}

void ToolBox::ParseContour(const JSON & js, Tool::Contour & contour)
{
	if(js.HasKey("description")) contour.description =
			js["description"].GetString();
	if(js.HasKey("guid")) contour.guid = js["guid"].GetString();
	if(js.HasKey("vendor")) contour.vendor = js["vendor"].GetString();
	if(js.HasKey("product-id")) contour.productid =
			js["product-id"].GetString();
	if(js.HasKey("product-link")) contour.productlink =
			js["product-link"].GetString();
	if(js.HasKey("type")){
		std::string type = js["type"].GetString();
		contour.type = Tool::no_type;
		if(type.compare("flat end mill") == 0) contour.type =
				Tool::flat_end_mill;
		if(type.compare("radius mill") == 0) contour.type = Tool::radius_mill;
		if(type.compare("camfer mill") == 0) contour.type = Tool::camfer_mill;
		if(type.compare("tapered mill") == 0) contour.type = Tool::tapered_mill;
		if(type.compare("bull nose end mill") == 0) contour.type =
				Tool::bull_nose_end_mill;
		if(type.compare("ball end mill") == 0) contour.type =
				Tool::ball_end_mill;

		if(type.compare("spot drill") == 0) contour.type = Tool::spot_drill;
		if(type.compare("counter sink") == 0) contour.type = Tool::counter_sink;

		if(type.compare("holder") == 0) contour.type = Tool::tool_holder;
		if(type.compare("shaft") == 0) contour.type = Tool::tool_shaft;
		if(type.compare("probe") == 0) contour.type = Tool::probe;
	}
	if(js.HasKey("unit")){
		std::string unit = js["unit"].GetString();
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
	if(js.HasKey("segments")){
		contour.hasSegments = true;
		const JSON & segments = js["segments"];
		contour.segments.resize(segments.Size());
		for(size_t m = 0; m < segments.Size(); ++m){
			const JSON & segment = segments[m];
			if(segment.HasKey("height")) contour.segments[m].height =
					segment["height"].GetNumber();
			if(segment.HasKey("lower-diameter")) contour.segments[m].lowerdiameter =
					segment["lower-diameter"].GetNumber();
			if(segment.HasKey("upper-diameter")) contour.segments[m].upperdiameter =
					segment["upper-diameter"].GetNumber();
		}
	}else{
		contour.hasSegments = false;
	}
}

void ToolBox::StoreGeometry(JSON& js, const Tool::Geometry& geometry) const
{
	js.SetObject(false);
	js["CSP"].SetBool(geometry.CSP);
	js["DC"].SetNumber(geometry.DC);
	js["HAND"].SetBool(geometry.HAND);
	js["LB"].SetNumber(geometry.LB);
	js["LCF"].SetNumber(geometry.LCF);
	js["NOF"].SetNumber(geometry.NOF);
	js["NT"].SetNumber(geometry.NT);
	js["OAL"].SetNumber(geometry.OAL);
	js["RE"].SetNumber(geometry.RE);
	js["SFDM"].SetNumber(geometry.SFDM);
	js["SIG"].SetNumber(geometry.SIG);
	js["TA"].SetNumber(geometry.TA);
	js["TP"].SetNumber(geometry.TP);
	js["shoulder-length"].SetNumber(geometry.shoulderlength);
	js["thread-profile-angle"].SetNumber(geometry.threadprofileangle);
	js["tip-diameter"].SetNumber(geometry.tipdiameter);
	js["tip-length"].SetNumber(geometry.tiplength);
	js["tip-offset"].SetNumber(geometry.tipoffset);
}

void ToolBox::StoreStartValues(JSON& js,
		const Tool::StartValues& startvalues) const
{
	js.SetObject(false);
	js["name"].SetString(startvalues.name);
	js["guid"].SetString(startvalues.guid);
	js["description"].SetString(startvalues.description);
	js["tool-coolant"].SetString(startvalues.toolcoolant);
	js["f_n"].SetNumber(startvalues.fn);
	js["f_z"].SetNumber(startvalues.fz);
	js["n"].SetNumber(startvalues.n);
	js["n_ramp"].SetNumber(startvalues.nramp);
	js["v_c"].SetNumber(startvalues.vc);
	js["v_f"].SetNumber(startvalues.vf);
	js["v_f_leadIn"].SetNumber(startvalues.vfleadin);
	js["v_f_leadOut"].SetNumber(startvalues.vfleadout);
	js["v_f_plunge"].SetNumber(startvalues.vfplunge);
	js["v_f_ramp"].SetNumber(startvalues.vframp);
	js["v_f_retract"].SetNumber(startvalues.vfretract);
}

void ToolBox::StorePostProcess(JSON& js,
		const Tool::PostProcess& postprocess) const
{
	js.SetObject(false);
	js["break-control"].SetBool(postprocess.breakcontrol);
	js["comment"].SetString(postprocess.comment);
	js["diameter-offset"].SetNumber(postprocess.diameteroffset);
	js["length-offset"].SetNumber(postprocess.lengthoffset);

	js["live"].SetBool(postprocess.live);
	js["manual-tool-change"].SetBool(postprocess.manualtoolchange);
	js["number"].SetNumber(postprocess.number);
	js["turret"].SetNumber(postprocess.turret);
	js["tool-coolant"].SetString(postprocess.toolcoolant);
}

void ToolBox::StoreTools(JSON& js) const
{
	js.SetObject();
	JSON & data = js["data"];
	data.SetArray(tools.size());
	for(size_t n = 0; n < tools.size(); ++n){
		JSON &tool = data[n];
		tool.SetObject();
		tool["GRADE"].SetString(tools[n].GRADE);
		tool["BMC"].SetString(tools[n].BMC);
		tool["last_modified"].SetNumber(tools[n].lastmodified);
		tool["addtonewprojects"].SetBool(tools[n].addtonewprojects);

		StoreContour(tool, tools[n].base);

		if(tools[n].hasGeometry) StoreGeometry(tool["geometry"],
				tools[n].geometry);
		if(tools[n].hasHolder) StoreContour(tool["holder"], tools[n].holder);
		if(tools[n].hasShaft) StoreContour(tool["shaft"], tools[n].shaft);

		if(!tools[n].startvalues.empty()){
			tool["start-values"].SetArray(tools[n].startvalues.size());
			for(size_t m = 0; m < tools[n].startvalues.size(); ++m)
				StoreStartValues(tool["start-values"][m],
						tools[n].startvalues[m]);
		}
		if(tools[n].hasPostProcess) StorePostProcess(tool["post-process"],
				tools[n].postprocess);
	}
	js["version"].SetNumber(version);
}

void ToolBox::StoreContour(JSON& js, const Tool::Contour& contour) const
{
	js.SetObject(false);
	js["description"].SetString(contour.description);
	js["guid"].SetString(contour.guid);
	js["vendor"].SetString(contour.vendor);
	js["product-id"].SetString(contour.productid);
	js["product-link"].SetString(contour.productlink);

	switch(contour.type){

	case Tool::flat_end_mill:
		js["type"].SetString("flat end mill");
		break;
	case Tool::radius_mill:
		js["type"].SetString("radius mill");
		break;
	case Tool::camfer_mill:
		js["type"].SetString("camfer mill");
		break;
	case Tool::tapered_mill:
		js["type"].SetString("tapered mill");
		break;
	case Tool::bull_nose_end_mill:
		js["type"].SetString("bull nose end mill");
		break;
	case Tool::ball_end_mill:
		js["type"].SetString("ball end mill");
		break;
	case Tool::spot_drill:
		js["type"].SetString("spot drill");
		break;
	case Tool::counter_sink:
		js["type"].SetString("counter sink");
		break;
	case Tool::tool_holder:
		js["type"].SetString("holder");
		break;
	case Tool::tool_shaft:
		js["type"].SetString("shaft");
		break;
	case Tool::probe:
		js["type"].SetString("probe");
		break;
	}

	switch(contour.unit){
	case Tool::unit_SI:
		js["unit"].SetString("meters");
		break;
	case Tool::unit_millimeter:
		js["unit"].SetString("millimeters");
		break;
	case Tool::unit_inch:
		js["unit"].SetString("inches");
		break;
	}

	if(contour.hasSegments){
		JSON & segments = js["segments"];
		segments.SetArray(contour.segments.size());
		for(size_t n = 0; n < contour.segments.size(); ++n){
			segments[n].SetObject();
			segments[n]["height"].SetNumber(contour.segments[n].height);
			segments[n]["lower-diameter"].SetNumber(
					contour.segments[n].lowerdiameter);
			segments[n]["upper-diameter"].SetNumber(
					contour.segments[n].upperdiameter);
		}
	}
}
