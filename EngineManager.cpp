#include "EngineManager.h"

//(*InternalHeaders(EngineManager)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(EngineManager)
//*)

BEGIN_EVENT_TABLE(EngineManager,wxDialog)
    //(*EventTable(EngineManager)
    //*)
END_EVENT_TABLE()

EngineManager::EngineManager(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(EngineManager)
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    //*)
}

EngineManager::~EngineManager()
{
    //(*Destroy(EngineManager)
    //*)
}

wxGrid * EngineManager::GetEngineTable() const
{
	//return ui->engineTable;
}

EngineProtocol EngineManager::StringToEngineProtocol(const wxString& str)
{
	if (str == "UCI")
		return UCI;
	if (str == "UCCI")
		return UCCI;
	if (str == "Qianhong")
		return Qianhong;
	if (str == "USI")
		return USI;
	return XBoard;
}

GameVariant EngineManager::StringToGameVariant(const wxString& str)
{
	if (str == "Xiangqi")
		return Xiangqi;
	if (str == "Shogi")
		return Shogi;
	if (str == "Sho Shogi")
		return ShoShogi;
	if (str == "Chu Shogi")
		return ChuShogi;
	if (str == "Dai Shogi")
		return DaiShogi;
	if (str == "Tenjiku Shogi")
		return TenjikuShogi;
	if (str == "Dai Dai Shogi")
		return DaiDaiShogi;
	if (str == "Maka Dai Dai Shogi")
		return MakaDaiDaiShogi;
	if (str == "Ko Shogi")
		return KoShogi;
	if (str == "Mini Shogi")
		return MiniShogi;
	if (str == "Judkins Shogi")
		return JudkinShogi;
	if (str == "Shatranj")
		return Shatranj;
	if (str == "Makruk")
		return Makruk;
	if (str == "Wa Shogi")
		return WaShogi;
	if (str == "CrazyWa")
		return CrazyWa;
	return Chess;
}
