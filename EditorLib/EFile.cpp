

#include "EFile.h"

EFile::EFile()
{
}

EFile::~EFile()
{
}

bool EFile::FormatFile(wchar_t* _pFileName)
{
    return false;
}
bool EFile::ExportName(wchar_t* _pExportName)
{
    m_wExportName = _pExportName;

	std::string ExportStream;
	ExportStream.assign(m_wExportName.begin(), m_wExportName.end());

	writeFile << '#';
	writeFile << ExportStream;
    writeFile << std::endl;
	writeFile << '{';
    writeFile << std::endl;
    return false;
}
bool EFile::OpenFile(wchar_t* _pFileName)
{
	std::locale::global(std::locale("Korean"));


	std::wstring FilePath = L"../Resources/Data/";

    m_wFimeName = _pFileName;

	std::string InputData;
	std::string InputPath = InputData.assign(FilePath.begin(), FilePath.end());
	std::string InputName = InputData.assign(m_wFimeName.begin(), m_wFimeName.end());
    InputData = InputPath + InputData;

    writeFile.open(InputData, std::ios_base::out );

    

    return false;
}
bool EFile::WirteFile(std::wstring _pMsg)
{

    wchar_t* nNum = 0;

    float n = std::wcstof(_pMsg.c_str(), &nNum);

    std::wstring PushNum = nNum;

    std::string fileStream;
   
   
    fileStream.assign(PushNum.begin(), PushNum.end());


    float DataStore = 0;
    std::string DataStream;

   

    if (writeFile.is_open())
    {
        unsigned int max = fileStream.size();
     

   
		for (unsigned int inx = 0; inx < max; inx++)
		{
			char text = fileStream[inx];
			if (text == ':')
			{
        
				std::string fData;
				unsigned int total = 0;
				unsigned int cInx = (inx + 1);
				total = (max - cInx);


				for (; cInx < max; cInx++)
				{
					
					char txt = fileStream[cInx];
					fData += (txt);

				}
                DataStream = fData;
               
			}
		}
        writeFile << '*';
        writeFile << DataStream;
        writeFile << '*';
        writeFile << std::endl;
 
    }

    return false;
}

bool EFile::ReadFile(wchar_t* _pFileName)
{
    return false;
}



bool EFile::CloseFile()
{
	writeFile << '}';

    writeFile.close();
    return false;
}
