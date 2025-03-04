#include "QianhongEngine.h"

QianhongEngine::QianhongEngine()
{
	_fen = XIANGQIFEN;
}

QianhongEngine::~QianhongEngine()
{
	Quit();
}

wxProcess* QianhongEngine::RunProcess(wxWindow* parentObject, const wxString& engineExe)
{
	_process = std::make_unique<wxProcess>(parentObject);
	_process->Redirect();
    wxFileName fn(engineExe);
    wxString workingDir = fn.GetPath();
    if (!workingDir.IsEmpty())
    {
        wxSetWorkingDirectory(workingDir);
    }
    long pid = wxExecute(engineExe + " -plugin", wxEXEC_ASYNC, _process.get());
    if (pid == 0)
    {
        _process.reset();
        return nullptr;
    }
	return _process.get();
}

void QianhongEngine::SetFEN(std::string fen)
{
	_fen = std::move(fen);
	WriteToProcess("FEN " + _fen + "\n");
	_moves.clear();
}

EngineProtocol QianhongEngine::GetType()
{
	return Qianhong;
}

void QianhongEngine::StartGame(wxString variant)
{
	_moves.clear();
}

void QianhongEngine::Move()
{
	_textEdit->Clear();
	WriteToProcess("ai\n");
}

void QianhongEngine::Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	_textEdit->Clear();
	WriteToProcess(AddMove(x1, y1, x2, y2, promotion) + "\n");
	WriteToProcess("ai\n");
}

wxString QianhongEngine::AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion)
{
	wxString moveStr;
	moveStr.Append('P');
	moveStr.Append('L');
	moveStr.Append('A');
	moveStr.Append('Y');
	moveStr.Append(' ');
	moveStr.Append((char)(x1 + 65));
	moveStr.Append((char)(y1 + '0'));
	moveStr.Append('-');
	moveStr.Append((char)(x2 + 65));
	moveStr.Append((char)(y2 + '0'));
	_moves.push_back(moveStr);
	return moveStr;
}
