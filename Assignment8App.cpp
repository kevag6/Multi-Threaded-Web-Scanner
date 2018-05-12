/***************************************************************
 * Name:      Assignment8App.cpp
 * Purpose:   Code for Application Class
 * Author:    Kevin Grifo ()
 * Created:   2018-04-02
 * Copyright: Kevin Grifo ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "Assignment8App.h"

//(*AppHeaders
#include "Assignment8Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(Assignment8App);

bool Assignment8App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	Assignment8Frame* Frame = new Assignment8Frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
