///////////////////////////////////////////////////////////////////////////////
// Name               : MatlabMatrix.cpp
// Purpose            : Matrix for data transfer to Matlab
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 04.11.2014
// Copyright          : (C) 2014 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "MatlabMatrix.h"

#include <string.h>
#include <string>
#include <stdexcept>
#include <cassert>

MatlabMatrix::MatlabMatrix()
{
	buffer = NULL;
	size = 0;
	bufferpos = 0;
}

MatlabMatrix::MatlabMatrix(const size_t S1, const size_t S2, const size_t S3,
		const size_t S4)
{
	buffer = NULL;
	size = 0;
	bufferpos = 0;
	SetSize(S1, S2, S3, S4);
}

MatlabMatrix::MatlabMatrix(const std::string& name, const size_t S1,
		const size_t S2, const size_t S3, const size_t S4)
{
	buffer = NULL;
	size = 0;
	bufferpos = 0;
	SetSize(S1, S2, S3, S4);
	SetVariableName(name);
}

MatlabMatrix::MatlabMatrix(const MatlabMatrix& other)
{
	this->variablename = other.variablename;
	this->size = other.size;
	this->dimension = other.dimension;
	this->bufferpos = other.bufferpos;
	if(other.buffer == NULL){
		buffer = NULL;
	}else{
		buffer = new double[size];
		if(buffer == NULL) throw(std::length_error(
				std::string(__FILE__) + " : Copy constructor: Out of memory."));
		memcpy(buffer, other.buffer, sizeof(double) * size);
	}
}

MatlabMatrix& MatlabMatrix::operator=(const MatlabMatrix& other)
{
	if(this == &other) return *this;
	this->variablename = other.variablename;
	this->SetSize(other);
	memcpy(buffer, other.buffer, sizeof(double) * size);
	return *this;
}

MatlabMatrix::~MatlabMatrix()
{
	if(buffer != NULL) delete[] buffer;
}

void MatlabMatrix::SetVariableName(const std::string& name)
{
	this->variablename = name;
}

const std::string& MatlabMatrix::GetVariableName(void) const
{
	return variablename;
}

void MatlabMatrix::Reset(void)
{
	if(buffer != NULL) delete[] buffer;
	buffer = NULL;
	dimension.resize(4, 1);
	dimension[0] = 0;
	size = 0;
	bufferpos = 0;
}

void MatlabMatrix::Clear(void)
{
	if(buffer == NULL) return;
	memset(buffer, 0, sizeof(double) * size);
}

bool MatlabMatrix::IsEmpty(void) const
{
	return (buffer == NULL);
}

void MatlabMatrix::SetSize(const size_t S1, const size_t S2, const size_t S3,
		const size_t S4)
{
	dimension.resize(4, 1);
	dimension[0] = S1;
	dimension[1] = S2;
	dimension[2] = S3;
	dimension[3] = S4;
	size = S1 * S2 * S3 * S4;

	if(buffer != NULL) delete[] buffer;
	buffer = new double[size];
	if(buffer == NULL) throw(std::length_error(
			std::string(__FILE__) + ": SetSize: Out of memory."));
	memset(buffer, 0, sizeof(double) * size);
	bufferpos = 0;
}

void MatlabMatrix::SetSize(const MatlabMatrix& other)
{
	this->SetSize(other.Size(1), other.Size(2), other.Size(3), other.Size(4));
}

void MatlabMatrix::SetSize(const std::vector <size_t>& dims)
{
	size_t N = 1;
	for(size_t n = 0; n < dims.size(); n++)
		N *= dims[n];
	dimension = dims;
	if(N == size) return;
	size = N;
	if(buffer != NULL) delete[] buffer;
	buffer = new double[size];
	if(buffer == NULL) throw(std::length_error(
			std::string(__FILE__) + ": SetSize: Out of memory."));
	memset(buffer, 0, sizeof(double) * size);
	bufferpos = 0;
}

size_t MatlabMatrix::Numel(void) const
{
	return size;
}

size_t MatlabMatrix::Size(const size_t dim) const
{
	if(dim < 1) throw(std::out_of_range(
			std::string(__FILE__)
					+ ": Size(dim): Dimensions are one-based (1, 2, 3, 4, ...)."));
	if(dim > dimension.size()) return (size > 0)? 1 : 0;
	return dimension[dim - 1];
}

std::vector <size_t> MatlabMatrix::Size(void) const
{
	return dimension;
}

void MatlabMatrix::SetInsertPosition(const size_t p1, const size_t p2,
		const size_t p3, const size_t p4)
{
	bufferpos = p1 + (p2 + (p3 + p4 * Size(3)) * Size(2)) * Size(1);
}

void MatlabMatrix::Insert(const double value)
{
	assert(buffer != NULL);
	if(bufferpos >= size) throw(std::logic_error(
			std::string(__FILE__) + ": Insert(double): Matrix full."));
	buffer[bufferpos] = value;
	bufferpos++;
}

void MatlabMatrix::Insert(const double value, const size_t p1, const size_t p2)
{
	assert(buffer != NULL);
	if(p1 >= this->Size(1)) throw(std::out_of_range(
			std::string(__FILE__) + ": Insert(double,p1,p2): p1 >= S1."));
	if(p2 >= this->Size(2)) throw(std::out_of_range(
			std::string(__FILE__) + ": Insert(double,p1,p2): p2 >= S2."));

	bufferpos = p1 + p2 * Size(1);
	buffer[bufferpos] = value;
	bufferpos++;
}

void MatlabMatrix::Insert(const double value, const size_t p1, const size_t p2,
		const size_t p3, const size_t p4)
{
	assert(buffer != NULL);
	if(p1 >= this->Size(1)) throw(std::out_of_range(
			std::string(__FILE__) + ": Insert(double,p1,p2,p3,p4): p1 >= S1."));
	if(p2 >= this->Size(2)) throw(std::out_of_range(
			std::string(__FILE__) + ": Insert(double,p1,p2,p3,p4): p2 >= S2."));
	if(p3 >= this->Size(3)) throw(std::out_of_range(
			std::string(__FILE__) + ": Insert(double,p1,p2,p3,p4): p3 >= S3."));
	if(p4 >= this->Size(4)) throw(std::out_of_range(
			std::string(__FILE__) + ": Insert(double,p1,p2,p3,p4): p4 >= S4."));
	bufferpos = p1 + (p2 + (p3 + p4 * Size(3)) * Size(2)) * Size(1);
	buffer[bufferpos] = value;
	bufferpos++;
}

void MatlabMatrix::Insert(const double* value, const size_t count)
{
	assert(buffer != NULL);
	if(bufferpos + count > size) throw(std::logic_error(
			std::string(__FILE__) + ": Insert(double*,count): Matrix is full."));
	if(value == NULL) throw(std::logic_error(
			std::string(__FILE__) + ": Insert(double*,count): value == NULL."));
	for(size_t i = 0; i < count; i++)
		buffer[bufferpos++] = value[i];
}

void MatlabMatrix::Insert(const double* value, const size_t count,
		const size_t p2)
{
	assert(buffer != NULL);
	bufferpos = p2 * Size(1);
	if(bufferpos + count > size) throw(std::logic_error(
			std::string(__FILE__) + ": Insert(col,double*,count): Matix full."));
	if(value == NULL) throw(std::logic_error(
			std::string(__FILE__)
					+ ": Insert(col,double*,count): value == NULL."));

	for(size_t i = 0; i < count; i++)
		buffer[bufferpos++] = value[i];
}

void MatlabMatrix::Insert(const float* value, const size_t count)
{
	assert(buffer != NULL);
	if(bufferpos + count > size) throw(std::logic_error(
			std::string(__FILE__) + ": Insert(float*,count): Matrix is full."));
	if(value == NULL) throw(std::logic_error(
			std::string(__FILE__) + ": Insert(float*,count): value == NULL."));
	for(size_t i = 0; i < count; i++)
		buffer[bufferpos++] = (double) value[i];
}

void MatlabMatrix::Insert(const bool* value, const size_t count)
{
	assert(buffer != NULL);
	if(bufferpos + count > size) throw(std::logic_error(
			std::string(__FILE__) + ": Insert(bool*,count): Matrix is full."));
	if(value == NULL) throw(std::logic_error(
			std::string(__FILE__) + ": Insert(bool*,count): value == NULL."));
	for(size_t i = 0; i < count; i++)
		buffer[bufferpos++] = value[i]? 1.0 : 0.0;
}

bool MatlabMatrix::IsFilled(void) const
{
	if(buffer == NULL) return true;
	return bufferpos >= size;
}

double& MatlabMatrix::operator[](const size_t& index)
{
	if(index >= size) throw(std::out_of_range(
			std::string(__FILE__) + ": operator[]: Access out of bounds!"));
	return buffer[index];
}

double MatlabMatrix::operator[](const size_t& index) const
{
	if(index >= size) throw(std::out_of_range(
			std::string(__FILE__) + ": operator[]: Access out of bounds!"));
	return buffer[index];
}

double& MatlabMatrix::operator ()(const size_t p1, const size_t p2,
		const size_t p3, const size_t p4)
{
	assert(buffer != NULL);
	if(p1 >= this->Size(1)) throw(std::out_of_range(
			std::string(__FILE__) + ": GetValue(p1,p2,p3,p4): p1 >= S1."));
	if(p2 >= this->Size(2)) throw(std::out_of_range(
			std::string(__FILE__) + ": GetValue(p1,p2,p3,p4): p2 >= S2."));
	if(p3 >= this->Size(3)) throw(std::out_of_range(
			std::string(__FILE__) + ": GetValue(p1,p2,p3,p4): p3 >= S3."));
	if(p4 >= this->Size(4)) throw(std::out_of_range(
			std::string(__FILE__) + ": GetValue(p1,p2,p3,p4): p4 >= S4."));
	const size_t pos = p1 + (p2 + (p3 + p4 * Size(3)) * Size(2)) * Size(1);
	return buffer[pos];
}

double MatlabMatrix::operator ()(const size_t p1, const size_t p2,
		const size_t p3, const size_t p4) const
{
	assert(buffer != NULL);
	if(p1 >= this->Size(1)) throw(std::out_of_range(
			std::string(__FILE__) + ": GetValue(p1,p2,p3,p4): p1 >= S1."));
	if(p2 >= this->Size(2)) throw(std::out_of_range(
			std::string(__FILE__) + ": GetValue(p1,p2,p3,p4): p2 >= S2."));
	if(p3 >= this->Size(3)) throw(std::out_of_range(
			std::string(__FILE__) + ": GetValue(p1,p2,p3,p4): p3 >= S3."));
	if(p4 >= this->Size(4)) throw(std::out_of_range(
			std::string(__FILE__) + ": GetValue(p1,p2,p3,p4): p4 >= S4."));
	const size_t pos = p1 + (p2 + (p3 + p4 * Size(3)) * Size(2)) * Size(1);
	return buffer[pos];
}

double* MatlabMatrix::Pointer()
{
	return buffer;
}

const double* MatlabMatrix::Pointer() const
{
	return buffer;
}

std::vector <size_t> MatlabMatrix::GetMinDimensions(void) const
{
	std::vector <size_t> temp;
	for(size_t m = 0; m < dimension.size(); m++)
		if(dimension[m] != 1) temp.push_back(dimension[m]);
	return temp;
}

void MatlabMatrix::Squeeze(void)
{
	dimension = GetMinDimensions();
}

void MatlabMatrix::Reshape(const size_t S1, const size_t S2, const size_t S3,
		const size_t S4)
{
	if(size == 0) throw(std::logic_error(
			std::string(__FILE__) + ": Reshape: Matrix has size 0."));
	unsigned int zeroElements = 0;
	size_t newNumel = 1;
	if(S1 == 0)
		zeroElements++;
	else
		newNumel *= S1;
	if(S2 == 0)
		zeroElements++;
	else
		newNumel *= S2;
	if(S3 == 0)
		zeroElements++;
	else
		newNumel *= S3;
	if(S4 == 0)
		zeroElements++;
	else
		newNumel *= S4;

	if(zeroElements > 1) throw(std::logic_error(
			std::string(__FILE__)
					+ ": Reshape: More than one dimension is set to 0."));
	if(newNumel > size) throw(std::logic_error(
			std::string(__FILE__)
					+ ": Reshape: The new dimensions describe a matrix with more values than before."));
	if(zeroElements == 0 && newNumel != size) throw(std::logic_error(
			std::string(__FILE__)
					+ ": Reshape: The new dimensions describe a different number of values than contained in the matrix."));
	if(zeroElements > 0){
		if(size % newNumel != 0) throw(std::logic_error(
				std::string(__FILE__)
						+ ": Reshape: The new dimensions do not fit without remainder."));
	}
	size_t zeroDimension = size / newNumel;
	dimension.resize(4);
	if(S1 == 0)
		dimension[0] = zeroDimension;
	else
		dimension[0] = S1;
	if(S2 == 0)
		dimension[1] = zeroDimension;
	else
		dimension[1] = S2;
	if(S3 == 0)
		dimension[2] = zeroDimension;
	else
		dimension[2] = S3;
	if(S4 == 0)
		dimension[3] = zeroDimension;
	else
		dimension[3] = S4;
}

void MatlabMatrix::Reshape(const std::vector <size_t>& dims)
{
	size_t N = 1;
	for(size_t n = 0; n < dims.size(); n++)
		N *= dims[n];
	if(N != size){
		throw(std::logic_error(
				std::string(__FILE__)
						+ ": Reshape(vector<size_t>): New shape has wrong number of elements."));
	}
	dimension = dims;
}

void MatlabMatrix::Transpose()
{
	if(size > 0 && buffer == NULL) throw(std::logic_error(
			std::string(__FILE__) + ": Transpose: Numel()>0 but buffer==NULL."));
	if(dimension.size() == 0) return;
	if(dimension.size() == 1) dimension.push_back(1);
	if(size > 0){

		const size_t D1 = Size(1);
		const size_t D2 = Size(2);
		const size_t D12 = D1 * D2;
		size_t Dr = 1;
		for(size_t n = 2; n < dimension.size(); n++)
			Dr *= dimension[n];

		double* temp = new double[size];
		size_t pFrom = 0;
		size_t pTo2 = 0;
		for(size_t p3 = 0; p3 < Dr; p3++){
			size_t pTo = pTo2;
			const size_t limit = pTo + D12;
			for(size_t p2 = 0; p2 < D12; p2++){
				temp[pTo] = buffer[pFrom++];
				pTo += D2;
				if(pTo >= limit) pTo = pTo - D12 + 1;
			}
			pTo2 += D12;
		}

		delete[] buffer;
		buffer = temp;
	}
	size_t h1 = this->Size(1);
	size_t h2 = this->Size(2);
	if(dimension.size() < 2) dimension.resize(2);
	dimension[0] = h2;
	dimension[1] = h1;
}

