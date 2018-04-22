///////////////////////////////////////////////////////////////////////////////
// Name               : NelderMeadOptimizer.cpp
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.02.2018
// Copyright          : (C) 2018 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "NelderMeadOptimizer.h"

#include <stdexcept>
#include <string>

NelderMeadOptimizer::NelderMeadOptimizer()
{
	alpha = 1;
	gamma = 2;
	rho = 0.5;
	sigma = 0.5;

	simplexSpread = 0.1;

	errorLimit = 1e-3;
	evalLimit = 1000;

	reevalBest = false;

	// Internal variables
	N = 0;
	M = 0;
	fxo = 0.0;
	fxr = 0.0;
	fxe = 0.0;
	fxc = 0.0;
	state = 0;
	index = 0;
	evaluationCount = 0;
}

NelderMeadOptimizer::~NelderMeadOptimizer()
{
}

void NelderMeadOptimizer::Start(void)
{
	N = param.size();
	if(N == 0){
		state = 0;
		return;
	}
	M = N + 1;

	// Setup the simplex
	simplex.resize(N * M);
	size_t c = 0;
	for(size_t m = 0; m < M; m++)
		for(size_t n = 0; n < N; n++){
			simplex[c] = param[n] + (((n + 1) == m)? simplexSpread : 0.0);
			c++;
		}

	f.resize(M);
	xo.resize(N);
	xr.resize(N);
	xe.resize(N);
	xc.resize(N);
	index = 0;
	evaluationCount = 0;
	state = 1;
}

bool NelderMeadOptimizer::IsRunning(void)
{
	switch(state){
	case 0:
		throw(std::logic_error(
				"NelderMeadOptimizer::IsRunning - StartRun was not called."));

	case 1:
		{
			if(index >= M) throw(std::logic_error(
					"NelderMeadOptimizer::IsRunning - State progression not working."));
			for(size_t n = 0; n < N; n++)
				param[n] = simplex[index * N + n];
			state = 2;
			return true;
		}

	case 2:
		throw(std::logic_error(
				"NelderMeadOptimizer::IsRunning - SetError was not called."));

	case 3:
		break;

	case 4:
		throw(std::logic_error(
				"NelderMeadOptimizer::IsRunning - SetError was not called."));

	case 5:
		if(f[0] <= fxr && fxr < f[M - 2]){
			for(size_t n = 0; n < N; n++)
				simplex[(M - 1) * N + n] = xr[n];
			f[M - 1] = fxr;
			state = 3;
			break;
		}

		// 4.) Expansion
		if(fxr < f[0]){

			for(size_t n = 0; n < N; n++)
				xe[n] = xo[n] + gamma * (xr[n] - xo[n]);
			for(size_t n = 0; n < N; n++)
				param[n] = xe[n];
			state = 6;
			return true;
		}

		// 5.) Contraction
		for(size_t n = 0; n < N; n++)
			xc[n] = xo[n] + rho * (simplex[(M - 1) * N + n] - xo[n]);
		for(size_t n = 0; n < N; n++)
			param[n] = xc[n];
		state = 8;
		return true;

	case 6:
		throw(std::logic_error(
				"NelderMeadOptimizer::IsRunning - SetError was not called."));

	case 7:
		if(fxe < fxr){
			for(size_t n = 0; n < N; n++)
				simplex[(M - 1) * N + n] = xe[n];
			f[M - 1] = fxe;
		}else{
			for(size_t n = 0; n < N; n++)
				simplex[(M - 1) * N + n] = xr[n];
			f[M - 1] = fxr;
		}
		state = 3;
		break;

	case 8:
		throw(std::logic_error(
				"NelderMeadOptimizer::IsRunning - SetError was not called."));
	case 9:
		if(fxc < f[M - 1]){
			for(size_t n = 0; n < N; n++)
				simplex[(M - 1) * N + n] = xc[n];
			f[M - 1] = fxc;
			state = 3;
			break;
		}

		// 6.) Shrink
		for(size_t m = 1; m < M; m++){
			for(size_t n = 0; n < N; n++){
				simplex[m * N + n] = simplex[n]
						+ sigma * (simplex[m * N + n] - simplex[n]);
			}
		}
		index = 1;
		for(size_t n = 0; n < N; n++)
			param[n] = simplex[index * N + n];
		state = 2;
		return true;
	case 10:
		break;
	case 11:
		state = 12;
		break;
	case 12:
		return false;
	default:
		throw(std::logic_error(
				"NelderMeadOptimizer::IsRunning - State machine reached invalid state."));
	}

	if(state == 3){
		// 1.) Sort corners of simplex
		bool flag = true;
		while(flag){
			flag = false;
			for(size_t m = 0; m < (M - 1); m++){
				if(f[m] > f[m + 1]){
					for(size_t n = 0; n < N; n++)
						std::swap(simplex[m * N + n], simplex[(m + 1) * N + n]);
					std::swap(f[m], f[m + 1]);
					flag = true;
				}
			}
		}

		// Termination of algorithm?
		if(f[0] < errorLimit){
			state = 10;
		}else{

			// 2.) Calculate centroid
			for(size_t n = 0; n < N; n++)
				xo[n] = 0;
			for(size_t n = 0; n < (N * N); n++)
				xo[n % N] += simplex[n];
			for(size_t n = 0; n < N; n++)
				xo[n] /= (double) N;

			// 3.) Reflection
			for(size_t n = 0; n < N; n++)
				xr[n] = xo[n] + alpha * (xo[n] - simplex[n + N * N]);
			for(size_t n = 0; n < N; n++)
				param[n] = xr[n];
			state = 4;
			return true;
		}
	}

	if(state == 10){
		for(size_t n = 0; n < N; n++)
			param[n] = simplex[n];
		if(reevalBest){
			state = 11;
			return true;
		}
		state = 12;
		return false;
	}

	return false;
}

void NelderMeadOptimizer::SetError(double error)
{
	evaluationCount++;

	switch(state){
	case 2:
		f[index] = error;
		index++;
		state = (index < M)? 1 : 3;
		break;

	case 4:
		fxr = error;
		state = 5;
		break;

	case 6:
		fxe = error;
		state = 7;
		break;

	case 8:
		fxc = error;
		state = 9;
		break;

	case 10:
		break;

	case 11:
		state = 12;
		break;

	default:
		throw(std::logic_error(
				"NelderMeadOptimizer::SetError was called outside the main loop."));
	}

	if(evaluationCount >= evalLimit){
		if(state < 10) state = 10;
	}
}

void NelderMeadOptimizer::Stop(void)
{
	if(state < 10) state = 10;
}

size_t NelderMeadOptimizer::EvaluationsDone(void) const
{
	return evaluationCount;
}

double NelderMeadOptimizer::ResidualError(void) const
{
	return f[0];
}
