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
	std::vector<Collider*> m_CQueue;
public:
	VS_MFC_EXPORT ColliderExporter();
	VS_MFC_EXPORT virtual ~ColliderExporter() final;
public:
	VS_MFC_EXPORT bool Export();
	VS_MFC_EXPORT bool PushInfo(Collider*);

};

