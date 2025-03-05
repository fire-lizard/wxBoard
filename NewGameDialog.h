#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

//(*Headers(NewGameDialog)
#include <wx/dialog.h>
//*)

#include <wx/combobox.h>
#include <wx/stattext.h>

class NewGameDialog: public wxDialog
{
    public:

        NewGameDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
        virtual ~NewGameDialog();

        //(*Declarations(NewGameDialog)
        //*)

        wxComboBox* GetWhitePlayer() const;
        wxComboBox* GetBlackPlayer() const;
        wxStaticText* GetWhitePlayerLabel() const;

    protected:

        //(*Identifiers(NewGameDialog)
        //*)

    private:

        //(*Handlers(NewGameDialog)
        //*)

        DECLARE_EVENT_TABLE()
};

#endif
