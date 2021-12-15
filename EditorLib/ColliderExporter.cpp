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

bool ColliderExporter::Export()
{
    if (m_CQueue.size() > 0)
    {
        for (auto k = m_CQueue.begin(); k != m_CQueue.end(); k++)
        {
            int a = (*k)->GetCenter()[0];
            std::wstring msg0 =  std::to_wstring((*k)->GetCenter()[0]).c_str();
            std::wstring msg1 =  std::to_wstring((*k)->GetCenter()[1]).c_str();
            std::wstring msg2 =  std::to_wstring((*k)->GetCenter()[2]).c_str();

            OpenFile(L"Collider.txt");
            ExportName(L"BoxCollider");
			WirteFile(L"CenterX:" + msg0);
			WirteFile(L"CenterY:" + msg1);
			WirteFile(L"CenterZ:" + msg2);

            int b = (*k)->GetSize()[0];
			std::wstring size0 = std::to_wstring((*k)->GetSize()[0]).c_str();
			std::wstring size1 = std::to_wstring((*k)->GetSize()[1]).c_str();
			std::wstring size2 = std::to_wstring((*k)->GetSize()[2]).c_str();

			WirteFile(L"SizeX:" + size0);
			WirteFile(L"SizeY:" + size1);
			WirteFile(L"SizeZ:" + size2);
            CloseFile();

        }
        return false;
    }
    else
    {
        return true;
    }

}

bool ColliderExporter::PushInfo(Collider* _pColliderData)
{
    m_CQueue.push_back(_pColliderData);

    return false;
}
