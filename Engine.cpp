#include "Engine.h"

#include <utility>

Engine::Engine()
{
}

Engine::~Engine()
{
	Quit();
}

wxProcess* Engine::RunProcess(wxWindow *parentObject, const wxString& engineExe)
{
	_process = std::make_unique<wxProcess>(parentObject);
	_process->Redirect();
    wxFileName fn(engineExe);
    wxString workingDir = fn.GetPath();
    if (!workingDir.IsEmpty())
    {
        wxSetWorkingDirectory(workingDir);
    }
    long pid = wxExecute(engineExe, wxEXEC_ASYNC, _process.get());
    if (pid == 0)
    {
        _process.reset();
        return nullptr;
    }
	return _process.get();
}

void Engine::Quit() const
{
	if (_process)
	{
        if (_process->IsRedirected())
        {
            const char *str = "quit\n";
            _process->GetOutputStream()->Write(str, strlen(str));
        }
         wxKill(_process->GetPid(), wxSIGKILL, nullptr, wxKILL_CHILDREN);
        _process.reset();
    }
}

bool Engine::IsActive() const
{
	return _isActive;
}

void Engine::SetActive(bool val)
{
	_isActive = val;
}

wxTextCtrl* Engine::GetTextEdit() const
{
	return _textEdit;
}

void Engine::SetTextEdit(wxTextCtrl* textEdit)
{
	_textEdit = textEdit;
}

wxProcess* Engine::GetProcess() const
{
	return _process.get();
}

void Engine::WriteToProcess(wxString buf) const
{
    if (!_process || !_process->IsRedirected())
        return;

    bool isPrintable = true;
    for (auto c : buf)
    {
        if (!isprint(static_cast<unsigned char>(c)))
        {
            isPrintable = false;
            break;
        }
    }

    if (isPrintable && _textEdit)
    {
        _textEdit->AppendText(buf);
        _textEdit->AppendText("\n");
    }

    _process->GetOutputStream()->Write(buf.c_str(), buf.size());
}

std::vector<wxString> Engine::Moves() const
{
	return _moves;
}
