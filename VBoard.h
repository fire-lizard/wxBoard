#ifndef VBOARD_H
#define VBOARD_H

//(*Headers(VBoard)
#include <wx/panel.h>
//*)

class VBoard: public wxPanel
{
    public:

        VBoard(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
        virtual ~VBoard();

        //(*Declarations(VBoard)
        //*)

    protected:

        //(*Identifiers(VBoard)
        //*)

    private:

        //(*Handlers(VBoard)
        //*)

        DECLARE_EVENT_TABLE()
};

#endif
