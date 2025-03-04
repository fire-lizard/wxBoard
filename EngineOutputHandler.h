#ifndef HEADER_ED01A654551722A2
#define HEADER_ED01A654551722A2

#pragma once
#include <wx/regex.h>
#include "Common.h"
#include "WbEngine.h"
#include "ChessBoard.h"
#include "XiangqiBoard.h"
#include "ShogiBoard.h"
#include "MakrukBoard.h"
#include "XiangqiPiece.h"
#include "WaShogiPiece.h"
#include "TenjikuShogiPiece.h"
#include "DaiDaiShogiPiece.h"
#include "KoShogiPiece.h"

struct Move
{
	int x1, y1, x2, y2;
};

class EngineOutputHandler
{
public:
	static std::array<char, 5> ExtractMove(const wxString& buf, EngineProtocol engineProtocol, GameVariant gameVariant);
	static Move ByteArrayToMove(std::array<char, 5> moveArray, EngineProtocol engineProtocol, GameVariant gameVariant, int width, int height);
	static wxString MoveToByteArray(Move m, EngineProtocol engineProtocol, int width, int height);
	static void ReadStandardOutput(const wxString& buf, const std::shared_ptr<Engine>& engine, Board* board, wxTextCtrl* textEdit,
		GameVariant gameVariant, EngineOutput engineOutput, PieceColour currentPlayer);
	static void ReadStandardError(const wxString& buf, wxTextCtrl* textEdit);
	static void AddMove(Board* board, GameVariant gameVariant, PieceType p, int x1, int y1, int x2, int y2, int x3, int y3);
	static wxString SetFenToBoard(Board* board, const wxString& str, GameVariant gameVariant);
	static void CalculateCheck(Board* board, PieceColour pieceColour, std::vector<std::pair<int, int>>& moves, int oldX, int oldY, int newX, int newY);
	static bool IsInsidePromotionZone(GameVariant gameVariant, PieceColour pieceColour, int y);
	static bool CanBePromoted(const Piece* piece, GameVariant gameVariant, int oldY, int newY);
	static bool IsLionMove(const Piece* piece, int x1, int y1, int x2, int y2);

private:
	static void RemoveMove(std::vector<std::pair<int, int>>& moves, int x, int y);
	static std::pair<int, int> GetPieceLocation(const Board* board, PieceType pieceType, PieceColour pieceColour);
};

#endif // header guard

