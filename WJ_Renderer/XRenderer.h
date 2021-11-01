#pragma once
/// <summary>
/// 렌더러의 기능을 지닌 인터페이스이다.
/// </summary>
__interface IRenderableFunc
{
	bool Render_Begin ()=0;
	bool Render_Update()=0;
	bool Render_End	  ()=0;
};
/// <summary>
/// 이제 어떻게 그릴것인가..
/// </summary>
class XRenderer : public IRenderableFunc
{
public:
	XRenderer();
	virtual ~XRenderer() final;

	
	bool Render_Begin ();
	bool Render_Update();
	bool Render_End   ();

};

