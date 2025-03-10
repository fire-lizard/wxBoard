#ifndef ADDENGINEDIALOG_H
#define ADDENGINEDIALOG_H

//(*Headers(AddEngineDialog)
#include <wx/dialog.h>
//*)

#include <wx/combobox.h>
#include <wx/textctrl.h>

class AddEngineDialog: public wxDialog
{
    public:

        AddEngineDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
        virtual ~AddEngineDialog();

        //(*Declarations(AddEngineDialog)
        //*)

        wxTextCtrl* GetEngineName() const;
        wxComboBox* GetGameVariant() const;
        wxComboBox* GetEngineProtocol() const;
        wxTextCtrl* GetEnginePath() const;
        void SetEngineName(const wxString &engineName) const;
        void SetGameVariant(const wxString& gameVariant) const;
        void SetEngineProtocol(const wxString& engineProtocol) const;
        void SetEnginePath(const wxString& enginePath) const;

    protected:

        //(*Identifiers(AddEngineDialog)
        //*)

    private:

        //(*Handlers(AddEngineDialog)
        //*)

        DECLARE_EVENT_TABLE()
};

#endif
