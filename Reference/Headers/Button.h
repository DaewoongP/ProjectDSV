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
	virtual void Update() override;
	// ��ư Ŭ�� �� ȣ��
	// Update���� �ڵ����� �˻��մϴ�.
	virtual void Click() {}

protected:
	Texture* m_pNormalTexture;
	Texture* m_pClickTexture;

public: // handling func
	static Button* Create(const std::wstring& wstrTexturePath, const std::wstring& wstrClickTexturePath, _float2 vPos, _float fWidth, _float fHeight);
	virtual void Free() override;
};

END