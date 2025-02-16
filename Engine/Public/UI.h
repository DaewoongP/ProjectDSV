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
	virtual void Update() override;
	virtual void Render() override;

public:
	void ChangeTexture(Texture* pTexture);

public:
	bool IsOnMe(_int x, _int y);
	virtual void LButtonDown(_int x, _int y);
	virtual void RButtonDown(_int x, _int y);
	virtual void LButtonUp(_int x, _int y);
	virtual void RButtonUp(_int x, _int y);

public:
	bool IsLClicked() const { return m_bLClicked; }
	bool IsRClicked() const { return m_bRClicked; }

protected: // component
	RectBuffer*		m_pRectBuffer;
	Shader*			m_pShader;
	Texture*		m_pTexture;

protected: // data
	_float2		m_vPos;
	_float		m_fWidth;
	_float		m_fHeight;
	bool		m_bLClicked;
	bool		m_bRClicked;
	
public: // handling func
	static UI* Create(const std::wstring& wstrTexturePath, _float2 vPos, _float fWidth, _float fHeight);
	virtual void Free() override;
};

END