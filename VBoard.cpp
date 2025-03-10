#include "VBoard.h"

//(*InternalHeaders(VBoard)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(VBoard)
//*)

BEGIN_EVENT_TABLE(VBoard,wxPanel)
    //(*EventTable(VBoard)
    //*)
END_EVENT_TABLE()

VBoard::VBoard(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(VBoard)
    Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
    //*)
}

VBoard::~VBoard()
{
    //(*Destroy(VBoard)
    //*)
}

