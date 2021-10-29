#pragma once
#include "Component.h"

class UIBehaviour : public Component
{
public:
	UIBehaviour();
	~UIBehaviour();

public:
	virtual void Awake() override;
	virtual void Start()override;
	virtual void Update()override;
};

