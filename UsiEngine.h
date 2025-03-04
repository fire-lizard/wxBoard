#ifndef HEADER_CCADB7F9CA94475
#define HEADER_CCADB7F9CA94475

#pragma once
#include "UciEngine.h"

class UsiEngine : public UciEngine
{
public:
	UsiEngine();
	~UsiEngine() override;
	void SetFEN(std::string fen) override;
	EngineProtocol GetType() override;
	void Move() override;
	void StartGame(wxString variant = "") override;
	void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
	wxString AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
};

#endif // header guard

