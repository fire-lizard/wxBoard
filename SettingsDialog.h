#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

//(*Headers(SettingsDialog)
#include <wx/dialog.h>
//*)

#include <wx/combobox.h>

class SettingsDialog: public wxDialog
{
    public:

        SettingsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
        virtual ~SettingsDialog();

        //(*Declarations(SettingsDialog)
        //*)

        wxComboBox* GetGameVariants() const;
        wxComboBox* GetGamePieces() const;
        wxComboBox* GetEngineOutput() const;

    protected:

        //(*Identifiers(SettingsDialog)
        //*)

    private:

        //(*Handlers(SettingsDialog)
        //*)

        DECLARE_EVENT_TABLE()
};

#endif
