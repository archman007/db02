/***************************************************************
 * Name:      db02Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    Mr. Arch Brooks (arch@archbrooks.com)
 * Created:   2022-10-16
 * Copyright: Mr. Arch Brooks (https://archbrooks.us/b4)
 * License:
 **************************************************************/

#include "db02Main.h"
#include <wx/msgdlg.h>
#include <mysql++.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;
using namespace mysqlpp;

//(*InternalHeaders(db02Frame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(db02Frame)
const long db02Frame::ID_MENUITEM1 = wxNewId();
const long db02Frame::idMenuQuit = wxNewId();
const long db02Frame::idMenuAbout = wxNewId();
const long db02Frame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(db02Frame,wxFrame)
    //(*EventTable(db02Frame)
    //*)
END_EVENT_TABLE()

db02Frame::db02Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(db02Frame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    menDoData = new wxMenuItem(Menu1, ID_MENUITEM1, _("Do Data"), _("Begin Data Process"), wxITEM_NORMAL);
    Menu1->Append(menDoData);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&db02Frame::OnmenDoDataSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&db02Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&db02Frame::OnAbout);
    //*)
}

db02Frame::~db02Frame()
{
    //(*Destroy(db02Frame)
    //*)
}

void db02Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void db02Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void db02Frame::OnmenDoDataSelected(wxCommandEvent& event)
{
    try
    {
        Connection conn(true);
        conn.connect("bcswebtools", "localhost", "bcs", "Peace007!amb");
        Query query = conn.query();
        query << "SELECT * FROM lk1 LIMIT 10";
        StoreQueryResult ares = query.store();
        for (size_t i = 0; i < ares.num_rows(); i++)
        {
            string buf = std::string(ares[i]["cat"]);
            wxMessageBox(buf);
            cout << "Name: " << ares[i]["idlk1"] << " - Address: " << ares[i]["cat"] << endl;

        }

        if (ares.num_rows() == 0)
        {
            wxMessageBox("No Data Detected!!", "Zero Query Results", wxICON_HAND);

        }
    }
    catch (BadQuery er)     // handle any connection or
    {
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        wxMessageBox("Connection Error!", "Connection Error Detected", wxICON_ERROR | wxICON_HAND);
    }
    catch (const BadConversion& er)
    {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
             "\tretrieved data size: " << er.retrieved <<
             ", actual size: " << er.actual_size << endl;
        wxMessageBox("Conversino Error!", "Conversin Error Detected", wxICON_HAND);
    }
    catch (const Exception& er)
    {
        // Catch-all for any other MySQL++ exceptions
        string buf = er.what();
        cerr << "Error: " << er.what() << endl;
        wxMessageBox("Miscalleanous Error!", "Other Error Detected", wxICON_HAND);
    }
}
