#pragma once
#include "UIBehaviour.h"

class Button : public UIBehaviour
{
public:
	Button();
	virtual ~Button();
public:
	virtual void Awake() override;
	virtual void Start()override;
	virtual void Update()override;
};

