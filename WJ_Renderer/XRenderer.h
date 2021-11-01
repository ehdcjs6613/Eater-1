#pragma once

__interface IRenderableFunc
{
	bool Render_Begin ()=0;
	bool Render_Update()=0;
	bool Render_End	  ()=0;
};

class XRenderer : public IRenderableFunc
{
public:
	XRenderer();
	virtual ~XRenderer() final;

	
	bool Render_Begin ();
	bool Render_Update();
	bool Render_End   ();

};

