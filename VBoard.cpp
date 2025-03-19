#include "VBoard.h"

//(*InternalHeaders(VBoard)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(VBoard)
//*)

BEGIN_EVENT_TABLE(VBoard,wxPanel)
    //(*EventTable(VBoard)
    //*)
END_EVENT_TABLE()

VBoard::VBoard(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(VBoard)
    Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
    //*)
}

VBoard::~VBoard()
{
    //(*Destroy(VBoard)
    //*)
}

bool VBoard::AskForPromotion()
{
	return wxMessageBox("Would you like to promote this piece?", "Promotion",
		wxYES_NO | wxICON_QUESTION, this) == wxYES;
}

void VBoard::FinishMove()
{
	if (_currentPlayer == White)
	{
		_whiteMoves.push_back(_board->GetFEN());
		if (!_board->HasPiece(King, Black) && !_board->HasPiece(Prince, Black))
		{
			wxMessageBox("White wins by elminating Black King", "Game over");
		}
	}
	else
	{
		_blackMoves.push_back(_board->GetFEN());
		if (!_board->HasPiece(King, White) && !_board->HasPiece(Prince, White))
		{
			wxMessageBox("Black wins by elminating White King", "Game over");
		}
	}
	_currentPlayer = _currentPlayer == White ? Black : White;
	_statusBar->SetForegroundColour(*wxBLACK);
	_statusBar->SetStatusText(_currentPlayer == White ? _gameVariant == Xiangqi ? "Red move" : "White move" : "Black move");
	_opponentMoves = _board->GetAllMoves(_currentPlayer == White ? Black : White);
	_currentPiece = nullptr;
	_oldX = -1;
	_oldY = -1;
	_moves.clear();
	_lionMovedOnce = false;
	_lionMovedTwice = false;
	_lionFirstMove.first = -1;
	_lionFirstMove.second = -1;
	_lionSecondMove.first = -1;
	_lionSecondMove.second = -1;
	this->Refresh();
}

void VBoard::CancelLionMove()
{
	_lionMovedOnce = false;
	_lionMovedTwice = false;
	_lionFirstMove.first = -1;
	_lionFirstMove.second = -1;
	_lionSecondMove.first = -1;
	_lionSecondMove.second = -1;
}

Board* VBoard::GetBoard() const
{
	return _board;
}

GameVariant VBoard::GetGameVariant() const
{
	return _gameVariant;
}

void VBoard::SetGameVariant(GameVariant gameVariant)
{
	_whiteMoves.clear();
	_blackMoves.clear();
	if (_whiteEngine != nullptr)
	{
		_whiteEngine->SetActive(false);
	}
	if (_blackEngine != nullptr)
	{
		_blackEngine->SetActive(false);
	}
	_currentPiece = nullptr;
	_moves.clear();
	_opponentMoves.clear();
	_attackers.clear();
	_defenders.clear();
	_gameVariant = gameVariant;
	int s = 66;
	switch (_gameVariant)
	{
	case Chess:
		_board = new ChessBoard();
		break;
	case Shogi:
		_board = new ShogiBoard();
		break;
	case ShoShogi:
		_board = new ShogiBoard();
		dynamic_cast<ShogiBoard*>(_board)->SetDrops(false);
		break;
	case ChuShogi:
		_board = new ChuShogiBoard();
		break;
	case DaiShogi:
		s = 60;
		_board = new DaiShogiBoard();
		break;
	case TenjikuShogi:
		s = 56;
		_board = new TenjikuShogiBoard();
		break;
	case DaiDaiShogi:
		s = 52;
		_board = new DaiDaiShogiBoard();
		break;
	case MakaDaiDaiShogi:
		s = 48;
		_board = new MakaDaiDaiShogiBoard();
		break;
	case KoShogi:
		s = 48;
		_board = new KoShogiBoard();
		break;
	case MiniShogi:
		_board = new MiniShogiBoard();
		break;
	case JudkinShogi:
		_board = new JudkinShogiBoard();
		break;
	case WaShogi:
		_board = new WaShogiBoard();
		dynamic_cast<ShogiBoard*>(_board)->SetDrops(false);
		break;
	case CrazyWa:
		_board = new WaShogiBoard();
		break;
	case Xiangqi:
		_board = new XiangqiBoard();
		break;
	case Shatranj:
		_board = new ShatranjBoard();
		break;
	case Makruk:
		_board = new MakrukBoard();
		break;
	}
	this->SetSize(_board->GetWidth() * s + 1, _board->GetHeight() * s + 1);
	if (this->_window != nullptr)
	{
		// TODO: Use sizers
		//this->_window->SetSize(width() + 280, height() + 100);
		//this->_textEdit->setSize(x() + width() + 10, y(), 250, height() / 2);
		//this->_textEdit2->setSize(x() + width() + 10, y() + 2 + height() / 2, 250, height() / 2);
	}
}

PieceStyle VBoard::GetPieceStyle() const
{
	return _pieceStyle;
}

void VBoard::SetPieceStyle(PieceStyle pieceStyle)
{
	_pieceStyle = pieceStyle;
}

EngineOutput VBoard::GetEngineOutput() const
{
	return _engineOutput;
}

void VBoard::SetEngineOutput(EngineOutput engineOutput)
{
	_engineOutput = engineOutput;
}

PieceColour VBoard::GetCurrentPlayer() const
{
	return _currentPlayer;
}

void VBoard::SetCurrentPlayer(PieceColour currentPlayer)
{
	_moves.clear();
	_opponentMoves.clear();
	_currentPlayer = currentPlayer;
}

void VBoard::SetTextEdit(wxTextCtrl* textEdit)
{
	_textEdit = textEdit;
}

void VBoard::SetTextEdit2(wxTextCtrl* textEdit)
{
	_textEdit2 = textEdit;
}

bool VBoard::PossibleMove(int x, int y) const
{
	return std::any_of(_moves.begin(), _moves.end(), [x, y](const std::pair<int, int>& p) {return p.first == x && p.second == y;});
}

void VBoard::SetStatusBar(wxStatusBar *statusBar)
{
	_statusBar = statusBar;
}

void VBoard::SetMainWindow(wxFrame *window)
{
	_window = window;
}

void VBoard::SetWhiteEngine(std::shared_ptr<Engine> engine)
{
	_whiteEngine = std::move(engine);
}

void VBoard::SetBlackEngine(std::shared_ptr<Engine> engine)
{
	_blackEngine = std::move(engine);
}

bool VBoard::GetEditorMode() const
{
	return _editorMode;
}

void VBoard::SetEditorMode(bool editorMode)
{
	if (editorMode)
	{
		if (_gameVariant == Chess)
		{
			dynamic_cast<ChessBoard*>(_board)->SetCastling("-");
			dynamic_cast<ChessBoard*>(_board)->SetEnPassant("-");
		}
		delete _editorBoard;
		_editorBoard = _board->Clone();
	}
	else
	{
		if (*_board != _editorBoard->GetFEN())
		{
			const int response = wxMessageBox("Do you want to preserve the changes?", "Question", wxYES_NO | wxICON_QUESTION, this);
			if (response == wxYES)
			{
				delete _editorBoard;
				_editorBoard = nullptr;
				if (_blackEngine != nullptr && _blackEngine->IsActive())
				{
					if (_blackEngine->GetType() == XBoard && !std::dynamic_pointer_cast<WbEngine>(_blackEngine)->GetOption("setboard"))
					{
						std::dynamic_pointer_cast<WbEngine>(_blackEngine)->Edit(_board);
					}
					else
					{
						_blackEngine->SetFEN(_board->GetFEN());
					}
				}
				if (_whiteEngine != nullptr && _whiteEngine->IsActive())
				{
					if (_whiteEngine->GetType() == XBoard && !std::dynamic_pointer_cast<WbEngine>(_whiteEngine)->GetOption("setboard"))
					{
						std::dynamic_pointer_cast<WbEngine>(_whiteEngine)->Edit(_board);
					}
					else
					{
						_whiteEngine->SetFEN(_board->GetFEN());
					}
				}
			}
			else
			{
				delete _board;
				_board = _editorBoard;
				Refresh();
			}
		}
	}
	_editorMode = editorMode;
}

bool VBoard::CheckRepetition(int oldX, int oldY, int newX, int newY)
{
	// Repetition rule
	Board *board = _board->Clone();
	board->Move(oldX, oldY, newX, newY);
	int repetitions = 0;
	if (_currentPlayer == White)
	{
		for (auto& _whiteMove : _whiteMoves)
		{
			if (*board == _whiteMove)
			{
				repetitions++;
			}
		}
	}
	else
	{
		for (auto& _blackMove : _blackMoves)
		{
			if (*board == _blackMove)
			{
				repetitions++;
			}
		}
	}
	delete board;
	if (repetitions >= 4)
	{
		wxMessageBox("Repetition rule violated.\nPlease make another move.", "Warning", wxYES_NO | wxICON_WARNING, this);
		return true;
	}
	return false;
}
