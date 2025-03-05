#ifndef ENGINEMANAGER_H
#define ENGINEMANAGER_H

//(*Headers(EngineManager)
#include <wx/dialog.h>
//*)

#include <wx/grid.h>
#include "Common.h"

class EngineManager: public wxDialog
{
    public:

        EngineManager(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
        virtual ~EngineManager();

        //(*Declarations(EngineManager)
        //*)

        wxGrid* GetEngineTable() const;
        static GameVariant StringToGameVariant(const wxString& str);
        static EngineProtocol StringToEngineProtocol(const wxString& str);

    protected:

        //(*Identifiers(EngineManager)
        //*)

    private:

        //(*Handlers(EngineManager)
        //*)

        DECLARE_EVENT_TABLE()
};

#endif
