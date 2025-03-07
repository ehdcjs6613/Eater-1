#pragma once

#include "EaterEngineDLL.h"
#include "SimpleMath.h"
#include <DirectXMath.h>
#include <vector>
#include "Component.h"

class Transform :public Component
{
public:
	EATER_ENGINEDLL Transform();
	virtual EATER_ENGINEDLL ~Transform();
	
	
	//가장먼저 실행되는 업데이트
	void TransformUpdate();

public:
	//위치
	DirectX::XMFLOAT3 Position;
	//회전
	DirectX::XMFLOAT3 Rotation;
	//크기
	DirectX::XMFLOAT3 Scale;

	

	///로컬 함수를 가져오기전에 SetLocalUpdate
	///이함수를 실행시켜서 로컬업데이트를 하는지 확인하자
	//로컬 윗방향 벡터를 가져온다
	DirectX::XMFLOAT3 GetLocalPosition_UP();
	//로컬 오른쪽방향 벡터를 가져온다
	DirectX::XMFLOAT3 GetLocalPosition_Right();
	//로컬 앞방향 벡터를 가져온다
	DirectX::XMFLOAT3 GetLocalPosition_Look();

	
	

	//현재위치값에 값을 더해줌
	EATER_ENGINEDLL void SetLocalPosition(float X, float Y, float Z);
	EATER_ENGINEDLL void SetTranlate(float X, float Y, float Z);
	EATER_ENGINEDLL void SetTranlate(DirectX::XMFLOAT3 mPos);

	//현재 회전값에 값을 더해줌
	EATER_ENGINEDLL void SetRotate(float X, float Y, float Z);
	EATER_ENGINEDLL void SetRotate(DirectX::XMFLOAT3 mRot);

	//현재 크기값에 값을 더해줌
	EATER_ENGINEDLL void SetScale(float X, float Y, float Z);
	EATER_ENGINEDLL void SetScale(DirectX::XMFLOAT3 mScl);

	//위치,회전,크기 행렬들을 따로 가져온다
	EATER_ENGINEDLL DirectX::XMMATRIX GetPositionXM();
	EATER_ENGINEDLL DirectX::XMMATRIX GetRotationXM();
	EATER_ENGINEDLL DirectX::XMMATRIX GetScaleXM();

	//월드매트릭스를 가져옴
	EATER_ENGINEDLL DirectX::XMMATRIX*GetWorld();

	//로컬좌표들을 매프레임 업데이트 해줄것인가 여부
	EATER_ENGINEDLL void SetLocalUpdate(bool isUpdate);


	DirectX::XMMATRIX Load_World; //로드된 월드
	DirectX::XMMATRIX Load_Local; //로드된 로컬

	//자식객체 넣기
	void SetChild(Transform* mChild);
	//부모 객체 넣기
	void SetParnet(Transform* mParent);
	//자식객체 로컬 업데이트
	void Child_Local_Updata();
private:
	//현재 위치 회전 크기값을 가져와 행렬을 구한다
	DirectX::XMMATRIX CreateXMPos4x4();
	DirectX::XMMATRIX CreateXMRot4x4();
	DirectX::XMMATRIX CreateXMScl4x4();

	///로컬 좌표들 현재위치에서 로컬방향으로 1만큼 움직인 좌표들
	///직접 클라쪽에서 바꿀필요가없기때문에 가져오는것만 가능
	//자기 기준으로 위방향으로 1만큼 움직인 좌표
	DirectX::XMFLOAT3 Local_UP;
	//자기 기준으로 오른쪽 방향으로 1만큼 움직인 좌표
	DirectX::XMFLOAT3 Local_Right;
	//자기 기준으로 앞방향으로 1만큼 움직인 좌표
	DirectX::XMFLOAT3 Local_Look;


	//각각의 행렬들을 따로보관
	DirectX::XMMATRIX PositionXM;
	DirectX::XMMATRIX RotationXM;
	DirectX::XMMATRIX ScaleXM;

	///행렬 업데이트 함수들
	//로컬좌표를 프레임마다 구할것인가 여부
	bool LocalUpdate;

	//업데이트에서 매번 월드행렬 갱신
	void UpdateWorldXM();
	//로컬좌표를 업데이트 시켜준다
	void UpdateLocalPosition();

	//게임 오브젝트의 위치 회전 크기값을 모두곱한 월드 행렬
	DirectX::XMMATRIX World_M;



	///계층 구조에서 부모 객체 자식객체
	Transform* Parent;
	std::vector<Transform*> ChildList;
};