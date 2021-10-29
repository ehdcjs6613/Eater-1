#pragma once

#include "Component.h"

class CanvasRenderer :public  Component
{
private:
	CanvasRenderer() ;
	virtual ~CanvasRenderer() final;

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update()override;

	bool Render();
};

