#include "UsiEngine.h"

UsiEngine::UsiEngine()
{
	_fen = SHOGIFEN;
}

UsiEngine::~UsiEngine()
{
	Quit();
}

void UsiEngine::SetFEN(std::string fen)
{
	trimNewline(fen);
	_fen = std::move(fen);
	WriteToProcess("usinewgame\n");
	_moves.clear();
}

EngineProtocol UsiEngine::GetType()
{
	return USI;
}

void UsiEngine::StartGame(wxString variant)
{
	_moves.clear();
	WriteToProcess("usi\n");
	WriteToProcess("isready\n");
	WriteToProcess("usinewgame\n");
}

void UsiEngine::Move()
{
	_textEdit->Clear();
	wxString moveStr;
	moveStr += "position sfen " + _fen + " moves ";
	for (const auto& _move : _moves)
	{
		moveStr += _move;
		moveStr += " ";
	}
	moveStr += "\n";
	WriteToProcess(moveStr);
	WriteToProcess("go depth 10\n");
}

void UsiEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_textEdit->Clear();
	wxString moveStr;
	moveStr += "position sfen " + _fen + " moves ";
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

wxString UsiEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	wxString moveStr;
	if (y1 == '*')
	{
		moveStr.Append(static_cast<char>(x1));
		moveStr.Append(static_cast<char>(y1));
		moveStr.Append(wxString::Format(wxT("%d"), x2)[0]);
		moveStr.Append(static_cast<char>(y2 + 97));
	}
	else if (x1 < 10)
	{
		moveStr.Append(wxString::Format(wxT("%d"), x1)[0]);
		moveStr.Append(static_cast<char>(y1 + 97));
		moveStr.Append(wxString::Format(wxT("%d"), x2)[0]);
		moveStr.Append(static_cast<char>(y2 + 97));
	}
	else
	{
		moveStr.Append(static_cast<char>(x1));
		moveStr.Append(static_cast<char>(y1));
		moveStr.Append(static_cast<char>(x2));
		moveStr.Append(static_cast<char>(y2));
	}
	if (promotion == '+')
	{
		moveStr.Append(promotion);
	}
	_moves.push_back(moveStr);
	return moveStr;
}
