/*
 * AboutDialog.cpp
 *
 *  Created on: 21.2.2010
 *      Author: Tobias Schaefer
 */
#include "AboutDialog.h"

AboutDialog::AboutDialog(wxWindow* parent) :
	GUIAboutDialog(parent)
{
	}

AboutDialog::~AboutDialog()
{

}

void AboutDialog::OnClose(wxCommandEvent& event)
{
	Close();
}
