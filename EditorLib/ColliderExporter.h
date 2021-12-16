#pragma once
///StandardHeader
#include <fstream>
#include <deque>
#include <vector>
//CustimHeader
#include "DllExport.h"
#include "Exporter.h"

class Collider;
class BoxCollider;

class ColliderExporter : public Exporter
{
private:
	std::deque<Collider*> m_CQueue;
public:
	VS_MFC_EXPORT ColliderExporter();
	VS_MFC_EXPORT virtual ~ColliderExporter() final;
public:
	VS_MFC_EXPORT bool Export(const wchar_t*);
	VS_MFC_EXPORT bool Start();
	VS_MFC_EXPORT bool End();
	VS_MFC_EXPORT bool PushInfo(Collider*);

};

