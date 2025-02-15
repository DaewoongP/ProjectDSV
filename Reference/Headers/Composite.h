#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL Composite : public Component
{
public:
	Composite();
	Composite(const Composite& rhs);
	virtual ~Composite() = default;

public:
	std::shared_ptr<Component> GetComponent(const std::wstring& _key);

public:
	virtual void Tick(_float _timeDelta) override;
	virtual void LateTick(_float _timeDelta) override;

public:
	std::shared_ptr<Component> AddComponent(const std::wstring& _prototypeKey, const std::wstring& _componentKey, void* _arg = nullptr, _int _levelIndex = -1);
	size_t RemoveComponent(const std::wstring& _key);

private:
	std::shared_ptr<Component> FindComponent(const std::wstring& _key);

private:
	_umap<std::wstring, std::shared_ptr<Component>> mComponents;
};

END