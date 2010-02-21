/*
 * MainFrame.h
 *
 *  Created on: 18.09.2009
 *      Author: Tobias Schaefer
 */

#ifndef MAINFRAME_H_
#define MAINFRAME_H_

#include "Config.h"
#include "StdInclude.h"
#include "gui/gui.h"

#include "GameEngine.h"

class MainFrame:public MainFrameGui {
	// Constructor/ Destructor
public:
	MainFrame(wxWindow* parent);
	virtual ~MainFrame();


	// Member variables
private:
	float cogShift;

	unsigned char takeFrom;

	GameEngine engine;


	// Methods
private:

//	void OnLoadImage(wxCommandEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnMotion(wxMouseEvent& event);
	void OnLeftDown(wxMouseEvent& event);

	void Animate(void);


};

#endif /* MAINFRAME_H_ */
