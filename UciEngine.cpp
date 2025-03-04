#include "UciEngine.h"

UciEngine::UciEngine()
{
	_fen = CHESSFEN;
}

UciEngine::~UciEngine()
{
	Quit();
}

void UciEngine::SetFEN(std::string fen)
{
	trimNewline(fen);
	_fen = std::move(fen);
	WriteToProcess("ucinewgame\n");
	_moves.clear();
}

EngineProtocol UciEngine::GetType()
{
	return UCI;
}

void UciEngine::StartGame(wxString variant)
{
	_moves.clear();
	WriteToProcess("uci\n");
	WriteToProcess("isready\n");
	WriteToProcess("ucinewgame\n");
}

void UciEngine::Move()
{
	_textEdit->Clear();
	wxString moveStr;
	moveStr += "position fen " + _fen + " moves ";
	for (const auto& _move : _moves)
	{
		moveStr += _move;
		moveStr += " ";
	}
	moveStr += "\n";
	WriteToProcess(moveStr);
	WriteToProcess("go depth 10\n");
}

void UciEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_textEdit->Clear();
	wxString moveStr;
	moveStr += "position fen " + _fen + " moves ";
	for (const auto& _move : _moves)
	{
		moveStr += _move;
		moveStr += " ";
    }
	moveStr += AddMove(x1, y1, x2, y2, promotion);
	moveStr += "\n";
	WriteToProcess(moveStr);
	WriteToProcess("go depth 10\n");
}

wxString UciEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	wxString moveStr;
	if (y1 < 10)
	{
		moveStr.Append(static_cast<char>(x1 + 97));
		moveStr.Append(wxString::Format(wxT("%d"), y1)[0]);
		moveStr.Append(static_cast<char>(x2 + 97));
		moveStr.Append(wxString::Format(wxT("%d"), y2)[0]);
	}
	else
	{
		moveStr.Append(static_cast<char>(x1));
		moveStr.Append(static_cast<char>(y1));
		moveStr.Append(static_cast<char>(x2));
		moveStr.Append(static_cast<char>(y2));
	}
	if (promotion == 'n' || promotion == 'b' || promotion == 'r' || promotion == 'q')
	{
		moveStr.Append(promotion);
	}
	_moves.push_back(moveStr);
	return moveStr;
}

void UciEngine::trimNewline(std::string& str)
{
	if (!str.empty() && (str.back() == '\n' || str.back() == '\r'))
	{
		str.erase(str.find_last_not_of("\r\n") + 1);
	}
}
