#pragma once
#include "Composite.h"

BEGIN(Engine)

class Shader;
class Texture;
class RectBuffer;
class ENGINE_DLL UI : public Composite
{
public: // constructor
	UI();
	virtual ~UI() = default;

public:
	void Initialize(const std::wstring& wstrTexturePath, _float2 vPos, _float fWidth, _float fHeight);
	virtual void Render() override;

public:
	void ChangeTexture(Texture* pTexture);
	bool IsOnMe();

protected: // component
	RectBuffer*		m_pRectBuffer;
	Shader*			m_pShader;
	Texture*		m_pTexture;

protected: // data
	_float2		m_vPos;
	_float		m_fWidth;
	_float		m_fHeight;
	
public: // handling func
	static UI* Create(const std::wstring& wstrTexturePath, _float2 vPos, _float fWidth, _float fHeight);
	virtual void Free() override;
};

END