#include "PromotionDialog.h"

//(*InternalHeaders(PromotionDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PromotionDialog)
//*)

BEGIN_EVENT_TABLE(PromotionDialog,wxDialog)
    //(*EventTable(PromotionDialog)
    //*)
END_EVENT_TABLE()

PromotionDialog::PromotionDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(PromotionDialog)
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    //*)
}

PromotionDialog::~PromotionDialog()
{
    //(*Destroy(PromotionDialog)
    //*)
}

