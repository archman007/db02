/***************************************************************
 * Name:      db02App.cpp
 * Purpose:   Code for Application Class
 * Author:    Mr. Arch Brooks (arch@archbrooks.com)
 * Created:   2022-10-16
 * Copyright: Mr. Arch Brooks (https://archbrooks.us/b4)
 * License:
 **************************************************************/

#include "db02App.h"

//(*AppHeaders
#include "db02Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(db02App);

bool db02App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	db02Frame* Frame = new db02Frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
