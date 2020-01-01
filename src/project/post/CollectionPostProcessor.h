///////////////////////////////////////////////////////////////////////////////
// Name               : CollectionPostProcessor.h
// Purpose            : Abstract Base Postprocessor
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.12.2019
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

#ifndef SRC_PROJECT_POST_COLLECTIONPOSTPROCESSOR_H_
#define SRC_PROJECT_POST_COLLECTIONPOSTPROCESSOR_H_

#include <string>
#include <vector>

#include "PostProcessor.h"

class CollectionPostProcessor {
public:
	CollectionPostProcessor();
	virtual ~CollectionPostProcessor();
	void Refresh(void);

	std::vector <std::string> GetNames(void) const;
	size_t Size(void) const;
	PostProcessor& operator[](size_t index);

private:
	std::vector <PostProcessor *> pp;
};

#endif /* SRC_PROJECT_POST_COLLECTIONPOSTPROCESSOR_H_ */
