#include "IniFile.h"

void IniFile::writeToIniFile(const wxString& filePath, const wxString& gameVariant, const wxString& pieceStyle, const wxString& engineOutput) {
    wxFileConfig config(
        "wxBoard",
        wxEmptyString,
        filePath,
        wxEmptyString,
        wxCONFIG_USE_LOCAL_FILE
    );
	// Write values
	config.SetPath("General");
    config.Write("GameVariant", gameVariant);
    config.Write("PieceStyle", pieceStyle);
    config.Write("EngineOutput", engineOutput);

	config.Flush();
}

wxArrayString IniFile::readFromIniFile(const wxString& filePath) {
    wxFileConfig config(
        "wxBoard",
        wxEmptyString,
        filePath,
        wxEmptyString,
        wxCONFIG_USE_LOCAL_FILE
    );

    config.SetPath("General");
    wxString gameVariant  = config.Read("GameVariant",  "Chess");
    wxString pieceStyle   = config.Read("PieceStyle",   "European");
    wxString engineOutput = config.Read("EngineOutput", "Concise");

    // Read values from the "General" group
    wxArrayString result;
    result.Add(gameVariant);
    result.Add(pieceStyle);
    result.Add(engineOutput);

    // Return values
    return result;
}
