#include "MainHeader.h"
#include "Directxmath.h"
#include "GameObject.h"
#include "Transform.h"
#include "TKeyInput.h"

TKeyInput::TKeyInput()
{
	transform = nullptr;
}

TKeyInput::~TKeyInput()
{

}

void TKeyInput::Start()
{
	transform = gameobject->GetComponent<Transform>();
}

void TKeyInput::Update()
{

	float speed = 0.005f;
	if (GetKey('D'))
	{
		transform->SetLocalPosition(speed, 0, 0);
	}

	if (GetKey('A'))
	{
		transform->SetLocalPosition(-speed, 0, 0);
	}

	if (GetKey('W'))
	{
		transform->SetLocalPosition(0, 0, speed);
	}

	if (GetKey('S'))
	{
		transform->SetLocalPosition(0, 0, -speed);
	}

	if (GetKeyDown(VK_RBUTTON) == true)
	{
		mLastMousePosX = GetMousePosX();
		mLastMousePosY = GetMousePosY();
	}

	if (GetKeyUp(VK_RBUTTON) == true)
	{
		mLastMousePosX = GetMousePosX();
		mLastMousePosY = GetMousePosY();
	}

	float RotSpeed = 5;
	float x = GetMousePosX();
	float y = GetMousePosY();

	if (GetKey(VK_RBUTTON) == true)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = DirectX::XMConvertToRadians(0.5f * static_cast<float>(x - mLastMousePosX));
		float dy = DirectX::XMConvertToRadians(0.5f * static_cast<float>(y - mLastMousePosY));

		transform->SetRotate(-dy * RotSpeed, -dx * RotSpeed, 0);
	}
	mLastMousePosX = x;
	mLastMousePosY = y;
}
