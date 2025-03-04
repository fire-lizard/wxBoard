#include "UcciEngine.h"

UcciEngine::UcciEngine()
{
	_fen = XIANGQIFEN;
}

UcciEngine::~UcciEngine()
{
	Quit();
}

void UcciEngine::SetFEN(std::string fen)
{
	trimNewline(fen);
	_fen = std::move(fen);
	WriteToProcess("uccinewgame\n");
	_moves.clear();
}

EngineProtocol UcciEngine::GetType()
{
	return UCCI;
}

void UcciEngine::StartGame(wxString variant)
{
	_moves.clear();
	WriteToProcess("ucci\n");
	WriteToProcess("isready\n");
	WriteToProcess("uccinewgame\n");
}

wxString UcciEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	wxString moveStr;
	if (x1 < 10)
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
	_moves.push_back(moveStr);
	return moveStr;
}
