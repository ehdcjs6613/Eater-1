#pragma once

/// <summary>
/// �� �ȿ��� ������ �׸��带 �׷��ִ� Ŭ�����̴�.
/// </summary>
//class Transform;

class ViewGrid
{
public:
	ViewGrid();
	ViewGrid(const ViewGrid& _pViewGrid);
	~ViewGrid();
	
private:
	//Transform* m_pTransform;

public:

	void Start();
	void Update(float _pTimer);
	void LateUpdate(float _pTimer);
	void Finalize();
};

