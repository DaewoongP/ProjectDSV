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
	virtual void Update() override;
	// ��ư Ŭ�� �� ȣ��
	// Update���� �ڵ����� �˻��մϴ�.
	virtual void Click();

public:
	bool IsClicked() const { return m_bClicked; }

protected:
	Texture* m_pNormalTexture;
	Texture* m_pClickTexture;

protected:
	std::function<void()>	m_ClickFunc;
	bool					m_bClicked;

public: // handling func
	static Button* Create(const std::wstring& wstrTexturePath, const std::wstring& wstrClickTexturePath, _float2 vPos, _float fWidth, _float fHeight);
	virtual void Free() override;
};

END