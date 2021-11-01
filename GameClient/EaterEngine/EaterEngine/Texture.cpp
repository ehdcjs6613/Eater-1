#include "D2DSupport.h"
#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(D2DSupport* _pD2DSupport)
{
	this->m_pD2DSupport = _pD2DSupport;
}

Texture::Texture(std::wstring _str, D2DSupport* _pD2DSupport)
{
	this->m_pD2DSupport = _pD2DSupport;
	m_str = _str;
	//m_pD2DSupport->Draw_AllImage();
	this->m_pD2DSupport->LoadBitMap(m_str, m_str);

}

Texture::~Texture()
{
	delete m_pD2DSupport;

}

void Texture::LoadTexture(std::wstring _str)
{
	m_str = _str;
}

void Texture::Render()
{
	if (nullptr != m_pD2DSupport)
		m_pD2DSupport->Push_DrawSprite
		(
			L"../Image/atk_1.png", //name
			{ 500,500 },				//Image Position
			{ 2.0f,2.0f },				//Image Scale//
			0,
			1.0f,
			{ 0 ,0 }, //POS
			{ 1.0f, 1.0f }, //SCALE
			0,
			1.0f,		//Alpha Channel
			7,			//MAX Image index
			171,
			144
		);
}

void Texture::Awake()
{

}

void Texture::Start()
{
}

void Texture::Update()
{
}
