#!/bin/bash
sed -i -e "s/class wxDocChildFrame;/#include <wx\/docview.h>\n#include <wx\/config.h>/" -e "s/class wxDocParentFrame\;//" -e "s/GUIFrameMain(\s*wxWindow\* parent,/GUIFrameMain(wxDocument\* doc, wxView\* view, wxDocParentFrame\* parent,/" ../src/gui/gui.h
sed -i -e "s/GUIFrameMain( wxWindow\* parent,/GUIFrameMain(wxDocument\* doc, wxView\* view, wxDocParentFrame\* parent,/" -e "s/wxDocChildFrame( parent,/wxDocChildFrame( doc, view, parent,/" ../src/gui/gui.cpp


