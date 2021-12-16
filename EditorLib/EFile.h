#pragma once

#include <string>
#include <fstream>
#include <ostream>

class EFile
{
public:
	EFile();
	virtual ~EFile();
protected:
	std::wstring m_wFimeName;
	std::wstring m_wExportName;

	std::ifstream readFile;
	std::ofstream writeFile;

	bool FormatFile(const wchar_t* _pFileName);
	bool OpenFile(wchar_t* _pFileName);
	bool WirteFile(std::wstring _pMsg);
	bool ReadFile(wchar_t* _pFileName);
	bool CloseFile();

	bool ExportName(const wchar_t* _pExportName);
};

