///////////////////////////////////////////////////////////////////////////////
// Name               : MatlabFile.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 07.08.2016
// Copyright          : (C) 2016 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "MatlabFile.h"

#include <string>
#include <cstring>
#include <ctime>
#include <stdint.h>
#include <stdlib.h>

MatlabFile::MatlabFile()
{
	fhd = NULL;
	version = V6;
}

MatlabFile::MatlabFile(const MatlabFile& other)
{
	printf("MatlabFile copy constructor called.\n");
	this->fhd = NULL;
	this->filename = other.filename;
	this->version = other.version;
}

MatlabFile& MatlabFile::operator=(const MatlabFile& other)
{
	if(fhd != NULL) fclose(fhd);
	this->fhd = NULL;
	this->filename = other.filename;
	this->version = other.version;
	return *this;
}

MatlabFile::MatlabFile(const std::string& filename, Version version)
{
	this->filename = filename;
	this->fhd = NULL;
	this->version = version;
}

MatlabFile::~MatlabFile()
{
	if(fhd != NULL) fclose(fhd);
}

void MatlabFile::SetFilename(const std::string& filename)
{
	this->Close();
	this->filename = filename;
}

bool MatlabFile::IsOpen(void) const
{
	return (fhd != NULL);
}

void MatlabFile::Close(void)
{
	if(fhd != NULL) fclose(fhd);
	fhd = NULL;
}

void MatlabFile::SetVersion(Version version)
{
	if(this->version == version) return;
	if(fhd != NULL) throw __FILE__ ": SetVersion: Cannot change version while file is open.";
	this->version = version;
}

MatlabFile::Version MatlabFile::GetVersion(void) const
{
	return version;
}

void MatlabFile::ReadMatrix(MatlabMatrix* M, const std::string& matrixname)
{
	if(M == NULL) throw __FILE__ ": ReadData(MatlabMatrix*): Matrix == NULL.";
	if(fhd != NULL) throw __FILE__ ": ReadData(MatlabMatrix*): File is in write-mode.";
	fhd = fopen(filename.c_str(), "rb");
	if(fhd == NULL) throw __FILE__ ": ReadData(MatlabMatrix*): Could not open file.";

	int res;

	// Determine version
	char magic[4];
	res = fread((char *) magic, sizeof(char), 4, fhd);
	if(res == 0) throw __FILE__ ": File is empty.";
	if(strncmp(magic, "MATL", 4) == 0)
		version = V6;
	else
		version = V4;
	rewind(fhd);

	M->Reset();

	switch(version){
	case V4:
		{
			// Header lesen:
			uint32_t zero1;
			uint32_t zero2;
			uint32_t S1;
			uint32_t S2;

			do{
				res = fread(((uint32_t*) &zero1), sizeof(uint32_t), 1, fhd);
				if(res == 0) break;
				if(zero1 != 0) throw __FILE__ ": ReadData(MatlabMatrix*): Wrong header.";
				res = fread(((uint32_t*) &S1), sizeof(uint32_t), 1, fhd);
				if(S1 == 0 || res == 0) throw __FILE__ ": ReadData(MatlabMatrix*): Wrong header.";
				res = fread(((uint32_t*) &S2), sizeof(uint32_t), 1, fhd);
				if(S2 == 0 || res == 0) throw __FILE__ ": ReadData(MatlabMatrix*): Wrong header.";
				res = fread(((uint32_t*) &zero2), sizeof(uint32_t), 1, fhd);
				if(zero2 != 0 || res == 0) throw __FILE__ ": ReadData(MatlabMatrix*): Wrong header.";

				uint32_t x;
				res = fread(((uint32_t*) &x), sizeof(uint32_t), 1, fhd);

				if(res == 0) break;

				M->SetVariableName("");
				if(x > 0){
					char* tempchar = new char[x + 1];
					tempchar[x] = 0;
					res = fread(tempchar, sizeof(char), x, fhd);
					M->SetVariableName(std::string(tempchar));
					delete[] tempchar;
					if(res == 0) break;
				}

				if(matrixname.empty()
						|| M->GetVariableName().compare(matrixname) == 0){
					// Matrix lesen:
					M->SetSize(S1, S2);
					res = fread(M->Pointer(), sizeof(double), M->Numel(), fhd);
					if(res == 0) throw __FILE__ ": ReadData(MatlabMatrix*): Truncated file.";
					fclose(fhd);
					fhd = NULL;
					return;
				}else{
					fseek(fhd,
							(long int) S1 * (long int) S2
									* (long int) sizeof(double)
									- sizeof(uint32_t),
							SEEK_CUR);

					res = fread(((uint32_t*) &x), sizeof(uint32_t), 1, fhd);
					if(res == 0) throw __FILE__ ": ReadData(MatlabMatrix*): Truncated file.";
				}
			}while(!feof(fhd));
		}
		break;
	case V6:
		{
			char headertext[125];
			res = fread((char*) headertext, sizeof(char), 124, fhd);
			if(res == 0) throw __FILE__ ": ReadData(MatlabMatrix*): Headertext incomplete.";
			headertext[124] = 0;
			throw __FILE__": ReadMatrix for this version not implemented.";
		}
		break;
	default:
		throw __FILE__": ReadMatrix for this version not implemented.";
		break;
	}

	fclose(fhd);
	fhd = NULL;
}
void MatlabFile::WriteMatrix(const MatlabMatrix& M)
{
	if(M.GetVariableName().size() == 0) throw __FILE__ ": WriteMatrix: Variablename empty.";
	if(fhd == NULL){
		fhd = fopen(filename.c_str(), "wb");
		if(fhd == NULL) throw __FILE__ ": WriteData: Could not open file.";

		// Write Header
		switch(version){
		case V6:
			{
				char headertext[124];
				time_t rawtime;
				struct tm * timeinfo;
				char bufferTime[80];
				time(&rawtime);
				timeinfo = localtime(&rawtime);
				strftime(bufferTime, 80, "%F %X %Z", timeinfo);
				memset(headertext, 32, sizeof(char) * 124);
				sprintf(headertext,
						"MATLAB 5.0 MAT-file, written by MatlabFile.cpp, %s",
						bufferTime);
				headertext[124] = 0;
				fwrite(headertext, sizeof(char), 124, fhd);
				int16_t matVersion = 0x0100;
				fwrite(&matVersion, sizeof(int16_t), 1, fhd);
//				fwrite("MI", sizeof(char), 2, fhd); // Big Endian System
				fwrite("IM", sizeof(char), 2, fhd); // Little Endian System
			}
			break;
		case V4:
			// V4 files have no header
			break;
		}
	}

	switch(version){
	case V4:
		{
			const uint32_t zero = 0;
			const uint32_t S1 = M.Size(1);
			const uint32_t S2 = M.Size(2);
			fwrite(&zero, sizeof(uint32_t), 1, fhd);
			fwrite(&S1, sizeof(uint32_t), 1, fhd);
			fwrite(&S2, sizeof(uint32_t), 1, fhd);
			fwrite(&zero, sizeof(uint32_t), 1, fhd);

			uint32_t x;
			if(M.GetVariableName().empty()){
				x = 1;
				fwrite(&x, sizeof(uint32_t), 1, fhd);
				fwrite((char*) &zero, sizeof(char), x, fhd);
			}else{
				x = M.GetVariableName().length() + 1;
				fwrite(&x, sizeof(uint32_t), 1, fhd);
				fwrite(M.GetVariableName().c_str(), sizeof(char), x, fhd);
			}
			// Matrix write out matrix:
			fwrite(M.Pointer(), sizeof(double), M.Numel(), fhd);

		}
		break;
	case V6:
		{
			size_t NDim;
			for(NDim = 4; NDim > 1; NDim--)
				if(M.Size(NDim) > 1) break;
			if(NDim == 0) throw __FILE__ ": WriteData(MatlabMatrix*): Matrix has no Dimensions.";

			const uint8_t zeros8 = 0;
			const uint32_t zeros32 = 0;
			const uint32_t miINT8 = 1;
			const uint32_t miINT32 = 5;
			const uint32_t miUINT32 = 6;
			const uint32_t miDOUBLE = 9;
			const uint32_t miMatrix = 14;

			const uint32_t arrayFlagsSize = 8;
			const uint32_t mxDOUBLE_CLASS = 6;
			const uint32_t arrayFlags = mxDOUBLE_CLASS;
			const uint32_t nameSize = M.GetVariableName().size();
			const size_t namePadding = (8
					- ((nameSize + ((nameSize <= 4)? 4 : 0)) % 8)) % 8;
			uint32_t dataSize = M.Numel() * 8;
			uint32_t dimensionSize = sizeof(uint32_t) * NDim;
			const uint32_t miMatrixSize = 16 + 8 + ((NDim + 1) / 2) * 8 + 4
					+ ((NDim > 1)? 4 : 0)
					+ ((nameSize + 3 + ((nameSize <= 4)? 0 : 4)) / 8) * 8 + 8
					+ dataSize;

			fwrite(&miMatrix, sizeof(uint32_t), 1, fhd);
			fwrite(&miMatrixSize, sizeof(uint32_t), 1, fhd);

			fwrite(&miUINT32, sizeof(uint32_t), 1, fhd);
			fwrite(&arrayFlagsSize, sizeof(uint32_t), 1, fhd);

			fwrite(&arrayFlags, sizeof(uint32_t), 1, fhd);
			fwrite(&zeros32, sizeof(uint32_t), 1, fhd);

			if(NDim == 1){
				uint16_t miINT32_ = miINT32;
				uint16_t dimSize_ = 4;
				fwrite(&miINT32_, sizeof(uint16_t), 1, fhd);
				fwrite(&dimSize_, sizeof(uint16_t), 1, fhd);
				uint32_t temp = M.Size(1);
				fwrite(&temp, sizeof(uint32_t), 1, fhd);
			}else{
				fwrite(&miINT32, sizeof(uint32_t), 1, fhd);
				fwrite(&dimensionSize, sizeof(uint32_t), 1, fhd);
				for(size_t i = 0; i < NDim; i++){
					uint32_t temp = M.Size(i + 1);
					fwrite(&temp, sizeof(uint32_t), 1, fhd);
				}
				if((NDim % 2) == 1) fwrite(&zeros32, sizeof(uint32_t), 1, fhd);
			}

			if(nameSize <= 4){
				uint16_t miINT8_ = miINT8;
				uint16_t nameSize_ = nameSize;
				fwrite(&miINT8_, sizeof(uint16_t), 1, fhd);
				fwrite(&nameSize_, sizeof(uint16_t), 1, fhd);
			}else{
				fwrite(&miINT8, sizeof(uint32_t), 1, fhd);
				fwrite(&nameSize, sizeof(uint32_t), 1, fhd);
			}
			fwrite(M.GetVariableName().c_str(), sizeof(char), nameSize, fhd);
			for(size_t i = 0; i < namePadding; i++)
				fwrite(&zeros8, sizeof(uint8_t), 1, fhd);

			fwrite(&miDOUBLE, sizeof(uint32_t), 1, fhd);
			fwrite(&dataSize, sizeof(uint32_t), 1, fhd);
			fwrite(M.Pointer(), sizeof(double), M.Numel(), fhd);
			// Padding not necessary if dataclass is double.
			// for(size_t i = 0; i < nameSize; i++)
			// fwrite(&zeros8, sizeof(uint8_t), 1, fhd);
		}
		break;
	default:
		throw __FILE__": ReadMatrix for this version not implemented.";
		break;
	}
}

