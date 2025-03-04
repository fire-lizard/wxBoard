#ifndef HEADER_536AD3585B466C7C
#define HEADER_536AD3585B466C7C

#pragma once
#include "Engine.h"

class QianhongEngine : public Engine
{
public:
	QianhongEngine();
	~QianhongEngine() override;
	wxProcess* RunProcess(wxWindow* parentObject, const wxString& engineExe) override;
	void SetFEN(std::string fen) override;
	EngineProtocol GetType() override;
	void StartGame(wxString variant = "") override;
	void Move() override;
	void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
	wxString AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
};

#endif // header guard 

