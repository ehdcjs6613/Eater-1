#pragma once

#include "EaterEngineDLL.h"
#include "Component.h"

class ModelData;
class SkinningFilter :public Component
{
public:
	EATER_ENGINEDLL SkinningFilter();
	virtual EATER_ENGINEDLL ~SkinningFilter();

	//모델을 넣어준다
	void PushModelData(ModelData* mModel);

private:


};