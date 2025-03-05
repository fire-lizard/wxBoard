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
const wxWindowID wxBoardMain::ID_STATUSBAR1 = wxNewId();
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
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -10 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    //*)

	Bind(wxEVT_TOOL, &wxBoardMain::OnNewGame, this, ID_TOOLBARITEM1);
	Bind(wxEVT_TOOL, &wxBoardMain::OnOpen, this, ID_TOOLBARITEM2);
	Bind(wxEVT_TOOL, &wxBoardMain::OnSave, this, ID_TOOLBARITEM3);
	Bind(wxEVT_TOOL, &wxBoardMain::OnStopGame, this, ID_TOOLBARITEM4);
	Bind(wxEVT_TOOL, &wxBoardMain::OnEditorMode, this, ID_TOOLBARITEM5);
	Bind(wxEVT_TOOL, &wxBoardMain::OnClearBoard, this, ID_TOOLBARITEM6);
	Bind(wxEVT_TOOL, &wxBoardMain::OnSettings, this, ID_TOOLBARITEM7);
	Bind(wxEVT_TOOL, &wxBoardMain::OnEngineManager, this, ID_TOOLBARITEM8);
	Bind(wxEVT_TOOL, &wxBoardMain::OnAbout, this, ID_TOOLBARITEM9);
	Bind(wxEVT_TOOL, &wxBoardMain::OnQuit, this, ID_TOOLBARITEM10);

	if (!wxGetEnv("USER", &_userName))
		wxGetEnv("USERNAME", &_userName);
	//this->ui->vboard->SetMainWindow(this);
	//this->ui->vboard->SetTextEdit(this->ui->textEdit);
	//this->ui->vboard->SetTextEdit2(this->ui->textEdit_2);
	//this->ui->vboard->SetStatusBar(this->ui->statusBar);
	//QFont font = this->ui->statusBar->font();
	//font.setBold(true);
	//this->ui->statusBar->setFont(font);
	//this->ui->statusBar->showMessage(this->ui->vboard->GetGameVariant() == Xiangqi ? "Red move" : "White move");
	_settingsDir = wxStandardPaths::Get().GetUserDataDir();
	if (wxFileExists(_settingsDir + "/" + _settingsFileName))
	{
		wxArrayString settings = IniFile::readFromIniFile(_settingsDir + "/" + _settingsFileName);
		//this->ui->vboard->SetGameVariant(EngineManager::StringToGameVariant(settings[0]));
		PieceStyle pieceStyle;
		if (settings[2] == "Mnemonic")
		{
			pieceStyle = Mnemonic;
		}
		else if (settings[2] == "Asian")
		{
			pieceStyle = Asian;
		}
		else if (settings[2] == "Asian 2")
		{
			pieceStyle = Asian2;
		}
		else
		{
			pieceStyle = European;
		}
		//this->ui->vboard->SetPieceStyle(pieceStyle);
		//this->ui->vboard->SetEngineOutput(settings[3] == "Verbose" ? Verbose : Concise);
		//this->ui->vboard->GetBoard()->Initialize();
		//this->ui->statusBar->showMessage(settings[1] == "Xiangqi" ? "Red move" : "White move");
		//this->ui->vboard->repaint();
	}
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
	this->StatusBar1->SetStatusText(newGameVariant == Xiangqi ? "Red move" : "White move");
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

void wxBoardMain::OnAbout(wxCommandEvent& event)
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

void wxBoardMain::OnClearBoard(wxCommandEvent& event)
{
	int response = wxMessageBox("Are you sure you want to clear the board?", "Warning", wxYES_NO | wxICON_QUESTION, this);
	if (response == wxYES)
	{
		StopEngine(_whiteEngine);
		StopEngine(_blackEngine);
		Board* board = new ChessBoard();// ui->vboard->GetBoard();
		const int width = board->GetWidth();
		const int height = board->GetHeight();
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				const Piece* p = board->GetData(i, j);
				delete p;
				board->SetData(i, j, nullptr);
			}
		}
		//if (!ui->vboard->GetEditorMode())
		{
			//ui->vboard->SetEditorMode(true);
		}
		//ui->vboard->repaint();
	}
}

void wxBoardMain::OnNewGame(wxCommandEvent& event)
{
    NewGameDialog* newGameDialog = new NewGameDialog(this);
    GameVariant currentGameVariant = Chess; //this->ui->vboard->GetGameVariant()

    newGameDialog->GetWhitePlayer()->Append(_userName);
    newGameDialog->GetBlackPlayer()->Append(_userName);

    if (currentGameVariant == Xiangqi)
    {
        newGameDialog->GetWhitePlayerLabel()->SetLabel("Red player");
    }
    else
    {
        newGameDialog->GetWhitePlayerLabel()->SetLabel("White player");
    }

    _engines.clear();

    wxString filePath = _settingsDir + "/" + _enginesListFileName;
    wxFile file(filePath);
    if (!file.IsOpened())
    {
        wxLogError("Failed to open the file '%s' for reading.", filePath);
        return;
    }

    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filePath))
    {
        wxLogError("Error reading XML from '%s'.", filePath);
        return;
    }

    wxXmlNode* root = xmlDoc.GetRoot();
    if (!root)
    {
        wxLogError("XML file has no root node.");
        return;
    }

    for (wxXmlNode* node = root->GetChildren(); node; node = node->GetNext())
    {
        if (node->GetName() == "Engine")
        {
            wxString engineName;
            GameVariant gameVariant = Chess;      // default
            EngineProtocol engineProtocol = UCI;  // default
            wxString enginePath;

            wxXmlAttribute* attr = node->GetAttributes();
            while (attr)
            {
                if (attr->GetName() == "EngineName")
                {
                    engineName = attr->GetValue();
                }
                else if (attr->GetName() == "GameVariant")
                {
                    gameVariant = EngineManager::StringToGameVariant(attr->GetValue());
                }
                else if (attr->GetName() == "EngineProtocol")
                {
                    engineProtocol = EngineManager::StringToEngineProtocol(attr->GetValue());
                }
                else if (attr->GetName() == "EnginePath")
                {
                    enginePath = attr->GetValue();
                }
                attr = attr->GetNext();
            }

            if (!engineName.IsEmpty() && !enginePath.IsEmpty() &&
                gameVariant == currentGameVariant)
            {
                _engines.emplace_back(engineName, gameVariant, engineProtocol, enginePath);
            }
        }
    }
    file.Close();

    for (auto& engine : _engines)
    {
        newGameDialog->GetWhitePlayer()->Append(std::get<0>(engine));
        newGameDialog->GetBlackPlayer()->Append(std::get<0>(engine));
    }

    int result = newGameDialog->ShowModal();
    if (result == wxID_OK)
    {
        //this->ui->textEdit->SetValue("");
        //this->ui->textEdit_2->SetValue("");
        this->StatusBar1->SetStatusText("");

        int bpSelectedIndex = newGameDialog->GetBlackPlayer()->GetSelection();
        int wpSelectedIndex = newGameDialog->GetWhitePlayer()->GetSelection();

        if (bpSelectedIndex > 0)
        {
            auto tpl = _engines[bpSelectedIndex - 1];
            _blackEngineName     = std::get<0>(tpl);
            _blackEngineProtocol = std::get<2>(tpl);
            _blackEngineExe      = std::get<3>(tpl);
        }
        else
        {
            _blackEngineExe.clear();
        }

        // White
        if (wpSelectedIndex > 0)
        {
            auto tpl = _engines[wpSelectedIndex - 1];
            _whiteEngineName     = std::get<0>(tpl);
            _whiteEngineProtocol = std::get<2>(tpl);
            _whiteEngineExe      = std::get<3>(tpl);
        }
        else
        {
            _whiteEngineExe.clear();
        }

        if (!_blackEngineExe.IsEmpty())
        {
            switch (_blackEngineProtocol)
            {
            case UCI:
                _blackEngine = std::make_shared<UciEngine>();
                break;
            case UCCI:
                _blackEngine = std::make_shared<UcciEngine>();
                break;
            case Qianhong:
                _blackEngine = std::make_shared<QianhongEngine>();
                break;
            case USI:
                _blackEngine = std::make_shared<UsiEngine>();
                break;
            case XBoard:
                _blackEngine = std::make_shared<WbEngine>();
                break;
            }

            //_blackEngine->SetTextEdit(ui->textEdit_2);
            _blackEngine->SetActive(true);

            LoadEngine(_blackEngine, _blackEngineExe, Black);
        }
        else
        {
            StopEngine(_blackEngine);
        }

        if (!_whiteEngineExe.IsEmpty())
        {
            switch (_whiteEngineProtocol)
            {
            case UCI:
                _whiteEngine = std::make_shared<UciEngine>();
                break;
            case UCCI:
                _whiteEngine = std::make_shared<UcciEngine>();
                break;
            case Qianhong:
                _whiteEngine = std::make_shared<QianhongEngine>();
                break;
            case USI:
                _whiteEngine = std::make_shared<UsiEngine>();
                break;
            case XBoard:
                _whiteEngine = std::make_shared<WbEngine>();
                break;
            }

            //_whiteEngine->SetTextEdit(ui->textEdit);
            _whiteEngine->SetActive(true);
            LoadEngine(_whiteEngine, _whiteEngineExe, White);
        }
        else
        {
            StopEngine(_whiteEngine);
        }

        //this->ui->vboard->GetBoard()->Initialize();
        //this->ui->vboard->SetCurrentPlayer(White);
        //this->ui->vboard->Refresh();
    }

    newGameDialog->Destroy();
}

void wxBoardMain::OnOpen(wxCommandEvent& event)
{
    wxFileDialog fileDialog(this, "Open file", wxEmptyString, wxEmptyString, "FEN Files (*.fen)|*.fen", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (fileDialog.ShowModal() == wxID_OK)
    {
        wxString fileName = fileDialog.GetPath();

        wxFile file;
        if (!file.Open(fileName))
        {
            wxLogError("Failed to open the file '%s' for reading.", fileName);
            return;
        }

        wxFileOffset size = file.Length();
        if (size == wxInvalidOffset)
        {
            wxLogError("Error reading the file size of '%s'.", fileName);
            return;
        }

        wxCharBuffer buffer(size);         // Allocate a buffer of 'size' chars
        file.Read(buffer.data(), size);    // Read raw data
        file.Close();

        wxString fenString = wxString::FromUTF8(buffer.data(), size);

        Board* board = new ChessBoard();// this->ui->vboard->GetBoard();
        wxString errorStr = EngineOutputHandler::SetFenToBoard(board, fenString, Chess/*ui->vboard->GetGameVariant()*/);
        if (!errorStr.IsEmpty())
        {
            wxMessageBox(errorStr, "Error", wxOK | wxICON_ERROR, this);
        }

        if (_blackEngine && _blackEngine->IsActive())
        {
            if (_blackEngine->GetType() == XBoard &&
                !std::dynamic_pointer_cast<WbEngine>(_blackEngine)->GetOption("setboard"))
            {
                // XBoard engine that doesn't support "setboard" => use Edit
                std::dynamic_pointer_cast<WbEngine>(_blackEngine)->Edit(board);
            }
            else
            {
                // Otherwise, pass FEN
                _blackEngine->SetFEN(std::string(fenString.mb_str()));
            }
        }

        if (_whiteEngine && _whiteEngine->IsActive())
        {
            if (_whiteEngine->GetType() == XBoard &&
                !std::dynamic_pointer_cast<WbEngine>(_whiteEngine)->GetOption("setboard"))
            {
                std::dynamic_pointer_cast<WbEngine>(_whiteEngine)->Edit(board);
            }
            else
            {
                _whiteEngine->SetFEN(std::string(fenString.mb_str()));
            }
        }
    }
}

void wxBoardMain::OnSave(wxCommandEvent& event)
{
    GameVariant gameVariant = Chess;//this->ui->vboard->GetGameVariant();
    Board *board = new ChessBoard();//ui->vboard->GetBoard();
    PieceColour currentPlayer = White;//this->ui->vboard->GetCurrentPlayer()

    if (gameVariant == Chess || gameVariant == Shatranj || gameVariant == Makruk)
    {
        // Define the wildcard with two filters: FEN and PGN
        wxString wildcard = "FEN Files (*.fen)|*.fen|PGN Files (*.pgn)|*.pgn";

        wxFileDialog fileDialog(this, "Save file", wxEmptyString, wxEmptyString, wildcard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (fileDialog.ShowModal() == wxID_OK)
        {
            wxString fileName = fileDialog.GetPath();
            int filterIndex   = fileDialog.GetFilterIndex();
            // filterIndex = 0 => FEN, filterIndex = 1 => PGN

            wxString str;
            if (filterIndex == 0) // FEN
            {
                // If gameVariant == Chess, gather additional castling, en-passant info
                if (gameVariant == Chess)
                {
                    wxString mcStr = wxString::Format("%d", board->MoveCount());
                    wxString hmStr = wxString::Format("%d", dynamic_cast<ChessBoard*>(board)->HalfMoveCount()
                    );
                    wxString clStr = wxString::FromUTF8(dynamic_cast<ChessBoard*>(board)->GetCastling());
                    if (clStr.IsEmpty())
                        clStr = "-";

                    wxString epStr = wxString::FromUTF8(
                        dynamic_cast<ChessBoard*>(board)->GetEnPassant()
                    );
                    if (epStr.IsEmpty())
                        epStr = "-";

                    // Base FEN
                    str = wxString::FromUTF8(board->GetFEN());
                    // Add current player
                    if (currentPlayer == Black)
                        str << " b ";
                    else
                        str << " w ";

                    // Add castling info, en-passant, halfmoves, fullmoves
                    str << clStr << " " << epStr << " " << hmStr << " " << mcStr;
                }
                else
                {
                    // Shatranj or Makruk
                    str = wxString::FromUTF8(board->GetFEN());
                    if (currentPlayer == Black)
                        str << " b ";
                    else
                        str << " w ";
                }
            }
            else // PGN
            {
                // Build PGN header
                wxString evt         = "[Event \"wxBoard Game\"]\n";
                wxString site        = "[Site \"" + wxGetHostName() + "\"]\n";
                wxString currentDate = "[Date \"" + wxDateTime::Now().Format("%d/%m/%Y") + "\"]\n";
                wxString currentRound= "[Round 1]\n";
                wxString whiteName   = "[White \"" + _whiteEngineName + "\"]\n";
                wxString blackName   = "[Black \"" + _blackEngineName + "\"]\n";
                wxString result      = "[Result \"*\"]\n\n";

                // Combine with the PGN moves
                wxString pgn = wxString::FromUTF8(dynamic_cast<ShatranjBoard*>(board)->GetPGN());

                str << evt << site << currentDate << currentRound
                    << whiteName << blackName << result << pgn;
            }

            str << "\n\n"; // Add extra spacing at the end

            // Open the file in either overwrite or append mode
            wxFile file;
            if (file.Open(fileName, (filterIndex == 0)
                ? wxFile::write            // FEN => overwrite
                : wxFile::write_append     // PGN => append
            ))
            {
                // Write as UTF-8
                file.Write(str.utf8_str(), str.utf8_str().length());
                file.Close();
            }
        }
    }
    else if (gameVariant == Xiangqi)
    {
        // "FEN Files (*.fen);;WXF Files (*.wxf)"
        wxString wildcard = "FEN Files (*.fen)|*.fen|WXF Files (*.wxf)|*.wxf";
        wxFileDialog fileDialog(this, "Save file", wxEmptyString, wxEmptyString, wildcard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (fileDialog.ShowModal() == wxID_OK)
        {
            wxString fileName   = fileDialog.GetPath();
            int filterIndex     = fileDialog.GetFilterIndex();
            // 0 => FEN, 1 => WXF

            wxString str;
            if (filterIndex == 0) // FEN
            {
                wxString mcStr = wxString::Format("%d", board->MoveCount());
                str = wxString::FromUTF8(board->GetFEN());
                if (currentPlayer == Black)
                    str << " b - - 0 ";
                else
                    str << " w - - 0 ";
                str << mcStr;
            }
            else // WXF
            {
                wxString header     = "FORMAT\tWXF\n";
                wxString evt        = "GAME\t" + _whiteEngineName + " vs. " + _blackEngineName + "\n";
                wxString gameTime   = "TIME\t00:00 ; 00:00\n";
                wxString currentDate= "DATE\t" + wxDateTime::Now().Format("%Y-%m-%d") + "\n";
                wxString author     = "AUTHOR\twxBoard (https://github.com/fire-lizard/wxBoard)\n\n";
                wxString redName    = "RED\t" + _whiteEngineName + "\n";
                wxString blackName  = "BLACK\t" + _blackEngineName + "\n";
                wxString result     = "RESULT\t0-0\n";

                wxString wxf = "START{\n"
                    + wxString::FromUTF8(dynamic_cast<XiangqiBoard*>(board)->GetWXF())
                    + "\n}END";

                str << header << evt << gameTime << result
                    << redName << blackName << currentDate << author << wxf;
            }

            str << "\n\n";

            wxFile file;
            if (file.Open(fileName, (filterIndex == 0)
                ? wxFile::write
                : wxFile::write_append
            ))
            {
                file.Write(str.utf8_str(), str.utf8_str().length());
                file.Close();
            }
        }
    }
    else if (gameVariant == Shogi || gameVariant == ShoShogi ||
             gameVariant == MiniShogi || gameVariant == JudkinShogi ||
             gameVariant == WaShogi || gameVariant == CrazyWa)
    {
        // Variation: If WaShogi or CrazyWa => "FEN Files (*.fen)"
        // Otherwise => "FEN Files (*.fen);;PSN Files (*.psn);;CSA Files (*.csa);;KIF Files (*.kif);;KI2 Files (*.ki2)"
        wxString wildcard;
        if (gameVariant == CrazyWa || gameVariant == WaShogi)
        {
            wildcard = "FEN Files (*.fen)|*.fen";
        }
        else
        {
            wildcard = "FEN Files (*.fen)|*.fen|"
                       "PSN Files (*.psn)|*.psn|"
                       "CSA Files (*.csa)|*.csa|"
                       "KIF Files (*.kif)|*.kif|"
                       "KI2 Files (*.ki2)|*.ki2";
        }

        wxFileDialog fileDialog(this, "Save file", wxEmptyString, wxEmptyString, wildcard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (fileDialog.ShowModal() == wxID_OK)
        {
            wxString fileName   = fileDialog.GetPath();
            int filterIndex     = fileDialog.GetFilterIndex();
            // 0 => FEN, 1 => PSN, 2 => CSA, 3 => KIF, 4 => KI2 (if present)

            wxString str;
            if (filterIndex == 0) // FEN
            {
                wxString mcStr = wxString::Format("%d", board->MoveCount());
                wxString cpStr = wxString::FromUTF8(dynamic_cast<ShogiVariantBoard*>(board)->CapturedPieceString());

                str = wxString::FromUTF8(board->GetFEN());
                if (currentPlayer == Black)
                    str << " b ";
                else
                    str << " w ";

                // ShoShogi and WaShogi skip the captured piece string
                if (gameVariant != ShoShogi && gameVariant != WaShogi)
                {
                    str << cpStr << " ";
                }
                str << mcStr;
            }
            else if ((filterIndex == 3) || (filterIndex == 4))
            {
                // KIF or KI2
                wxString kifStr;
                kifStr << "#KIF version=2.0 encoding=UTF-8\n"
                       << "# Generated by wxBoard\n"
                       << "Sente: " << _whiteEngineName << "\n"
                       << "Gote: " << _blackEngineName << "\n";

                if (filterIndex == 3) // KIF
                {
                    kifStr << wxString::FromUTF8(dynamic_cast<ShogiBoard*>(board)->GetKIF());
                }
                else // KI2
                {
                    kifStr << wxString::FromUTF8(dynamic_cast<ShogiBoard*>(board)->GetKI2());
                }
                str = kifStr;
            }
            else if (filterIndex == 2)
            {
                // CSA
                wxString csaStr;
                csaStr << "V2.2\n"
                       << "N+" << _whiteEngineName << "\n"
                       << "N-" << _blackEngineName << "\n";

                if (gameVariant == Shogi)
                {
                    csaStr << "P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n"
                           << "P2 * -HI *  *  *  *  * -KA *\n"
                           << "P3-FU-FU-FU-FU-FU-FU-FU-FU-FU\n"
                           << "P4 *  *  *  *  *  *  *  *  *\n"
                           << "P5 *  *  *  *  *  *  *  *  *\n"
                           << "P6 *  *  *  *  *  *  *  *  *\n"
                           << "P7+FU+FU+FU+FU+FU+FU+FU+FU+FU\n"
                           << "P8 * +KA *  *  *  *  * +HI *\n"
                           << "P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n";
                }
                else if (gameVariant == ShoShogi)
                {
                    csaStr << "P1-KY-KE-GI-KI-OU-KI-GI-KE-KY\n"
                           << "P2 * -HI *  *  SZ *  * -KA *\n"
                           << "P3-FU-FU-FU-FU-FU-FU-FU-FU-FU\n"
                           << "P4 *  *  *  *  *  *  *  *  *\n"
                           << "P5 *  *  *  *  *  *  *  *  *\n"
                           << "P6 *  *  *  *  *  *  *  *  *\n"
                           << "P7+FU+FU+FU+FU+FU+FU+FU+FU+FU\n"
                           << "P8 * +KA *  *  SZ *  * +HI *\n"
                           << "P9+KY+KE+GI+KI+OU+KI+GI+KE+KY\n";
                }
                else if (gameVariant == MiniShogi)
                {
                    csaStr << "P1-HI-KA-GI-KI-OU\n"
                           << "P2 *  *  *  * -FU\n"
                           << "P3 *  *  *  *  *\n"
                           << "P4+FU *  *  *  *\n"
                           << "P5+OU+KI+GI+KA+HI\n";
                }
                else if (gameVariant == JudkinShogi)
                {
                    csaStr << "P1-HI-KA-KE-GI-KI-OU\n"
                           << "P2 *  *  *  *  * -FU\n"
                           << "P3 *  *  *  *  *  *\n"
                           << "P4 *  *  *  *  *  *\n"
                           << "P5+FU *  *  *  *  *\n"
                           << "P6+OU+KI+GI+KE+KA+HI\n";
                }
                csaStr << "P+\nP-\n+\n";
                csaStr << wxString::FromUTF8(dynamic_cast<ShogiBoard*>(board)->GetCSA());
                str = csaStr;
            }
            else if (filterIndex == 1)
            {
                // PSN
                wxString senteName = "[Sente \"" + _whiteEngineName + "\"]\n";
                wxString goteName  = "[Gote \"" + _blackEngineName + "\"]\n\n";
                wxString psn       = wxString::FromUTF8(dynamic_cast<ShogiBoard*>(board)->GetPSN());
                str << senteName << goteName << psn;
            }

            str << "\n\n";

            // Decide how to open (overwrite vs. append)
            // We’ll treat *.fen as overwrite, everything else as append to match your original pattern
            bool isFen = (filterIndex == 0);
            wxFile file;
            if (file.Open(fileName, isFen ? wxFile::write : wxFile::write_append))
            {
                file.Write(str.utf8_str(), str.utf8_str().length());
                file.Close();
            }
        }
    }
    else
    {
        // Fallback: Only FEN
        wxString wildcard = "FEN Files (*.fen)|*.fen";
        wxFileDialog fileDialog(this, "Save file", wxEmptyString, wxEmptyString, wildcard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (fileDialog.ShowModal() == wxID_OK)
        {
            wxString fileName = fileDialog.GetPath();

            // Basic FEN
            wxString str = wxString::FromUTF8(board->GetFEN());
            if (currentPlayer == Black)
                str << " b";
            else
                str << " w";
            str << "\n\n";

            wxFile file;
            if (file.Open(fileName, wxFile::write))
            {
                file.Write(str.utf8_str(), str.utf8_str().length());
                file.Close();
            }
        }
    }
}

void wxBoardMain::OnSettings(wxCommandEvent& event)
{
	SettingsDialog *settingsDialog = new SettingsDialog(this);
	//settingsDialog->GetGameVariants()->setCurrentIndex(this->ui->vboard->GetGameVariant());
	//settingsDialog->GetGamePieces()->setCurrentIndex(this->ui->vboard->GetPieceStyle());
	//settingsDialog->GetEngineOutput()->setCurrentIndex(this->ui->vboard->GetEngineOutput());
	int result = settingsDialog->ShowModal();
	if (result == wxID_OK)
	{
		/*const GameVariant newGameVariant = static_cast<GameVariant>(settingsDialog->GetGameVariants()->currentIndex());
		const PieceStyle pieceStyle = static_cast<PieceStyle>(settingsDialog->GetGamePieces()->currentIndex());
		const EngineOutput engineOutput = static_cast<EngineOutput>(settingsDialog->GetEngineOutput()->currentIndex());
		if (pieceStyle != this->ui->vboard->GetPieceStyle())
		{
			this->ui->vboard->SetPieceStyle(pieceStyle);
			this->ui->vboard->repaint();
		}
		if (engineOutput != this->ui->vboard->GetEngineOutput())
		{
			this->ui->vboard->SetEngineOutput(engineOutput);
		}
		if (newGameVariant != this->ui->vboard->GetGameVariant())
		{
			StartNewGame(newGameVariant);
		}*/
		IniFile::writeToIniFile(_settingsDir + "/" + _settingsFileName,
			settingsDialog->GetGameVariants()->	GetStringSelection(),
			settingsDialog->GetGamePieces()->GetStringSelection(),
			settingsDialog->GetEngineOutput()->	GetStringSelection());
	}
}

void wxBoardMain::OnEngineManager(wxCommandEvent& event)
{
	EngineManager *engineManager = new EngineManager(this);
	readXmlUsingStream(_settingsDir + "/" + _enginesListFileName, engineManager->GetEngineTable());
	int result = engineManager->ShowModal();
	if (result == wxID_OK)
	{
		createXmlFromTable(_settingsDir + "/" + _enginesListFileName, engineManager->GetEngineTable());
	}
}

void wxBoardMain::OnEditorMode(wxCommandEvent& event)
{
	//ui->vboard->SetEditorMode(!ui->vboard->GetEditorMode());
	//ui->vboard->repaint();
}

void wxBoardMain::OnStopGame(wxCommandEvent& event)
{
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
}

void wxBoardMain::OnQuit(wxCommandEvent& event)
{
	StopEngine(_whiteEngine);
	StopEngine(_blackEngine);
    this->Destroy();
}

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
