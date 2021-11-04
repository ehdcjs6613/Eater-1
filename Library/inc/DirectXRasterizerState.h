#pragma once
enum class StateRS
{
	eWireFrame,
	eSolid
};

__interface RasterizerState
{
	//인터페이스로 레스터라이져 를 만들어주는 인터페이스를 제공
	HRESULT Create(ID3D11Device* _pDevice, StateRS _StateRS) = 0;
};

/// <summary>
/// 레스터라이져 스테이트이다.
/// 그려질 대상을 어떻게 표현할것인가? 와이어, 솔리드?
/// </summary>
class DirectXRasterizerState : public RasterizerState
{
private:
	StateRS m_State;

public:
	ID3D11RasterizerState* m_pFrameRS;
	DirectXRasterizerState();
	~DirectXRasterizerState();

	//미리 레스터라이져스테이트(rs) 만들어주는 함수이다.
	virtual HRESULT Create(ID3D11Device* _pDevice, StateRS _StateRS) override;
public:
	ID3D11RasterizerState* GetFrameRS();
};

