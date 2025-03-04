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

//(*Headers(wxBoardDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
//*)

class wxBoardDialog: public wxDialog
{
    public:

        wxBoardDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~wxBoardDialog();

    private:

        //(*Handlers(wxBoardDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(wxBoardDialog)
        static const wxWindowID ID_STATICTEXT1;
        static const wxWindowID ID_BUTTON1;
        static const wxWindowID ID_STATICLINE1;
        static const wxWindowID ID_BUTTON2;
        //*)

        //(*Declarations(wxBoardDialog)
        wxBoxSizer* BoxSizer1;
        wxBoxSizer* BoxSizer2;
        wxButton* Button1;
        wxButton* Button2;
        wxStaticLine* StaticLine1;
        wxStaticText* StaticText1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WXBOARDMAIN_H
