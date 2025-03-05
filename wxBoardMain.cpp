/***************************************************************
 * Name:      wxBoardMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Anatoliy Sova (anatoliysova@gmail.com)
 * Created:   2025-03-04
 * Copyright: Anatoliy Sova (firelizardsoftware.com)
 * License:
 **************************************************************/

#include "wxBoardMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(wxBoardFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

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

//(*IdInit(wxBoardFrame)
const wxWindowID wxBoardFrame::idMenuQuit = wxNewId();
const wxWindowID wxBoardFrame::idMenuAbout = wxNewId();
const wxWindowID wxBoardFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxBoardFrame,wxFrame)
    //(*EventTable(wxBoardFrame)
    //*)
END_EVENT_TABLE()

wxBoardFrame::wxBoardFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wxBoardFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
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

    Connect(idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxBoardFrame::OnQuit);
    Connect(idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxBoardFrame::OnAbout);
    //*)
}

wxBoardFrame::~wxBoardFrame()
{
    //(*Destroy(wxBoardFrame)
    //*)
}

void wxBoardFrame::OnQuit(wxCommandEvent& event)
{
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
    Close();
}

void wxBoardFrame::StartNewGame(GameVariant newGameVariant) const
{
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
	//this->ui->vboard->SetGameVariant(newGameVariant);
	//this->ui->vboard->GetBoard()->Initialize();
	//this->ui->vboard->SetCurrentPlayer(White);
	//this->ui->textEdit->setText("");
	//this->ui->textEdit_2->setText("");
	//this->ui->statusBar->showMessage(newGameVariant == Xiangqi ? "Red move" : "White move");
	//this->ui->vboard->repaint();
}

void wxBoardFrame::LoadEngine(const std::shared_ptr<Engine>& engine, const wxString& engineExe, PieceColour player)
{
	if (engine != nullptr)
	{
		const wxProcess* process = engine->RunProcess(this, engineExe);
		if (process->GetPid() > 0 && process->IsRedirected())
		{
			if (engine->GetType() == XBoard)
			{
				GameVariant gv;
				switch (gv/*ui->vboard->GetGameVariant()*/)
				{
				case MiniShogi:
					engine->StartGame("5x5+5_shogi");
					break;
				case JudkinShogi:
					engine->StartGame("6x6+6_shogi");
					break;
				case ShoShogi:
					engine->StartGame("sho");
					break;
				case WaShogi:
					engine->StartGame("washogi");
					break;
				case CrazyWa:
					engine->StartGame("crazywa");
					break;
				case ChuShogi:
					engine->StartGame("chu");
					break;
				case DaiShogi:
					engine->StartGame("dai");
					break;
				case TenjikuShogi:
					engine->StartGame("tenjiku");
					break;
				case Shogi:
					engine->StartGame("shogi");
					break;
				case Shatranj:
					engine->StartGame("shatranj");
					break;
				case Makruk:
					engine->StartGame("makruk");
					break;
				case Xiangqi:
					engine->StartGame("xiangqi");
					break;
				case Chess:
					engine->StartGame("normal");
					break;
				case DaiDaiShogi:
				case MakaDaiDaiShogi:
				case KoShogi:
					engine->StartGame();
					break;
				}
				if (engineExe.Lower().Contains("hachu"))
				{
					std::dynamic_pointer_cast<WbEngine>(engine)->SetMemory(_engineMemorySize);
				}
			}
			else
			{
				engine->StartGame();
			}
			if (player == Black)
			{
				//connect(process, SIGNAL(readyReadStandardOutput()), this->ui->vboard, SLOT(blackEngineReadyReadStandardOutput()));
				//connect(process, SIGNAL(readyReadStandardError()), this->ui->vboard, SLOT(blackEngineReadyReadStandardError()));
				//connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this->ui->vboard, SLOT(blackEngineReadyReadStandardError()));
				//this->ui->vboard->SetBlackEngine(engine);
			}
			else
			{
				//connect(process, SIGNAL(readyReadStandardOutput()), this->ui->vboard, SLOT(whiteEngineReadyReadStandardOutput()));
				//connect(process, SIGNAL(readyReadStandardError()), this->ui->vboard, SLOT(whiteEngineReadyReadStandardError()));
				//connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this->ui->vboard, SLOT(whiteEngineReadyReadStandardError()));
				//this->ui->vboard->SetWhiteEngine(engine);
				engine->Move();
			}
		}
		else
			wxMessageBox("Error while running engine");
	}
}

void wxBoardFrame::OnAbout(wxCommandEvent& event)
{
	wxString msg;
	msg.Append("wxBoard 0.9.8 beta\n");
	msg.Append("Programming by Anatoliy Sova\n");
	msg.Append("Wa Shogi Mnemonic graphics by Ilya V. Novikov\n");
	msg.Append("Ko Shogi graphics by TKR101010 (from Deviantart)\n");
	msg.Append("Maka Dai Dai Shogi Kanji graphics by Joe Henbethydd\n");
	msg.Append("Shogi Variants Kanji graphics by Shigeki Watanabe\n");
	msg.Append("Fire Lizard Software 2025");
    wxMessageBox(msg);
}

void wxBoardFrame::StopEngine(std::shared_ptr<Engine> engine)
{
	if (engine)
	{
		engine->SetActive(false);
		engine->Quit();
		engine.reset();
	}
}

void wxBoardFrame::readXmlUsingStream(const wxString& fileName, wxGrid* engineTable)
{
    // Attempt to load the file into a wxXmlDocument
    wxXmlDocument doc;
    if (!doc.Load(fileName))
    {
        wxLogError("Failed to open the file '%s' for reading.", fileName);
        return;
    }

    // Check that the root element is what we expect (e.g. <Engines>).
    wxXmlNode* root = doc.GetRoot();
    if (!root || root->GetName() != "Engines")
    {
        wxLogError("Invalid or missing root element. Expected <Engines>.");
        return;
    }

    // Iterate over child nodes of <Engines>
    for (wxXmlNode* child = root->GetChildren(); child; child = child->GetNext())
    {
        // Only process <Engine> elements
        if (child->GetName() == "Engine")
        {
            // Read attributes
            wxString engineName    = child->GetAttribute("EngineName",    "");
            wxString gameVariant   = child->GetAttribute("GameVariant",   "");
            wxString engineProtocol= child->GetAttribute("EngineProtocol","");
            wxString enginePath    = child->GetAttribute("EnginePath",    "");

            // Insert a new row if we have at least an EngineName and EnginePath
            if (!engineName.IsEmpty() && !enginePath.IsEmpty())
            {
                int currentRow = engineTable->GetNumberRows();
                // Insert one new row at the bottom
                engineTable->InsertRows(currentRow, 1);

                // Populate that row's cells
                engineTable->SetCellValue(currentRow, 0, engineName);
                engineTable->SetCellValue(currentRow, 1, gameVariant);
                engineTable->SetCellValue(currentRow, 2, engineProtocol);
                engineTable->SetCellValue(currentRow, 3, enginePath);
            }
        }
    }
}

void wxBoardFrame::createXmlFromTable(const wxString& fileName, const wxGrid* engineTable)
{
    // We'll create an in-memory XML document, then write it to temp.xml
    wxXmlDocument doc;

    // Create a root node: <Engines>
    wxXmlNode* root = new wxXmlNode(nullptr, wxXML_ELEMENT_NODE, "Engines");
    doc.SetRoot(root);

    // For each row in the table, create an <Engine> element with attributes
    int rowCount = engineTable->GetNumberRows();
    for (int i = 0; i < rowCount; ++i)
    {
        wxString engineName     = engineTable->GetCellValue(i, 0);
        wxString gameVariant    = engineTable->GetCellValue(i, 1);
        wxString engineProtocol = engineTable->GetCellValue(i, 2);
        wxString enginePath     = engineTable->GetCellValue(i, 3);

        // <Engine EngineName="..." GameVariant="..." ... />
        wxXmlNode* engineNode = new wxXmlNode(root, wxXML_ELEMENT_NODE, "Engine");
        engineNode->AddAttribute("EngineName",     engineName);
        engineNode->AddAttribute("GameVariant",    gameVariant);
        engineNode->AddAttribute("EngineProtocol", engineProtocol);
        engineNode->AddAttribute("EnginePath",     enginePath);
    }

    // Replicate your "temp file" approach
    wxFileName fn(fileName);
    wxString tempFileName = fn.GetPathWithSep() + "temp.xml";

    // Write the document to tempFileName
    if (!doc.Save(tempFileName))
    {
        wxLogError("Failed to write to temp file: %s", tempFileName);
        return;
    }

    // Close any old handle to fileName, remove it, then rename temp.xml to the final path
    wxRemoveFile(fileName);
    if (!wxRenameFile(tempFileName, fileName))
    {
        wxLogError("Failed to rename temp file to: %s", fileName);
    }
}
