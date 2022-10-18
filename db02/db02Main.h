/***************************************************************
 * Name:      db02Main.h
 * Purpose:   Defines Application Frame
 * Author:    Mr. Arch Brooks (arch@archbrooks.com)
 * Created:   2022-10-16
 * Copyright: Mr. Arch Brooks (https://archbrooks.us/b4)
 * License:
 **************************************************************/

#ifndef DB02MAIN_H
#define DB02MAIN_H

//(*Headers(db02Frame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)

class db02Frame: public wxFrame
{
    public:

        db02Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~db02Frame();

    private:

        //(*Handlers(db02Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnmenDoDataSelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(db02Frame)
        static const long ID_MENUITEM1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(db02Frame)
        wxMenuItem* menDoData;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DB02MAIN_H
