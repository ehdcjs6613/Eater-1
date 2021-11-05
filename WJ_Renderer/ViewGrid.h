#pragma once

/// <summary>
/// 씬 안에서 보여줄 그리드를 그려주는 클래스이다.
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

