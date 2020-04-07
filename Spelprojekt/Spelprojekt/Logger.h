#pragma once
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

enum class LOG_LEVEL
{
	Info = 0,
	Error = 1,
	Warning = 2,
	Debug = 3,
	HALP = 4
};

// https://stackoverflow.com/questions/32185512/output-to-console-from-a-win32-gui-application-on-windows-10
#define ENABLE_CONSOLE_OUTPUT 1
#define ENABLE_TEXT_OUTPUT 1
#define TEXT_FILENAME "test_log.txt"

namespace Logger
{
	static bool _iocopen = false;
	static std::string LOG_LEVEL_NAMES[] = { "info", "error", "warning", "debug", "hj�lp" };
	static std::ofstream filestream;

	inline void Open()
	{
		if (!_iocopen)
		{
			std::string ss = "Console open\t\t";

#if ENABLE_TEXT_OUTPUT
			filestream.open(TEXT_FILENAME, std::ios::out | std::ios_base::app);
			ss += "Writing to file: " + std::string(TEXT_FILENAME);
			filestream << "\n" << ss << "\n";
			filestream.close();
#endif			

#if ENABLE_CONSOLE_OUTPUT
			AllocConsole();
			HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			int hConsole = _open_osfhandle((long)stdHandle, _O_TEXT);
			FILE* fp = _fdopen(hConsole, "w");
			freopen_s(&fp, "CONOUT$", "w", stdout);
			std::cout << ss << "\n";
#endif
			_iocopen = true;
		}
	}

	inline void Write(LOG_LEVEL logLevel, const std::string& msg)
	{
		std::string lineString = "[" + LOG_LEVEL_NAMES[static_cast<int>(logLevel)] + "] " + msg + "\n";

#if ENABLE_CONSOLE_OUTPUT
		if (!_iocopen)
			Open();
		std::cout << lineString;
#endif

#if ENABLE_TEXT_OUTPUT
		filestream.open(TEXT_FILENAME, std::ios::out | std::ios_base::app);

		filestream.exceptions(filestream.exceptions() | std::ios::failbit | std::ifstream::badbit);
		filestream << lineString;
		filestream.close();
#endif
	}

	inline void Close()
	{
		Write(LOG_LEVEL::Info, "Closing console");
		_iocopen = false;
		filestream.close();
	}
}