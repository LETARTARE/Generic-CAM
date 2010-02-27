/*
 * StdInclude.h
 *
 *  Takes care of precompiled header issues.
 *
 *  Created on: 21.05.2009
 *  Author: Tobias Schaefer
 *
 */

#ifndef STDINC_H_
#define STDINC_H_

// For compilers that support precompilation, includes "wx/wx.h".

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


#endif /* STDINC_H_ */
