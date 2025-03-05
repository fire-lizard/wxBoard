#include "NewGameDialog.h"

//(*InternalHeaders(NewGameDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(NewGameDialog)
//*)

BEGIN_EVENT_TABLE(NewGameDialog,wxDialog)
    //(*EventTable(NewGameDialog)
    //*)
END_EVENT_TABLE()

NewGameDialog::NewGameDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(NewGameDialog)
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    //*)
}

NewGameDialog::~NewGameDialog()
{
    //(*Destroy(NewGameDialog)
    //*)
}

wxComboBox* NewGameDialog::GetWhitePlayer() const
{
	//return ui->whitePlayerComboBox;
}

wxComboBox* NewGameDialog::GetBlackPlayer() const
{
	//return ui->blackPlayerComboBox;
}

wxStaticText* NewGameDialog::GetWhitePlayerLabel() const
{
	//return ui->whitePlayerLabel;
}
