#include "AddEngineDialog.h"

//(*InternalHeaders(AddEngineDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(AddEngineDialog)
//*)

BEGIN_EVENT_TABLE(AddEngineDialog,wxDialog)
    //(*EventTable(AddEngineDialog)
    //*)
END_EVENT_TABLE()

AddEngineDialog::AddEngineDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(AddEngineDialog)
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    //*)
}

AddEngineDialog::~AddEngineDialog()
{
    //(*Destroy(AddEngineDialog)
    //*)
}

wxTextCtrl* AddEngineDialog::GetEngineName() const
{
	//return ui->engineName;
}

wxComboBox* AddEngineDialog::GetGameVariant() const
{
	//return ui->gameVariant;
}

wxComboBox* AddEngineDialog::GetEngineProtocol() const
{
	//return ui->engineProtocol;
}

wxTextCtrl* AddEngineDialog::GetEnginePath() const
{
	//return ui->enginePath;
}

void AddEngineDialog::SetEngineName(const wxString& engineName) const
{
	//ui->engineName->setText(engineName);
}

void AddEngineDialog::SetGameVariant(const wxString& gameVariant) const
{
    //ui->gameVariant->setCurrentText(gameVariant);
}

void AddEngineDialog::SetEngineProtocol(const wxString& engineProtocol) const
{
    //ui->engineProtocol->setCurrentText(engineProtocol);
}

void AddEngineDialog::SetEnginePath(const wxString& enginePath) const
{
	//ui->enginePath->setText(enginePath);
}
