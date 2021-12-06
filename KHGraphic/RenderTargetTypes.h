#pragma once

/// <summary>
/// �������� Ÿ���� �Ѱ��� �Լ��� ��ȯ�ϱ� ���� ���� Class
/// �ش� Class�� Type�� �ݿ��Ͽ� ���� Class Operator�� ���� �������� Ÿ������ ��ȯ
/// </summary>

interface IGraphicResourceManager;

class RenderTarget;
class BasicRenderTarget;
class ComputeRenderTarget;

///
/// 2021/11/07 23:02
/// SeoKyuHwang
///
/// # OriginalRenderTarget Class
///
/// - OriginalRenderTarget Operator�� ���� �ش� RenderTarget Class ��ȯ
/// - operator (BasicRenderTarget, ComputeRenderTarget)
/// 
class OriginalRenderTarget
{
public:
	IGraphicResourceManager* pThis;
	size_t hash_code;

public:
	operator BasicRenderTarget* ();
	operator ComputeRenderTarget* ();
};