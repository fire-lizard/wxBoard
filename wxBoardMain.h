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

#include <memory>
#include <wx/grid.h>
#include <wx/xml/xml.h>
#include <wx/log.h>
//(*Headers(wxBoardFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)
#include "WbEngine.h"

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

        void LoadEngine(const std::shared_ptr<Engine>& engine, const wxString& engineExe, PieceColour player);

        static void StopEngine(std::shared_ptr<Engine> engine);

        void StartNewGame(GameVariant newGameVariant) const;

        static void readXmlUsingStream(const wxString& fileName, wxGrid* engineTable);

        static void createXmlFromTable(const wxString& fileName, const wxGrid* engineTable);

        int _engineMemorySize = 80;
        std::shared_ptr<Engine> _whiteEngine = nullptr;
        wxString _whiteEngineExe = "";
        wxString _whiteEngineName = "";
        EngineProtocol _whiteEngineProtocol = XBoard;
        std::shared_ptr<Engine> _blackEngine = nullptr;
        wxString _blackEngineExe = "";
        wxString _blackEngineName = "";
        EngineProtocol _blackEngineProtocol = XBoard;
        wxString _userName;
        wxString _settingsDir;
        wxString _settingsFileName = "QBoard.ini";
        wxString _enginesListFileName = "QBoardEngines.xml";
        std::vector<std::tuple<wxString, GameVariant, EngineProtocol, wxString>> _engines;
};

#endif // WXBOARDMAIN_H
#endif // header guard

