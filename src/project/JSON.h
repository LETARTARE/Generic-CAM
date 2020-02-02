///////////////////////////////////////////////////////////////////////////////
// Name               : JSON.h
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

#ifndef SRC_PROJECT_JSON_H_
#define SRC_PROJECT_JSON_H_

/*!\class JSON
 * \brief JSON handling class
 *
 * Reads and writes JSON files
 * and stores the data.
 *
 * Uses only standard libraries (stl & the other normal ones, i.e. only what is found on http://www.cplusplus.com/reference/ )
 */

// https://esprima.org/

#include <stddef.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

class JSON {
public:
	enum Type {
		Null, Boolean, Number, String, Array, Object
	};
	JSON();
	bool Load(std::string filename);

	Type GetType(void) const;
	size_t Size(void) const;
	const JSON & Begin(void) const;
	JSON & operator[](std::string key);
	const JSON & operator[](std::string key) const;
	JSON & operator[](size_t index);
	const JSON & operator[](size_t index) const;
	bool IsKey(std::string key) const;
	bool IsArray(void) const;
	bool IsNull(void) const;
	double GetNumber(void) const;
	bool GetBool(void) const;
	std::string GetString(void) const;

private:
	Type type;
	bool valueBoolean;
	double valueNumber;
	std::string valueString;
	std::vector <JSON> valueArray;
	std::map <std::string, JSON> valueObject;

	class Token {
	public:
		Token();
		std::string Lower(void) const;
		enum {
			_Null, _Boolean, _Char, _String, _Number
		} type;
		char c;
		bool b;
		std::string str;
		double num;
	};

	class FileTokenizer {
	public:
		FileTokenizer(std::string filename);
		virtual ~FileTokenizer();
		void NextToken(void);
		Token token;
	private:
		std::ifstream in;
		char * buffer;
		char nextc;
		size_t charsread;
		size_t position;
		size_t linenumber;
		size_t column;
		size_t buffersize;
		unsigned char * statetable;
		unsigned char * actiontable;
	};

	static JSON Parse(FileTokenizer &ft, int maxRecursion);
};

#endif /* SRC_PROJECT_JSON_H_ */
