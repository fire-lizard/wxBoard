#ifndef HEADER_EE579F4EDEF32A5A
#define HEADER_EE579F4EDEF32A5A

#pragma once
#include <wx/process.h>
#include <wx/filename.h>
#include <wx/textctrl.h>
#include <memory>
#include "Common.h"

class Engine
{
public:
	Engine();
	virtual ~Engine();
	virtual wxProcess* RunProcess(wxWindow *parentObject, const wxString& engineExe);
	void Quit() const;
	bool IsActive() const;
	void SetActive(bool val);
	wxTextCtrl* GetTextEdit() const;
	void SetTextEdit(wxTextCtrl* textEdit);
	wxProcess* GetProcess() const;
	void WriteToProcess(wxString buf) const;
	std::vector<wxString> Moves() const;
	virtual void SetFEN(std::string fen) = 0;
	virtual EngineProtocol GetType() = 0;
	virtual void StartGame(wxString variant = "") = 0;
	virtual void Move() = 0;
	virtual void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') = 0;
	virtual wxString AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') = 0;

protected:
	mutable std::unique_ptr<wxProcess> _process = nullptr;
	wxTextCtrl *_textEdit;
	bool _isActive = false;
	std::vector<wxString> _moves;
	std::string _fen;
};
#endif // header guard

