#pragma once
#include "UI.h"

BEGIN(Engine)

class ENGINE_DLL Button : public UI
{
public: // constructor
	Button();
	virtual ~Button() = default;

public:
	void Initialize(const std::wstring& wstrTexturePath, const std::wstring& wstrClickTexturePath, _float2 vPos, _float fWidth, _float fHeight);
	void SetClickFunc(std::function<void()>&& func);

public:
	virtual void LButtonDown(_int x, _int y) override;
	virtual void RButtonDown(_int x, _int y) override;
	virtual void LButtonUp(_int x, _int y) override;
	virtual void RButtonUp(_int x, _int y) override;

protected:
	Texture* m_pNormalTexture;
	Texture* m_pClickTexture;

protected:
	std::function<void()>	m_ClickFunc;

public: // handling func
	static Button* Create(const std::wstring& wstrTexturePath, const std::wstring& wstrClickTexturePath, _float2 vPos, _float fWidth, _float fHeight);
	virtual void Free() override;
};

END