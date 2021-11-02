#pragma once
enum class StateRS
{
	eWireFrame,
	eSolid
};

__interface RasterizerState
{
	//�������̽��� �����Ͷ����� �� ������ִ� �������̽��� ����
	HRESULT Create(ID3D11Device* _pDevice, StateRS _StateRS) = 0;
};

/// <summary>
/// �����Ͷ����� ������Ʈ�̴�.
/// �׷��� ����� ��� ǥ���Ұ��ΰ�? ���̾�, �ָ���?
/// </summary>
class DirectXRasterizerState : public RasterizerState
{
private:
	StateRS m_State;

public:
	ID3D11RasterizerState* m_pFrameRS;
	DirectXRasterizerState();
	~DirectXRasterizerState();

	//�̸� �����Ͷ�����������Ʈ(rs) ������ִ� �Լ��̴�.
	virtual HRESULT Create(ID3D11Device* _pDevice, StateRS _StateRS) override;
public:
	ID3D11RasterizerState* GetFrameRS();
};

