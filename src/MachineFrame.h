/*
 * MachineFrame.h
 *
 *  Created on: 21.02.2010
 *      Author: toby
 */

#ifndef MACHINEFRAME_H_
#define MACHINEFRAME_H_

#include "gui/gui.h"

class MachineFrame:public GUIMachineFrame {
public:
	MachineFrame(wxWindow* parent);
	virtual ~MachineFrame();
};

#endif /* MACHINEFRAME_H_ */
