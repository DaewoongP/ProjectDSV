#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL Composite : public Component
{
public:
	Composite();
	virtual ~Composite() = default;

public:
	Component* GetComponent(const std::wstring& wstrKey);

public:
	virtual void Update() override;

public:
	void		AddComponent(const std::wstring& wstrKey, Component* pComponent);
	void		RemoveComponent(const std::wstring& wstrKey);

private:
	_umap<std::wstring /*wstrKey*/, Component*> m_umapComponents;

public:
	virtual void Free() override { __super::Free(); }
};

END