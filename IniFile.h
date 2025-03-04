#ifndef HEADER_5D825D16F177D20
#define HEADER_5D825D16F177D20

#pragma once

#include <wx/fileconf.h>

class IniFile {
public:
    static void writeToIniFile(const wxString& filePath, const wxString& gameVariant,
                               const wxString& pieceStyle, const wxString& engineOutput);
    static wxArrayString readFromIniFile(const wxString& filePath);
};
#endif // header guard

