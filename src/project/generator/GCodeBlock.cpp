///////////////////////////////////////////////////////////////////////////////
// Name               : GCodeBlock.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 09.07.2017
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

#define _USE_MATH_DEFINES

#include "GCodeBlock.h"

#include <float.h>
#include <stdint.h>
#include <stdexcept>
#include <sstream>

#include <math.h>

GCodeBlock::GCodeBlock(std::string block, double conversionFactor)
{
	t = 0.0;
	duration = 0.0;
//	length = 0.0;

	this->conversionFactor = conversionFactor;
	A = 0.0;
	B = 0.0;
	C = 0.0;
	D = -1;
	F = -1.0;
	for(uint_fast8_t n = 0; n < maxGModes; ++n)
		G[n] = -1;
	H = -1;
	I = 0.0;
	J = 0.0;
	K = 0.0;
	L = -1;
	for(uint_fast8_t n = 0; n < maxMModes; ++n)
		M[n] = -1;
	MCount = 0;
	N = -1;
	P = -1.0;
	Q = -1.0;
	R = 0.0;
	S = -1.0;
	T = -1;
	U = 0.0;
	V = 0.0;
	W = 0.0;
	X = 0.0;
	Y = 0.0;
	Z = 0.0;
	AFlag = false;
	BFlag = false;
	CFlag = false;
	IFlag = false;
	JFlag = false;
	KFlag = false;
	RFlag = false;
	UFlag = false;
	VFlag = false;
	WFlag = false;
	XFlag = false;
	YFlag = false;
	ZFlag = false;

	block_delete = false;
	message = false;

	if(block.empty()) return;

	bool negative = false;
	int numberI = 0;
	double numberD = 0;
	double shift = 1;
	char key = 0;
	uint_fast8_t state = 0;
	const size_t BL = block.size();
	for(size_t n = 0; n <= BL; ++n){
		const char c = (n < BL)? block[n] : 0;
		bool unexpected = false;
		switch(state){
		case 0:
		{
			if(c == ' ' || c == 9) break;
			if(c == 'n' || c == 'N'){
				N = 0;
				state = 2;
				break;
			}
			if(c == '/'){
				block_delete = true;
				state = 1;
				break;
			}
			if(((c >= 'A') && (c <= 'D')) || ((c >= 'F') && (c <= 'M'))
					|| ((c >= 'P') && (c <= 'Z'))){
				key = c;
				negative = false;
				state = 6;
				break;
			}
			if(((c >= 'a') && (c <= 'd')) || ((c >= 'f') && (c <= 'm'))
					|| ((c >= 'p') && (c <= 'z'))){
				key = c - 32; // converts a-z to A-Z
				negative = false;
				state = 6;
				break;
			}
			if(c == '('){
				state = 7;
				break;
			}
			unexpected = true;
			break;
		}
		case 1:
		{
			if(c == ' ' || c == 9) break;
			if(c == 'n' || c == 'N'){
				N = 0; // Has a line number.
				state = 2;
				break;
			}
			if(((c >= 'A') && (c <= 'D')) || ((c >= 'F') && (c <= 'M'))
					|| ((c >= 'P') && (c <= 'Z'))){
				key = c;
				negative = false;
				state = 6;
				break;
			}
			if(((c >= 'a') && (c <= 'd')) || ((c >= 'f') && (c <= 'm'))
					|| ((c >= 'p') && (c <= 'z'))){
				key = c - 32; // converts a-z to A-Z
				state = 6;
				negative = false;
				break;
			}
			if(c == '('){
				state = 7;
				break;
			}
			unexpected = true;
			break;
		}
		case 2:
		{
			if(c == ' ' || c == 9) break;
			if(((c >= '0') && (c <= '9'))){
				N = c - '0';
				state = 3;
				break;
			}
			unexpected = true;
			break;
		}
		case 3:
		{
			if(c == ' ' || c == 9) break;
			if(c == 0){
				state = 4;
				break;
			}
			if(((c >= '0') && (c <= '9'))){
				//TODO: Maybe limit number of number chars?
				N = N * 10 + (c - '0');
				break;
			}
			if(((c >= 'A') && (c <= 'D')) || ((c >= 'F') && (c <= 'M'))
					|| ((c >= 'P') && (c <= 'Z'))){
				key = c;
				negative = false;
				state = 6;
				break;
			}
			if(((c >= 'a') && (c <= 'd')) || ((c >= 'f') && (c <= 'm'))
					|| ((c >= 'p') && (c <= 'z'))){
				key = c - 32; // converts a-z to A-Z
				negative = false;
				state = 6;
				break;
			}
			if(c == '('){
				state = 7;
				break;
			}

			unexpected = true;
			break;
		}
		case 4:
		{
			if(c == ' ' || c == 9) break;
			if(((c >= 'A') && (c <= 'D')) || ((c >= 'F') && (c <= 'M'))
					|| ((c >= 'P') && (c <= 'Z'))){
				key = c;
				negative = false;
				state = 6;
				break;
			}
			if(((c >= 'a') && (c <= 'd')) || ((c >= 'f') && (c <= 'm'))
					|| ((c >= 'p') && (c <= 'z'))){
				key = c - 32; // converts a-z to A-Z
				negative = false;
				state = 6;
				break;
			}
			if(c == '('){
				state = 7;
				break;
			}
			unexpected = true;
			break;
		}
		case 6:
		{
			if(c == ' ' || c == 9) break;
			if(c == '+'){
				state = 13;
				break;
			}
			if(c == '-'){
				state = 13;
				negative = true;
				break;
			}
			if(((c >= '0') && (c <= '9'))){
				numberI = c - '0';
				numberD = numberI;
				state = 14;
				break;
			}
			if(c == '.'){
				numberI = 0;
				numberD = numberI;
				shift = 1.0;
				state = 15;
				break;
			}
			unexpected = true;
			break;
		}
		case 7:
		{
			if(c == ')'){
				state = 4;
				break;
			}
			if(c == ' ' || c == 9) break;
			Comment += c;
			if(c == 'm' || c == 'M'){
				state = 9;
				break;
			}
			state = 8;
			break;
		}
		case 8:
		{
			if(c == ')'){
				state = 4;
			}else{
				Comment += c;
			}
			break;
		}
		case 9:
		{
			if(c == ')'){
				state = 4;
				break;
			}
			Comment += c;
			if(c == ' ' || c == 9) break;
			if(c == 's' || c == 'S'){
				state = 10;
				break;
			}
			state = 8;
			break;
		}
		case 10:
		{
			if(c == ')'){
				state = 4;
				break;
			}
			Comment += c;
			if(c == ' ' || c == 9) break;
			if(c == 'g' || c == 'G'){
				state = 11;
				break;
			}
			state = 8;
			break;
		}
		case 11:
		{
			if(c == ')'){
				state = 4;
				break;
			}
			Comment += c;
			if(c == ' ' || c == 9) break;
			if(c == ','){
				Comment.clear();
				message = true;
				state = 8;
				break;
			}
			state = 8;
			break;
		}
		case 13:
		{
			if(((c >= '0') && (c <= '9'))){
				numberI = c - '0';
				numberD = numberI;
				state = 14;
				break;
			}
			if(c == '.'){
				numberI = 0;
				numberD = numberI;
				shift = 1.0;
				state = 15;
				break;
			}
			unexpected = true;
			break;
		}
		case 14:
		{
			if(((c >= '0') && (c <= '9'))){
				numberI = numberI * 10 + (c - '0');
				numberD = numberI;
				break;
			}
			if(c == '.'){
				shift = 1.0;
				state = 15;
				break;
			}
			if(c == ' ' || c == 9) break;
			if(c == 0){
				Update(key, negative, numberI, numberD);
				state = 4;
				break;
			}
			if(((c >= 'A') && (c <= 'D')) || ((c >= 'F') && (c <= 'M'))
					|| ((c >= 'P') && (c <= 'Z'))){
				Update(key, negative, numberI, numberD);
				key = c;
				negative = 0;
				state = 6;
				break;
			}
			if(((c >= 'a') && (c <= 'd')) || ((c >= 'f') && (c <= 'm'))
					|| ((c >= 'p') && (c <= 'z'))){
				Update(key, negative, numberI, numberD);
				key = c - 32; // converts a-z to A-Z
				negative = 0;
				state = 6;
				break;
			}
			if(c == '('){
				Update(key, negative, numberI, numberD);
				state = 7;
				break;
			}
			unexpected = true;
			break;
		}
		case 15:
		{
			if(((c >= '0') && (c <= '9'))){
				shift /= 10.0;
				numberD = numberD + ((double) (c - '0')) * shift;
				break;
			}

			if(c == ' ' || c == 9) break;
			if(c == 0){
				Update(key, negative, numberI, numberD);
				state = 4;
				break;
			}
			if(((c >= 'A') && (c <= 'D')) || ((c >= 'F') && (c <= 'M'))
					|| ((c >= 'P') && (c <= 'Z'))){
				Update(key, negative, numberI, numberD);
				key = c;
				negative = 0;
				state = 6;
				break;
			}
			if(((c >= 'a') && (c <= 'd')) || ((c >= 'f') && (c <= 'm'))
					|| ((c >= 'p') && (c <= 'z'))){
				Update(key, negative, numberI, numberD);
				key = c - 32; // converts a-z to A-Z
				negative = 0;
				state = 6;
				break;
			}
			if(c == '('){
				Update(key, negative, numberI, numberD);
				state = 7;
				break;
			}
			unexpected = true;
			break;
		}
		default:
			throw(__FILE__ ": GCodeBlock Error in statemachine.");
			break;
		}

		if(unexpected && n < BL){
			std::ostringstream temp;
			temp << "Character " << c << " was not expected.";
			error = temp.str();
		}

		if(n == BL && state != 4 && state != 0) error =
				"Missing closing character at end of line.";
		if(!error.empty()){
			std::ostringstream temp;
			temp << "Column " << n << ": " << error;
			temp << "\nafter " << block.substr(0, n);
			temp << "<";
			error = temp.str();
			break;
		}
	}
}

std::string GCodeBlock::GetCode(void) const
{
	std::ostringstream temp;

	if(block_delete) temp << "/";
	if(N >= 0) temp << " N" << N;

	for(uint_fast8_t n = 0; n < maxMModes; ++n){
		if(M[n] < 0) continue;
		temp << " M" << M[n];
	}

	if(T >= 0) temp << " T" << T;
	if(S >= -FLT_EPSILON) temp << " S" << S * 60;

	for(uint_fast8_t n = 0; n < maxGModes; ++n){
		if(G[n] < 0) continue;
		const uint_fast16_t gmaj = (G[n] / 10);
		const uint_fast8_t gmin = (G[n] % 10);
		if(gmin == 0){
			temp << " G" << gmaj;
		}else{
			temp << " G" << gmaj << "." << gmin;
		}
	}

	if(D >= 0) temp << " D" << D;
	if(H >= 0) temp << " H" << H;
	if(L >= 0) temp << " L" << L;

	if(RFlag) temp << " R" << (R / conversionFactor);

	if(P >= -FLT_EPSILON) temp << " P" << P;
	if(Q >= -FLT_EPSILON) temp << " Q" << (Q / conversionFactor);

	if(F >= -FLT_EPSILON) temp << " F" << (F / conversionFactor * 60);

	if(XFlag){
		temp << " X" << (X / conversionFactor);
	}
	if(YFlag){
		temp << " Y" << (Y / conversionFactor);
	}
	if(ZFlag){
		temp << " Z" << (Z / conversionFactor);
	}
	if(AFlag){
		temp << " A" << (A * 180.0 * M_1_PI);
	}
	if(BFlag){
		temp << " B" << (B * 180.0 * M_1_PI);
	}
	if(CFlag){
		temp << " C" << (C * 180.0 * M_1_PI);
	}
	if(UFlag){
		temp << " U" << (U / conversionFactor);
	}
	if(VFlag){
		temp << " V" << (V / conversionFactor);
	}
	if(WFlag){
		temp << " W" << (W / conversionFactor);
	}
	if(IFlag){
		temp << " I" << (I / conversionFactor);
	}
	if(JFlag){
		temp << " J" << (J / conversionFactor);
	}
	if(KFlag){
		temp << " K" << (K / conversionFactor);
	}

	// Convert , to . on every machine.

	if(!Comment.empty()){
		if(message){
			temp << " (MSG," << Comment << ")";
		}else{
			temp << " (" << Comment << ")";
		}
	}
	std::string temp2 = temp.str();

	if(!temp2.empty() && temp2[0] == ' ') temp2 = temp2.substr(1,
			temp2.size() - 1);
	for(size_t n = 0; n < temp2.size(); ++n)
		if(temp2[n] == ',') temp2[n] = '.';
	return temp2;
}

static const int Gindex[1000] =
	{1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			7, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			12, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, 12, 12, 12, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, 13, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 13, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			0, 0, 0, 0, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1};

static const int Mindex[120] =
	{4, 4, 4, 7, 7, 7, 6, 8, 8, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 9, 9, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 4, 4, 10, 10, 10, 10, 10, 10,
			10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

void GCodeBlock::Update(char key, bool negative, int numberI, double numberD)
{
	std::ostringstream errstr;

	if(negative){
		numberI = -numberI;
		numberD = -numberD;
	}

	switch(key){
	case 'A':
	{
		AFlag = true;
		A = numberD * M_PI / 180.0;
		break;
	}
	case 'B':
	{
		BFlag = true;
		B = numberD * M_PI / 180.0;
		break;
	}
	case 'C':
	{
		CFlag = true;
		C = numberD * M_PI / 180.0;
		break;
	}
	case 'I':
	{
		IFlag = true;
		I = numberD * conversionFactor;
		break;
	}
	case 'J':
	{
		JFlag = true;
		J = numberD * conversionFactor;
		break;
	}
	case 'K':
	{
		KFlag = true;
		K = numberD * conversionFactor;
		break;
	}
	case 'R':
	{
		RFlag = true;
		R = numberD * conversionFactor;
		break;
	}
	case 'U':
	{
		UFlag = true;
		U = numberD * conversionFactor;
		break;
	}
	case 'V':
	{
		VFlag = true;
		V = numberD * conversionFactor;
		break;
	}
	case 'W':
	{
		WFlag = true;
		W = numberD * conversionFactor;
		break;
	}
	case 'X':
	{
		XFlag = true;
		X = numberD * conversionFactor;
		break;
	}
	case 'Y':
	{
		YFlag = true;
		Y = numberD * conversionFactor;
		break;
	}
	case 'Z':
	{
		ZFlag = true;
		Z = numberD * conversionFactor;
		break;
	}

	case 'D':
	{
		if(numberI < 0){
			errstr << "Integer negative for D.";
		}else{
			D = numberI;
		}
		break;
	}
	case 'F':
	{
		if(numberD < 0){
			errstr << "Integer negative for F.";
		}else{
			F = numberD * conversionFactor / 60.0;
		}
		break;
	}
	case 'H':
	{
		if(numberI < 0){
			errstr << "Integer negative for H.";
		}else{
			H = numberI;
		}
		break;
	}
	case 'L':
	{
		if(numberI < 0){
			errstr << "Integer negative for L.";
		}else{
			L = numberI;
		}
		break;
	}
	case 'P':
	{
		if(numberD < 0){
			errstr << "Integer negative for P.";
		}else{
			P = numberD;
		}
		break;
	}
	case 'Q':
	{
		if(numberD < 0){
			errstr << "Integer negative for Q.";
		}else{
			Q = numberD * conversionFactor;
		}
		break;
	}

	case 'S':
	{
		if(numberD < 0){
			errstr << "Integer negative for S.";
		}else{
			S = numberD / 60.0;
		}
		break;
	}

	case 'T':
	{
		if(numberI < 0){
			errstr << "Integer negative for T.";
		}else{
			T = numberI;
		}
		break;
	}

	case 'G':
	{
		const int temp = round(numberD * 10.0);
		if(temp >= 0 && temp < 1000){
			const int index = Gindex[temp];
			if(index == -1){
				errstr << "Unknown or unsupported G command.";
			}else{
				if(G[index] >= 0){
					errstr << "From this modal-group there is already G";
					errstr << ((double) G[index] / 10.0);
					errstr << ".";
				}else{
					G[index] = temp;
				}
			}
		}else{
			if(temp < 0) errstr << "G command may not be negative.";
			if(temp >= 1000) errstr
					<< "G command may not be greater than 99.9.";
		}
		break;
	}
	case 'M':
	{
		const int temp = numberI;
		if(temp >= 0 && temp < 120){
			const int index = Mindex[temp];
			if(index == -1){
				errstr << "Unknown or unsupported M command.";
			}else{
				if(M[index] >= 0){
					errstr
							<< "A command for this M command-group was already found. (M";
					errstr << M[index];
					errstr << ")";
				}else{
					M[index] = temp;
				}
			}
		}else{
			if(temp < 0) errstr << "M command may not be negative.";
			if(temp >= 120) errstr << "M command may not be greater than 119.";
		}
		break;
	}
	default:
		errstr << "Missing case for ";
		errstr << key;
		errstr << ".";
		break;
	}
	error = errstr.str();
}

int GCodeBlock::Motion(void) const
{
	if(G[1] >= 0) return G[1] / 10;
	return -1;
}

bool GCodeBlock::IsStateChange(void) const
{
	for(uint_fast8_t n = 2; n < maxGModes; n++)
		if(G[n] >= 0) return false;
	for(uint_fast8_t n = 0; n < maxMModes; n++)
		if(M[n] >= 0) return false;

	if(XFlag || YFlag || ZFlag) return false;
	if(F >= 0) return false;
	if(S >= 0) return false;
	if(T >= 0) return false;

	return true;

}

bool GCodeBlock::IsMotion(void) const
{
	const uint_fast8_t c = G[1] / 10;
	if(c >= 0 && c <= 3) return true;
	if(c >= 80 && c <= 89) return true;
	return false;
}

bool GCodeBlock::IsLinearMotion(void) const
{
	if(G[1] == 0) return true;
	if(G[1] == 10) return true;
	return false;
}

bool GCodeBlock::IsPureLinearMotion(void) const
{
	if(G[1] != 0 && G[1] != 10) return false;
	if(G[0] >= 0) return false;
	for(uint_fast8_t n = 2; n < maxGModes; n++)
		if(G[n] >= 0) return false;
	for(uint_fast8_t n = 0; n < maxMModes; n++)
		if(M[n] >= 0) return false;
	if(AFlag || BFlag || CFlag) return false;
	if(UFlag || VFlag || WFlag) return false;
	if(IFlag || JFlag || KFlag) return false;
	if(RFlag) return false;
	if(message) return false;
	if(D >= 0 || F >= 0.0 || H >= 0.0) return false;
	if(L >= 0 || P >= 0.0 || Q >= 0.0) return false;
	if(S >= 0 || T >= 0.0) return false;
	return true;
}

//TODO: Make error messages translatable.
bool GCodeBlock::IsCutting(void) const
{
	return G[1] > 0; // neither empty nor rapid motion selected
}

void GCodeBlock::CopySelective(const GCodeBlock& other)
{
	if(other.AFlag){
		A = other.A;
		AFlag = true;
	}
	if(other.BFlag){
		B = other.B;
		BFlag = true;
	}
	if(other.CFlag){
		C = other.C;
		CFlag = true;
	}
	if(other.message) Comment = other.Comment;
	if(other.D >= 0) D = other.D;
	if(other.F >= 0) F = other.F;
	for(uint_fast8_t n = 0; n < maxGModes; ++n)
		if(other.G[n] >= 0) G[n] = other.G[n];
	if(other.H >= 0) H = other.H;
	if(other.IFlag){
		I = other.I;
		IFlag = true;
	}
	if(other.JFlag){
		J = other.J;
		JFlag = true;
	}
	if(other.KFlag){
		K = other.K;
		KFlag = true;
	}
	if(other.L >= 0) L = other.L;
	for(uint_fast8_t n = 0; n < maxMModes; ++n)
		if(other.M[n] >= 0) M[n] = other.M[n];
	N = other.N;
	if(other.P >= 0) P = other.P;
	if(other.Q >= 0) Q = other.Q;
	if(other.RFlag){
		R = other.R;
		RFlag = true;
	}
	if(other.S >= 0) S = other.S;
	if(other.T >= 0) T = other.T;
	if(other.UFlag){
		U = other.U;
		UFlag = true;
	}
	if(other.VFlag){
		V = other.V;
		VFlag = true;
	}
	if(other.WFlag){
		W = other.W;
		WFlag = true;
	}
	if(other.XFlag){
		X = other.X;
		XFlag = true;
	}
	if(other.YFlag){
		Y = other.Y;
		YFlag = true;
	}
	if(other.ZFlag){
		Z = other.Z;
		ZFlag = true;
	}
}

void GCodeBlock::ClearGM(void)
{
	for(uint_fast8_t n = 0; n < maxGModes; ++n)
		G[n] = -1;
	for(uint_fast8_t n = 0; n < maxMModes; ++n)
		M[n] = -1;
	MCount = 0;
}

void GCodeBlock::SetG(unsigned int nr, unsigned char subnr)
{
	const int temp = nr * 10 + subnr;
	if(temp < 0) throw(std::out_of_range("G command may not be negative."));
	if(temp >= 1000) throw(std::out_of_range(
			"G command may not be greater than 99.9."));
	const int index = Gindex[temp];
	if(index == -1) throw(std::logic_error("Unknown or unsupported G command."));
	G[index] = temp;
}

void GCodeBlock::SetM(unsigned int nr)
{
	if(nr < 0) throw(std::out_of_range("M command may not be negative."));
	if(nr >= 120) throw(std::out_of_range(
			"M command may not be greater than 119."));
	const int index = Mindex[nr];
	if(index == -1) throw(std::logic_error("Unknown or unsupported M command."));
	M[index] = nr;
}

void GCodeBlock::Rapid(void)
{
	SetG(0);
}

void GCodeBlock::FeedSpeed(void)
{
	SetG(1);
}

void GCodeBlock::ArcCW(void)
{
	SetG(2);
}

void GCodeBlock::ArcCCW(void)
{
	SetG(3);
}

void GCodeBlock::UpdateFlags(const GCodeBlock& rhs)
{
	AFlag |= rhs.AFlag;
	BFlag |= rhs.BFlag;
	CFlag |= rhs.CFlag;
	IFlag |= rhs.IFlag;
	JFlag |= rhs.JFlag;
	KFlag |= rhs.KFlag;
	RFlag |= rhs.RFlag;
	UFlag |= rhs.UFlag;
	VFlag |= rhs.VFlag;
	WFlag |= rhs.WFlag;
	XFlag |= rhs.XFlag;
	YFlag |= rhs.YFlag;
	ZFlag |= rhs.ZFlag;
}
GCodeBlock& GCodeBlock::operator +=(const GCodeBlock& rhs)
{
	UpdateFlags(rhs);
	A += rhs.A;
	B += rhs.B;
	C += rhs.C;
	U += rhs.U;
	V += rhs.V;
	W += rhs.W;
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
	I += rhs.I;
	J += rhs.J;
	K += rhs.K;
	F += rhs.F;
	L += rhs.L;
	N += rhs.N;
	P += rhs.P;
	Q += rhs.Q;
	R += rhs.R;
	S += rhs.S;
	return *this;
}
GCodeBlock& GCodeBlock::operator -=(const GCodeBlock& rhs)
{
	UpdateFlags(rhs);
	A -= rhs.A;
	B -= rhs.B;
	C -= rhs.C;
	U -= rhs.U;
	V -= rhs.V;
	W -= rhs.W;
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	I -= rhs.I;
	J -= rhs.J;
	K -= rhs.K;
	F -= rhs.F;
	L -= rhs.L;
	N -= rhs.N;
	P -= rhs.P;
	Q -= rhs.Q;
	R -= rhs.R;
	S -= rhs.S;
	return *this;
}
GCodeBlock& GCodeBlock::operator *=(const double& rhs)
{
	A *= rhs;
	B *= rhs;
	C *= rhs;
	U *= rhs;
	V *= rhs;
	W *= rhs;
	X *= rhs;
	Y *= rhs;
	Z *= rhs;
	I *= rhs;
	J *= rhs;
	K *= rhs;
	F *= rhs;
	L *= rhs;
	N *= rhs;
	P *= rhs;
	Q *= rhs;
	R *= rhs;
	S *= rhs;
	return *this;
}
GCodeBlock& GCodeBlock::operator /=(const double& rhs)
{
	A /= rhs;
	B /= rhs;
	C /= rhs;
	U /= rhs;
	V /= rhs;
	W /= rhs;
	X /= rhs;
	Y /= rhs;
	Z /= rhs;
	I /= rhs;
	J /= rhs;
	K /= rhs;
	F /= rhs;
	L /= rhs;
	N /= rhs;
	P /= rhs;
	Q /= rhs;
	R /= rhs;
	S /= rhs;
	return *this;
}

GCodeBlock operator+(GCodeBlock lhs, const GCodeBlock& rhs)
{
	lhs += rhs;
	return lhs;
}
GCodeBlock operator-(GCodeBlock lhs, const GCodeBlock& rhs)
{
	lhs -= rhs;
	return lhs;
}
GCodeBlock operator*(GCodeBlock lhs, const double& rhs)
{
	lhs *= rhs;
	return lhs;
}
GCodeBlock operator/(GCodeBlock lhs, const double& rhs)
{
	lhs /= rhs;
	return lhs;
}
