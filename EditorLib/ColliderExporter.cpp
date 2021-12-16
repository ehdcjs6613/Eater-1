#include "LibDefine.h"
#include "../Physics/Collider.h" 
#include "../Physics/BoxCollider.h" 
#include "ColliderExporter.h"

ColliderExporter::ColliderExporter()
{
    m_CQueue.clear();
}

ColliderExporter::~ColliderExporter()
{

}

bool ColliderExporter::Export(const wchar_t* _pExportName)
{
	
    if (m_CQueue.size() > 0)
    {
		
		ExportName(_pExportName);
        for (auto k = m_CQueue.begin(); k != m_CQueue.end(); k++)
        {
            std::wstring msg0 =  std::to_wstring((*k)->GetWorld()._41).c_str();
            std::wstring msg1 =  std::to_wstring((*k)->GetWorld()._42).c_str();
            std::wstring msg2 =  std::to_wstring((*k)->GetWorld()._43).c_str();

			
			WirteFile(L"CenterX:" + msg0);
			WirteFile(L"CenterY:" + msg1);
			WirteFile(L"CenterZ:" + msg2);

			std::wstring size0 = std::to_wstring((*k)->GetWorld()._11).c_str();
			std::wstring size1 = std::to_wstring((*k)->GetWorld()._22).c_str();
			std::wstring size2 = std::to_wstring((*k)->GetWorld()._33).c_str();

			WirteFile(L"SizeX:" + size0);
			WirteFile(L"SizeY:" + size1);
			WirteFile(L"SizeZ:" + size2);
           

        }
        m_CQueue.pop_front();
    }
   
    return false;
   

}

bool ColliderExporter::Start()
{
    OpenFile(L"Collider.txt");
    return false;
}

bool ColliderExporter::End()
{
    CloseFile();
    return  false;
}

bool ColliderExporter::PushInfo(Collider* _pColliderData)
{
    m_CQueue.push_back(_pColliderData);

    return false;
}
