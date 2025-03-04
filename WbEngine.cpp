#include "WbEngine.h"

WbEngine::WbEngine()
{
}

WbEngine::~WbEngine()
{
	Quit();
}

EngineProtocol WbEngine::GetType()
{
	return XBoard;
}

void WbEngine::SetFEN(std::string fen)
{
	_fen = std::move(fen);
	if (_setboard)
	{
		WriteToProcess("setboard " + _fen + "\n");
	}
	_moves.clear();
}

void WbEngine::Edit(const Board* board) const
{
	PieceColour pieceColour = White;
	WriteToProcess("edit\n");
	WriteToProcess("#\n");
	for (int j = 0; j < board->GetHeight(); j++)
	{
		for (int i = 0; i < board->GetWidth(); i++)
		{
			Piece* p = board->GetData(i, j);
			if (p != nullptr)
			{
				const char letter = i + 97;
				const int number = board->GetHeight() - j;
				const PieceColour newPieceColour = p->GetColour();
				std::string str;
				if (newPieceColour != pieceColour)
				{
					WriteToProcess("c\n");
					pieceColour = newPieceColour;
				}
				str += p->StringCode();
				str.push_back(letter);
				str += std::to_string(number);
				str.push_back('\n');
				WriteToProcess(str);
			}
		}
	}
	WriteToProcess(".\n");
}

void WbEngine::StartGame(wxString variant)
{
	_moves.clear();
	WriteToProcess("xboard\n");
	WriteToProcess("protover\n");
	WriteToProcess("new\n");
	if (variant != "")
	{
		const wxString str = "variant " + variant + "\n";
		WriteToProcess(str);
	}
}

void WbEngine::SetMemory(int memorySize)
{
	const wxString memoryStr = "memory " + wxString::Format(wxT("%d"), _memorySize) + "\n";
	WriteToProcess(memoryStr);
	_memorySize = memorySize;
}

void WbEngine::Move()
{
	_textEdit->Clear();
	WriteToProcess("go\n");
}

void WbEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_textEdit->Clear();
	WriteToProcess(AddMove(x1, y1, x2, y2, promotion));
	WriteToProcess("\n");
}

void WbEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3)
{
	_textEdit->Clear();
	WriteToProcess(AddMove(x1, y1, x2, y2, x3, y3));
	WriteToProcess("\n");
}

void WbEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3, signed char x4, signed char y4)
{
	_textEdit->Clear();
	WriteToProcess(AddMove(x1, y1, x2, y2, x3, y3, x4, y4));
	WriteToProcess("\n");
}

wxString WbEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	wxString moveStr;
	if (_usermove)
	{
		moveStr += "usermove ";
	}
	if (y1 == '@')
	{
		moveStr.Append(static_cast<char>(x1));
		moveStr.Append(static_cast<char>(y1));
		moveStr.Append(static_cast<char>(x2 + 97));
		moveStr.Append(wxString::Format(wxT("%d"), y2)[0]);
	}
	else if (x1 == x2 && y1 == y2)
	{
		moveStr += "@@@@";
	}
	else if (y1 <= 19 || y2 <= 19)
	{
		moveStr.Append(static_cast<char>(x1 < 30 ? x1 + 97 : x1));
		moveStr.Append(wxString::Format(wxT("%d"), y1)[0]);
		if (y1 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y1)[1]);
		moveStr.Append(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.Append(wxString::Format(wxT("%d"), y2)[0]);
		if (y2 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y2)[1]);
	}
	else
	{
		moveStr.Append(static_cast<char>(x1));
		moveStr.Append(static_cast<char>(y1));
		moveStr.Append(static_cast<char>(x2));
		moveStr.Append(static_cast<char>(y2));
	}
	if (promotion == 'n' || promotion == 'b' || promotion == 'r' || promotion == 'q' || promotion == '+')
	{
		moveStr.Append(promotion);
	}
	_moves.push_back(moveStr);
	return moveStr;
}

wxString WbEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3)
{
	wxString moveStr;
	moveStr += "usermove ";
	if (y1 <= 19 || y2 <= 19)
	{
		moveStr.Append(static_cast<char>(x1 < 30 ? x1 + 97 : x1));
		moveStr.Append(wxString::Format(wxT("%d"), y1)[0]);
		if (y1 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y1)[1]);
		moveStr.Append(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.Append(wxString::Format(wxT("%d"), y2)[0]);
		if (y2 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y2)[1]);
	}
	else
	{
		moveStr.Append(static_cast<char>(x1));
		moveStr.Append(static_cast<char>(y1));
		moveStr.Append(static_cast<char>(x2));
		moveStr.Append(static_cast<char>(y2));
	}
	moveStr.Append(',');
	if (y2 <= 19 || y3 <= 19)
	{
		moveStr.Append(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.Append(wxString::Format(wxT("%d"), y2)[0]);
		if (y2 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y2)[1]);
		moveStr.Append(static_cast<char>(x3 < 30 ? x3 + 97 : x3));
		moveStr.Append(wxString::Format(wxT("%d"), y3)[0]);
		if (y2 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y3)[1]);
	}
	else
	{
		moveStr.Append(static_cast<char>(x2));
		moveStr.Append(static_cast<char>(y2));
		moveStr.Append(static_cast<char>(x3));
		moveStr.Append(static_cast<char>(y3));
	}
	_moves.push_back(moveStr);
	return moveStr;
}

wxString WbEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, signed char x3, signed char y3, signed char x4, signed char y4)
{
	wxString moveStr;
	moveStr += "usermove ";
	if (y1 <= 19 || y2 <= 19)
	{
		moveStr.Append(static_cast<char>(x1 < 30 ? x1 + 97 : x1));
		moveStr.Append(wxString::Format(wxT("%d"), y1)[0]);
		if (y2 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y1)[1]);
		moveStr.Append(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.Append(wxString::Format(wxT("%d"), y2)[0]);
		if (y2 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y2)[1]);
	}
	else
	{
		moveStr.Append(static_cast<char>(x1));
		moveStr.Append(static_cast<char>(y1));
		moveStr.Append(static_cast<char>(x2));
		moveStr.Append(static_cast<char>(y2));
	}
	moveStr.Append(',');
	if (y2 <= 19 || y3 <= 19)
	{
		moveStr.Append(static_cast<char>(x2 < 30 ? x2 + 97 : x2));
		moveStr.Append(wxString::Format(wxT("%d"), y2)[0]);
		if (y2 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y2)[1]);
		moveStr.Append(static_cast<char>(x3 < 30 ? x3 + 97 : x3));
		moveStr.Append(wxString::Format(wxT("%d"), y3)[0]);
		if (y2 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y3)[1]);
	}
	else
	{
		moveStr.Append(static_cast<char>(x2));
		moveStr.Append(static_cast<char>(y2));
		moveStr.Append(static_cast<char>(x3));
		moveStr.Append(static_cast<char>(y3));
	}
	moveStr.Append(',');
	if (y3 <= 19 || y4 <= 19)
	{
		moveStr.Append(static_cast<char>(x3 < 30 ? x3 + 97 : x3));
		moveStr.Append(wxString::Format(wxT("%d"), y3)[0]);
		if (y2 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y3)[1]);
		moveStr.Append(static_cast<char>(x4 < 30 ? x4 + 97 : x4));
		moveStr.Append(wxString::Format(wxT("%d"), y4)[0]);
		if (y2 >= 10) moveStr.Append(wxString::Format(wxT("%d"), y4)[1]);
	}
	else
	{
		moveStr.Append(static_cast<char>(x3));
		moveStr.Append(static_cast<char>(y3));
		moveStr.Append(static_cast<char>(x4));
		moveStr.Append(static_cast<char>(y4));
	}
	_moves.push_back(moveStr);
	return moveStr;
}

void WbEngine::SetOption(const std::string& name, bool value)
{
	if (name == "setboard") _setboard = value;
	if (name == "memory") _memory = value;
	if (name == "usermove") _usermove = value;
}

bool WbEngine::GetOption(const std::string& name) const
{
	if (name == "setboard") return _setboard;
	if (name == "memory") return _memory;
	if (name == "usermove") return _usermove;
	return false;
}
