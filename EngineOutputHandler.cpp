#include "EngineOutputHandler.h"

void EngineOutputHandler::RemoveMove(std::vector<std::pair<int, int>>& moves, int x, int y)
{
	const long long cnt = static_cast<long long>(moves.size()) - 1;
	for (long long index = cnt; index >= 0; index--)
	{
		if (moves[index].first == x && moves[index].second == y)
			moves.erase(moves.begin() + index);
	}
}

bool EngineOutputHandler::IsLionMove(const Piece* piece, int x1, int y1, int x2, int y2)
{
	if (piece != nullptr)
	{
		if (piece->GetType() == Unicorn)
		{
			if ((x1 == x2 && y1 - y2 == +1 || x1 == x2 && y1 - y2 == +2) && piece->GetColour() == White ||
				(x1 == x2 && y1 - y2 == -1 || x1 == x2 && y1 - y2 == -2) && piece->GetColour() == Black)
			{
				return true;
			}
		}
		else if (piece->GetType() == Eagle)
		{
			if ((abs(x1 - x2) == 1 && y1 - y2 == +1 || abs(x1 - x2) == 2 && y1 - y2 == +2) && piece->GetColour() == White ||
				(abs(x1 - x2) == 1 && y1 - y2 == -1 || abs(x1 - x2) == 2 && y1 - y2 == -2) && piece->GetColour() == Black)
			{
				return true;
			}
		}
		else if (piece->GetType() == FreeEagle || piece->GetType() == WingedTiger)
		{
			if (abs(x1 - x2) == 1 && abs(y1 - y2) == 1 || abs(x1 - x2) == 2 && abs(y1 - y2) == 2 ||
				abs(x1 - x2) == 2 && abs(y1 - y2) == 0 || abs(x1 - x2) == 0 && abs(y1 - y2) == 2)
			{
				return true;
			}
		}
		else if (piece->GetType() == GreatElephant)
		{
			if (piece->GetColour() == White && !(abs(x1 - x2) == 1 && y1 - y2 == +1 || abs(x1 - x2) == 2 && y1 - y2 == +2) ||
				piece->GetColour() == Black && !(abs(x1 - x2) == 1 && y1 - y2 == -1 || abs(x1 - x2) == 2 && y1 - y2 == -2))
			{
				return abs(x1 - x2) < 4 && abs(y1 - y2) < 4;
			}
		}
		else if (piece->GetType() == Lion || piece->GetType() == LionDog || piece->GetType() == FuriousFiend || piece->GetType() == Thunderclap ||
            piece->GetType() == KnightCaptain || piece->GetType() == ExtensiveFog || piece->GetType() == HolyLight ||
			piece->GetType() == WingedHorse || piece->GetType() == DoubleKylin || piece->GetType() == DoublePhoenix ||
			piece->GetType() == RoamingAssault)
		{
			return true;
		}
		else if (piece->GetType() == LionHawk || piece->GetType() == BuddhistSpirit || piece->GetType() == RisingDragon)
		{
			return abs(x1 - x2) < 3 && abs(y1 - y2) < 3;
		}
		else if (piece->GetType() == TeachingKing)
		{
			return abs(x1 - x2) < 4 && abs(y1 - y2) < 4;
		}
		else if (piece->GetType() == FlyingHawk)
		{
			return abs(x1 - x2) + abs(y1 - y2) < 3;
		}
	}
	return false;
}

void EngineOutputHandler::CalculateCheck(Board* board, PieceColour pieceColour, std::vector<std::pair<int, int>>& moves, int oldX, int oldY, int newX, int newY)
{
	Board* brd = board->Clone();
	brd->GetMoves(board->GetData(oldX, oldY), oldX, oldY);
	brd->Move(oldX, oldY, newX, newY);
	const auto location = GetPieceLocation(board, King, pieceColour);
	const int kx = location.first;
	const int ky = location.second;
	auto opponentMoves = brd->GetAllMoves(pieceColour == White ? Black : White);
	std::for_each(opponentMoves.begin(), opponentMoves.end(), [&](std::tuple<int, int, int, int> t)
	{
		if (std::get<2>(t) == kx && std::get<3>(t) == ky)
		{
			board->RemoveMove(newX, newY);
			RemoveMove(moves, newX, newY);
		}
	});
	delete brd;
}

std::pair<int, int> EngineOutputHandler::GetPieceLocation(const Board* board, PieceType pieceType, PieceColour pieceColour)
{
	int kx = -1, ky = -1;
	for (int i = 0; i < board->GetWidth(); i++)
	{
		for (int j = 0; j < board->GetHeight(); j++)
		{
			const Piece* p = board->GetData(i, j);
			if (p != nullptr && p->GetBaseType() == pieceType && p->GetColour() == pieceColour)
			{
				kx = i;
				ky = j;
				break;
			}
		}
		if (kx > -1 && ky > -1)
			break;
	}
	return { kx, ky };
}

std::vector<std::pair<int, int>> EngineOutputHandler::GetPieceLocations(const Board* board, PieceType pieceType, PieceColour pieceColour)
{
	int kx = -1, ky = -1;
	std::vector<std::pair<int, int>> result;
	for (int i = 0; i < board->GetWidth(); i++)
	{
		for (int j = 0; j < board->GetHeight(); j++)
		{
			const Piece* p = board->GetData(i, j);
			if (p != nullptr && p->GetBaseType() == pieceType && p->GetColour() == pieceColour)
			{
				kx = i;
				ky = j;
				result.emplace_back(kx, ky);
			}
		}
	}
	return result;
}

std::array<char, 5> EngineOutputHandler::ExtractMove(const wxString& buf, EngineProtocol engineProtocol, GameVariant gameVariant)
{
	const wxRegEx _csre = wxRegEx(R"(([a-s])(1[0-6]|[0-9])([a-s])(1[0-6]|[0-9])([+nbrq])?)");
	const wxRegEx _cwre = wxRegEx(R"(([PXRFSEODUGWVCLMHa-k])(@|1[0-1]|[0-9])([a-k])(1[0-1]|[0-9])([+nbrq])?)");
	const wxRegEx _qhre = wxRegEx(R"(([A-I])([0-9])(\-)([A-I])([0-9]))");
	const wxRegEx _sgxbre = wxRegEx(R"(([RBGSNLPa-o])(\*|@|[1-9])([a-o])([1-9])(\+)?)");
	const wxRegEx _sgusre = wxRegEx(R"(([RBGSNLP1-9])(\*|@|[a-o])([1-9])([a-o])(\+)?)");
	wxString result;
	wxArrayString parts = wxSplit(buf.Strip(wxString::both), '\n');
	for (auto& part : parts)
	{
		if (engineProtocol == XBoard ? part.StartsWith("move ") : part.StartsWith("bestmove "))
		{
			if (engineProtocol == USI)
			{
				if (_sgusre.Matches(part))
				{
					wxString firstDigit = _sgusre.GetMatch(part, 1);
					wxString firstLetter = _sgusre.GetMatch(part, 2);
					wxString secondDigit = _sgusre.GetMatch(part, 3);
					wxString secondLetter = _sgusre.GetMatch(part, 4);
					wxString promotionChar = _sgusre.GetMatch(part, 5);
					result.Append(firstDigit[0]);
					result.Append(firstLetter[0]);
					result.Append(secondDigit[0]);
					result.Append(secondLetter[0]);
					if (!promotionChar.empty()) result.Append(promotionChar[0]);
				}
			}
			else if (gameVariant == ChuShogi || gameVariant == DaiShogi || gameVariant == WaShogi || gameVariant == TenjikuShogi ||
					 gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi)
			{
				if (_csre.Matches(part))
				{
					wxString firstLetter = _csre.GetMatch(part, 1);
					wxString firstDigit = _csre.GetMatch(part, 2);
					wxString secondLetter = _csre.GetMatch(part, 3);
					wxString secondDigit = _csre.GetMatch(part, 4);
					wxString promotionChar = _csre.GetMatch(part, 5);
					result.Append(firstLetter[0]);
					int fd;
					firstDigit.ToInt(&fd);
					result.Append(static_cast<char>(fd));
					result.Append(secondLetter[0]);
					int sd;
					secondDigit.ToInt(&sd);
					result.Append(static_cast<char>(sd));
					if (!promotionChar.empty()) result.Append(promotionChar[0]);
				}
			}
			else if (gameVariant == CrazyWa)
			{
				if (_cwre.Matches(part))
				{
					wxString firstLetter = _cwre.GetMatch(part, 1);
					wxString firstDigit = _cwre.GetMatch(part, 2);
					wxString secondLetter = _cwre.GetMatch(part, 3);
					wxString secondDigit = _cwre.GetMatch(part, 4);
					wxString promotionChar = _cwre.GetMatch(part, 5);
					result.Append(firstLetter[0]);
					if (firstDigit == '@')
                    {
                        result.Append(firstDigit[0]);
                    }
                    else
                    {
                        int fd;
                        firstDigit.ToInt(&fd);
                        result.Append(static_cast<char>(fd));
                    }
					result.Append(secondLetter[0]);
					int sd;
					secondDigit.ToInt(&sd);
					result.Append(static_cast<char>(sd));
					if (!promotionChar.empty()) result.Append(promotionChar[0]);
				}
			}
			else
			{
				if (gameVariant == Shogi || gameVariant == MiniShogi || gameVariant == JudkinShogi)
                {
                    if (_sgxbre.Matches(part))
                    {
                        wxString firstLetter = _sgxbre.GetMatch(part, 1);
                        wxString firstDigit = _sgxbre.GetMatch(part, 2);
                        wxString secondLetter = _sgxbre.GetMatch(part, 3);
                        wxString secondDigit = _sgxbre.GetMatch(part, 4);
                        wxString promotionChar = _sgxbre.GetMatch(part, 5);
                        result.Append(firstLetter[0]);
                        result.Append(firstDigit[0]);
                        result.Append(secondLetter[0]);
                        result.Append(secondDigit[0]);
                        if (!promotionChar.empty()) result.Append(promotionChar[0]);
                    }
                }
                else if (_csre.Matches(part))
                {
                        wxString firstLetter = _csre.GetMatch(part, 1);
                        wxString firstDigit = _csre.GetMatch(part, 2);
                        wxString secondLetter = _csre.GetMatch(part, 3);
                        wxString secondDigit = _csre.GetMatch(part, 4);
                        wxString promotionChar = _csre.GetMatch(part, 5);
                        result.Append(firstLetter[0]);
                        result.Append(firstDigit[0]);
                        result.Append(secondLetter[0]);
                        result.Append(secondDigit[0]);
                        if (!promotionChar.empty()) result.Append(promotionChar[0]);
                }
			}
		}
		else if (engineProtocol == Qianhong)
		{
			if (_qhre.Matches(part))
			{
				wxString firstLetter = _qhre.GetMatch(part, 1);
				wxString firstDigit = _qhre.GetMatch(part, 2);
				wxString secondLetter = _qhre.GetMatch(part, 4);
				wxString secondDigit = _qhre.GetMatch(part, 5);
				result.Append(firstLetter[0]);
				int fd;
				firstDigit.ToInt(&fd);
				result.Append(static_cast<char>(fd));
				result.Append(secondLetter[0]);
				int sd;
				secondDigit.ToInt(&sd);
				result.Append(static_cast<char>(sd));
			}
		}
	}
	std::array<char, 5> resultArray;
	resultArray[0] = (char)result[0];
	resultArray[1] = (char)result[1];
	resultArray[2] = (char)result[2];
	resultArray[3] = (char)result[3];
	if (result.size() == 5)
    {
        resultArray[4] = (char)result[4];
    }
    else
    {
        resultArray[4] = ' ';
    }
	return resultArray;
}

Move EngineOutputHandler::ByteArrayToMove(std::array<char, 5> moveArray, EngineProtocol engineProtocol, GameVariant gameVariant, int width, int height)
{
	int x1, y1, x2, y2;
	if (engineProtocol == Qianhong)
	{
		x1 = moveArray[0] - 65;
		y1 = 10 - moveArray[1];
		x2 = moveArray[2] - 65;
		y2 = 10 - moveArray[3];
	}
	else if (engineProtocol == USI)
	{
		x1 = width - moveArray[0] + 48;
		y1 = moveArray[1] - 97;
		x2 = width - moveArray[2] + 48;
		y2 = moveArray[3] - 97;
	}
	else if (gameVariant == ChuShogi || gameVariant == DaiShogi || gameVariant == WaShogi || gameVariant == CrazyWa || gameVariant == TenjikuShogi ||
			 gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi)
	{
		x1 = moveArray[0] - 97;
		y1 = width - moveArray[1];
		x2 = moveArray[2] - 97;
		y2 = width - moveArray[3];
	}
	else
	{
		x1 = moveArray[0] - 97;
		y1 = height - moveArray[1] + 48;
		x2 = moveArray[2] - 97;
		y2 = height - moveArray[3] + 48;
	}
	return {x1, y1, x2, y2};
}

wxString EngineOutputHandler::MoveToByteArray(Move m, EngineProtocol engineProtocol, int width, int height)
{
	wxString result;
	if (engineProtocol == USI)
	{
		result.Append(char(width - m.x1));
		result.Append(char(m.y1));
		result.Append(char(width - m.x2));
		result.Append(char(m.y2));
	}
	else
	{
		result.Append(char(m.x1));
		result.Append(char(height - m.y1));
		result.Append(char(m.x2));
		result.Append(char(height - m.y2));
	}
	return result;
}

void EngineOutputHandler::ReadStandardOutput(const wxString& buf, const std::shared_ptr<Engine>& engine, Board * board, wxTextCtrl * textEdit,
	GameVariant gameVariant, EngineOutput engineOutput, PieceColour currentPlayer)
{
	if (engine->GetType() == XBoard)
	{
		if (buf.Contains("setboard=0")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("setboard", false);
		if (buf.Contains("setboard=1")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("setboard", true);
		if (buf.Contains("memory=0")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("memory", false);
		if (buf.Contains("memory=1")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("memory", true);
		if (buf.Contains("usermove=0")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("usermove", false);
		if (buf.Contains("usermove=1")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("usermove", true);
	}
	const std::array<char, 5> moveArray = ExtractMove(buf, engine->GetType(), gameVariant);
	textEdit->Clear();
    textEdit->AppendText(engineOutput == Verbose ? buf : wxString(moveArray.data(), moveArray.size()));
	if (moveArray.empty()) return;
	const Move m = ByteArrayToMove(moveArray, engine->GetType(), gameVariant, board->GetWidth(), board->GetHeight());
	int x1 = m.x1;
	int y1 = m.y1;
	int x2 = m.x2;
	int y2 = m.y2;
	if (gameVariant == ChuShogi || gameVariant == DaiShogi || gameVariant == TenjikuShogi ||
		gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			if (moveArray.size() < 8)
			{
				const bool isPromoted = moveArray.size() == 5 && moveArray[4] == '+' && (y2 <= 3 || y2 >= 8);
				board->GetMoves(board->GetData(x1, y1), x1, y1);
				if (board->GetData(x2, y2) != nullptr)
				{
					delete board->GetData(x2, y2);
				}
				board->SetData(x2, y2, board->GetData(x1, y1));
				board->SetData(x1, y1, nullptr);
				AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, isPromoted ? moveArray[4] : ' ', ' ');
				engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[4] : ' ');
				if (isPromoted)
				{
					board->GetData(x2, y2)->Promote();
				}
			}
			else
			{
				const int x3 = moveArray[6] - 97;
				const int y3 = board->GetWidth() - moveArray[7];
				if (board->GetData(x2, y2) != nullptr)
				{
					delete board->GetData(x2, y2);
				}
				if (x1 != x3 || y1 != y3)
				{
					if (board->GetData(x3, y3) != nullptr)
					{
						delete board->GetData(x3, y3);
					}
					board->SetData(x3, y3, board->GetData(x1, y1));
					board->SetData(x1, y1, nullptr);
				}
				board->SetData(x2, y2, nullptr);
				AddMove(board, gameVariant, board->GetData(x3, y3)->GetType(), x1, y1, x2, y2, x3, y3);
				std::dynamic_pointer_cast<WbEngine>(engine)->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], moveArray[6], moveArray[7]);
			}
		}
	}
	else if (gameVariant == Xiangqi)
	{
		y1--;
		y2--;
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			board->Move(x1, y1, x2, y2, false);
			AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, ' ', ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
	}
	else if (gameVariant == Chess)
	{
		// Castling check
		wxString str = wxString(moveArray.data(), moveArray.size()).Strip(wxString::both);
		if ((str == "e8g8" || str == "e8h8" || str == "e8c8" || str == "e8b8" || str == "e8a8" ||
			str == "e1g1" || str == "e1h1" || str == "e1c1" || str == "e1b1" || str == "e1a1") &&
			board->GetData(x1, y1) != nullptr && board->GetData(x1, y1)->GetType() == King &&
			board->GetData(x2 > 4 ? 7 : 0, y2) != nullptr && board->GetData(x2 > 4 ? 7 : 0, y2)->GetType() == Rook)
		{
			Piece* rook = board->GetData(x2 > 4 ? 7 : 0, y2);
			board->SetData(x2 > 4 ? 7 : 0, y2, board->GetData(x1, y1));
			board->SetData(4, y1, rook);
			dynamic_cast<ChessBoard*>(board)->WriteCastling(x1 == 7 ? "O-O" : "O-O-O");
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
		else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			const bool isPromoted = moveArray.size() == 5
				&& (y2 == 0 || y2 == board->GetHeight() - 1)
				&& board->GetData(x1, y1)->GetType() == Pawn
				&& (moveArray[4] == 'n' || moveArray[4] == 'b' || moveArray[4] == 'r' || moveArray[4] == 'q');
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			const PieceType ct = board->GetData(x2, y2) != nullptr ? board->GetData(x2, y2)->GetType() : None;
			board->Move(x1, y1, x2, y2, false);
			AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, isPromoted ? moveArray[4] : ' ', ct != None ? 'x' : ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[4] : ' ');
			if (isPromoted)
			{
				switch (moveArray[4])
				{
				case 'n':
					board->GetData(x2, y2)->Promote(Knight);
					break;
				case 'b':
					board->GetData(x2, y2)->Promote(Bishop);
					break;
				case 'r':
					board->GetData(x2, y2)->Promote(Rook);
					break;
				case 'q':
					board->GetData(x2, y2)->Promote(Queen);
					break;
				default:
					break;
				}
			}
		}
	}
	else if (gameVariant == Shatranj)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			const bool isPromoted = board->GetData(x1, y1)->GetType() == Pawn && (y2 == 0 || y2 == board->GetHeight() - 1);
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			const PieceType ct = board->GetData(x2, y2) != nullptr ? board->GetData(x2, y2)->GetType() : None;
			board->Move(x1, y1, x2, y2, false);
			AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, ' ', ct != None ? 'x' : ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
			if (isPromoted)
			{
				board->GetData(x2, y2)->Promote();
			}
		}
	}
	else if (gameVariant == Makruk)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			const bool isPromoted = board->GetData(x1, y1)->GetType() == Pawn && (y2 <= 2 || y2 >= board->GetHeight() - 3);
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			const PieceType ct = board->GetData(x2, y2) != nullptr ? board->GetData(x2, y2)->GetType() : None;
			board->Move(x1, y1, x2, y2, false);
			AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, ' ', ct != None ? 'x' : ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
			if (isPromoted)
			{
				board->GetData(x2, y2)->Promote();
			}
		}
	}
	else if (gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi || gameVariant == JudkinShogi || gameVariant == WaShogi || gameVariant == CrazyWa)
	{
		if ((gameVariant == Shogi || gameVariant == MiniShogi || gameVariant == JudkinShogi || gameVariant == CrazyWa) && (moveArray[1] == '@' || moveArray[1] == '*'))
		{
			PieceType newPiece;
			if (gameVariant != CrazyWa)
			{
				switch (moveArray[0])
				{
				case 'R':
					newPiece = Rook;
					break;
				case 'B':
					newPiece = Bishop;
					break;
				case 'G':
					newPiece = Gold;
					break;
				case 'S':
					newPiece = Silver;
					break;
				case 'N':
					newPiece = Knight;
					break;
				case 'L':
					newPiece = Lance;
					break;
				case 'P':
					newPiece = Pawn;
					break;
				default:
					newPiece = None;
					break;
				}
			}
			else
			{
				switch (moveArray[0])
				{
				case 'D':
					newPiece = Dog;
					break;
				case 'R':
					newPiece = RunningRabbit;
					break;
				case 'W':
					newPiece = Gold;
					break;
				case 'V':
					newPiece = Silver;
					break;
				case 'X':
					newPiece = TreacherousFox;
					break;
				case 'M':
					newPiece = ClimbingMonkey;
					break;
				case 'G':
					newPiece = FlyingGoose;
					break;
				case 'C':
					newPiece = FlyingCock;
					break;
				case 'F':
					newPiece = FlyingFalcon;
					break;
				case 'U':
					newPiece = StruttingCrow;
					break;
				case 'E':
					newPiece = CloudEagle;
					break;
				case 'L':
					newPiece = SwoopingOwl;
					break;
				case 'H':
					newPiece = LiberatedHorse;
					break;
				case 'S':
					newPiece = SideMover;
					break;
				case 'O':
					newPiece = Lance;
					break;
				case 'P':
					newPiece = Pawn;
					break;
				default:
					newPiece = None;
					break;
				}
			}
			dynamic_cast<ShogiVariantBoard*>(board)->PlacePiece(newPiece, currentPlayer, x2, y2);
			AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), moveArray[0], moveArray[1], x2, y2, ' ', ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
		else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			const bool isPromoted = moveArray.size() == 5 &&
				((gameVariant == MiniShogi && (y2 == 0 || y2 == 4) && moveArray[4] == '+')
					|| (gameVariant == JudkinShogi && (y2 == 0 || y2 == 5) && moveArray[4] == '+')
					|| ((gameVariant == Shogi || gameVariant == ShoShogi) && (y2 <= 2 || y2 >= 6) && moveArray[4] == '+')
					|| ((gameVariant == WaShogi || gameVariant == CrazyWa) && (y2 <= 2 || y2 >= 8) && moveArray[4] == '+'));
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			board->Move(x1, y1, x2, y2, false);
			AddMove(board, gameVariant, isPromoted ? board->GetData(x2, y2)->GetBaseType() : board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, isPromoted ? moveArray[4] : ' ', ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[4] : ' ');
			if (isPromoted)
			{
				board->GetData(x2, y2)->Promote();
			}
		}
	}
}

void EngineOutputHandler::ReadStandardError(const wxString& buf, wxTextCtrl* textEdit)
{
	textEdit->Clear();
	textEdit->SetDefaultStyle(wxTextAttr(*wxRED));
    textEdit->AppendText(buf);
	textEdit->SetDefaultStyle(wxTextAttr(*wxBLACK));
}

void EngineOutputHandler::AddMove(Board* board, GameVariant gameVariant, PieceType p, int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (gameVariant == Chess || gameVariant == Shatranj)
	{
		dynamic_cast<ShatranjBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (gameVariant == Makruk)
	{
		dynamic_cast<MakrukBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi || gameVariant == JudkinShogi)
	{
		dynamic_cast<ShogiBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (gameVariant == Xiangqi)
	{
		dynamic_cast<XiangqiBoard*>(board)->WriteMove(p, x1, y1, x2, y2);
	}
}

template <typename T> std::basic_string<T> uppercase(const std::basic_string<T>& s)
{
	std::basic_string<T> s2 = s;
	std::transform(s2.begin(), s2.end(), s2.begin(),
		[](const T v) { return static_cast<T>(std::toupper(v)); });
	return s2;
}

template <typename T> std::basic_string<T> lowercase(const std::basic_string<T>& s)
{
	std::basic_string<T> s2 = s;
	std::transform(s2.begin(), s2.end(), s2.begin(),
		[](const T v) { return static_cast<T>(std::tolower(v)); });
	return s2;
}

wxString EngineOutputHandler::SetFenToBoard(Board* board, const wxString& str, GameVariant gameVariant)
{
	wxArrayString parts = wxSplit(str.Strip(wxString::both), '\n');
	wxString fen = parts[0];
	board->Clear();
	const int w = board->GetWidth();
	const int h = board->GetHeight();
	int i = 0, j = 0, k = 0;
	std::string promo;
	do
	{
		const char c = fen[k];
		if (c == '/')
		{
			k++;
			j++;
			i = 0;
		}
		if (c == '+')
		{
			k++;
			promo = "+";
		}
		else if (c >= '0' && c <= '9')
		{
			k++;
			i += c - 48;
		}
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			std::string stringCode(1, c);
			PieceType pieceType = None;
			if (gameVariant == Chess || gameVariant == Shatranj)
			{
				pieceType = ShatranjPiece::FromStringCode(uppercase(stringCode));
			}
			else if (gameVariant == Xiangqi)
			{
				pieceType = XiangqiPiece::FromStringCode(uppercase(stringCode));
			}
			else if (gameVariant == Makruk)
			{
				pieceType = MakrukPiece::FromStringCode(uppercase(stringCode));
			}
			else if (gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi || gameVariant == JudkinShogi)
			{
				pieceType = ShogiPiece::FromStringCode(promo + uppercase(stringCode));
			}
			else if (gameVariant == WaShogi || gameVariant == CrazyWa)
			{
				pieceType = WaShogiPiece::FromStringCode(promo + uppercase(stringCode));
			}
			else if (gameVariant == ChuShogi)
			{
				pieceType = ChuShogiPiece::FromStringCode(promo + uppercase(stringCode));
			}
			else if (gameVariant == DaiShogi || gameVariant == TenjikuShogi ||
				gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi)
			{
				if (k < fen.size() - 1 && (fen[k + 1] == '\'' || fen[k + 1] == '!' || fen[k + 1] == '~'))
				{
					k++;
					stringCode.push_back(fen[k]);
				}
				if (gameVariant == DaiShogi)
				{
					pieceType = DaiShogiPiece::FromStringCode(promo + uppercase(stringCode));
				}
				else if (gameVariant == TenjikuShogi)
				{
					pieceType = TenjikuShogiPiece::FromStringCode(promo + uppercase(stringCode));
				}
				else if (gameVariant == DaiDaiShogi)
				{
					pieceType = DaiDaiShogiPiece::FromStringCode(promo + uppercase(stringCode));
				}
				else if (gameVariant == MakaDaiDaiShogi)
				{
					pieceType = MakaDaiDaiShogiPiece::FromStringCode(promo + uppercase(stringCode));
				}
				else if (gameVariant == KoShogi)
				{
					pieceType = KoShogiPiece::FromStringCode(promo + uppercase(stringCode));
				}
			}
			if (pieceType == None)
			{
				return "Invalid character found in the FEN string at position " + wxString::Format(wxT("%i"), k);
			}
			if (j == h || i == w)
			{
				return "Invalid FEN string for this game";
			}
			Piece* piece = board->CreatePiece(pieceType, c >= 'a' && c <= 'z' ? Black : White);
			if (promo == "+")
			{
				piece->Promote();
			}
			board->SetData(i, j, piece);
			promo = "";
			k++;
			i++;
		}
	} while ((i < w || j < h - 1) && k < fen.size());
	if (gameVariant == Chess)
	{
		ChessBoard* cb = dynamic_cast<ChessBoard*>(board);
		if (parts.size() >= 3)
		{
			cb->SetCastling(parts[2].ToStdString());
		}
		if (parts.size() >= 4)
		{
			if (parts[3].size() == 2 && parts[3][0] >= 'a' && parts[3][0] <= 'h' && parts[3][1] >= '1' && parts[3][1] <= '8')
			{
				cb->SetEnPassant(parts[3].ToStdString());
			}
			else
			{
				cb->SetEnPassant("-");
			}
		}
	}
	if (gameVariant == Shogi || gameVariant == MiniShogi || gameVariant == JudkinShogi)
	{
		if (parts.size() >= 3)
		{
			ShogiVariantBoard* svb = dynamic_cast<ShogiVariantBoard*>(board);
			k = 0;
			do
			{
				if (parts[2][k] >= 'a' && parts[2][k] <= 'z')
				{
					svb->AddCapturedPiece(ShogiPiece::FromStringCode(uppercase(std::string(1, parts[2][k]))), Black);
				}
				else if (parts[2][k] >= 'A' && parts[2][k] <= 'Z')
				{
					svb->AddCapturedPiece(ShogiPiece::FromStringCode(std::string(1, parts[2][k])), White);
				}
				k++;
			} while (k < parts[2].size() && ((parts[2][k] >= 'a' && parts[2][k] <= 'z') || (parts[2][k] >= 'A' && parts[2][k] <= 'Z')));
		}
	}
	return "";
}

bool EngineOutputHandler::IsInsidePromotionZone(GameVariant gameVariant, PieceColour pieceColour, int y)
{
	if (gameVariant == MiniShogi)
	{
		if ((y == 4 && pieceColour == Black) ||
			(y == 0 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == JudkinShogi)
	{
		if ((y == 5 && pieceColour == Black) ||
			(y == 0 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == Shogi || gameVariant == ShoShogi)
	{
		if ((y >= 6 && pieceColour == Black) ||
			(y <= 2 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == WaShogi || gameVariant == CrazyWa)
	{
		if ((y >= 8 && pieceColour == Black) ||
			(y <= 2 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == ChuShogi)
	{
		if ((y >= 8 && pieceColour == Black) ||
			(y <= 3 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == DaiShogi)
	{
		if ((y >= 10 && pieceColour == Black) ||
			(y <= 4 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == TenjikuShogi)
	{
		if ((y >= 11 && pieceColour == Black) ||
			(y <= 4 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == KoShogi)
	{
		if ((y >= 13 && pieceColour == Black) ||
			(y <= 5 && pieceColour == White))
		{
			return true;
		}
	}
	return false;
}

bool EngineOutputHandler::CanBePromoted(const Piece* piece, GameVariant gameVariant, int oldY, int newY)
{
	if (piece != nullptr)
	{
		if (gameVariant == MiniShogi && !piece->IsPromoted() &&
			piece->GetType() != King && piece->GetType() != Gold &&
			piece->GetType() != DragonKing && piece->GetType() != DragonHorse)
		{
			return IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) || IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if (gameVariant == JudkinShogi && !piece->IsPromoted() &&
			piece->GetType() != King && piece->GetType() != Gold &&
			piece->GetType() != DragonKing && piece->GetType() != DragonHorse)
		{
			return IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) || IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if ((gameVariant == Shogi || gameVariant == ShoShogi) && !piece->IsPromoted() &&
			piece->GetType() != King && piece->GetType() != Gold &&
			piece->GetType() != DragonKing && piece->GetType() != DragonHorse)
		{
			return IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) || IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if ((gameVariant == WaShogi || gameVariant == CrazyWa) && !piece->IsPromoted() &&
			piece->GetType() != King && piece->GetType() != CloudEagle && piece->GetType() != TreacherousFox)
		{
			return IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) || IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if (gameVariant == ChuShogi && !piece->IsPromoted() && piece->GetType() != King &&
			piece->GetType() != Queen && piece->GetType() != Lion)
		{
			return !IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) && IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if (gameVariant == DaiShogi && !piece->IsPromoted() && piece->GetType() != King &&
			piece->GetType() != Queen && piece->GetType() != Lion)
		{
			return !IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) && IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if (gameVariant == TenjikuShogi && !piece->IsPromoted() && piece->GetType() != King &&
			piece->GetType() != Queen && piece->GetType() != Lion && piece->GetType() != LionHawk &&
			piece->GetType() != ViceGeneral && piece->GetType() != GreatGeneral &&
			piece->GetType() != FireDemon && piece->GetType() != FreeEagle)
		{
			return !IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) && IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if (gameVariant == KoShogi && !piece->IsPromoted() && piece->GetType() != King &&
			piece->GetType() != Lion && piece->GetType() != Bishop)
		{
			return IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) || IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
	}
	return false;
}
