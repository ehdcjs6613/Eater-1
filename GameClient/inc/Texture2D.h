#pragma once

#include "Texture.h"
class D2DSupport;

class Texture2D : public Texture
{
public:
	Texture2D();
	Texture2D(std::wstring _str);
	Texture2D(std::wstring _str, D2DSupport* _pD2DSupport);
	virtual ~Texture2D() final;

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update()override;
public:
	void Render();
	void LoadTexture(std::wstring _str);
};

