#include "SettingsDialog.h"

//(*InternalHeaders(SettingsDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(SettingsDialog)
//*)

BEGIN_EVENT_TABLE(SettingsDialog,wxDialog)
    //(*EventTable(SettingsDialog)
    //*)
END_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(SettingsDialog)
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    //*)
}

SettingsDialog::~SettingsDialog()
{
    //(*Destroy(SettingsDialog)
    //*)
}

wxComboBox* SettingsDialog::GetGameVariants() const
{
	//return ui->variantsComboBox;
}

wxComboBox* SettingsDialog::GetGamePieces() const
{
	//return ui->piecesComboBox;
}

wxComboBox* SettingsDialog::GetEngineOutput() const
{
	//return ui->engineOutputComboBox;
}
