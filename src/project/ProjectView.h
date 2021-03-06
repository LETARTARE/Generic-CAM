///////////////////////////////////////////////////////////////////////////////
// Name               : ProjectView.h
// Purpose            : View for a Project
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.12.2018
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

#ifndef SRC_PROJECT_PROJECTVIEW_H_
#define SRC_PROJECT_PROJECTVIEW_H_

/*!\class ProjectView
 * \brief View of DocView model
 *
 * This class is the View part of the Data/View model. The other part is the Project.
 *
 * This class displays the Project depending on the selections made in the TreeSetup.
 *
 */

#include "generator/CNCSimulator.h"
#include "Selection.h"

#include <stddef.h>
#include <wx/docview.h>
#include <wx/object.h>
#include <wx/event.h>

class ProjectView:public wxView {
	friend class DialogAnimation;
public:
	enum ViewType {
		vIdle= 0, vObject, vRun, vOrigin, vGenerator, vSimulation
	} type;
	enum SimulationCenterType {
		vCenterMachine, vCenterTool, vCenterWorkpiece
	} simulationCenter;
	enum SimulationDisplayType {
		vSimulationWorkpiece = 0,
		vSimulationTool = 1,
		vSimulationHolder = 2,
		vSimulationMachine = 3
	} simulationDisplay;

	ProjectView();
	virtual ~ProjectView();

	void SetViewType(ViewType type);
	void FreezeViewType(bool freeze);
	void SetSelection(const Selection &selection);
	void SetHover(const Selection &hover);

	void Render(void) const;
	void RenderPick(void) const;

	bool OnCreate(wxDocument* doc, long flags);
	void OnDraw(wxDC *dc);
	void OnUpdate(wxView *sender, wxObject *hint = NULL);
	void OnUpdate3D(void);
	void OnUpdateTree(wxCommandEvent& event);

	bool OnClose(bool deleteWindow = true);

protected:
	CNCSimulator simulator; ///< Simulator, controlled by DialogAnimation
	bool showSimulated;

private:
	Selection selection; ///< Selection for displaying, set by FrameMain
	Selection hover; ///< Hilighted element, set by FrameMain
	bool freeze;
	size_t lastRunID;
private:
	void RenderCoordinateSystem(void) const;

	void PaintObjects(const Selection& sel, const OpenGLMaterial &face,
			const OpenGLMaterial &edge) const;
	void PaintRun(const Selection& sel) const;
	void PaintGenerators(const Selection& sel) const;

wxDECLARE_EVENT_TABLE();

DECLARE_DYNAMIC_CLASS(ProjectView)
	;
};

#endif /* SRC_PROJECT_PROJECTVIEW_H_ */
