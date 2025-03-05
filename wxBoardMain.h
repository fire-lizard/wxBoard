#ifndef HEADER_4EEDF789F72450FD
#define HEADER_4EEDF789F72450FD

/***************************************************************
 * Name:      wxBoardMain.h
 * Purpose:   Defines Application Frame
 * Author:    Anatoliy Sova (anatoliysova@gmail.com)
 * Created:   2025-03-04
 * Copyright: Anatoliy Sova (firelizardsoftware.com)
 * License:
 **************************************************************/

#ifndef WXBOARDMAIN_H
#define WXBOARDMAIN_H

//(*Headers(wxBoardFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)

class wxBoardFrame: public wxFrame
{
    public:

        wxBoardFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wxBoardFrame();

    private:

        //(*Handlers(wxBoardFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(wxBoardFrame)
        static const wxWindowID idMenuQuit;
        static const wxWindowID idMenuAbout;
        static const wxWindowID ID_STATUSBAR1;
        //*)

        //(*Declarations(wxBoardFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WXBOARDMAIN_H
#endif // header guard

