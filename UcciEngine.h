#ifndef HEADER_5BFCD404AA5B08C8
#define HEADER_5BFCD404AA5B08C8

#pragma once
#include "UciEngine.h"

class UcciEngine : public UciEngine
{
public:
	UcciEngine();
	~UcciEngine() override;
	void SetFEN(std::string fen) override;
	EngineProtocol GetType() override;
	void StartGame(wxString variant = "") override;
	wxString AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
};

#endif // header guard

