#ifndef PROMOTIONDIALOG_H
#define PROMOTIONDIALOG_H

//(*Headers(PromotionDialog)
#include <wx/dialog.h>
//*)

class PromotionDialog: public wxDialog
{
    public:

        PromotionDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
        virtual ~PromotionDialog();

        //(*Declarations(PromotionDialog)
        //*)

    protected:

        //(*Identifiers(PromotionDialog)
        //*)

    private:

        //(*Handlers(PromotionDialog)
        //*)

        DECLARE_EVENT_TABLE()
};

#endif
