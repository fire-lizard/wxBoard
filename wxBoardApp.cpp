/***************************************************************
 * Name:      wxBoardApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Anatoliy Sova (anatoliysova@gmail.com)
 * Created:   2025-03-04
 * Copyright: Anatoliy Sova (firelizardsoftware.com)
 * License:
 **************************************************************/

#include "wxBoardApp.h"

//(*AppHeaders
#include "wxBoardMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxBoardApp);

bool wxBoardApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        wxBoardDialog Dlg(NULL);
        SetTopWindow(&Dlg);
        Dlg.ShowModal();
        wxsOK = false;
    }
    //*)
    return wxsOK;

}
