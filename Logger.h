#ifndef HEADER_482A1C656B340F0B
#define HEADER_482A1C656B340F0B

#pragma once
#include <wx/stdpaths.h>
#include <wx/file.h>
#include <wx/log.h>
#include <wx/datetime.h>

enum class LogLevel {Info, Warning, Error};

class Logger
{
public:
	static void writeToLog(const wxString& message, const LogLevel level = LogLevel::Info);
};

#endif // header guard

