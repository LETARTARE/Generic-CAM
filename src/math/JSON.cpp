///////////////////////////////////////////////////////////////////////////////
// Name               : JSON.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 26.11.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#define _USE_MATH_DEFINES

#include "JSON.h"

#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <math.h>

static JSON nullobject;

JSON::JSON()
{
	type = Null;
	valueBoolean = false;
	valueNumber = 0.0;
}

JSON::Type JSON::GetType(void) const
{
	return type;
}

size_t JSON::Size(void) const
{
	if(type == Array) return valueArray.size();
	if(type == Object) return valueObject.size();
	return 1;
}

JSON& JSON::operator [](const std::string &key)
{
	if(type == Object) return valueObject[key];
	throw(std::logic_error("Not an object."));
}

const JSON& JSON::operator [](const std::string &key) const
{
	if(type == Object){
		if(valueObject.find(key) == valueObject.end()) return nullobject;
		return valueObject.at(key);
	}
	throw(std::logic_error("Not an object."));
}

JSON& JSON::operator [](size_t index)
{
	if(type == Array) return valueArray.at(index);
	if(type == Object){
		std::map <std::string, JSON>::iterator it = valueObject.begin();
		for(size_t n = 0; n < index; ++n)
			++it;
		return it->second;
	}
	throw(std::logic_error("Not an array or object."));
}

const JSON& JSON::operator [](size_t index) const
{
	if(type == Array) return valueArray.at(index);
	if(type == Object){
		std::map <std::string, JSON>::const_iterator it = valueObject.begin();
		for(size_t n = 0; n < index; ++n)
			++it;
		return it->second;
	}
	throw(std::logic_error("Not an array or object."));
}

bool JSON::HasKey(std::string key) const
{
	if(type != Object) return false;
	return (valueObject.find(key) != valueObject.end());
}

std::string JSON::GetKey(size_t index) const
{
	if(type == Object){
		std::map <std::string, JSON>::const_iterator it = valueObject.begin();
		for(size_t n = 0; n < index; ++n)
			++it;
		return it->first;
	}
	throw(std::logic_error("Not an object."));
}

bool JSON::IsNull(void) const
{
	return (type == Null);
}

double JSON::GetNumber(const double defaultvalue) const
{
	if(type == Number) return valueNumber;
	if(type == Boolean) return (valueBoolean)? 1 : 0;
	if(type == String) return strtod(valueString.c_str(), NULL);
	if(type == Null) return defaultvalue;
	throw(std::logic_error("Not a number."));
}

bool JSON::GetBool(const bool defaultvalue) const
{
	if(type == Boolean) return valueBoolean;
	if(type == Number) return fabs(valueNumber) > 1e-6;
	if(type == Null) return defaultvalue;
	throw(std::logic_error("Not convertable to boolean."));
}

std::string JSON::GetString(const std::string &defaultvalue) const
{
	if(type == String) return valueString;
	if(type == Boolean) return valueBoolean? "true" : "false";
	if(type == Null) return defaultvalue;
	throw(std::logic_error("Not a string."));
}

bool JSON::IsArray(void) const
{
	return (type == Array);
}

bool JSON::IsObject(void) const
{
	return type == Object;
}

const JSON& JSON::Begin(void) const
{
	if(type == Array) return *(valueArray.begin());
	if(type == Object) return valueObject.begin()->second;
	throw(std::logic_error("Not an array or object."));
}

void JSON::SetNull(void)
{
	type = Null;
}

void JSON::SetBool(const bool value)
{
	type = Boolean;
	valueBoolean = value;
}

void JSON::SetNumber(const double value)
{
	type = Number;
	valueNumber = value;
}

void JSON::SetString(const std::string& value)
{
	type = String;
	valueString = value;
}

void JSON::SetArray(size_t size)
{
	type = Array;
	valueArray.resize(size);
}

void JSON::SetObject(const bool clear)
{
	type = Object;
	if(clear) valueObject.clear();
}

JSON JSON::Load(std::string filename)
{
	std::ifstream in;
	in.open(filename.c_str(), std::ifstream::in | std::ios::binary);
	if(!in.good()){
		throw(std::runtime_error("JSON::Load(...) - Could not read file."));
	}
	return JSON::Load(in);
}

JSON JSON::Load(std::istream &in)
{
	FileTokenizer ft(&in);
	ft.NextToken();
	return Parse(ft, 127);
}

void JSON::Save(std::string filename)
{
	std::ofstream out;
	out.open(filename.c_str(), std::ofstream::out | std::ios::binary);
	JSON::Save(out);
}

void JSON::Save(std::ostream &out)
{
	ToStream(out, true);
}

JSON JSON::Parse(FileTokenizer &ft, int maxRecursion)
{
	JSON temp;
	if(maxRecursion <= 0) throw(std::range_error(
			"JSON JSON::Parse(...) - Maximum recursion depth reached."));
	switch(ft.token.type){
	case Token::_Null:
		temp.type = Null;
		break;
	case Token::_Char:
		if(ft.token.c == '{'){
			temp.type = Object;
			ft.NextToken();
			while(ft.token.type == Token::_String){
				std::string key = ft.token.str;
				ft.NextToken();
				if(ft.token.type != Token::_Char || ft.token.c != ':'){
					throw(std::logic_error("Expected ':' here."));
				}
				ft.NextToken();
				JSON value = Parse(ft, maxRecursion - 1);
				temp.valueObject[key] = value;
				ft.NextToken();
				if(ft.token.type != Token::_Char
						|| (ft.token.c != ',' && ft.token.c != '}')){

					throw(std::logic_error(
							"JSON::Parse(...) - Expected ',' or '}' here."));
				}
				if(ft.token.c == '}') break;
				ft.NextToken();
			}
		}
		if(ft.token.c == '['){
			temp.type = Array;
			ft.NextToken();
			while(ft.token.type != Token::_Char || ft.token.c != ']'){
				JSON value = Parse(ft, maxRecursion - 1);
				temp.valueArray.push_back(value);
				ft.NextToken();
				if(ft.token.type != Token::_Char
						|| (ft.token.c != ',' && ft.token.c != ']')){
					throw(std::logic_error(
							"JSON::Parse(...) - Expected ',' or ']' here."));
				}
				if(ft.token.c == ']') break;
				ft.NextToken();
			}
		}
		break;
	case Token::_Boolean:
		temp.type = Boolean;
		temp.valueBoolean = ft.token.b;
		break;
	case Token::_String:
		temp.type = String;
		temp.valueString = ft.token.str;
		break;
	case Token::_Number:
		temp.type = Number;
		temp.valueNumber = ft.token.num;
		break;
	}
	return temp;
}

JSON::Token::Token()
{
	type = _Null;
	c = 0;
	b = false;
	num = 0.0;
}

std::string JSON::Token::Lower(void) const
{
	std::string temp = str;
	for(size_t n = 0; n < temp.size(); ++n)
		if(temp[n] >= 'A' && temp[n] <= 'Z') temp[n] = (char) (temp[n] + 32);
	return temp;
}

JSON::FileTokenizer::FileTokenizer(std::istream * in)
{
	buffersize = 1e7;

	charsread = 0;
	position = 0;
	linenumber = 1;
	column = 0;
	nextc = 0;

	buffer = NULL;
	statetable = NULL;
	actiontable = NULL;

	this->in = in;

	buffer = new char[buffersize];
	if(buffer == NULL) throw(std::logic_error(
			"JSON::FileTokenizer::FileTokenizer(...) - Out of memory."));

	SetupTables();
}

JSON::FileTokenizer::~FileTokenizer()
{
	if(actiontable != NULL) delete[] actiontable;
	if(statetable != NULL) delete[] statetable;
	if(buffer != NULL) delete[] buffer;
}

void JSON::FileTokenizer::SetupTables(void)
{
	// Setup state transition table with the states 0 - 26

	statetable = new unsigned char[27 * 256];
	if(statetable == NULL) throw(std::logic_error(
			"JSON::FileTokenizer::SetupTables(...) - Out of memory."));
	for(size_t n = 0; n < 27 * 256; ++n){
		unsigned char m = (n % 256);
		unsigned char s = (unsigned char) (n >> 8);
		statetable[n] = 1;
		if(s == 0){
			statetable[n] = 0;
			if(m == '{' || m == '}' || m == '[' || m == ']' || m == ','
					|| m == ':') statetable[n] = 1;
			if(m >= 'a' && m <= 'z') statetable[n] = 15;
			if(m >= 'A' && m <= 'Z') statetable[n] = 15;
			if(m == '_') statetable[n] = 15;
			if(m == '+' || m == '-') statetable[n] = 19;
			if(m == '"') statetable[n] = 16;
			if(m == 'N' || m == 'n') statetable[n] = 2;
			if(m == 'T' || m == 't') statetable[n] = 6;
			if(m == 'F' || m == 'f') statetable[n] = 10;
		}
		if((s >= 2 && s <= 15)
				&& ((m >= 'A' && m <= 'Z') || (m >= 'a' && m <= 'z')
						|| (m >= '0' && m <= '9') || m == '-' || m == '_'
						|| m == '.')) statetable[n] = 15;
		if(s == 2 && (m == 'U' || m == 'u')) statetable[n] = 3;
		if(s == 3 && (m == 'L' || m == 'l')) statetable[n] = 4;
		if(s == 4 && (m == 'L' || m == 'l')) statetable[n] = 5;
		if(s == 6 && (m == 'R' || m == 'r')) statetable[n] = 7;
		if(s == 7 && (m == 'U' || m == 'u')) statetable[n] = 8;
		if(s == 8 && (m == 'E' || m == 'e')) statetable[n] = 9;
		if(s == 10 && (m == 'A' || m == 'a')) statetable[n] = 11;
		if(s == 11 && (m == 'L' || m == 'l')) statetable[n] = 12;
		if(s == 12 && (m == 'S' || m == 's')) statetable[n] = 13;
		if(s == 13 && (m == 'E' || m == 'e')) statetable[n] = 14;
		if(s == 16 || s == 17) statetable[n] = 16;
		if(s == 16 && m == '\\') statetable[n] = 17;
		if(s == 16 && m == '"') statetable[n] = 18;
		if(s == 18) statetable[n] = 1;

		if((s == 0 || s == 19 || s == 20 || s == 21) && (m >= '0' && m <= '9')) statetable[n] =
				21;
		if((s == 18 || s == 20) && m >= 1 && m <= 32) statetable[n] = 20;
		if((s == 0 || s == 19 || s == 20 || s == 21) && m == '.') statetable[n] =
				22;
		if((s == 22 || s == 23) && (m >= '0' && m <= '9')) statetable[n] = 23;
		if((s == 21 || s == 22 || s == 23) && (m == 'e' || m == 'E')) statetable[n] =
				24;
		if(s == 24 && (m == '+' || m == '-')) statetable[n] = 25;
		if((s == 24 || s == 25 || s == 26) && (m >= '0' && m <= '9')) statetable[n] =
				26;
	}

	// Setup action table
	// 1: Send char token back
	// 2: Send string token back
	// 3: Send value token back
	// 4: Send 'null' token back
	// 5: Send boolean 'true' token back
	// 6: Send boolean 'false' token back
	// 7: Error: Unexpected character
	// 8: Error: Number incomplete
	// 9: Add character to string
	// 10: Add char to value
	// 11: Add char to value as fraction
	// 12: Add char to exponent
	// 13: Mark value negative
	// 14: Mark exponent negative

	actiontable = new unsigned char[27 * 256];
	if(actiontable == NULL) throw(std::logic_error(
			"JSON::FileTokenizer::SetupTables(...) - Out of memory."));
	for(size_t n = 0; n < 27 * 256; ++n){
		unsigned char m = (n % 256);
		unsigned char s = (unsigned char) (n >> 8);
		actiontable[n] = 0;
		if(s != 0 && s < 19) actiontable[n] = 7;
		if(s == 0
				&& (m == '[' || m == ']' || m == '{' || m == '}' || m == ','
						|| m == ':')) actiontable[n] = 1;
		if(statetable[n] >= 2 && statetable[n] <= 15) actiontable[n] = 9;
		if(statetable[n] == 1){
			if((s >= 2 && s <= 4) || (s >= 6 && s <= 8) || (s >= 10 && s <= 13)) actiontable[n] =
					2;
			if(s == 5) actiontable[n] = 4;
			if(s == 9) actiontable[n] = 5;
			if(s == 14) actiontable[n] = 6;
			if(s == 15) actiontable[n] = 2;
		}
		if(s == 16){
			actiontable[n] = (statetable[n] == 16)? 9 : 0;
		}
		if(s == 17) actiontable[n] = 9;
		if(s == 18) actiontable[n] = 2;
		if(statetable[n] == 1){
			if(s >= 19) actiontable[n] = 8;
			if(s == 21 || s == 22 || s == 23 || s == 26) actiontable[n] = 3;
		}
		if(statetable[n] == 19 && m == '-') actiontable[n] = 13;
		if(statetable[n] == 21) actiontable[n] = 10;
		if(statetable[n] == 23) actiontable[n] = 11;
		if(statetable[n] == 25 && m == '-') actiontable[n] = 14;
		if(statetable[n] == 26) actiontable[n] = 12;
	}
}

void JSON::FileTokenizer::NextToken(void)
{
	bool negative = false;
	double factor = 0.1;
	bool exponentnegative = false;
	int exponent = 0;

	token.c = 0;
	token.b = false;
	token.num = 0.0;
	token.str.clear();
	token.type = Token::_Null;
	unsigned char state = 0;

//	std::cout << "Line: " << linenumber << " Column: " << column << "\n";

	do{
		if(position >= charsread){
			in->read(buffer, buffersize);
			charsread = in->gcount();
			if(charsread < buffersize){
				// Add a 0 byte to the end
				buffer[charsread] = 0;
				++charsread;
			}
			position = 0;
		}
		do{
			char c = nextc;
			nextc = buffer[position++];
//			std::cout << c;
//			++position;
//			if(c == 10){
//				++linenumber;
//				column = 0;
//			}else{
//				column += (c == (char) 9)? 2 : 1;
//			}
			unsigned char nextstate = statetable[(state << 8)
					+ (unsigned char) c];
			unsigned char action = actiontable[(state << 8) + (unsigned char) c];
			switch(action){
			case 1:
				token.type = Token::_Char;
				token.c = c;
				return;
				break;
			case 7:
				throw(std::runtime_error("Character not expected."));
			case 8:
				throw(std::runtime_error("Number incomplete."));
			case 9:
				token.str += c;
				break;
			case 10:
				token.num = 10 * token.num + (double) (c - '0');
				break;
			case 11:
				token.num += factor * (double) (c - '0');
				factor /= 10.0;
				break;
			case 12:
				exponent = 10 * exponent + (int) (c - '0');
				break;
			case 13:
				negative = true;
				break;
			case 14:
				exponentnegative = true;
				break;
			}
			unsigned char nextaction = actiontable[(nextstate << 8)
					+ (unsigned char) nextc];
			switch(nextaction){
			case 2:
				token.type = Token::_String;
				return;
			case 3:
				token.type = Token::_Number;
				if(exponent != 0){
					if(exponentnegative) exponent = -exponent;
					token.num *= exp(M_LN10 * (double) exponent);
				}
				if(negative) token.num = -token.num;
				return;
			case 4:
				return;
			case 5:
				token.type = Token::_Boolean;
				token.b = true;
				return;
			case 6:
				token.type = Token::_Boolean;
				return;
			}
			state = nextstate;
		}while(position < charsread);
	}while(charsread == buffersize);
}

void JSON::ToStream(std::ostream &out, bool usenewline, size_t indent) const
{
	switch(type){
	case Null:
		out << "null";
		break;
	case Boolean:
		if(valueBoolean){
			out << "true";
		}else{
			out << "false";
		}
		break;
	case Number:
		out << valueNumber;
		break;
	case String:
		out << '"' << EscapeString(valueString) << '"';
		break;
	case Array:
	{
		out << "[";
		bool flag = false;
		for(std::vector <JSON>::const_iterator it = valueArray.begin();
				it != valueArray.end(); ++it){
			if(flag) out << ",";
			if(usenewline){
				out << '\n';
				for(size_t m = 0; m < indent; ++m)
					out << "  ";
			}
			it->ToStream(out, usenewline, indent + 1);
			flag = true;
		}
		out << "]";
		break;
	}
	case Object:
	{
		out << "{";
		bool flag = false;
		for(std::map <std::string, JSON>::const_iterator it =
				valueObject.begin(); it != valueObject.end(); ++it){
			if(flag) out << ",";
			if(usenewline){
				out << '\n';
				for(size_t m = 0; m < indent; ++m)
					out << "  ";
			}
			out << '"' << EscapeString(it->first) << '"';
			if(usenewline) out << "\t";
			out << ':';
			if(usenewline) out << " ";
			it->second.ToStream(out, usenewline, indent + 1);
			flag = true;
		}
		out << "}";
		break;
	}
	}
}

std::string JSON::EscapeString(const std::string& txt)
{
	std::string temp = txt;
	for(size_t index = 0; index < temp.size(); ++index){
		index = temp.find_first_of("\"\\", index);
		if(index == std::string::npos) break;
		temp.insert(index, 1, '\\');
		++index;
	}
	return temp;
}
