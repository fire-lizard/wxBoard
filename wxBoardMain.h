#ifndef WXBOARDMAIN_H
#define WXBOARDMAIN_H

//(*Headers(wxBoardMain)
#include <wx/frame.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
//*)

#include <memory>
#include <wx/grid.h>
#include <wx/xml/xml.h>
#include <wx/log.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/stdpaths.h>
#include "WbEngine.h"
#include "UcciEngine.h"
#include "QianhongEngine.h"
#include "UsiEngine.h"
#include "ChessBoard.h"
#include "WaShogiBoard.h"
#include "EngineOutputHandler.h"
#include "IniFile.h"
#include "NewGameDialog.h"
#include "EngineManager.h"
#include "SettingsDialog.h"

class wxBoardMain: public wxFrame
{
    public:

        wxBoardMain(wxWindow* parent,wxWindowID id=wxID_ANY);
        virtual ~wxBoardMain();

        //(*Declarations(wxBoardMain)
        wxStatusBar* StatusBar1;
        wxToolBar* ToolBar1;
        wxToolBarToolBase* ToolBarItem10;
        wxToolBarToolBase* ToolBarItem1;
        wxToolBarToolBase* ToolBarItem2;
        wxToolBarToolBase* ToolBarItem3;
        wxToolBarToolBase* ToolBarItem4;
        wxToolBarToolBase* ToolBarItem5;
        wxToolBarToolBase* ToolBarItem6;
        wxToolBarToolBase* ToolBarItem7;
        wxToolBarToolBase* ToolBarItem8;
        wxToolBarToolBase* ToolBarItem9;
        //*)

    protected:

        //(*Identifiers(wxBoardMain)
        static const wxWindowID ID_TOOLBARITEM1;
        static const wxWindowID ID_TOOLBARITEM2;
        static const wxWindowID ID_TOOLBARITEM3;
        static const wxWindowID ID_TOOLBARITEM4;
        static const wxWindowID ID_TOOLBARITEM5;
        static const wxWindowID ID_TOOLBARITEM6;
        static const wxWindowID ID_TOOLBARITEM7;
        static const wxWindowID ID_TOOLBARITEM8;
        static const wxWindowID ID_TOOLBARITEM9;
        static const wxWindowID ID_TOOLBARITEM10;
        static const wxWindowID ID_TOOLBAR1;
        static const wxWindowID ID_STATUSBAR1;
        //*)

    private:

        //(*Handlers(wxBoardMain)
        //*)

        DECLARE_EVENT_TABLE()

        void LoadEngine(const std::shared_ptr<Engine>& engine, const wxString& engineExe, PieceColour player);

        static void StopEngine(std::shared_ptr<Engine> engine);

        void StartNewGame(GameVariant newGameVariant) const;

        static void readXmlUsingStream(const wxString& fileName, wxGrid* engineTable);

        static void createXmlFromTable(const wxString& fileName, const wxGrid* engineTable);

        void OnNewGame(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnStopGame(wxCommandEvent& event);
        void OnEditorMode(wxCommandEvent& event);
        void OnClearBoard(wxCommandEvent& event);
        void OnSettings(wxCommandEvent& event);
        void OnEngineManager(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnQuit(wxCommandEvent& event);

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

#endif
