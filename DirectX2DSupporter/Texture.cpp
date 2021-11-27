
#include "Component.h"
#include "D2DSupport.h"
#include "Texture.h"



Texture::Texture(D2DSupport* _pD2DSupport)
{
	this->m_pD2DSupport = _pD2DSupport;
}

Texture::Texture (ATL::CString _str,D2DSupport* _pD2DSupport)
{
	this->m_pD2DSupport = _pD2DSupport;
	m_str = _str;
	m_pD2DSupport->LoadBitMap(m_str, m_str);
}

Texture::~Texture()
{
	delete m_pD2DSupport;

}

void Texture::LoadTexture(ATL::CString _str)
{
	m_str = _str;
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
