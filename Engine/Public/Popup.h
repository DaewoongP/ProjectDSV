#pragma once
#include "UI.h"

BEGIN(Engine)

class ENGINE_DLL Popup : public UI
{
public:
	Popup();
	~Popup() = default;

public:
	virtual void Update() override;
	virtual void Render() override;

public:
	static Popup* Create(const std::wstring& wstrTexturePath, _float2 vPos, _float fWidth, _float fHeight);
	virtual void Free() override;
};

END