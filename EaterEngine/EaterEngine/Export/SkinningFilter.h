#pragma once

#include "EaterEngineDLL.h"
#include "Component.h"

class ModelData;
class SkinningFilter :public Component
{
public:
	EATER_ENGINEDLL SkinningFilter();
	virtual EATER_ENGINEDLL ~SkinningFilter();

	//���� �־��ش�
	void PushModelData(ModelData* mModel);

private:


};