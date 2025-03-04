#include "Logger.h"

void Logger::writeToLog(const wxString& message, const LogLevel level)
{
    wxString settingsDir = wxStandardPaths::Get().GetUserDataDir();
    if (!wxDirExists(settingsDir))
    {
        // Create the directory if it doesn’t exist
        wxMkdir(settingsDir);
    }

    wxString logFilePath = settingsDir + "/QBoard.log";

    wxFile logFile;
    // The style wxFile::write_append opens (or creates) the file for writing at the end.
    if (!logFile.Open(logFilePath, wxFile::write_append))
    {
        wxLogError("Failed to open log file: %s", logFilePath);
        return;
    }

    // Format the log message with a timestamp
    wxString timestamp = wxDateTime::Now().Format("%Y-%m-%d %H:%M:%S");
    wxString levelStr;
    switch (level)
    {
    case LogLevel::Error:
        levelStr = "ERROR";
        break;
    case LogLevel::Warning:
        levelStr = "WARNING";
        break;
    case LogLevel::Info:
        levelStr = "INFO";
        break;
    }
    wxString logLine = wxString::Format("[%s] [%s] %s\n", timestamp, levelStr, message);

    logFile.Write(logLine.mb_str(), logLine.size());

    logFile.Close();
}
