#include "wxBoardMain.h"

//(*InternalHeaders(wxBoardMain)
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(wxBoardMain)
const wxWindowID wxBoardMain::ID_TOOLBARITEM1 = wxNewId();
const wxWindowID wxBoardMain::ID_TOOLBARITEM2 = wxNewId();
const wxWindowID wxBoardMain::ID_TOOLBARITEM3 = wxNewId();
const wxWindowID wxBoardMain::ID_TOOLBARITEM4 = wxNewId();
const wxWindowID wxBoardMain::ID_TOOLBARITEM5 = wxNewId();
const wxWindowID wxBoardMain::ID_TOOLBARITEM6 = wxNewId();
const wxWindowID wxBoardMain::ID_TOOLBARITEM7 = wxNewId();
const wxWindowID wxBoardMain::ID_TOOLBARITEM8 = wxNewId();
const wxWindowID wxBoardMain::ID_TOOLBARITEM9 = wxNewId();
const wxWindowID wxBoardMain::ID_TOOLBARITEM10 = wxNewId();
const wxWindowID wxBoardMain::ID_TOOLBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxBoardMain,wxFrame)
    //(*EventTable(wxBoardMain)
    //*)
END_EVENT_TABLE()

wxBoardMain::wxBoardMain(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wxBoardMain)
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL, _T("ID_TOOLBAR1"));
    ToolBarItem1 = ToolBar1->AddTool(ID_TOOLBARITEM1, _("New game"), wxBitmap(wxImage(_T("D:\\Code\\wxBoard\\images\\toolbar\\New.png"))), wxNullBitmap, wxITEM_NORMAL, _("New game"), wxEmptyString);
    ToolBarItem2 = ToolBar1->AddTool(ID_TOOLBARITEM2, _("Open"), wxBitmap(wxImage(_T("D:\\Code\\wxBoard\\images\\toolbar\\Open.png"))), wxNullBitmap, wxITEM_NORMAL, _("Open"), wxEmptyString);
    ToolBarItem3 = ToolBar1->AddTool(ID_TOOLBARITEM3, _("Save"), wxBitmap(wxImage(_T("D:\\Code\\wxBoard\\images\\toolbar\\Save.png"))), wxNullBitmap, wxITEM_NORMAL, _("Save"), wxEmptyString);
    ToolBarItem4 = ToolBar1->AddTool(ID_TOOLBARITEM4, _("Stop game"), wxBitmap(wxImage(_T("D:\\Code\\wxBoard\\images\\toolbar\\Stop.png"))), wxNullBitmap, wxITEM_NORMAL, _("Stop game"), wxEmptyString);
    ToolBar1->AddSeparator();
    ToolBarItem5 = ToolBar1->AddTool(ID_TOOLBARITEM5, _("Editor mode"), wxBitmap(wxImage(_T("D:\\Code\\wxBoard\\images\\toolbar\\Place.png"))), wxNullBitmap, wxITEM_NORMAL, _("Editor mode"), wxEmptyString);
    ToolBarItem6 = ToolBar1->AddTool(ID_TOOLBARITEM6, _("Clear board"), wxBitmap(wxImage(_T("D:\\Code\\wxBoard\\images\\toolbar\\Clear.png"))), wxNullBitmap, wxITEM_NORMAL, _("Clear board"), wxEmptyString);
    ToolBar1->AddSeparator();
    ToolBarItem7 = ToolBar1->AddTool(ID_TOOLBARITEM7, _("Settings"), wxBitmap(wxImage(_T("D:\\Code\\wxBoard\\images\\toolbar\\Settings.png"))), wxNullBitmap, wxITEM_NORMAL, _("Settings"), wxEmptyString);
    ToolBarItem8 = ToolBar1->AddTool(ID_TOOLBARITEM8, _("Engine Manager"), wxBitmap(wxImage(_T("D:\\Code\\wxBoard\\images\\toolbar\\Table.png"))), wxNullBitmap, wxITEM_NORMAL, _("Engine Manager"), wxEmptyString);
    ToolBar1->AddSeparator();
    ToolBarItem9 = ToolBar1->AddTool(ID_TOOLBARITEM9, _("About"), wxBitmap(wxImage(_T("D:\\Code\\wxBoard\\images\\toolbar\\About.png"))), wxNullBitmap, wxITEM_NORMAL, _("About"), wxEmptyString);
    ToolBarItem10 = ToolBar1->AddTool(ID_TOOLBARITEM10, _("Exit"), wxBitmap(wxImage(_T("D:\\Code\\wxBoard\\images\\toolbar\\Exit.png"))), wxNullBitmap, wxITEM_NORMAL, _("Exit"), wxEmptyString);
    ToolBar1->Realize();
    SetToolBar(ToolBar1);
    //*)
}

wxBoardMain::~wxBoardMain()
{
    //(*Destroy(wxBoardMain)
    //*)
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
}

void wxBoardMain::StartNewGame(GameVariant newGameVariant) const
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

void wxBoardMain::LoadEngine(const std::shared_ptr<Engine>& engine, const wxString& engineExe, PieceColour player)
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

/*void wxBoardMain::OnAbout(wxCommandEvent& event)
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
}*/

void wxBoardMain::StopEngine(std::shared_ptr<Engine> engine)
{
	if (engine)
	{
		engine->SetActive(false);
		engine->Quit();
		engine.reset();
	}
}

void wxBoardMain::readXmlUsingStream(const wxString& fileName, wxGrid* engineTable)
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

void wxBoardMain::createXmlFromTable(const wxString& fileName, const wxGrid* engineTable)
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
