#ifndef HEADER_D78799D078430182
#define HEADER_D78799D078430182

#pragma once
#include "Engine.h"

class UciEngine : public Engine
{
public:
	UciEngine();
	~UciEngine() override;
	void SetFEN(std::string fen) override;
	EngineProtocol GetType() override;
	void StartGame(wxString variant = "") override;
	void Move() override;
	void Move(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;
	wxString AddMove(signed char x1, signed char y1, signed char x2, signed char y2, char promotion = ' ') override;

protected:
	static void trimNewline(std::string& str);
};
#endif // header guard 

